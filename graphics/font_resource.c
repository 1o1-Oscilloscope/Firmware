/*
 * Raster Font Module
 * 
 * @Company
 *   1o1 Oscilloscope Team
 * 
 * @File Name
 *   font_resource.c
 * 
 * @Summary
 *   Defines a basic raster font.
*/

#include "font.h"

#include <stdlib.h>

#include "../common/screen.h"

s_pixel_t font_default_glyph_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_default_glyph = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_default_glyph_pixels
}; // Box

// font_standard data

s_pixel_t font_standard_glyph_32_pixels[1][1] = {
	{0}
};
font_glyph_t font_standard_glyph_32 = {
	CONST_VECTOR(1,	1),
	0,
	(s_pixel_t *) font_standard_glyph_32_pixels
}; // Space

s_pixel_t font_standard_glyph_33_pixels[1][7] = {
	{1, 1, 1, 1, 1, 0, 1}
};
font_glyph_t font_standard_glyph_33 = {
	CONST_VECTOR(1,	7),
	0,
	(s_pixel_t *) font_standard_glyph_33_pixels
}; // !

s_pixel_t font_standard_glyph_34_pixels[3][2] = {
	{1, 1},
	{0, 0},
	{1, 1}
};
font_glyph_t font_standard_glyph_34 = {
	CONST_VECTOR(3,	2),
	0,
	(s_pixel_t *) font_standard_glyph_34_pixels
}; // "

s_pixel_t font_standard_glyph_35_pixels[5][7] = {
	{0, 0, 1, 0, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 1, 0, 0}
};
font_glyph_t font_standard_glyph_35 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_35_pixels
}; // #

s_pixel_t font_standard_glyph_36_pixels[5][7] = {
	{0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 1, 0, 1, 0},
	{0, 1, 0, 0, 1, 0, 0}
};
font_glyph_t font_standard_glyph_36 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_36_pixels
}; // $

s_pixel_t font_standard_glyph_37_pixels[5][7] = {
	{0, 1, 0, 0, 0, 1, 0},
	{1, 0, 1, 0, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0}
};
font_glyph_t font_standard_glyph_37 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_37_pixels
}; // %

s_pixel_t font_standard_glyph_38_pixels[5][7] = {
	{0, 1, 1, 0, 1, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 1},
	{0, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 1, 0, 1}
};
font_glyph_t font_standard_glyph_38 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_38_pixels
}; // &

s_pixel_t font_standard_glyph_39_pixels[1][2] = {
	{1, 1},
};
font_glyph_t font_standard_glyph_39 = {
	CONST_VECTOR(1,	2),
	0,
	(s_pixel_t *) font_standard_glyph_39_pixels
}; // '

