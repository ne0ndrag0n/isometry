| SEGA MegaDrive support code
| by Chilly Willy

        .text

| Initial exception vectors

        .long   0x01000000,initialize,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,hblank,exception,vblank,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception
        .long   exception,exception,exception,exception,exception,exception,exception,exception

| Standard MegaDrive ROM header at 0x100

        .ascii  "SEGA EVERDRIVE  "      /* SEGA must be the first four chars for TMSS */
        .ascii  "(C)2021.FEB NOOD"
        .ascii  "Concordia - The "      /* export name */
        .ascii  "World of Harmony"
        .ascii  "                "
        .ascii  "Concordia - The "      /* domestic (Japanese) name */
        .ascii  "World of Harmony"
        .ascii  "                "
        .ascii  "GM MK-0000 -00"
        .word   0x0000                  /* checksum - not needed */
        .ascii  "J6              "
        .long   0x00000000,0x0007FFFF   /* ROM start, end */
        .long   0x00FF0000,0x00FFFFFF   /* RAM start, end */

        .ifdef  HAS_SAVE_RAM
        .ascii  "RA"                    /* External RAM */
        .byte   0xF8                    /* don't clear + odd bytes */
        .byte   0x20                    /* SRAM */
        .long   0x00200001,0x0020FFFF   /* SRAM start, end */
        .else
        .ascii  "            "          /* no SRAM */
        .endif

        .ascii  "    "
        .ascii  "        "

        .ifdef  MYTH_HOMEBREW
        .ascii  "MYTH3900"              /* memo indicates Myth native executable */
        .else
        .ascii  "        "              /* memo */
        .endif

        .ascii  "                "
        .ascii  "                "
        .ascii  "F               "      /* enable any hardware configuration */


| Standard MegaDrive startup at 0x200

initialize:
        move    #0x2700,sr              /* disable interrupts */

        tst.l   0xA10008                /* check CTRL1 and CTRL2 setup */
        bne.b   1f
        tst.w   0xA1000C                /* check CTRL3 setup */
1:
        bne.b   skip_tmss               /* if any controller control port is setup, skip TMSS handling */

| Check Hardware Version Number
        move.b  0xA10001,d0
        andi.b  #0x0F,d0                /* VERS */
        beq     2f                      /* 0 = original hardware, TMSS not present */
        move.l  #0x53454741,0xA14000    /* Store Sega Security Code "SEGA" to TMSS */
2:
        move.w  0xC00004,d0             /* read VDP Status reg */

skip_tmss:
        move.w  #0x8104,0xC00004        /* display off, vblank disabled */
        move.w  0xC00004,d0             /* read VDP Status reg */

| Clear Work RAM
        lea     0xFF0000,a0
        moveq   #0,d0
        move.w  #0x3FFF,d1
1:
        move.l  d0,(a0)+
        dbra    d1,1b

| Copy initialized variables from ROM to Work RAM
        lea     _stext,a0
        lea     0xFF0000,a1
        move.l  #_sdata,d0
        lsr.l   #1,d0
        subq.w  #1,d0
2:
        move.w  (a0)+,(a1)+
        dbra    d0,2b

        lea     0x01000000,a0
        movea.l a0,sp                   /* set stack pointer to top of Work RAM */
        link.w  a6,#-8                  /* set up initial stack frame */

        jsr     init_hardware           /* initialize the console hardware */

        jsr     __INIT_SECTION__        /* do all program initializers */
        jsr     main                    /* call program main() */
        jsr     __FINI_SECTION__        /* do all program finishers */
3:
        bra.b   3b


| put redirection vectors and gTicks at start of Work RAM
        .data
        .global gTicks
gTicks:
        .long   0
        .global joypad1
joypad1:
        .word   0x00FF


| Exception handlers

        .text

exception:
        rte

hblank:
        rte

vblank:
        move.l  d0, -(sp)
        move.l  d1, -(sp)

        addq.l  #1,gTicks       /* Increment tick counter */
        /* Dump joypad */
        move.w  #0x100, 0xA11100

        move.b  #0x40, 0xA10003
        nop
        nop
        nop
        nop
        move.b (0xA10003),d0

        move.b #0x0, 0xA10003
        nop
        nop
        nop
        nop
        move.b (0xA10003),d1

        move.w  #0x0, 0xA11100

        and.b   #0x3F, d0    /* Rearrange bits */
        and.b   #0x30, d1    /* into SACBRLDU */
        lsl.b   #2, d1
        or.b    d1, d0

        move.w  d0, joypad1  /* Save value to global */

        jsr mdDmaExecute

        move.l  (sp)+, d1
        move.l  (sp)+, d0
        rte
