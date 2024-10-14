#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char fmt[] = "%d";       // Format string for scanf/printf
    int num;           // Variable to store user input numbers
    char fprompt[] = "How many numbers ? ";
    char prompt[] = "Enter a number: ";
    char positive[] = "Positive: %d\n";
    char negative[] = "Negative: %d\n";
    char zero[] = "Zero: %d\n";
    char line[] = "---------------------\n";
    int zCount = 0;
    int nCount = 0;
    int pCount = 0;


    _asm {
        // ask user for num of numbers(iterations):
        lea eax, fprompt
        push eax
        call printf
        // get user input:
        lea eax, num
        push eax
        lea eax, fmt
        push eax
        call scanf
        add esp, 12   //clean the stack

        mov ecx, [num]  // move it to ecx, for loop iteration

        floop:
        push ecx  // to avoid corrupted ecx
            //ask user to enter a number for every iteration:
            lea eax, prompt
            push eax
            call printf
            //get input , store in num:
            lea eax, num
            push eax
            lea eax, fmt
            push eax
            call scanf
            add esp, 12
            // compare with zero , and update counters:
            cmp num, 0
            jg positiveResult   // if >0
            jl negativeResult   // if <0
            zeroResult :   // if neither
                  inc zCount
                  jmp bypass
            positiveResult :
                  inc pCount
                  jmp bypass
            negativeResult:
                  inc nCount
            bypass :
                  pop ecx   // get the loop counter back
                  loop floop   // loop until ecx is zero

           // print the seperator line:            
            lea eax, line
            push eax
            call printf
           // Print the counts of positive, negative, and zero numbers:
            push pCount
            lea eax,positive
            push eax
            call printf

            push nCount
            lea eax, negative
            push eax
            call printf

            push zCount
            lea eax, zero
            push eax
            call printf
            add esp, 28        // we pushed 7 times, 4*7=28
    }
    return 0;
}
