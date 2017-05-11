#==============================================================================
# Project9.s
#
# by Joshua Pollock
#
# This program produces a maze in an 80 X 24 grid by recursively pathing
# through the grid space. Code that was TODO has been surronded by comment
# lines of equal signs. All the C++ code and given headers are at the bottom
# of the file to reduce clutter. The Visit functionality has not been added
# as it was not required for Project 9. This program should be ran with
# QTSPIM and should only print out a grid of # characters due to lack of the
# Visit function. The Visit functionality will be later implemented within
# Project 10.
#
# Last modified: 21 April 2017 by Joshua Pollock
#==============================================================================

	.data
GRID_WIDTH:	.word	80		# need to add 1 to print as string
GRID_HEIGHT:	.word	23
GRID_SIZE:	.word	1840		# because I can't precalculate it in
					# MIPS like I could in MASM
NORTH:		.word	0
EAST:		.word   1
SOUTH:		.word	2
WEST:		.word	3
RGEN:		.word	1073807359	# a sufficiently large prime for rand
POUND:		.byte	35		# the '#' character
SPACE:		.byte	32		# the ' ' character
NEWLINE:	.byte	10		# the newline character

#==============================================================================
# STRING VARIABLES
#==============================================================================

rsdPrompt:	.asciiz "Enter a seed number (1073741824 - 2147483646): "
smErr1:		.asciiz "That number is too small,try again: "
bgErr:		.asciiz "That number is too large,try again: "

randomTest:		.asciiz  "\nRandom Test:\n"
indexTest:		.asciiz "\nIndex Test:\n"
boundsTest:		.asciiz  "\nBounds Test:\n"

newLine:	.asciiz "\n"

#==============================================================================
# GLOBAL VARIABLES
#==============================================================================

grid:	.space	1841		# ((79 + 1) * 23) + 1 bytes reserved for grid
rSeed:	.word	0		# a seed for generating a random number

#==============================================================================
# FUNCTIONS:
#==============================================================================
	.text
	.globl main

main:
	sw	$ra, 0($sp)	# save the return address
	jal	srand		# Get a random seed
	jal	ResetGrid	# reset the grid to '#'s
	li	$t0, 1		# set up for start of generation at (1,1)
	sw	$t0, -4($sp)	# push first param
	sw	$t0, -8($sp) 	# push second param
	jal	PrintGrid	# Displays the grid of # symbols
	jal IsInBounds # Tests that the seed is within the bounds
	jal rand # Generates a random number based off of the seed
	jal XYToIndex # Converts 2 points to 1 index
	lw	$ra, 0($sp)	# restore the return address
	jr	$ra		# exit the program


ResetGrid:
	# save the registers
	sw	$s0,-4($sp)	# $s0 will be the loop counter
	sw	$s1,-8($sp)	# $s1 will hold the array bound
	sw	$s2,-12($sp)	# $s2 will be the grid base address
	sw	$s3,-16($sp)	# $s3 will hold the character
	sw	$s4,-20($sp)	# $s4 will hold the grid width
	sw      $s5,-24($sp)   # $s5 will hold the newline character
	sw	$s6,-28($sp)	# $s6 used for calculations
	# NOTICE THAT I DON'T BOTHER MOVING THE STACK POINTER

	# load the working values
	li	$s0,1		# initialize the counter
	lw	$s1,GRID_SIZE	# initialize the array bound
	la	$s2,grid	# get the base address
	lb	$s3,POUND	# store the '#' ASCII code
	lw	$s4,GRID_WIDTH # store the grid width
	lb	$s5,NEWLINE	# store the newline ASCII code

ResetLoop:
	sb	$s3,0($s2)	# put a '#' in the grid
	addi	$s0,$s0,1	# increment the loop counter
	addi	$s2,$s2,1	# point at next char position
	div	$s0,$s4	# divide the counter by grid width
	mfhi	$s6		# get remainder in calculation register
	bnez	$s6,NoNewLine	# keep going

	sb	$s5,0($s2)     # put a newline in the grid
	addi	$s0,$s0,1	# increment the loop counter
	addi	$s2,$s2,1	# point at next char position

