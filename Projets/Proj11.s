/*
Proj11.s by Joshua Pollock
This is an extra credit project for CS200. This project will
use some sort of assembly language in order to perform I/O
on a LED. In my case, I will be using ARM assembly on a
Raspberry Pi 3 with a breadboard attached to pin 7 (for power)
and pin 6 (for ground). The breadboard will have 4 68-ohm resistors
linked in series, totaling 272 ohms of resistance. When compiling
the argument -lwiringPi **MUST** be added to the gcc line.

To compile on the Raspberry Pi 3:

cd Desktop
as -o Proj11.o Proj11.s
gcc -o Proj11exec Proj11.o -lwiringPi
./Proj11exec
*/

@--------------------------------------------------------------------------------
@----------------------------------Data Section----------------------------------
@--------------------------------------------------------------------------------
.data
          .balign 4
          hello:        .asciz "Hello! Welcome to Joshua Pollocks Project 11 using ARM assembly!\nAttempting to setup Wiring Pi.\n"
          error:        .asciz "Something went wrong!\nAbandon ship!\nAbandon ship!\n"
          noError:    	.asciz "We're a go for launch. Initializing morse code sequence!\n"
          pin:          .int   7
          dotSpace:     .int 100
          dashSpace:    .int 750
          sleepSpace:   .int 1000

@--------------------------------------------------------------------------------
@----------------------------------Code Section----------------------------------
@--------------------------------------------------------------------------------
.text
          .global main
          .extern printf
          .extern wiringPiSetup
          .extern delay
          .extern digitalWrite
          .extern pinMode

main:
          push    {ip, lr}
          // Saves the initial return adress into ip

	        ldr     r0, =hello
          // Load hello into r0
          bl      printf
          // Jump and links to printf

          bl      wiringPiSetup
          // Jump and links to wiringPiSetup
          mov     r1,#-1
          // Move -1 into r1 for comparison
          cmp     r0, r1
          // Compare r0 to r1
          bne     morse
          // If not equal, jump to morse
          ldr     r0, =error
          // Else load error into r0
          bl      printf
          // Jump and links to printf
          pop     {ip, pc}
          // Ends the program by poping the original return adress (ip) into pc

morse:
	       ldr     r0, =noError
          // Load noError into r0
          bl      printf
          // Jump and links to printf

          ldr     r0, =pin
          // Loads pin number into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          mov     r1, #1
          // Moves 1 into r1
          bl      pinMode
          // Jump and links to pindMode

          // J in morse code .---
          bl      dot
          bl      dash
          bl      dash
          bl      dash

          bl      space
          // Jumps to space to add a space between letters

          // O in morse code ---
          bl      dash
          bl      dash
          bl      dash

          bl      space
          // Jumps to space to add a space between letters

          // S in morse code ...
          bl      dot
          bl      dot
          bl      dot

          bl      space
          // Jumps to space to add a space between letters

          // H in morse code ....
          bl      dot
          bl      dot
          bl      dot
          bl      dot

          bl      space
          // Jumps to space to add a space between letters

          // U in morse code ..-
          bl      dot
          bl      dot
          bl      dash

          bl      space
          // Jumps to space to add a space between letters

          // A in morse code .-
          bl      dot
          bl      dash

          pop     {ip, pc}
          // Ends the program by poping the original return adress (ip) into pc

dot:
          push    {r4, lr}
          // Saves return adress into r4

          // Write 1 to pin 7
          ldr     r0, =pin
          // Loads pin number into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          mov     r1, #1
          // r1 is 1 to turn on the LED
          bl      digitalWrite
          // Jump and link to digitalWrite


          ldr     r0, =dotSpace
          ldr     r0, [r0]
          // Loads dotSpace into r0
          bl      delay
          // Jump and links to delay

          // Write 0 to pin 7
          ldr     r0, =pin
          // Loads pin number into r0
          ldr     r0, [r0]
          mov     r1, #0
          // r1 is 0 to turn LED off
          bl      digitalWrite
          // Jump and links to digitalWrite


          ldr     r0, =sleepSpace
          // Loads sleepSpace into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0

          bl      delay
          // Jump and links to delay

          pop     {r4, pc}
          // Returns to caller

dash:
          push    {r4, lr}
          // Save return adress into r4

          // Write 1 to pin 7
          ldr     r0, =pin
          // Loads pin number into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          mov     r1, #1
          // r1 is 1 to turn on the LED
          bl      digitalWrite
          // Jump and links to digitalWrite


          ldr     r0, =dashSpace
          // Loads dashSpace into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          bl      delay
          // Jump and links to delay

          // Write 0 to pin 7
          ldr     r0, =pin
          // Loads pin number into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          mov     r1, #0
          // r1 is 0 to turn LED off
          bl      digitalWrite
          // Jump and links to digitalWrite

          ldr     r0, =sleepSpace
          // Loads sleepSpace into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          bl      delay
          // Jump and links to delay

          pop     {r4, pc}
          // Returns to caller
space:
          push    {r4, lr}
          // Save return adress into r4

          // Sleep space in between letters
          ldr     r0, =sleepSpace
          // Loads sleepSpace into r0
          ldr     r0, [r0]
          // Reads r0 address from memory then stores value in r0
          bl      delay
          // Jump and links to delay

          pop     {r4, pc}
          // Return to caller

@--------------------------------------------------------------------------------
@-------------------------------------C Code-------------------------------------
@--------------------------------------------------------------------------------

/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int system(const char *command);
int dot();
int dash();
int main()
{
        system("gpio mode 7 out");
        sleep(2);// Waits before starting code
        // J
        dot();
        dash();
        dash();
        dash();
        sleep(1.5);// Space between letters
        // O
        dash();
        dash();
        dash();
        sleep(1.5);// Space between letters
        // S
        dot();
        dot();
        dot();
        sleep(1.5);// Space between letters
        // H
        dot();
        dot();
        dot();
        dot();
        sleep(1.5);// Space between letters
        // U
        dot();
        dot();
        dash();
        sleep(1.5);// Space between letters
        // A
        dot();
        dash();
        return 0;
}
int dot()
{
        system("gpio write 7 1");
        sleep(0.75);
        system("gpio write 7 0");
        sleep(1);
        return 0;
}
int dash()
{
        system("gpio write 7 1");
        sleep(1.5);
        system("gpio write 7 0");
        sleep(1);
        return 0;
}
*/
