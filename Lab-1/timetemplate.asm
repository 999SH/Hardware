  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

hexasc:

    andi $v0, $a0, 0xf    	#Copies the 4 lsb of $a0
    addi $v0, $v0, 0x30     	#Adds hex 30 to number since that is where 1 starts
    bge  $v0, 0x3a, greater 	#If the number is greater or equal to hex 39 (a) then it will jump to the greater function.
    nop                     	#This will not be needed in this program since the time cannot be alphabetical letters

    jr $ra
    nop

greater: 
    addi $v0 ,$v0, 7
    jr $ra
    nop

delay: 
    		PUSH ($ra) 			#$ra must have the same contents as when the subroutine was called 
    		li $a0, -1
    		move $t0, $a0        		#store $a0 from time2string in a temporary register 
	while: 
    		blez $t0, leave_loop     	#if $t0 greater than zero branch to leave_loop 
    		nop
    		addi $t0, $t0, -1    		#ms = ms - 1 

    		li $t1, 0        		#int i = 0 
	for:
    		bge $t1, 4711, while   		#if $t1 is greater than or equal to 1000 branch to while
    		nop 
    		addi $t1, $t1, 1    		#i = i + 1
    		j for             		#runs loop until condition is fulfilled 
    		nop 
	
	leave_loop: 
    		POP ($ra)        		#$ra value retreived from stack 
    		jr $ra
    		nop
time2string:
	PUSH	($s0)				# Save contents of s1 to restore it after the function ends
	PUSH	($ra)				# Save the return adress on the stack
	move	$s1, $a1			# Move contents of $a1 to $s1 so we can work with it
	move	$s0, $a0

	# First digit
	andi 	$t1, $a1, 0xf000		# Masking out bit from index 15 to 12
	srl 	$a0, $t1, 12			# Shifting the bits to lowest position and store it in $a0 for hexas
	jal	hexasc				# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 0($s0)		 	# Save the return value from hexasc in the first byte location $s1 
						# points to					

	# Second digit
	andi 	$t1, $a1, 0x0f00		# Masking out bit from index 11 to 8
	srl 	$a0, $t1, 8			# Shifting the bits to lowest position and store it in $a0 for hexasc
	jal	hexasc				# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 1($s0)		 	# Save the return value from hexasc in the second byte location $s1 
						# points to					

	# Adding the colon
	li 	$t1, 0x3a			# Loading the ASCII code for colon
	sb 	$t1, 2($s0)		 	# Save the return value from hexasc in the third byte location $s1 
						# points to
	
	# Third digit
	andi 	$t1, $a1, 0x00f0		# Masking out bit from index 7 to 4
	srl 	$a0, $t1, 4			# Shifting the bits to lowest position and store it in $a0 for hexasc
	jal	hexasc				# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 3($s0)		 	# Save the return value from hexasc in the fourth byte location $s1 
						# points to
										
	# Forth digit
	andi 	$t1, $a1, 0x000f		# Masking out bit from index 3 to 0
	move 	$a0, $t1			# No need for shifting, just move it to the argument.
	jal	hexasc				# Calling the hexasc that will transform the decimal into hexadecimal
	nop
	sb 	$v0, 4($s0)		 	# Save the return value from hexasc in the fifth byte location $s1 
						# points to

	# Adding the NUL byte
	li	$t1, 0x00			# Loading the ASCII code for NUL
	sb 	$t1, 5($s0)		 	# Save the return value from hexasc in the sixth byte location $s1 
	j	exit_timesubroutine		# points to

	# End of subroutine. Restoring registers and jumping back to caller.
exit_timesubroutine:																																																																																										
	POP	($ra)
	POP	($s0)	
 	jr 	$ra
 	nop	

