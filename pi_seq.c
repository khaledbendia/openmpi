//gcc pi_seq.c -o test -lm
// ./test
#include <stdio.h>
#include <math.h>
int main (int argc, char* argv[]) {
int n=24;
double pi=0;
for(int i=0;i<n;i++)
{
    double a,b;
    a= i*(1.0/n);
    b= i*(1.0/n)+(1.0/n);
    double x= 4*atan(a);
    double y= 4*atan(b);
    pi+=(y-x);
}
printf("pi=%f\n", pi);
}
