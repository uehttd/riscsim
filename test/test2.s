	.file	"test2.c"
	.option nopic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,-2147483648
	xori	a5,a5,-1
	sw	a5,-20(s0)
	li	a5,-2147483648
	xori	a5,a5,-1
	sw	a5,-24(s0)
	li	a5,-1
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a5,a4,a5
	sw	a5,-32(s0)
	lw	a4,-32(s0)
	lw	a5,-28(s0)
	add	a5,a4,a5
	sw	a5,-32(s0)
	lw	a5,-32(s0)
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"
