	.file	"test1.c"
	.option nopic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,5
	sw	a5,-20(s0)
	li	a5,10
	sw	a5,-24(s0)
	li	a5,14
	sw	a5,-20(s0)
	li	a5,0
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"