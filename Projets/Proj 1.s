# TITLE Proj7	(Proj7.s)
# This program prompts for Upper/Lower Limit,Seed,and Amount to generate
# It then generates random numbers on that given range

.data
		# variables
		RandomPrompt:         .asciiz "Enter the amount of random numbers to generate: "
		UpperNumPrompt:       .asciiz "Enter the upper limit: "
		LowerNumPrompt:       .asciiz "Enter the lower limit: "
		SeedPrompt:       		.asciiz "Enter the seed: "
		Invalid:       		    .asciiz "Invalid Input! Try again!\n"
		OutStr:               .asciiz "\nRandom number: "
		Multiplier:						.word   982451653

.text
		main:   # start of the main procedure
				lw       $t6,Multiplier						# Loads constant multiplier into $t6
				j        randomget                # Jumps to randomget to initiate getters

		randomget:
				la        $a0,RandomPrompt        # point to IntPrompt
				li        $v0,4                   # print_string
				syscall
				li        $v0,5                   # read_integer
				syscall
				move      $t9,$v0                 # move input before it gets changed
				ble       $t9,0,randominvalid     # If number of randoms to generate =< 0
				j         seedget                 # Jumps to seedget if no errors

		seedget:
				la        $a0,SeedPrompt          # point to SeedPrompt
				li        $v0,4                   # print_string
				syscall
				li        $v0,5                   # read_integer
				syscall
				move      $t0,$v0                 # Move input to $t0
				# Checks seed value
				ble       $t0,0,seedinvalid     # If seed =< 100
				j         rangeget                # Jumps to rangeget if no errors

		rangeget:
				la        $a0,LowerNumPrompt      # point to LowerNumPrompt
				li        $v0,4                   # print_string
				syscall
				li        $v0,5                   # read_integer
				syscall
				move      $t8,$v0                 # Stores lower limit into $t8

				# Prompt for upper limit
				la        $a0,UpperNumPrompt      # point to UpperNumPrompt
				li        $v0,4                   # print_string
				syscall
				li        $v0,5                   # read_integer
				syscall
				move      $t7,$v0                 # Stores upper limit into $t7

				# Checks upper and lower limit
				ble       $t7,$t8,rangeinvalid		# If UpperNum=<LowerNum
				ble       $t7,0,rangeinvalid      # If UpperNum =< 0
				ble       $t8,-1,rangeinvalid     # If LowerNum =< -1
				j         loop                    # Jumps to loop if no error

		loop: # loop for number generation
				# generates a hi and lo (random number and new seed)
				beqz     $t9,end								  # If the number of random #s left is 0,goto end
				multu    $t0,$t6  				        # Multiply seed by multiplier,store in $t4
				mflo		 $t1                      # Moves lo into $t1
				mfhi		 $t2                      # Moves hi into $t2
				move		 $t0,$t1                  # Makes the seed into the lo

				#range setting setup
				sub	     $t3,$t7,$t8              # Subtrcts upper limit from lower limit,stores in $t3
				add  		 $t3,$t3,1                # Adds one to $t3
				#Modulus div
				div 		 $t4,$t2,$t3              # Divides hi by $t3
				mul      $t4,$t4,$t3              # Multiplies $t4 by $t3
				sub      $t4,$t2,$t4              # Subtract $t4 from hi
				#finsih range setting formula
				add      $t4,$t4,1                # Adds 1 to the final result
				ble      $t7,$t4,loop							# If generated number is greater than upper limit
				ble      $t4,$t8,loop							# If generated number is less than lower limit

				sub      $t9,$t9,1                #Subtracts 1 from amount of randoms to generate (my counter)
				j 			 print                    #Jumps to print

		print: # print to decluter the loop
				la        $a0,OutStr              # Point to OutStr
				li  		  $v0,4                   # print_string
				syscall
				move	    $a0,$t4		              # Move stored integer into $a0
				li        $v0,1                   # print_integer
				syscall
				j         loop                    # Jumps to loop

		seedinvalid:
				la        $a0,Invalid							# Point to Invalid
				li        $v0,4										# print_string
				syscall
				j         seedget									# Jumps back to seed get

		rangeinvalid:
				la        $a0,Invalid							# Point to Invalid
				li        $v0,4										# print_string
				syscall
				j         rangeget                # Jumps back to rangeget

		randominvalid:
				la        $a0,Invalid							# Point to Invalid
				li        $v0,4										# print_string
				syscall
				j         randomget								# Jumps back to randomget

		end:
				jr	      $ra