s_pixel_t font_standard_glyph_40_pixels[2][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_40 = {
	CONST_VECTOR(2,	7),
	0,
	(s_pixel_t *) font_standard_glyph_40_pixels
}; // (

s_pixel_t font_standard_glyph_41_pixels[2][7] = {
	{1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_41 = {
	CONST_VECTOR(2,	7),
	0,
	(s_pixel_t *) font_standard_glyph_41_pixels
}; // )

s_pixel_t font_standard_glyph_42_pixels[3][4] = {
	{0, 1, 0, 1},
	{1, 1, 1, 0},
	{0, 1, 0, 1}
};
font_glyph_t font_standard_glyph_42 = {
	CONST_VECTOR(3,	4),
	0,
	(s_pixel_t *) font_standard_glyph_42_pixels
}; // *

s_pixel_t font_standard_glyph_43_pixels[3][3] = {
	{0, 1, 0},
	{1, 1, 1},
	{0, 1, 0}
};
font_glyph_t font_standard_glyph_43 = {
	CONST_VECTOR(3,	3),
	2,
	(s_pixel_t *) font_standard_glyph_43_pixels
}; // +

s_pixel_t font_standard_glyph_44_pixels[2][2] = {
	{0, 1},
	{1, 0}
};
font_glyph_t font_standard_glyph_44 = {
	CONST_VECTOR(2,	2),
	6,
	(s_pixel_t *) font_standard_glyph_44_pixels
}; // ,

s_pixel_t font_standard_glyph_45_pixels[3][1] = {
	{1},
	{1},
	{1}
};
font_glyph_t font_standard_glyph_45 = {
	CONST_VECTOR(3,	1),
	3,
	(s_pixel_t *) font_standard_glyph_45_pixels
}; // -

s_pixel_t font_standard_glyph_46_pixels[1][1] = {
	{1}
};
font_glyph_t font_standard_glyph_46 = {
	CONST_VECTOR(1,	1),
	6,
	(s_pixel_t *) font_standard_glyph_46_pixels
}; // .

s_pixel_t font_standard_glyph_47_pixels[3][7] = {
	{0, 0, 0, 0, 0, 1, 1},
	{0, 0, 1, 1, 1, 0, 0},
	{1, 1, 0, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_47 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_47_pixels
}; // /

s_pixel_t font_standard_glyph_48_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_48 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_48_pixels
}; // 0

s_pixel_t font_standard_glyph_49_pixels[4][7] = {
	{0, 0, 1, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_49 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_49_pixels
}; // 1

s_pixel_t font_standard_glyph_50_pixels[4][7] = {
	{0, 1, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_50 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_50_pixels
}; // 2

s_pixel_t font_standard_glyph_51_pixels[4][7] = {
	{0, 1, 0, 0, 0, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0}
};
font_glyph_t font_standard_glyph_51 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_51_pixels
}; // 3

s_pixel_t font_standard_glyph_52_pixels[4][7] = {
	{0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 0},
	{0, 1, 0, 0, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_52 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_52_pixels
}; // 4

s_pixel_t font_standard_glyph_53_pixels[4][7] = {
	{1, 1, 1, 0, 0, 1, 0},
	{1, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_53 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_53_pixels
}; // 5

s_pixel_t font_standard_glyph_54_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 0, 0, 1, 1, 0}
};
font_glyph_t font_standard_glyph_54 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_54_pixels
}; // 6

s_pixel_t font_standard_glyph_55_pixels[4][7] = {
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0},
	{1, 0, 1, 1, 0, 0, 0},
	{1, 1, 0, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_55 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_55_pixels
}; // 7

s_pixel_t font_standard_glyph_56_pixels[4][7] = {
	{0, 1, 1, 0, 1, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0}
};
font_glyph_t font_standard_glyph_56 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_56_pixels
}; // 8

s_pixel_t font_standard_glyph_57_pixels[4][7] = {
	{0, 1, 1, 0, 0, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_57 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_57_pixels
}; // 9

s_pixel_t font_standard_glyph_58_pixels[1][5] = {
	{1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_58 = {
	CONST_VECTOR(1,	5),
	2,
	(s_pixel_t *) font_standard_glyph_58_pixels
}; // :

s_pixel_t font_standard_glyph_59_pixels[2][6] = {
	{0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0}
};
font_glyph_t font_standard_glyph_59 = {
	CONST_VECTOR(2,	6),
	2,
	(s_pixel_t *) font_standard_glyph_59_pixels
}; // ;

s_pixel_t font_standard_glyph_60_pixels[3][5] = {
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_60 = {
	CONST_VECTOR(3,	5),
	1,
	(s_pixel_t *) font_standard_glyph_60_pixels
}; // <

s_pixel_t font_standard_glyph_61_pixels[3][3] = {
	{1, 0, 1},
	{1, 0, 1},
	{1, 0, 1}
};
font_glyph_t font_standard_glyph_61 = {
	CONST_VECTOR(3,	3),
	2,
	(s_pixel_t *) font_standard_glyph_61_pixels
}; // =

s_pixel_t font_standard_glyph_62_pixels[3][5] = {
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0}
};
font_glyph_t font_standard_glyph_62 = {
	CONST_VECTOR(3,	5),
	1,
	(s_pixel_t *) font_standard_glyph_62_pixels
}; // >

s_pixel_t font_standard_glyph_63_pixels[4][7] = {
	{0, 1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_63 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_63_pixels
}; // ?

s_pixel_t font_standard_glyph_64_pixels[5][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1},
	{0, 1, 1, 1, 1, 0, 1}
};
font_glyph_t font_standard_glyph_64 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_64_pixels
}; // @

s_pixel_t font_standard_glyph_65_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_65 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_65_pixels
}; // A

s_pixel_t font_standard_glyph_66_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0}
};
font_glyph_t font_standard_glyph_66 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_66_pixels
}; // B

