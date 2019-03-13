#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*****Functions*****/

// The function of y=f(x)
double fx(double x);

// The function used to define K,
// such that K > f(x) for all x in [a,b]
double defineK(double a, double b);

// The function to verify if (x,y) is in the area of f(x)
// If in, return 1; else return 0;
int compare(double x, double y);


/**********MAIN**********/

int main() {

    double a, b;
    srand(time(0));
    // get a & b from input
    printf("Enter a value for a: ");
    scanf("%lf", &a);
    printf("Enter a value for b: ");
    scanf("%lf", &b);
    printf("You entered a=%f and b=%f\n", a, b);

    if (!(a < b && fx(a) >= 0 && fx(b) >= 0)) {
        printf("Inputs illegal!\n");
        exit(1);
    }


    double K = defineK(a, b);
    //printf("K = %lf\n", K);
    double x0, y0;      // (x0,y0) is a random point in the area K(b-a)
    int N[10] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for (int j = 0; j < 10; j++) {
        int count = 0;
        double Z = 0;
        for (int i = 0; i < N[j]; i++) {
            x0 = a + (double)(rand()) / (double)(RAND_MAX) * (b - a);
            y0 = (double)(rand()) / (double)(RAND_MAX) * K;
            //printf("x' = %lf, y' = %lf\n", x0, y0);
            if (K < fx(x0)) {
                // K should be larger than any f(x) for x in [a,b]
                printf("Invalid K!\n");
                exit(1);
            }
            count += compare(x0, y0);
        }
        //printf("count = %d\n", count);
        Z = K * (b - a) * (double)(count) / (double)(N[j]);
        printf("N = %d, Z = %lf\n", N[j], Z);
    }

    return 0;
}

// The function of y=f(x) can be modified here
double fx(double x) {
    double y;
    y = pow(x, 2);    //y = f(x) = x^2
    //y = sin(x) + 1;
    //y = pow(x,3) - 3*pow(x,2) + 4;
    return y;
}

double defineK(double a, double b) {
    double K;
    K = (fx(a) > fx(b)) ? fx(a) : fx(b);
    for (double x = a; x < b; x += 0.01) {
        // find the approximate max of f(x) by step of 0.01
        if (fx(x) > K) {
            K = fx(x);
        }
    }

    // double-size K in case K is not the maximum.
    return (K * 2);
}

int compare(double x, double y) {
    if (fx(x) >= y) {
        //(x,y) is in the area of f(x)
        return 1;
    }
    else return 0;
}