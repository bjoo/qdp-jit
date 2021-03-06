#ifndef SAVE_FP_REGS_H
#define SAVE_FP_REGS_H


#define _save_fp_regs(ptr) \
{ \
  __asm__ __volatile__( \
	"or 13, %0, %0 ; " \
        "stfd  0, 0(13); " \
        "stfd  1, 8(13); " \
        "stfd  2, 16(13); " \
        "stfd  3, 24(13); " \
        "stfd  4, 32(13); " \
        "stfd  5, 40(13); " \
        "stfd  6, 48(13); " \
        "stfd  7, 56(13); " \
        "stfd  8, 64(13); " \
        "stfd  9, 72(13); " \
        "stfd 10, 80(13); " \
        "stfd 11, 88(13); " \
        "stfd 12, 96(13); " \
        "stfd 13, 104(13); " \
        "stfd 14, 112(13); " \
        "stfd 15, 120(13); " \
        "stfd 16, 128(13); " \
        "stfd 17, 136(13); " \
        "stfd 18, 144(13); " \
        "stfd 19, 152(13); " \
        "stfd 20, 160(13); " \
        "stfd 21, 168(13); " \
        "stfd 22, 176(13); " \
        "stfd 23, 184(13); " \
        "stfd 24, 192(13); " \
        "stfd 25, 200(13); " \
        "stfd 26, 208(13); " \
        "stfd 27, 216(13); " \
        "stfd 28, 224(13); " \
        "stfd 29, 232(13); " \
        "stfd 30, 240(13); " \
        "stfd 31, 248(13); "  : :  "r" (ptr)); \
}


#define _restore_fp_regs(ptr) \
{\
  __asm__ __volatile__( \
	"or 13, %0, %0 ; " \
        "lfd  0, 0(13); " \
        "lfd  1, 8(13); " \
        "lfd  2, 16(13); " \
        "lfd  3, 24(13); " \
        "lfd  4, 32(13); " \
        "lfd  5, 40(13); " \
        "lfd  6, 48(13); " \
        "lfd  7, 56(13); " \
        "lfd  8, 64(13); " \
        "lfd  9, 72(13); " \
        "lfd 10, 80(13); " \
        "lfd 11, 88(13); " \
        "lfd 12, 96(13); " \
        "lfd 13, 104(13); " \
        "lfd 14, 112(13); " \
        "lfd 15, 120(13); " \
        "lfd 16, 128(13); " \
        "lfd 17, 136(13); " \
        "lfd 18, 144(13); " \
        "lfd 19, 152(13); " \
        "lfd 20, 160(13); " \
        "lfd 21, 168(13); " \
        "lfd 22, 176(13); " \
        "lfd 23, 184(13); " \
        "lfd 24, 192(13); " \
        "lfd 25, 200(13); " \
        "lfd 26, 208(13); " \
        "lfd 27, 216(13); " \
        "lfd 28, 224(13); " \
        "lfd 29, 232(13); " \
        "lfd 30, 240(13); " \
        "lfd 31, 248(13); "  : :  "r" (ptr)); \
}

#endif