NoNewLine:
	blt	$s0,$s1,ResetLoop	# if less than end,loop again

	# when we fall out of the loop,restore the registers and return
	lw	$s0,-4($sp)
	lw	$s1,-8($sp)
	lw	$s2,-12($sp)
	lw	$s3,-16($sp)
	lw	$s4,-20($sp)
	lw      $s5,-24($sp)
	lw	$s6,-28($sp)
	# IN A LANGUAGE WITH PUSH/POP,YOU WOULD HAVE TO POP THEM
	# FROM THE STACK IN THE REVERSE ORDER YOU PUSHED THEM.

	jr	$ra		# return

srand:
	# For this function,we only need to preserve 3 registers.  We use
	# $a0 and $v0 for I/0,and we use $s0 as a scratch register.
	# save the registers
	sw	$v0,-4($sp)	# $v0 will be the service code
	sw	$a0,-8($sp)	# $a0 will point to the grid string
	sw	$s0,-12($sp)	# $s0 will hold the input for testing

	# prompt for a random seed and get the value
	la	$a0,rsdPrompt
	li	$v0,4		# print_string
	syscall

input10:
	li	$v0,5		# read_int
	syscall
	li	$s0,1073741823		# put 2147483646 in t0 for comparison
	bgtu	$v0,$s0,input11	# input bigger than 1073741823?
	la	$a0,smErr1	# no,point to error and
	li	$v0,4		# print_string
	syscall
	j	input10		# try again

input11:
	li	$s0,2147483646	# upper bound in register t0 for comparison
	bleu	$v0,$s0,input12	# less than or equal 2147483646?
	la	$a0,bgErr	# no,point to error and
	li	$v0,4		# print_string
	syscall
	j	input10		# try again

input12:
	# number is good,save and move on
	sw	$v0,rSeed

	# restore the registers
	lw	$v0,-4($sp)
	lw	$a0,-8($sp)
	lw	$s0,-12($sp)

	jr	$ra		# return

#==============================================================================
rand:
	lw       $t0, rSeed        # Puts rSeed into $t0
	lw       $t1, RGEN         # Puts RGEN into $t1
	lw       $t2, -8($sp)      # Puts min into $t2
	lw       $t3, -12($sp)     # Puts max into $t3

	mult     $t0,$t1					 # Multiplies rSeed($t0) by RGEN($t1)
	mflo     $t9							 # Stores lo into $t9
	mfhi     $t8               # Stores hi in $t8

	sw       $t9, rSeed        # Saves $t9 (lo) as new rSeed

	sub      $t7,$t3,$t2			 # Subracts $t2 from $t3 (max-min), stores in $t7
	add      $t7,$t7,1				 # Adds 1 to result($t7)

	divu     $t8,$t7					 # Divides hi($t8) by result($t7)
	mflo     $t6							 # Stores lo into $t6
	mul      $t6,$t6,$t7			 # Multiplies lo($t6) by result($t7), stores in $t6
	sub      $t6,$t8,$t6			 # Subtracts result($t6) from hi($t8), stores in $t6

	add      $t6,$t6,1				 # Adds 1 to result, stores in $t6

	sw       $t6,-4($sp)			 # Saves result into return address of the stack

	# Test Print
	li       $v0, 4						 # print_string
	la       $a0, randomTest	 # Points to randomTest
	syscall
	li       $v0, 1						 # print_integer
	lw 	     $a0, -4($sp)      # Points to the result
	syscall

	jr	      $ra		             # Return to caller
#==============================================================================

