#include <stdint.h>

const uint8_t levelmap[16*16] = {
    0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 0, 0, 0,11,12, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 9,10, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,15,14,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

#pragma rodata-name(push, "LVLDAT0")
const char name0[] = "LVLDAT0";
//const struct Level *level0 = {
const uint8_t level0[][16*16] = {
// LVLDAT0 -- screen 0
"E               "
"E               "
"E               "
"E               "
"E               "
"E   EEE         "
"E               "
"E     EEEEE     "
"E              D"
"E           D  D"
"E          DD  D"
"gggggggggggggggg"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\xEA\x01\xA6\x02",

// LVLDAT0 -- screen 1
"                "
"                "
"                "
"                "
"                "
"                "
"    DD          "
"   DDDD         "
"ggggggggggAggggg"
"FIIIIIIIIIAIIIIF"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"FFFFFFFFFFFFFFFF"
"\x2D\x03\xED\x04",

// LVLDAT0 -- screen 2
"                "
"                "
"                "
"                "
"                "
"                "
"                "
"                "
"gggAgggggggggggg"
"FIIAIIIIIIIIIIII"
"F@@A@@@D@@@@@@@@"
"F@@A@@@D@@@@@@@@"
"F@@A@@@D@@@@@@@@"
"F@@A@@@@@@@@@@@@"
"FFFFFFFFFFFFAFFF"
"\x7D\x05",

// LVLDAT0 -- screen 3
"               D"
"               D"
"               D"
"               D"
"               D"
"               D"
"    DD         D"
"   DDDD        D"
"ggggggggggAggggg"
"FIIIIIIIIIAIIIIF"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"FFFFFFFFFFFFFFFF"
"\x2D\x03\xED\x02",



// LVLDAT0 -- screen 4
"FFFFFFFFFFFFAFFF"
"FIIIIIIIIIIIAIIF"
"F@@@@@@@@@@@A@@F"
"F@@@@@@@@@@@A@@F"
"F@@@@@@@@@@@A@@F"
"F@@A@@@@@@@@A@@F"
"FDDADDDDDDDDDDDF"
"F@@A@@@@@@@@@@@F"
"F@@A@@@@@@@@@@@F"
"F@@A@@@@@@@@@@@F"
"F@@A@@@@@@@@@@@F"
"FFFFFFFF@@@@@@@F"
"FFFFFFFFFF@@@@@F"
"FFFFFFFFFFFF@@@F"
"FFFFFFFFFFFFFAFF"
"",

// LVLDAT0 -- screen 5
"FFFFFFFFFFFFFAFF"
"FIIIIIIIIIIIIAIF"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"FFFFFFFFFFFFFAFF"
"FIIIIIIIIIIIIAIF"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"F@@@@@@@@@@@@A@F"
"FFFFFFFFFFFFFAFF"
"FFFFFFFFFFFFFAFF"
"FFFFFFFFFFFFFAFF"
"\x35\x02\x3B\x06",

};
#pragma rodata-name(pop)

#pragma rodata-name(push, "LVLDAT1")
const char name1[] = "LVLDAT1";
#pragma rodata-name(pop)
#pragma rodata-name(push, "LVLDAT2")
const char name2[] = "LVLDAT2";
#pragma rodata-name(pop)
#pragma rodata-name(push, "LVLDAT3")
const char name3[] = "LVLDAT3";
#pragma rodata-name(pop)
#pragma rodata-name(push, "LVLDAT4")
const char name4[] = "LVLDAT4";
#pragma rodata-name(pop)



