#include <stdio.h>
#include <math.h>
 
 
int main(void)
{
        double a,b,c;
        double x1,x2;
 
        printf("enter the real number a,b,c : ");
        scanf("%lf %lf %lf",&a,&b,&c);
 
        x1 = (-b + sqrt(pow(b,2)-4*a*c))/2*a;
        x2 = (-b - sqrt(pow(b,2)-4*a*c))/2*a;
 
        printf("%.2f %.2f",x1,x2);
        return 0;
}