s_pixel_t font_standard_glyph_67_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 1, 0}
};
font_glyph_t font_standard_glyph_67 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_67_pixels
}; // C

s_pixel_t font_standard_glyph_68_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_68 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_68_pixels
}; // D

s_pixel_t font_standard_glyph_69_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_69 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_69_pixels
}; // E

s_pixel_t font_standard_glyph_70_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_70 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_70_pixels
}; // F

s_pixel_t font_standard_glyph_71_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 0, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_71 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_71_pixels
}; // G

s_pixel_t font_standard_glyph_72_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_72 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_72_pixels
}; // H

s_pixel_t font_standard_glyph_73_pixels[3][7] = {
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_73 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_73_pixels
}; // I

s_pixel_t font_standard_glyph_74_pixels[4][7] = {
	{0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_74 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_74_pixels
}; // J

s_pixel_t font_standard_glyph_75_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 0},
	{1, 1, 0, 0, 0, 1, 1}
};
font_glyph_t font_standard_glyph_75 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_75_pixels
}; // K

s_pixel_t font_standard_glyph_76_pixels[3][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_76 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_76_pixels
}; // L

s_pixel_t font_standard_glyph_77_pixels[5][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_77 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_77_pixels
}; // M

s_pixel_t font_standard_glyph_78_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_78 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_78_pixels
}; // N

s_pixel_t font_standard_glyph_79_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_79 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_79_pixels
}; // O

s_pixel_t font_standard_glyph_80_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_80 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_80_pixels
}; // P

s_pixel_t font_standard_glyph_81_pixels[5][7] = {
	{0, 1, 1, 1, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
};
font_glyph_t font_standard_glyph_81 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_81_pixels
}; // Q

s_pixel_t font_standard_glyph_82_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{1, 0, 0, 1, 1, 0, 0},
	{0, 1, 1, 0, 0, 1, 1}
};
font_glyph_t font_standard_glyph_82 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_82_pixels
}; // R

s_pixel_t font_standard_glyph_83_pixels[4][7] = {
	{0, 1, 1, 0, 0, 1, 0},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{0, 1, 0, 0, 1, 1, 0}
};
font_glyph_t font_standard_glyph_83 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_83_pixels
}; // S

s_pixel_t font_standard_glyph_84_pixels[5][7] = {
	{1, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_84 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_84_pixels
}; // T

s_pixel_t font_standard_glyph_85_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_85 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_85_pixels
}; // U

s_pixel_t font_standard_glyph_86_pixels[3][7] = {
	{1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_86 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_86_pixels
}; // V

s_pixel_t font_standard_glyph_87_pixels[5][7] = {
	{1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 1, 0, 0}
};
font_glyph_t font_standard_glyph_87 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_87_pixels
}; // W

s_pixel_t font_standard_glyph_88_pixels[5][7] = {
	{1, 1, 0, 0, 0, 1, 1},
	{0, 0, 1, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 0},
	{1, 1, 0, 0, 0, 1, 1}
};
font_glyph_t font_standard_glyph_88 = {
	CONST_VECTOR(5,	7),
	0,
	(s_pixel_t *) font_standard_glyph_88_pixels
}; // X

s_pixel_t font_standard_glyph_89_pixels[4][7] = {
	{1, 1, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 1, 0, 0},
	{1, 1, 1, 1, 0, 0, 0}
};
font_glyph_t font_standard_glyph_89 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_89_pixels
}; // Y

