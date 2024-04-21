#include <stdint.h>
#include <time.h>
#include "jjy.h"

static uint8_t get_bcd(uint16_t bin, int digit)
{
	const int scale[] = {
		1, 10, 100, 1000, 10000
	};

	if (digit < 0 || digit >= 5) {
		return 0;
	}

	return bin / scale[digit] % 10;
}

static t_jjy_bit get_jjy_bit_from_bcd(uint8_t bcd, int index, int end_index)
{
	int bcd_index = end_index - index;

	return bcd & 1 << bcd_index
		? JJY_BIT_1
		: JJY_BIT_0;
}

static t_jjy_bit calc_parity_jjy_bit(uint8_t bcd0, uint8_t bcd1)
{
	uint8_t xor_bcd = bcd0 ^ bcd1;

	// GCC built-in function (https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html)
	return __builtin_parity(xor_bcd)
		? JJY_BIT_1
		: JJY_BIT_0;
}

t_jjy_bit get_jjy_bit(struct tm *tm, int index)
{
	switch (index)
	{
	// Marker
	case ST_MK:
	case P0_MK:
	case P1_MK:
	case P2_MK:
	case P3_MK:
	case P4_MK:
	case P5_MK:
		return JJY_BIT_MK;

	// Hours Parity
	case H_PA:
		return calc_parity_jjy_bit(
			get_bcd(tm->tm_hour, 0),
			get_bcd(tm->tm_hour, 1)
		);
	// Minutes Parity
	case M_PA:
		return calc_parity_jjy_bit(
			get_bcd(tm->tm_min, 0),
			get_bcd(tm->tm_min, 1)
		);

// GCC extension (https://gcc.gnu.org/onlinedocs/gcc/Case-Ranges.html)
#define CASE(START, END, BCD) \
	case START ... END: \
		return get_jjy_bit_from_bcd(BCD, index, END)

	// Minutes
	CASE(M01_ST, M01_ED, get_bcd(tm->tm_min, 0));
	CASE(M10_ST, M10_ED, get_bcd(tm->tm_min, 1));
	// Hours
	CASE(H01_ST, H01_ED, get_bcd(tm->tm_hour, 0));
	CASE(H10_ST, H10_ED, get_bcd(tm->tm_hour, 1));
	// Day of year
	CASE(YD001_ST, YD001_ED, get_bcd(tm->tm_yday + 1, 0));
	CASE(YD010_ST, YD010_ED, get_bcd(tm->tm_yday + 1, 1));
	CASE(YD100_ST, YD100_ED, get_bcd(tm->tm_yday + 1, 2));
	// Year
	CASE(Y01_ST, Y01_ED, get_bcd(tm->tm_year, 0));
	CASE(Y10_ST, Y10_ED, get_bcd(tm->tm_year, 1));
	// Day of week
	CASE(WD_ST, WD_ED, get_bcd(tm->tm_wday, 0));
#undef CASE

	default:
		return JJY_BIT_0;
	}
}
