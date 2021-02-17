
	.text

	.global mdDmaExecute
mdDmaExecute:
	lea 	dmaQueue, a0
	move.w	#14, d1

1:
	tst.l	(a0)		/* sourceAddress = 0, nothing to transfer. */
	bne.s	3f			/* if the address is not zero, we need to do a DMA operation */
2:
	adda.l	#10, a0
	dbra	d1, 1b

	/* Finished processing queue */
	rts

3:
	/* a0 contains the top of the struct */
	/* Write size to VDP registers 0x13 and 0x14 */
	move.w	#0x9300, d0
	move.b	5(a0), d0
	move.w	d0, (0xC00004)		/* Write low byte */

	move.w	#0x9400, d0
	move.b	4(a0), d0
	move.w	d0, (0xC00004)		/* Write high byte */

	/* Write source address to VDP registers 0x15, 0x16, and 0x17 */
	move.w	#0x9500, d0
	move.b	3(a0), d0
	move.w	d0, (0xC00004)		/* Write low byte */

	move.w	#0x9600, d0
	move.b	2(a0), d0
	move.w	d0, (0xC00004)		/* Write middle byte */

	move.w	#0x9700, d0
	move.b	1(a0), d0
	move.w	d0, (0xC00004)		/* Write high byte */

	/* The destination word can be written as-is since it is preformatted in mdDmaEnqueue */

	move.w #0x100, (0xA11100)	/* Pause the z80 really quick */
	move.l 6(a0), (0xC00004)	/* Execute DMA */
	move.w #0x000, (0xA11100)	/* Restart the z80 */

	/* Done transferring - get rid of it! */
	move.l	#0, (a0)
	move.w	#0, 4(a0)
	move.l	#0, 6(a0)

	bra.s	2b
