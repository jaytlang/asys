/* Supervisor trap vector
 * Gang gang
 */

 .global llstrap
 llstrap:
    addi sp, sp, -256

    sd ra, 0(sp)
    sd sp, 8(sp)
    sd gp, 16(sp)
#   sd tp, 24(sp)
    sd a0, 32(sp)
    sd a1, 40(sp)
    sd a2, 48(sp)
    sd a3, 56(sp)
    sd a4, 64(sp)
    sd a5, 72(sp)
    sd a6, 80(sp)
    sd a7, 88(sp)
    sd s0, 96(sp)
    sd s1, 104(sp)
    sd s2, 112(sp)
    sd s3, 120(sp)
    sd s4, 128(sp)
    sd s5, 136(sp)
    sd s6, 144(sp)
    sd s7, 152(sp)
    sd s8, 160(sp)
    sd s9, 168(sp)
    sd s10, 176(sp)
    sd s11, 184(sp)
    sd t0, 192(sp)
    sd t1, 200(sp)
    sd t2, 208(sp)
    sd t3, 216(sp)
    sd t4, 224(sp)
    sd t5, 232(sp)
    sd t6, 240(sp)

    csrr a0, sepc
    csrr a1, sstatus
    csrr a2, scause
    call ktrap

    ld ra, 0(sp)
    ld sp, 8(sp)
    ld gp, 16(sp)
#   ld tp, 24(sp)
    ld a0, 32(sp)
    ld a1, 40(sp)
    ld a2, 48(sp)
    ld a3, 56(sp)
    ld a4, 64(sp)
    ld a5, 72(sp)
    ld a6, 80(sp)
    ld a7, 88(sp)
    ld s0, 96(sp)
    ld s1, 104(sp)
    ld s2, 112(sp)
    ld s3, 120(sp)
    ld s4, 128(sp)
    ld s5, 136(sp)
    ld s6, 144(sp)
    ld s7, 152(sp)
    ld s8, 160(sp)
    ld s9, 168(sp)
    ld s10, 176(sp)
    ld s11, 184(sp)
    ld t0, 192(sp)
    ld t1, 200(sp)
    ld t2, 208(sp)
    ld t3, 216(sp)
    ld t4, 224(sp)
    ld t5, 232(sp)
    ld t6, 240(sp)

    addi sp, sp, 256
    sret