#==============================================================================
XYToIndex:

	lw		 $t0,-12($sp) 		# Puts y into $t1 from the stack
	lw		 $t1,GRID_WIDTH 	# Puts GRID_WIDTH into $t2
	lw		 $t2,-8($sp)			# Puts x into $t0 from the stack


	mult   $t0,$t1					# Multiplies y by GRID_WIDTH
	mflo	 $t3							# Puts lo into $t3
	add	   $t3,$t2,$t3			# Adds x to (y*GRID_WIDTH), Stores in $t3

	sw	   $t3,-4($sp)			# Saves result ($t3) into the return value of the stack

	# Print out the return
	li       $v0, 4					# print_string
	la       $a0, indexTest # Points to indexTest
	syscall
	li       $v0, 1					# print_integer
	lw 	     $a0, -4($sp)   # Points to the result
	syscall

	jr		 $ra							# Return to caller


#==============================================================================

#==============================================================================
IsInBounds:

	lw		 $t0,-8($sp)					# Puts x into $t0 from the stack
	lw		 $t1,-12($sp) 				# Puts y into $t1 from the stack
	lw		 $t2,GRID_HEIGHT  		# Puts GRID_HEIGHT into $t2
	lw		 $t3,GRID_WIDTH 			# Puts GRID_WIDTH into $t3

	blt	 	 $t1,$zero,false 			# If 0>y, jump to false
	bge		 $t1,$t2,false	  		# If y>=GRID_WIDTH, jump to false
	blt		 $t0,$zero,false 			# If x<0, jump to false
	bgt		 $t0,$t3,false 				# If GRID_WIDTH<x, jump to false

	sw		 $zero,-4($sp)				# True, so puts 0 into the stack return

	# Print out the return
	li       $v0, 4							# print_string
	la       $a0, boundsTest		# Points to boundsTest
	syscall
	li       $v0, 1							# print_integer
	lw 	     $a0, -4($sp)   		# Points to the result
	syscall

	jr		 $ra									# Return to caller
	false:
		li		 $t5,1 							# Loads 1 into $t5 (No $one register :( )
		sw		 $t5,-4($sp)				# False, so puts 1 ($t5) into the stack return

		# Print out the return
		li       $v0, 4						# print_string
		la       $a0, boundsTest	# Points to boundsTest
		syscall
		li       $v0, 1						# print_integer
		lw 	     $a0, -4($sp)   	# Points to the result
		syscall

		jr		 $ra								# Return to caller
#==============================================================================

#==============================================================================
Visit:

	# TO DO:  You won't need this for project 9; it is just a placeholder
	#         for project 10.

	jr	$ra # Return to caller
#==============================================================================

#==============================================================================
PrintGrid:
	li 	$v0,4       # Print_int
	la 	$a0,grid	  # Loads grid into $a0
	syscall
	jr	$ra					# Return to caller
#==============================================================================



#==============================================================================
#C++ code for the functions
#==============================================================================
#==============================================================================
# CONSTANTS:
#
# #define GRID_WIDTH 79
# #define GRID_HEIGHT 23
# #define NORTH 0
# #define EAST 1
# #define SOUTH 2
# #define WEST 3
#==============================================================================

