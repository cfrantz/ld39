MEMORY {
    # First 28 bytes of the zero page are used by NES library

    ZP: start = $28, size = $d8, type = rw, define = yes;

    # INES Cartridge Header

    HEADER: start = $0, size = $10, file = %O ,fill = yes;

    # 2 16K ROM Banks
    # - startup
    # - code
    # - rodata
    # - data (load)

    # PRG: start = $8000, size = $3f00, file = %O ,fill = yes, define = yes;

    
    BANK0: start = $8000, size = $2000, file = %O ,fill = yes, define = yes;
    BANK1: start = $8000, size = $2000, file = %O ,fill = yes, define = yes;
    BANK2: start = $8000, size = $2000, file = %O ,fill = yes, define = yes;
    BANK3: start = $8000, size = $2000, file = %O ,fill = yes, define = yes;
    BANK4: start = $8000, size = $2000, file = %O ,fill = yes, define = yes;

    # NROM256
    PRG: start = $A000, size = $5f00, file = %O ,fill = yes, define = yes;

    # DPCM Samples at end of the ROM

    # DMC: start = $7f00, size = $fa, file = %O, fill = yes;

    # NROM256
    DMC: start = $ff00, size = $80, file = %O, fill = yes;

    # Hardware Vectors at end of the ROM

    # VECTORS: start = $7ffa, size = $6, file = %O, fill = yes;
    MMC3BOOT: start = $ff80, size = $7a, file = %O, fill = yes;

    # NROM256
    VECTORS: start = $fffa, size = $6, file = %O, fill = yes;

    # 1 8K CHR Bank

    CHR: start = $0000, size = $2000, file = %O, fill = yes;

    # standard 2K SRAM (-zeropage)
    # $0100 famitone, palette, cpu stack
    # $0200 oam buffer
    # $0300..$800 ca65 stack

    RAM: start = $0300, size = $0500, define = yes;

    # Use this definition instead if you going to use extra 8K RAM
    MORERAM: start = $6000, size = $2000, define = yes;
}

SEGMENTS {
    HEADER:   load = HEADER,         type = ro;

    LVLDAT0:  load = BANK0,          type = ro,  define = yes;
    LVLDAT1:  load = BANK1,          type = ro,  define = yes;
    LVLDAT2:  load = BANK2,          type = ro,  define = yes;
    LVLDAT3:  load = BANK3,          type = ro,  define = yes;
    LVLDAT4:  load = BANK4,          type = ro,  define = yes;
    STARTUP:  load = PRG,            type = ro,  define = yes;
    LOWCODE:  load = PRG,            type = ro,                optional = yes;
    ONCE:     load = PRG,            type = ro,  define = yes, optional = yes;
    INIT:     load = PRG,            type = ro,  define = yes, optional = yes;
    CODE:     load = PRG,            type = ro,  define = yes;
    RODATA:   load = PRG,            type = ro,  define = yes;
    DATA:     load = PRG, run = RAM, type = rw,  define = yes;
    MMC3BOOT: load = MMC3BOOT,       type = rw;
    VECTORS:  load = VECTORS,        type = rw;
    SAMPLES:  load = DMC,            type = rw;
    CHARS:    load = CHR,            type = ro;
    BSS:      load = RAM,            type = bss, define = yes;
    HEAP:     load = RAM,            type = bss, optional = yes;
    MORERAM:  load = MORERAM,        type = bss, optional = yes;
    ZEROPAGE: load = ZP,             type = zp;
}

FEATURES {
    CONDES: segment = INIT,
            type = constructor,
            label = __CONSTRUCTOR_TABLE__,
            count = __CONSTRUCTOR_COUNT__;
    CONDES: segment = RODATA,
            type = destructor,
            import = header1,
            label = __DESTRUCTOR_TABLE__,
            count = __DESTRUCTOR_COUNT__;
    CONDES: type = interruptor,
            segment = RODATA,
            label = __INTERRUPTOR_TABLE__,
            count = __INTERRUPTOR_COUNT__;
}

SYMBOLS {
    __STACKSIZE__: type = weak, value = $0500;  # 5 pages stack
}
