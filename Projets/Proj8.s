.data

amountPrompt:    .asciiz "How many numbers will be sorted? "
intPrompt:       .asciiz "Enter an integer: "
space:           .asciiz " "
outStr:          .asciiz "Sorted list:\n"
Invalid:       	 .asciiz "Invalid Input! Number must be 1 to 10.\n"


.text

main:
    ReadNums:
        la $a0,amountPrompt                       # Point to amountPrompt
        li $v0,4                                  # print_string
        syscall
        li $v0,5                                  # read_integer
        syscall
        move $t0,$v0                              # moves input into $t0
        bgt  $t0,10,amountinvalid                 # if input is greater than 10, goto invalid
        blt  $t0,1,amountinvalid                  # if input is less than 1, goto invalid

            readnumsloop:
            la $a0,intPrompt                      # Point to intPrompt
            li $v0,4                              # print_string
            syscall
            li $v0,5                              # read_integer
            syscall
            sub $sp,$sp,4                         # Decrement the stack by -4
            sw $v0,0($sp)                         # Puts the user input onto the stack
            add $s0,$s0,4                         # Adds to stack counter in $s0
            sub $t0,$t0,1                         # Subtracts 1 from the amount being sorted
            beqz $t0,BSort                        # If the amount is 0, goto sorting
            j readnumsloop                        # Else repeat the loop

            amountinvalid:
                la        $a0,Invalid							# Point to Invalid
                li        $v0,4										# print_string
                syscall
                j         ReadNums                # Jumps to ReadNums


    BSort:
        move $t0,$sp                              # Loop counter
        add $t4,$sp,$s0
        sub $t4,$t4,4                             # Outer loop stop condition stored in $t4

            BLoop:
            move $t1,$sp                          # Creates nested counter for stack position
            sub $t5,$t0,$sp
            sub $t5,$t4,$t5                       # Nested loop stop condition is stored in $t5

                NestedBLoop:
                lw $t2,0($t1)                     # Get integer a $t1 position
                lw $t3,4($t1)                     # Get integer below $t1 position
                blt $t3,$t2,swap                  # If $t3 is less than $t2
                bgt $t3,$t2,noSwap                # If $t2 is less than $t3

                    swap:
                      sw $t3,0($t1)               # Puts $t3 where $t2 used to be on the stack
                      sw $t2,4($t1)               # Puts $t2 where $t3 used to be on the stack

                    noSwap:
                      add $t1,$t1,4               # Inreases nested counter by 4 to next stack position
                      blt $t1,$t5,NestedBLoop     # If counter $t1 is less than the stop condition, jump back to nested loop
                      add $t0,$t0,4               # Inreases counter by 4 to next stack position
                      blt $t0,$t4,BLoop           # If counter $t0 is less than outer stop condition, jump back to outer loop
                      j PrintNums                 # Else jumps to PrintNums

    PrintNums:
        la $a0,outStr                             # Point to outStr
        li $v0,4                                  # print_string
        syscall
        move $t5,$sp                              # Counter for printing loop
        add $t2,$s0,$t5                           # Stop condition of the loop
            PrintNumsLoop:
            lw $a0,0($t5)                         # Points to number on stack to print
            li $v0, 1                             # print_integer
            syscall
            la $a0,space                          # points to space
            li $v0,4                              # print_string
            syscall
            add $t5,$t5,4                         # Adds 4 to counter/goes to next stack position
            blt $t5,$t2,PrintNumsLoop             # If counter is less than stop condition, goes back to loop
            j  end                                # Else, jump to end

end:
    jr $ra                                        # Ends the program
