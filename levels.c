#include <stdint.h>

const uint8_t levelmap[16*16] = {
    1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 0, 0,12,13, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 7, 8, 9,10,11, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0,17,16,15,14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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

const uint8_t level0[][16*16] = {
// LVLDAT0 -- screen 0
"                "
"   EEEEEEEEE    "
"   E       E    "
"   E  +,   E    "
"   E  -./  E    "
"   E       E    "
"   EEEEEEEEE    "
"                "
"                "
"                "
"                "
"ggggggggggAggggg"
"FIIIIIIIIIAIIIIF"
"F@@@@@@@@@A@@@@F"
"F@@@@@@@@@A@@@@F"
"\x2A\x07\xEA\x01\xA5\x02",

// LVLDAT0 -- screen 1
"                "
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
"\x2A\x07\xEA\x01\xA6\x02",

// LVLDAT0 -- screen 2
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

// LVLDAT0 -- screen 3
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

// LVLDAT0 -- screen 4
"                "
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



// LVLDAT0 -- screen 5
"                "
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
"FFFFFFFF@@@@@@@F"
"FFFFFFFFFF@@@@@F"
"FFFFFFFFFFFF@@@F"
"FFFFFFFFFFFFFAFF"
"",

// LVLDAT0 -- screen 6
"                "
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
"\x36\x02\x56\x01\x3C\x06\x6C\x01",

// LVLDAT0 -- screen 7
"                "
"FFFFFFFFFFFFFAFF"
"FIIIIIIIIIIIIAIF"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"F@@@@@@@@@@@@A@@"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\x4C\x04",

// LVLDAT0 -- screen 8
"                "
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"IIIFFFIIIIFFFIII"
"@@@III@@@@III@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\x8C\x01",

// LVLDAT0 -- screen 9
"                "
"FFFFFFFFFFFFFFFF"
"IIIIIIIIIIIIIIII"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"@@@@@@@@@@@@@@@@"
"FFFFFFFFFFFAFFFF"
"FFFFFFFFFFFAFFFF"
"\x7C\x01\x9C\x07",

// LVLDAT0 -- screen 10
"                "
"FFFFFFFAFFFFFFFF"
"IIIIIIIAIIIIIIII"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@EEEAEEEEEEEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@EEE"
"@@@@@@@A@@@@@@@@"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\xEC\x05\xA6\x04",

// LVLDAT0 -- screen 11
"                "
"FFFFFFFFFFFFFFFF"
"EIIIIIIIIIIIIIEE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"E@@@@@@@@@@@@@EE"
"@@@@@@@@@@@@@@EE"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\xBC\x01\xCC\x06",

// LVLDAT0 -- screen 12
"                "
"FFFFFFFFFFFFFFFF"
"IIIIIIIIIIIIIIII"
"EEEEEEEEEEEEEEEE"
"EEEEEEEEEEEEE@@@"
"EEEEEEEEEE@@@@@@"
"EEEEEE@A@@@@@@@@"
"EE@@@@@A@@@@@@@@"
"EE@@@@@A@@@@@@@@"
"EE@@@@@AEEEEEEEE"
"EE@@@@@A@@@@@@@@"
"EE@@@@@A@@@@@@@@"
"EE@@@@@A@@@@@@@@"
"FFFFFFFAFFFFFFFF"
"FFFFFFFAFFFFFFFF"
"",

// LVLDAT0 -- screen 13
"                "
"FFFFFFFFFFFFFFFF"
"IIIIIIIIIIIIIIII"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"EEEEEEEEE@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"@@@@@@@@@@@@@@DD"
"FFFFFFFFFFFFFFFF"
"FFFFFFFFFFFFFFFF"
"\x88\x03\x8C\x03\xCC\x02",

// LVLDAT0 -- screen 14
"                "   // 0
"FFFFFFFFFFFAFFFF"   // 1
"FFFFFFFFFFFAFFFF"   // 2
"FFFFFFFFFFFAFFFF"   // 3
"FFFFFFFFFFFAFFFF"   // 4
"FFFFFFFFFFFAFFFF"   // 5
"FFFFFFFFFFFAFFFF"   // 6
"FFFFFFFFFFFAFFFF"   // 7
"FFFFFFFFFFFAFFFF"   // 8
"IIIIIIIIIIIAIIIF"   // 9
"@@@@@@@@@@@A@@@F"   // A
"@@@@@@@@@@@A@@@F"   // B
"@@@@@@@@@@@A@@@F"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"",

// LVLDAT0 -- screen 15
"                "   // 0
"IIIIIIIIIIIIIIFI"   // 1
"@@@@@@@@@@@@@@FF"   // 2
"@@@@@@@@@@@@@@FF"   // 3
"@@@@@@@@@@@@@@FF"   // 4
"EEEEEEEEEEEE@@FF"   // 5
"@@@@@@@@@@@@@DFF"   // 6
"@@@@@@@@@@@@@DFF"   // 7
"@@@@@@@@@@@DDDFF"   // 8
"IIIIIIIIIIIIIIII"   // 9
"@@@@@@@@@@@@@@@@"   // A
"@@@@@@@@@@@@@@@@"   // B
"@@@@@@@@@@@@@@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"",

// LVLDAT0 -- screen 16
"                "   // 0
"IIIIIIIIIIIIIIFI"   // 1
"E@@@@@@@@@@@@@@@"   // 2
"E@@@@@@@@@@@@@@@"   // 3
"E@@@@@@@@@@@@@@@"   // 4
"EEAEEEEEEEEEEEEE"   // 5
"E@A@@@EE@@@@@@@@"   // 6
"E@A@@@EE@@@@@@@@"   // 7
"E@A@@@EE@@@@@@@@"   // 8
"E@A@@@EEAEEEEEEE"   // 9
"E@A@@@EEA@@@@@@@"   // A
"@@A@@@EEA@@@@@@@"   // B
"@@A@@@EEA@@@@@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x44\x03",

// LVLDAT0 -- screen 17
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"IIIIIIIIIIIIIIII"   // 2
"@@@@@@@@@@@@@@@@"   // 3
"E@@@@@@@@@@@@@@@"   // 4
"E@@@@@@@@@@@@@@@"   // 5
"E@@@@@@@@@@@@@@@"   // 6
"E@@@@@@@@@@@@@@@"   // 7
"E@@@@@@@@@@@@@@@"   // 8
"EEEE@@@@@@@@@@@@"   // 9
"EEEEEE@@@@@@@@@@"   // A
"EEEEEEEE@@@@@@@@"   // B
"EEEEEEEEEE@@@@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x28\x09\x28\x03\x8B\x01",






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



