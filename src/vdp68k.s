
    .text

    .global mdVdpWriteWord
mdVdpWriteWord:
    move.l  4(sp), (0xC00004)
    move.w  10(sp), (0xC00000)
    rts