s_pixel_t font_standard_glyph_90_pixels[4][7] = {
	{1, 0, 0, 0, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_90 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_90_pixels
}; // Z

s_pixel_t font_standard_glyph_91_pixels[2][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_91 = {
	CONST_VECTOR(2,	7),
	0,
	(s_pixel_t *) font_standard_glyph_91_pixels
}; // [

s_pixel_t font_standard_glyph_92_pixels[3][7] = {
	{1, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 1}
};
font_glyph_t font_standard_glyph_92 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_92_pixels
}; // \

s_pixel_t font_standard_glyph_93_pixels[2][7] = {
	{1, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_93 = {
	CONST_VECTOR(2,	7),
	0,
	(s_pixel_t *) font_standard_glyph_93_pixels
}; // ]

s_pixel_t font_standard_glyph_94_pixels[3][2] = {
	{0, 1},
	{1, 0},
	{0, 1}
};
font_glyph_t font_standard_glyph_94 = {
	CONST_VECTOR(3,	2),
	0,
	(s_pixel_t *) font_standard_glyph_94_pixels
}; // ^

s_pixel_t font_standard_glyph_95_pixels[4][1] = {
	{1},
	{1},
	{1},
	{1}
};
font_glyph_t font_standard_glyph_95 = {
	CONST_VECTOR(4,	1),
	6,
	(s_pixel_t *) font_standard_glyph_95_pixels
}; // _

s_pixel_t font_standard_glyph_96_pixels[3][3] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};
font_glyph_t font_standard_glyph_96 = {
	CONST_VECTOR(3,	3),
	0,
	(s_pixel_t *) font_standard_glyph_96_pixels
}; // `

s_pixel_t font_standard_glyph_97_pixels[4][5] = {
	{0, 0, 0, 1, 0},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{0, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_97 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_97_pixels
}; // a

s_pixel_t font_standard_glyph_98_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 0, 1},
	{0, 0, 0, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_98 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_98_pixels
}; // b

s_pixel_t font_standard_glyph_99_pixels[3][5] = {
	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_99 = {
	CONST_VECTOR(3,	5),
	2,
	(s_pixel_t *) font_standard_glyph_99_pixels
}; // c

s_pixel_t font_standard_glyph_100_pixels[4][7] = {
	{0, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 0, 0, 0, 1},
	{0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_100 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_100_pixels
}; // d

s_pixel_t font_standard_glyph_101_pixels[4][5] = {
	{0, 1, 1, 1, 0},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{0, 1, 1, 0, 1}
};
font_glyph_t font_standard_glyph_101 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_101_pixels
}; // e

s_pixel_t font_standard_glyph_102_pixels[4][7] = {
	{0, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_102 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_102_pixels
}; // f

s_pixel_t font_standard_glyph_103_pixels[4][7] = {
	{0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{0, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_103 = {
	CONST_VECTOR(4,	7),
	2,
	(s_pixel_t *) font_standard_glyph_103_pixels
}; // g

s_pixel_t font_standard_glyph_104_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_104 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_104_pixels
}; // h

s_pixel_t font_standard_glyph_105_pixels[1][6] = {
	{1, 0, 1, 1, 1, 1},
};
font_glyph_t font_standard_glyph_105 = {
	CONST_VECTOR(1,	6),
	1,
	(s_pixel_t *) font_standard_glyph_105_pixels
}; // i

s_pixel_t font_standard_glyph_106_pixels[3][8] = {
	{0, 0, 0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0},
};
font_glyph_t font_standard_glyph_106 = {
	CONST_VECTOR(3,	8),
	1,
	(s_pixel_t *) font_standard_glyph_106_pixels
}; // j

s_pixel_t font_standard_glyph_107_pixels[4][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_107 = {
	CONST_VECTOR(4,	7),
	0,
	(s_pixel_t *) font_standard_glyph_107_pixels
}; // k

s_pixel_t font_standard_glyph_108_pixels[2][7] = {
	{1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_108 = {
	CONST_VECTOR(2,	7),
	0,
	(s_pixel_t *) font_standard_glyph_108_pixels
}; // l

s_pixel_t font_standard_glyph_109_pixels[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_109 = {
	CONST_VECTOR(5,	5),
	2,
	(s_pixel_t *) font_standard_glyph_109_pixels
}; // m

s_pixel_t font_standard_glyph_110_pixels[4][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{0, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_110 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_110_pixels
}; // n

s_pixel_t font_standard_glyph_111_pixels[4][5] = {
	{0, 1, 1, 1, 0},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{0, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_111 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_111_pixels
}; // o

s_pixel_t font_standard_glyph_112_pixels[4][7] = {
	{0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0},
	{1, 0, 0, 0, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 0}
};
font_glyph_t font_standard_glyph_112 = {
	CONST_VECTOR(4,	7),
	2,
	(s_pixel_t *) font_standard_glyph_112_pixels
}; // p

s_pixel_t font_standard_glyph_113_pixels[4][7] = {
	{0, 1, 1, 1, 0, 0, 0},
	{1, 0, 0, 0, 1, 0, 0},
	{1, 0, 0, 0, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1}
};
font_glyph_t font_standard_glyph_113 = {
	CONST_VECTOR(4,	7),
	2,
	(s_pixel_t *) font_standard_glyph_113_pixels
}; // q

s_pixel_t font_standard_glyph_114_pixels[4][5] = {
	{1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0},
	{1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0}
};
font_glyph_t font_standard_glyph_114 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_114_pixels
}; // r

s_pixel_t font_standard_glyph_115_pixels[4][5] = {
	{0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 1, 0}
};
font_glyph_t font_standard_glyph_115 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_115_pixels
}; // s

s_pixel_t font_standard_glyph_116_pixels[3][7] = {
	{0, 0, 1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{0, 0, 1, 0, 0, 0, 0}
};
font_glyph_t font_standard_glyph_116 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_116_pixels
}; // t

s_pixel_t font_standard_glyph_117_pixels[4][5] = {
	{1, 1, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_117 = {
	CONST_VECTOR(4,	5),
	2,
	(s_pixel_t *) font_standard_glyph_117_pixels
}; // u

s_pixel_t font_standard_glyph_118_pixels[4][5] = {
	{1, 1, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_118 = {
	CONST_VECTOR(3,	5),
	2,
	(s_pixel_t *) font_standard_glyph_118_pixels
}; // v

s_pixel_t font_standard_glyph_119_pixels[5][5] = {
	{1, 1, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0},
	{0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_119 = {
	CONST_VECTOR(5,	5),
	2,
	(s_pixel_t *) font_standard_glyph_119_pixels
}; // w

s_pixel_t font_standard_glyph_120_pixels[5][5] = {
	{1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_120 = {
	CONST_VECTOR(5,	5),
	2,
	(s_pixel_t *) font_standard_glyph_120_pixels
}; // x

s_pixel_t font_standard_glyph_121_pixels[4][7] = {
	{1, 1, 1, 1, 0, 0, 1},
	{0, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 0}
};
font_glyph_t font_standard_glyph_121 = {
	CONST_VECTOR(4,	7),
	2,
	(s_pixel_t *) font_standard_glyph_121_pixels
}; // y

s_pixel_t font_standard_glyph_122_pixels[5][5] = {
	{1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_122 = {
	CONST_VECTOR(5,	5),
	2,
	(s_pixel_t *) font_standard_glyph_122_pixels
}; // z

s_pixel_t font_standard_glyph_123_pixels[3][7] = {
	{0, 0, 0, 1, 0, 0, 0},
	{0, 1, 1, 0, 1, 1, 0},
	{1, 0, 0, 0, 0, 0, 1}
};
font_glyph_t font_standard_glyph_123 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_123_pixels
}; // {

s_pixel_t font_standard_glyph_124_pixels[1][7] = {
	{1, 1, 1, 0, 1, 1, 1}
};
font_glyph_t font_standard_glyph_124 = {
	CONST_VECTOR(1,	7),
	0,
	(s_pixel_t *) font_standard_glyph_124_pixels
}; // |

s_pixel_t font_standard_glyph_125_pixels[3][7] = {
	{1, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 0, 1, 1, 0},
	{0, 0, 0, 1, 0, 0, 0}
};
font_glyph_t font_standard_glyph_125 = {
	CONST_VECTOR(3,	7),
	0,
	(s_pixel_t *) font_standard_glyph_125_pixels
}; // }

s_pixel_t font_standard_glyph_126_pixels[5][3] = {
	{0, 1, 0},
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 0}
};
font_glyph_t font_standard_glyph_126 = {
	CONST_VECTOR(5,	3),
	2,
	(s_pixel_t *) font_standard_glyph_126_pixels
}; // ~

font_glyph_t * font_standard_glyphs[FONT_ASCII_COUNT] = {
	&font_standard_glyph_32,
	&font_standard_glyph_33,
	&font_standard_glyph_34,
	&font_standard_glyph_35,
	&font_standard_glyph_36,
	&font_standard_glyph_37,
	&font_standard_glyph_38,
	&font_standard_glyph_39,
	&font_standard_glyph_40,
	&font_standard_glyph_41,
	&font_standard_glyph_42,
	&font_standard_glyph_43,
	&font_standard_glyph_44,
	&font_standard_glyph_45,
	&font_standard_glyph_46,
	&font_standard_glyph_47,
	&font_standard_glyph_48,
	&font_standard_glyph_49,
	&font_standard_glyph_50,
	&font_standard_glyph_51,
	&font_standard_glyph_52,
	&font_standard_glyph_53,
	&font_standard_glyph_54,
	&font_standard_glyph_55,
	&font_standard_glyph_56,
	&font_standard_glyph_57,
	&font_standard_glyph_58,
	&font_standard_glyph_59,
	&font_standard_glyph_60,
	&font_standard_glyph_61,
	&font_standard_glyph_62,
	&font_standard_glyph_63,
	&font_standard_glyph_64,
	&font_standard_glyph_65,
	&font_standard_glyph_66,
	&font_standard_glyph_67,
	&font_standard_glyph_68,
	&font_standard_glyph_69,
	&font_standard_glyph_70,
	&font_standard_glyph_71,
	&font_standard_glyph_72,
	&font_standard_glyph_73,
	&font_standard_glyph_74,
	&font_standard_glyph_75,
	&font_standard_glyph_76,
	&font_standard_glyph_77,
	&font_standard_glyph_78,
	&font_standard_glyph_79,
	&font_standard_glyph_80,
	&font_standard_glyph_81,
	&font_standard_glyph_82,
	&font_standard_glyph_83,
	&font_standard_glyph_84,
	&font_standard_glyph_85,
	&font_standard_glyph_86,
	&font_standard_glyph_87,
	&font_standard_glyph_88,
	&font_standard_glyph_89,
	&font_standard_glyph_90,
	&font_standard_glyph_91,
	&font_standard_glyph_92,
	&font_standard_glyph_93,
	&font_standard_glyph_94,
	&font_standard_glyph_95,
	&font_standard_glyph_96,
	&font_standard_glyph_97,
	&font_standard_glyph_98,
	&font_standard_glyph_99,
	&font_standard_glyph_100,
	&font_standard_glyph_101,
	&font_standard_glyph_102,
	&font_standard_glyph_103,
	&font_standard_glyph_104,
	&font_standard_glyph_105,
	&font_standard_glyph_106,
	&font_standard_glyph_107,
	&font_standard_glyph_108,
	&font_standard_glyph_109,
	&font_standard_glyph_110,
	&font_standard_glyph_111,
	&font_standard_glyph_112,
	&font_standard_glyph_113,
	&font_standard_glyph_114,
	&font_standard_glyph_115,
	&font_standard_glyph_116,
	&font_standard_glyph_117,
	&font_standard_glyph_118,
	&font_standard_glyph_119,
	&font_standard_glyph_120,
	&font_standard_glyph_121,
	&font_standard_glyph_122,
	&font_standard_glyph_123,
	&font_standard_glyph_124,
	&font_standard_glyph_125,
	&font_standard_glyph_126,
};

font_t font_standard = {
	10,
	1,
	FONT_CHARSET_ASCII,
	FONT_ASCII_START,
	FONT_ASCII_COUNT,
	(font_glyph_t **) font_standard_glyphs
};
