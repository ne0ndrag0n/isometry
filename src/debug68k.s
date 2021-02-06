
    .text

    .global mdWriteDebugFontColor
mdWriteDebugFontColor:
	move.l	#0xc01e0000, (0xC00004)     /* Set address - CRAM PAL_0 COL_F */
    move.w  6(sp), (0xC00000)           /* Write 16-bit value provided */
    rts

    .global  mdLoadDebugFont
mdLoadDebugFont:
    lea     0xC00004, a0
    move.w  #0x8F02,(a0)            /* INC = 2 */
    move.l  #0x40000000,(a0)        /* write VRAM address 0 */

    lea     font_data, a0
    lea     0xC00000, a1

    move.w  #0x60*8-1, d0           /* Count down */
1:
    move.l  (a0)+, (a1)
    dbra    d0, 1b

    rts
