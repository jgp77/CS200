.data
.align 4

promptInt: .asciiz   "[Integer] (0=exit) >>> "
crlf:          .asciiz   "\n"
space:         .asciiz   " "
sortedLabel:   .asciiz   "Sorted array: "

.text
.globl main

main:
    #add $fp, $zero, $sp    #set frame pointer
    move $s1, $ra           # store return address
    li $s0,0               # number of integers initialize

PROMPTINT:
    li $v0, 4              # opcode for print_string
    la $a0, promptInt  # argument for print_string
    syscall                # call print_string
    li $v0, 5              # opcode for read_int
    syscall                # call read_int
    beq $v0,0,bubblesort
    addi $sp,$sp,-4        # decrement stack -4
    sw $v0,0($sp)          # store user input onto the stack
    addi $s0, $s0, 4       # store stack counter in s0
    j PROMPTINT            # jump back to PROMPTINT

bubblesort:
    beq $s0,0,EXIT         # check if number of ints*4 is > 0
    move $t0,$sp           # outerloop counter
    add $t4,$sp,$s0        # outerloop termination
    addi $t4,$t4,-4

bubbleLoop1:
    move $t1,$sp           # innerloop counter
    sub $t6,$t0,$sp        # inner loop end condition
    sub $t6,$t4,$t6
bubbleLoop2:
    lw $t2,0($t1)          # get first int
    lw $t3,4($t1)          # get second int
    slt $t5,$t2,$t3        # if n[0] < n[+1] set t5 = 1
    bne $t5,$zero,swapFalse# if $t5 == 0 !swap ... else swap
    move $t5,$t2           # move $t2 into $t5
    move $t2,$t3           # move $t3 into $t2
    move $t3,$t5           # move $t5 into $t3
    sw $t2,0($t1)          # restore back to stack swapped
    sw $t3,4($t1)          # ..............................

    swapFalse:
     addi $t1,$t1,4         # increment to next int
     bne $t1,$t6,bubbleLoop2 # if not end then back to loop

    addi $t0,$t0,4          # increment outer loop counter
    bne $t0,$t4,bubbleLoop1 # if !=$t0 back to loop else:
    li $v0,4                # print:
    la $a0,sortedLabel      # sorted array...
    syscall                 # call the sys for print label
    jal printArrayList      # now print sorted array
    j EXIT                  # then exit cleanly

printArrayList:
     move $t5,$sp           # print counter
     add $t2,$s0,$t5        # end condition
 printArrayLoop:
    li $v0, 1               # opcode print int
    lw $a0,0($t5)           # arg for print int
    syscall                 # call
    li $v0,4                # print string
    la $a0,space            # space
    syscall                 # call
    addi $t5,$t5,4           # next int
    bne $t5,$t2,printArrayLoop  # if int left then print next
    li $v0,4                 # print code
    la $a0,crlf              # new line
    syscall                  # call
    jr $ra                   # return to caller

EXIT:
    move $ra,$s1
    jr $ra
