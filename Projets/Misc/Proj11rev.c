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