#==============================================================================
# int main()
# {
#   // Starting point and top-level control.
#   srand( time(0) ); // seed random number generator.
#   ResetGrid();
#   Visit(1,1);
#   PrintGrid();
#   return 0;
# }
#==============================================================================
#==============================================================================
# void ResetGrid()
# {
#   // Fills the grid with walls ('#' characters).
#   for (int i=0; i<GRID_WIDTH*GRID_HEIGHT; ++i)
#   {
#     grid[i] = '#';
#   }
# }
#==============================================================================
# It's a waste do do a stack frame when there are no parameters or
# return values,so I'll optimize and simply push any register I use
# onto the stack.  I need 7,a loop counter,a place to store the
# loop bound for comparison,the base address of the grid,a register
# to store the character value I will write,a register to store the
# width of the grid,a register to store the newline character,and
# finally,a register to hold calculation results.
#==============================================================================
# srand()
#
# Unlike the C++ equivalent,this routine has to ask the user for a seed,
# because we don't have access to a time string. So I borrowed code from a
# linear congruence project to prompt for a large integer and save it as a
# seed for another function that does linear congruence.
#==============================================================================
#==============================================================================
# rand(int min,int max)
#
# It uses the rSeed and RGEN values to create a new psuedo-random and a new
# seed for the next time this routine is called.  It range-fits the psuedo-
# random to the range min-max and returns it.  It does not need to formalize a
# stack frame since it doesn't call any other routines,so we simply set the
# two params and the return into the stack before calling and it begins pushing
# registers onto the stack above -12($sp).  Min is expected to be at -8($sp)
# and max is expected at -12($sp) while the return is at -4($sp).
#==============================================================================
#==============================================================================
# int XYToIndex( int x,int y )
# {
#   // Converts the two-dimensional index pair (x,y) into a
#   // single-dimensional index. The result is y * ROW_WIDTH + x.
#   return y * GRID_WIDTH + x;
# }
#
# Like rand,this uses the stack only for getting and returning values.
# -4($sp) is the return,-8($sp) is x,and -12($sp) is y.
#==============================================================================
#================================================================================
# int IsInBounds( int x,int y )
# {
#   // Returns "true" if x and y are both in-bounds.
#   if (x < 0 || x >= GRID_WIDTH) return false;
#   if (y < 0 || y >= GRID_HEIGHT) return false;
#   return true;
# }
#
# Like rand,this uses the stack only for getting and returning values.  -4($sp)
# is the return,-8($sp) is x,and -12($sp) is y.  Note that because we use a
# width that has an extra character,our first test is actually:
# 	if (x < 0 || x > GRID_WIDTH) return false;
#================================================================================
#==============================================================================
# void Visit( int x,int y )
# {
#   // Starting at the given index,recursively visits every direction in a
#   // randomized order.
#   // Set my current location to be an empty passage.
#   grid[ XYToIndex(x,y) ] = ' ';
#
#   // Create an local array containing the 4 directions and shuffle their
#   // order.
#   int dirs[4];
#   dirs[0] = NORTH;
#   dirs[1] = EAST;
#   dirs[2] = SOUTH;
#   dirs[3] = WEST;
#
#   for (int i=0; i<4; ++i)
#   {
#     int r = rand() & 3;
#     int temp = dirs[r];
#     dirs[r] = dirs[i];
#     dirs[i] = temp;
#   }
#
#   // Loop through every direction and attempt to Visit that direction.
#   for (int i=0; i<4; ++i)
#   {
#     // dx,dy are offsets from current location. Set them based
#     // on the next direction I wish to try.
#     int dx=0,dy=0;
#     switch (dirs[i])
#     {
#       case NORTH: dy = -1; break;
#       case SOUTH: dy = 1; break;
#       case EAST: dx = 1; break;
#       case WEST: dx = -1; break;
#     }
#
#     // Find the (x,y) coordinates of the grid cell 2 spots
#     // away in the given direction.
#     int x2 = x + (dx<<1);
#     int y2 = y + (dy<<1);
#
#     if (IsInBounds(x2,y2))
#     {
#       if (grid[ XYToIndex(x2,y2) ] == '#')
#       {
#         // (x2,y2) has not been visited yet... knock down the
#         // wall between my current position and that position
#         grid[ XYToIndex(x2-dx,y2-dy) ] = ' ';
#
#         // Recursively Visit (x2,y2)
#         Visit(x2,y2);
#       }
#     }
#   }
# }
#
# Visit is the tough one.  Because it is recursive,you have to use a stack-
# frame to properly handle all the levels of recursion.  There is no return
# but x is at -4($sp) and y is at -8($sp).
#==============================================================================
#==============================================================================
# void PrintGrid()
# {
#   // Displays the finished maze to the screen.
#   for (int y=0; y<GRID_HEIGHT; ++y)
#   {
#     for (int x=0; x<GRID_WIDTH; ++x)
#     {
#       cout << grid[XYToIndex(x,y)];
#     }
#     cout << endl;
#   }
# }
#==============================================================================
