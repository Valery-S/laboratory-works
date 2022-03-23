#include <stdio.h>
#include <conio.h>
extern "C" cdecl  asmrazn(int,int);
extern "C" pascal  asmsumm(int,int);
int summ;
int main()
{
int a,b,razn;
printf(" a=");
scanf("%d",&a);
printf(" b=");
scanf("%d",&b);
razn=asmrazn(a,b);
printf("\n‚Vivod v C (a-b)=%d",razn);
asmsumm(a,b);
printf("\n‚Vivod v C (a+b)=%d",summ);
return(0);
}
