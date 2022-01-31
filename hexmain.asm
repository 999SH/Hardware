  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,100		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
hexasc:

	andi $a0, 0xf	
	addi $a0, $a0, 0x30
	bge  $a0,0x39, greater
	nop
	
	jr $ra
	nop
greater: 
	addi $a0 ,$a0, 7
	jr $ra
	nop
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #

