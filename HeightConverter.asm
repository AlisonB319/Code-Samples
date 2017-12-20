#HW ASSIGNMENT 8, CONVERTING HEIGHT FROM FEET AND INCHES TO METERS AND CENTIMETERS
.text
.globl main
main:
.data 
	feetMsg: .asciiz "Enter the height in feet: "
	inchMsg: .asciiz "Enter the height in inches: "
	height: .asciiz "Height is "
	centimeters: .asciiz " centimeters "
	meters: .asciiz " meters\n"
	inch2meters: .float 0.0254
	twele: .float 12.0
	hundred: .float 100.0
	
.text
	#prompt feet
	li $v0, 4
	la $a0, feetMsg
	syscall
	
	#input
	li $v0, 6
	syscall
	mov.s $f1, $f0 #input in f1
	
	#prompt inches
	li $v0, 4
	la $a0, inchMsg
	syscall
	
	#input
	li $v0, 6
	syscall
	mov.s $f2, $f0 #input in f2
	
	#f3 = 12
	l.s $f3, twele
	#f1 = feet to inches
	mul.s $f1, $f1, $f3
	
	#add remaining feet
	add.s $f1, $f1, $f2
	
	#feet to meters
	l.s $f3, inch2meters
	mul.s $f1, $f1, $f3
	
	#height 
	li $v0, 4
	la $a0, height
	syscall
	
	#display result
	li $v0, 2
	mov.s $f12, $f1
	syscall
	
	#display meters
	li $v0, 4
	la $a0, meters
	syscall
	
	#meters to centi
	l.s $f3, hundred
	mul.s $f1, $f1, $f3
	
	#height message
	li $v0, 4
	la $a0, height
	syscall
	
	#height in centimeters
	li $v0, 2
	mov.s $f12, $f1
	syscall
	
	#display centi
	li $v0, 4
	la $a0, centimeters
	syscall
	
	
	
	
	li $v0,10
	syscall
