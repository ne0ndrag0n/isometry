    .text

    .global vdp_data
vdp_data:
    .incbin "out.bin"

    .global vdp_data_size
vdp_data_size:
    .word   160
