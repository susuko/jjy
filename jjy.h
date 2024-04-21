#ifndef _JJY_H
#define _JJY_H

// JJY indexes (https://en.wikipedia.org/wiki/JJY)
// Marker
#define ST_MK 0
#define P1_MK 9
#define P2_MK 19
#define P3_MK 29
#define P4_MK 39
#define P5_MK 49
#define P0_MK 59
// Parity
#define H_PA 36
#define M_PA 37
// Minutes
#define M10_ST 1
#define M10_ED 3
#define M01_ST 5
#define M01_ED 8
// Hours
#define H10_ST 12
#define H10_ED 13
#define H01_ST 15
#define H01_ED 18
// Day of year
#define YD100_ST 22
#define YD100_ED 23
#define YD010_ST 25
#define YD010_ED 28
#define YD001_ST 30
#define YD001_ED 33
// Year
#define Y10_ST 41
#define Y10_ED 44
#define Y01_ST 45
#define Y01_ED 48
// Day of week
#define WD_ST 50
#define WD_ED 52

typedef enum e_jjy_bit {
	JJY_BIT_0 = 0,
	JJY_BIT_1 = 1,
	JJY_BIT_MK,
} t_jjy_bit;

t_jjy_bit get_jjy_bit(struct tm *tm, int index);

#endif
