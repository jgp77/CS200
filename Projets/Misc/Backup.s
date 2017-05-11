# TITLE Proj7	(Proj7.s)
# This program prompts for Upper/Lower Limit, Seed, and Amount to generate
# It then generates random numbers on that given range

	.data
# variables
RandomPrompt:         .asciiz "Enter the amount of random numbers to generate: "
UpperNumPrompt:       .asciiz "Enter the upper limit: "
LowerNumPrompt:       .asciiz "Enter the lower limit: "
SeedPrompt:       		.asciiz "Enter the seed: "
Invalid:       		    .asciiz "Invalid Input! Try again!"
NewLine:              .asciiz "\n"
OutStr:               .asciiz "\nRandom number: "
Multiplier:						.word   213


.text
.globl   main

main:   # start of the main procedure

		# Prompt for amount of randoms
		la        $a0, RandomPrompt        # point to IntPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t9,$v0                  # move input before it gets changed
		ble       $t9,0,random

    # Prompt for lower limit
		la        $a0, LowerNumPrompt      # point to LowerNumPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t8,$v0                  # Stores lower limit into $t8

    # Prompt for upper limit
		la        $a0, UpperNumPrompt      # point to UpperNumPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t7,$v0                  # Stores upper limit into $t7

		# Checks upper and lower limit
		ble       $t7,$t8,range						 # If UpperNum=<LowerNum
		ble       $t7,0,range              # If UpperNum =< 0
		ble       $t8,-1,range             # If LowerNum =< -1

		# Prompt for seed
		la        $a0, SeedPrompt          # point to SeedPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t0,$v0                  # Move input to $t0
		# Checks seed value
		ble       $t0,10,seed           # If seed =< 10000
		lw       $t6,Multiplier						 # Loads constant multiplier into $t6
		j		loop                           # Jumps to loop


loop: # loop for number generation
		# generates a hi and lo (random number and new seed)
		beqz     $t9,end								   # If the number of random #s left is 0, goto end
		multu    $t0,$t6  				         # Multiply seed by multiplier, store in $t4
		mflo		 $t1                       # Moves lo into $t1
		mfhi		 $t2                       # Moves hi into $t2

		#range setting setup
		move		 $t0,$t1                   # Makes the seed into the lo
		sub	     $t3,$t7,$t8               # Subtrcts upper limit from lower limit, stores in $t3
		add  		 $t3,$t3,1                 # Adds one to $t3
		#Modulus div
		div 		 $t4,$t2,$t3               # Divides hi by $t3
		mul      $t4,$t4,$t3               # Multiplies $t4 by $t3
		sub      $t4,$t2,$t4               # Subtract $t4 from hi
		#finsih range setting formula
		add      $t4,$t4,1                 #Adds 1 to the final result

		sub      $t9,$t9,1                 #Subtracts 1 from amount of randoms to generate (my counter)
		j 			 print                     #Jumps to print

print: # print to decluter the loop
		la        $a0,OutStr               # Point to OutStr
		li  		  $v0,4                    # print_string
		syscall
		move	    $a0,$t4		               # Move stored integer into $a0
		li        $v0, 1                   # print_integer
		syscall
		j         loop                     # Jumps to loop

random: # random checker
		la        $a0,Invalid							 # Point to Invalid
		li        $v0,4										 # print_string
		syscall
		la        $a0, NewLine             # Point to NewLine
		li        $v0, 4                   # print_string
		syscall
		j         main                     # Jumps to main

seed: # seed checker
		la        $a0,Invalid							 # Point to Invalid
		li        $v0,4										 # print_string
		syscall
		la        $a0, NewLine             # Point to NewLine
		li        $v0, 4                   # print_string
		syscall

		la        $a0, SeedPrompt          # point to SeedPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t0,$v0                  # Move input to $t0
		ble       $t0,10,seed           # If seed is =< 10000

range: # range checker
		la        $a0,Invalid							 # Point to Invalid
		li        $v0,4										 # print_string
		syscall
		la        $a0, NewLine             # Point to NewLine
		li        $v0, 4                   # print_string
		syscall

		la        $a0, LowerNumPrompt      # point to LowerNumPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t8,$v0                  # Stores lower limit into $t8


		la        $a0, UpperNumPrompt      # point to UpperNumPrompt
		li        $v0, 4                   # print_string
		syscall
		li        $v0, 5                   # read_integer
		syscall
		move      $t7,$v0                  # Stores upper limit into $t7

		ble       $t7,$t8,range						 # If UpperNum=<LowerNum
		ble       $t7,0,range              # If UpperNum =< 0
		ble       $t8,-1,range             # If LowerNum =< -1



end:
		jr	      $ra
