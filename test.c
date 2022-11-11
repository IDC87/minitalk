#include "minitalk.h"


int binary(int n)
{
    // array to store binary number
    int binaryNum[32];
  
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
  
    // printing binary array in reverse order
    /* for (int j = i - 1; j >= 0; j--)
        printf("%d", binaryNum[j]); */
    return (n);
}

int main(int argc, char **argv)
{
    signed char byte1 = 0x80;
signed char byte2 = 0x10;

unsigned short value1 = ((byte2 << 8) | (byte1 & 0xFF));
unsigned short value2 = ((byte2 << 8) | byte1);

printf("value1=%hu %hx\n", value1, value1);
printf("value2=%hu %hx\n", value2, value2);

printf("\n");
printf("\n");

unsigned char x = 0;
unsigned char y = 1;
printf("%u\n", x - y); 

printf("\n");

int a = 0;
int b = 8;

while(a <= b)
{
    printf("%d / %d is: %d\n", a, b, (a / b));
    //printf("%d %% %d is: %d\n", a, b, (a % b));
    a++;      
}

int Z = atoi(argv[1]);
 binary(Z);




}