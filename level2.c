#include <stdint.h>
#include "levels.h"


#define ____ 0x00
#pragma rodata-name(push, "LVLDAT1")
const struct LevelHeader header1 = {
    "Level 2", {
0x01,0x02,0x03,0x04,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,0x05,____,____,____,____,____,____,____,____,____,____,____,____,
0x0d,0x0c,____,0x06,____,____,____,____,____,____,____,____,____,____,____,____,
0x0e,0x0b,0x0a,0x07,0x08,0x09,____,____,____,____,____,____,____,____,____,____,
0x0f,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
0x10,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
    },
    1,         // start room
    0, 0,      // start position in the map (above)
    104, 80,   // pixel location in start room
};

const uint8_t level1[][16*16] = {
// LVLDAT1 -- screen 0
"                "   // 0
"DDD    D   DDD  "   // 1
"D  D  D D  D  D "   // 2
"DDD  D   D D  D "   // 3
"D  D DDDDD D  D "   // 4
"DDD  D   D DDD  "   // 5
"                "   // 6
"                "   // 7
"                "   // 8
"                "   // 9
"                "   // A
"gggggggggggggggg"   // B
"FFFFFFFFFFFFFFFF"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"",

// LVLDAT1 -- screen 1
"                "   // 0
"E               "   // 1
"E               "   // 2
"E               "   // 3
"E               "   // 4
"E               "   // 5
"E   EEEEEEEEEEEE"   // 6
"EE              "   // 7
"EE              "   // 8
"EEE             "   // 9
"EEE             "   // A
"gggggggggggggggg"   // B
"FFFFFFFFFFFFFFFF"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x85\x07",

// LVLDAT1 -- screen 1
"                "   // 0
"            EEEE"   // 1
"            EEEE"   // 2
"            EEEE"   // 3
"            EEEE"   // 4
"            EEEE"   // 5
"EEEEEEEEEEEEEEEE"   // 6
"                "   // 7
"                "   // 8
"                "   // 9
"                "   // A
"gggggggggggggggg"   // B
"FFFFFFFFFFFFFFFF"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\xB5\x02\xCA\x01",

// LVLDAT1 -- screen 3
"                "   // 0
"                "   // 1
"                "   // 2
"                "   // 3
"                "   // 4
"               D"   // 5
"              DD"   // 6
"             DDD"   // 7
"            DDDD"   // 8
"           DDDDD"   // 9
"          DDDDDD"   // A
"gggggggggggggggg"   // B
"FFFFFFFFFFFFFFFF"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\xF4\x03",

// LVLDAT1 -- screen 4
"                "   // 0
"               D"   // 1
"               D"   // 2
"               D"   // 3
"               D"   // 4
"ggggggggggggAggg"   // 5
"FFFFFFFFFFFFAFFF"   // 6
"FIIIIIIIIIIIAIIF"   // 7
"F@@@@@@@@@@@A@@F"   // 8
"F@@@@@@@@@@@A@@F"   // 9
"F@@@@@@@@@FFA@@F"   // A
"F@@@@@@@@FFFA@@F"   // B
"F@@@@@@@@FFFA@@F"   // C
"FFFFFFFFFFFFAFFF"   // D
"FFFFFFFFFFFFAFFF"   // E
"\x4C\x03\x2C\x04",

// LVLDAT1 -- screen 5
"                "   // 0
"FFFFFFFFFFFFAFFF"   // 1
"F@@@@@@@@@@@A@@F"   // 2
"F@@@@@@@@@@@A@@F"   // 3
"F@@@@@@@@@@@A@@F"   // 4
"F@@@@@@@@@@@A@@F"   // 5
"F@@@@@@@@@@@A@@F"   // 6
"F@@@@@@@@@@@A@@F"   // 7
"F@@@@@@@@@@@A@@F"   // 8
"F@@@@@@@@@@@A@@F"   // 9
"F@@@@@@@@@@@A@@F"   // A
"F@@@@@@@@@@@A@@F"   // B
"F@@@@@@@@@@@A@@F"   // C
"F@@@@@@@@@@@A@@F"   // D
"F@@@@@@@@@@@A@@F"   // E
"",

// LVLDAT1 -- screen 6
"                "   // 0
"F@@@@@@@@@E@A@@F"   // 1
"F@@@@@@@@@E@A@@F"   // 2
"F@@@@@@@@@E@A@@F"   // 3
"F@@EEEEEEEE@A@@F"   // 4
"F@@@@@@@@@E@A@@F"   // 5
"F@@@@@@@@@E@A@@F"   // 6
"F@@@@@@@@@E@A@@F"   // 7
"F@@@@@@@@@E@A@@F"   // 8
"F@@@@@@@@@E@A@@F"   // 9
"F@@@@@@@@@E@A@@F"   // A
"F@@@@@@@@@E@A@@F"   // B
"F@@@@@@@@@@@A@@F"   // C
"FEEEEEEEAEEEEEEF"   // D
"FEEEEEEEAEEEEEEF"   // E
"\x7C\x07\x93\x02",


// LVLDAT1 -- screen 7
"                "   // 0
"FFFFFFFFAFFFFFFF"   // 1
"FFFFFFFFAIIIIIIF"   // 2
"FFFFFFFFA@@@@@E@"   // 3
"FFFFFFFFA@@@@@E@"   // 4
"FFFFFFFFA@@@@@E@"   // 5
"FFIIIIIIA@@@@@@@"   // 6
"FFD@@@@@AFFFFFFF"   // 7
"FFD@@@@@AFIIIIFF"   // 8
"FFD@@@@@AF@@@@IF"   // 9
"@@D@@@@@AF@@@@@I"   // A
"@@D@@@@@AF@@@@@@"   // B
"@@@@@@@@AF@@@@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x2C\x05\xE6\x05\xAC\x04",


// LVLDAT1 -- screen 8
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"FIIIIIIIIIIIIIIF"   // 2
"@@@@@@@@@@@@@@@F"   // 3
"@@@@@@@@@@@@@@@F"   // 4
"@@@@@@@@@@@@@@@F"   // 5
"@@@@@@@@@@@@@@@F"   // 6
"FFFFFFFFFFFFFA@F"   // 7
"FIIIIIIIIIIIIA@F"   // 8
"F@@@@@@@@@@D@A@F"   // 9
"F@@@@@@@@@@D@A@F"   // A
"@@@@@@@@@@@D@A@F"   // B
"@@@@@@@@@@@D@A@@"   // C
"FDDDDDDD@@@@@A@@"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x2C\x01\x4C\x06\x6C\x01\xBD\x05",

// LVLDAT1 -- screen 9
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"F@@@@@@@@@@@@@@F"   // 2
"F@@@@@@@@@@@@@@F"   // 3
"F@@@@@@@@@@@@@@F"   // 4
"FEEEEEEEEEE@@@@F"   // 5
"F@@@@@@@@@@@@@@F"   // 6
"F@@@@@@@@@@@@@@F"   // 7
"F@@@@EEEEEEEEEEF"   // 8
"F@@@@@@@@@@@@@@F"   // 9
"F@@@@@@@@@@@@@@F"   // A
"F@@@@@@@@@@FFFFF"   // B
"@@@@@@@@FFFFFFFF"   // C
"@@@@@FFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x11\x03\xEA\x02",

// LVLDAT1 -- screen 10
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"F@@@@@@@@@@@@@@F"   // 2
"F@@@@@@@@@@@@@@F"   // 3
"F@@@@@@@@@@@@@@F"   // 4
"F@@@@@@@@@@@@@@F"   // 5
"F@@@@@@@@@@@@@@F"   // 6
"F@@@@@@@@@@@@@@F"   // 7
"F@@@@@@DD@@@@@@F"   // 8
"@@@@@@DDDD@@@@@F"   // 9
"@@@@@DDDDDD@@@@@"   // A
"@@@@DDDDDDDD@@@@"   // B
"@@@DDDDDDDDDD@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x3B\x01\x77\x03",

// LVLDAT1 -- screen 11
"                "   // 0
"FFFAFFFFFFFFFFFF"   // 1
"FIIAIIIIIIIIIIIF"   // 2
"F@@A@@@@@@@@@@@F"   // 3
"F@@A@@@@@@@@@@@F"   // 4
"F@@A@@@@@@@@@@@F"   // 5
"F@@A@@@@@@@@@@@F"   // 6
"F@@A@@@@@@@@@@@F"   // 7
"F@@A@@@@@@@@@@@F"   // 8
"F@@A@@@@@@@@@@@F"   // 9
"FFFFF@@@@@@@@@@@"   // A
"FFFFFFF@@@@@@@@@"   // B
"FFFFFFFFF@@@@@@@"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"",
// LVLDAT1 -- screen 12
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"F@@@@@@@@@@@@@@F"   // 2
"F@@@@@@@@@@@@@@F"   // 3
"@@@@@@@@@@@@@@@F"   // 4
"@@@@@@@@@@@@@@@F"   // 5
"@@@@@@@@@@@@@@@F"   // 6
"@@@@@@@@@@@@@@@F"   // 7
"F@@A@@@@@@@@@@@F"   // 8
"F@@A@@@@@@@@@@@F"   // 9
"F@@A@@@@@@@@@@@F"   // A
"F@@A@@@@@D@D@D@F"   // B
"F@@A@@@@@D@D@D@F"   // C
"FFFAFFFFFFFFFFFF"   // D
"FFFAFFFFFFFFFFFF"   // E
"\x9A\x04\xBA\x02\xDA\x04",

// LVLDAT1 -- screen 13
"                "   // 0
"FFFFFFFFFFFFFFFF"   // 1
"F@@A@@@@@@@@@@@F"   // 2
"F@@A@@@@@@@@@@@F"   // 3
"F@@A@@@@@@@@@@@@"   // 4
"F@@A@@@@@@@@@@@@"   // 5
"F@@A@@@@@@@@@@@@"   // 6
"F@@A@@@@@@@@@@@@"   // 7
"F@@A@@@FFFFFFFFF"   // 8
"F@@A@@@FFFFFFFFF"   // 9
"F@@A@@@FFFFFFFFF"   // A
"F@@A@@@FFFFFFFFF"   // B
"F@@A@@@FFFFFFFFF"   // C
"F@@A@@@FFFFFFFFF"   // D
"FFFAFFFFFFFFFFFF"   // E
"",
// LVLDAT1 -- screen 14
"                "   // 0
"FFFAFFFFFFFFFFFF"   // 1
"F@@A@@FFFFFFFFFF"   // 2
"F@@A@@FFFFFFFFFF"   // 3
"F@@A@@@E@@@@@@FF"   // 4
"F@@A@@@@@@@@@@FF"   // 5
"FEEAEEEEE@@@@@FF"   // 6
"F@@A@@FFF@@@@@FF"   // 7
"F@@A@@FFF@@@@@FF"   // 8
"F@@A@@FFF@@@@@FF"   // 9
"F@@A@@FFF@@@@@FF"   // A
"F@@A@@FFF@@@@@FF"   // B
"F@@A@@FFF@@@@@FF"   // C
"F@@A@@FFF@@@@@FF"   // D
"F@@A@@FFF@@@@@FF"   // E
"\x75\x05",
// LVLDAT1 -- screen 15
"                "   // 0
"F@@A@@FFF@@@@@FF"   // 1
"F@@A@@FFF@@@@@FF"   // 2
"F@@A@@FFF@@@@@FF"   // 3
"F@@A@@FFF@@@@@FF"   // 4
"F@@A@@FFF@@@@@FF"   // 5
"F@@A@@FFF@@@@@FF"   // 6
"F@@A@@FFF@@@@@FF"   // 7
"F@@A@@FFF@@@@@FF"   // 8
"FFFFFFFFF@@@@@FF"   // 9
"FDDDDDFFF@@@@@FF"   // A
"FDDDDDFFF@@@@@FF"   // B
"FDDDDDFFF@@@@@FF"   // C
"FDDDDDFFF@@@@@FF"   // D
"FFFFFFFFF@@@@@FF"   // E
"",
// LVLDAT1 -- screen 16
"                "   // 0
"FFFFFFFFF@@@@@FF"   // 1
"F@@@@@@@@@@@@@FF"   // 2
"F@EEE@E@E@@@E@FF"   // 3
"F@E@@@E@EE@@E@FF"   // 4
"F@EE@@E@E@E@E@FF"   // 5
"F@E@@@E@E@@EE@FF"   // 6
"F@E@@@E@E@@@E@FF"   // 7
"F@@@@@@@@@@@@@FF"   // 8
"F@@@@@@@@@@@@@FF"   // 9
"F@@@@@@@@@@@@@FF"   // A
"F@@@@@@@@@@@@@FF"   // B
"F@@@@@@@@@@@@@FF"   // C
"FFFFFFFFFFFFFFFF"   // D
"FFFFFFFFFFFFFFFF"   // E
"\x3C\x09",



};
#pragma rodata-name(pop)
