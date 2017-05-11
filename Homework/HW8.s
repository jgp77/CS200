lw	    $t0,Num1	            #Loads Num1 into $t0
lw	    $t1,Num2	            #Loads Num2 into $t1
lw      $t2,Num3	            #Loads Num3 into $t2

move    $t4,$t0               #Sets result/$t4 to Num1
blt     $t0,$t1,end           #If Num1 is less than Num2
beq     $t0,$t1,equals        #If Num1==Num2, goes to equals
addi    $t4,$t2,5             #Else it adds 5 to Num3

equals:
ble     $t1,$t2,lessOrEquals  #Goes to lessOrEquals if Num2 <= Num3
or      $t4,$t0,$t2           #Else result is Num1 OR Num3 (Num1|Num3)
j       end                   #Jumps to end

lessOrEquals:
and     $t4,$t1,$t2           #Result is Num2 AND Num3 (Num1&Num3)
j       end                   #Jumps to end

end:
sw       $t4,Result           #Saves the result in Result



lw	    $t0,Num1	            #Loads Num1 into $t0
lw	    $t1,Num2	            #Loads Num2 into $t1
lw      $t2,Num3	            #Loads Num3 into $t2

loop:
bge     $t0,$t1,end           #If Num1 is >= to Num2, not fullfilling the while, goes to end
bge     $t2,$t3,end           #If Num2 is >= to Num3, not fullfilling the while, goes to end
addi    $t0,$t0,1             #Adds 1 to Num1
addi    $t2,$t2,-1            #Subtracts 1 from Num3
j       loop                  #Jumps back to the loop


end:
mul     $t4,$t1,$t2           #Mutiplies Num2 to Num3 (Num2*Num3) and stores in $t4
add     $t4,$t4,$t0           #Add Num1 to $t4
sw      $t4,Result            #Saves $t4 into Result
