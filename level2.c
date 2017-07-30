#include <stdint.h>
#include "levels.h"


#pragma rodata-name(push, "LVLDAT1")
const struct LevelHeader header1 = {
    "Level 2", {
0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
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

// LVLDAT1 -- screen xx
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

// LVLDAT1 -- screen xx
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

// LVLDAT1 -- screen xx
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
"FEEEEEEEEEEEAEEF"   // D
"FEEEEEEEEEEEAEEF"   // E
"\x93\x02",

};
#pragma rodata-name(pop)