/* 
*
*   The program will manipulate and caluclate functions using polynomials.
*   This includes integration, multiplication, evaluation and generation of polynomials.
*
*   T. Lee, 13 October 2017
*/

#include <stdin.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* functions to be implemented */
int readPoly(int coeff[], int degree);
void printPoly(int coeff[], int degree);
double evalPoly(int coeff[], int degree, double x);
double integratePoly(int coeff[], int degree, double low, double high);
int multPoly(int c1[], int d1, int c2[], int d2, int c3[], int d3);
int genPoly(int coeff[], int degree, int roots[], int nroots);

#ifndef NOMAIN

int main() {
    int f4[5] = {0};  /* f(x) - degree = 4 or less */
    int g4[5] = {0};  /* g(x) - degree = 4 or less */
    int p8[9] = {0};  /* p(x) - degree = 8 or less */
    int roots[4];     /* roots for generating */
    int degree = 0;   /* degree of generated poly */
    int status = 1;
    double x = 0;     /* point for evaluation */
    double low = 0, high = 0;  /* limits for integration */
    char command;     /* user command character */
    int done = 0;     /* set to 1 to quit */
    int i;
    
    while (!done) {
        printf("\nEnter a command (e,i,g,m,q): ");
        do {
            command = getchar();
        } while (command == '\n');
        while (getchar() != '\n');
        
        switch (command) {
            
            /* e: evaluate a polynomial */
            case 'e':
                printf("EVALUATE\n");
                printf("Enter a polynomial f(x):\n");
                status = readPoly(f4 ,4);
                if (!status) {
                    printf("Enter x: ");
                    scanf("%lf", &x);
                    printf("f(%g) = %g\n", x, evalPoly(f4, 4, x));
                }
                else {
                    printf("ERROR: Could not read polynomial.\n");
                }
                break;
                
            /* integrate a polynomial */    
            case 'i': 
                printf("INTEGRATE\n");
                printf("Enter a polynomial f(x):\n");
                status = readPoly(f4, 4);
                if (!status) {
                    printf("Enter lower limit: ");
                    scanf("%lg", &low);
                    printf("Enter upper limit: ");
                    scanf("%lg", &high);
                    printf("Integral of f(x) = %g\n", integratePoly(f4, 4, low, high));
                }
                else {
                    printf("ERROR: Could not read polynomial.\n");
                }
                break;
                
            /* generate a polynomial */
            case 'g':
                printf("GENERATE\n");
                printf("Enter the degree (<= 4): ");
                scanf("%d", &degree);
                for (i=0; i<=4; i++) roots[i] = 0;
                if ((degree <= 4) && (degree > 0)) {
                    for (i=0; i<degree; i++) {
                        printf("Integer Root %d = ", i+1);
                        scanf("%d", &roots[i]);
                    }
                    status = genPoly(f4, degree, roots, degree);
                    if (!status) {
                        printf("f(x) = ");
                        printPoly(f4, degree);
                    }
                    else {
                        printf("ERROR: could not generate polynomial");
                    }
                    printf("\n");
                }
                else {
                    printf("ERROR: Degree must be between 1 and 4.\n");
                }
                break;
                
            /* multiply two polynomials */
            case 'm':
                printf("MULTIPLY\n");
                printf("Enter first polynomial f(x):\n");
                status = readPoly(f4,4);
                if (!status) {
                    printf("Enter second polynomial g(x):\n");
                    status = readPoly(g4,4);
                    if (!status) {
                        printf("f(x) * g(x) = ");
                        status = multPoly(f4, 4, g4, 4, p8, 8);
                        if (status) printf("ERROR");
                        else printPoly(p8, 8);
                        printf("\n");
                    }
                    else {
                        printf("ERROR: Could not read polynomial.\n");
                    }
                }
                else {
                    printf("ERROR: Could not read polynomial.\n");
                }
                break;
                
            /* quit */
            case 'q':
                done = 1;
                break;
                
        }
    }
    return (EXIT_SUCCESS);
}

#endif  /*NOMAIN*/

/*---- DO NOT CHANGE ANYTHING ABOVE THIS LINE ----*/

/* function header - replace with a description of the function */
int readPoly(int *coeff, int degree) {
    int i = 0;
    char c = getchar();
    char lastC = 0;
	char flag = 'f';
	int temp = 0;
	
    for(i = 0; i <= degree; i++){ /* reset coefficient array */
        coeff[i] = 0;
    }
	
    while(c == 9 || c == 10 || c == 32) c = getchar(); /* ignore spaces before polyinomial */
	
	while(flag != 'd'){
	    switch(flag){
	        case 'f':
    	        if(lastC == '-' && c == 'x'){
    	            temp = -1;
    	            flag = 'x';
    	            break;
    	        }
	        case 'p':
	        case 'm':
    	        if(c >= '0' && c <= '9') {
    	            ungetc(c, stdin);
    	            if(lastC == '-') ungetc(lastC, stdin);
    	            scanf("%d", &temp);
    	            if(flag == 'm'){
    	                temp = -temp;
    	            }
    	            flag = 'n';
    	        }
    	        else if(c == 'x'){
    	            if(flag == 'm'){
    	                temp = -1;
    	            }
    	            else if(flag == 'p'){
    	                temp = 1;
    	            }
    	            flag = 'n';
    	        }
	        break;
	        case 'n':
	            if(c == 'x'){
	                flag = 'x';
	            }
	            else{
	                ungetc(c, stdin);
	                coeff[0] = temp;
	                flag = 'd';
	            }
	        break;
	        case 'x':
	            if(c == '^'){
	                scanf("%d", &i);
	                coeff[i] = temp;
	            }
	            else{
	                coeff[1] = temp;
	            }
	       break;
	    }
	    lastC = c;
	    c = getchar();
	}
	printPoly(coeff, degree);
    return 1;
}

/* prints a polyinomial in terms of degree and coefficients given */
void printPoly(int coeff[], int degree) {
    int i = degree;
    
    while(coeff[i] == 0 && i > 0) { /* Find the first part of the polynomial that isnt zero */
        i--;
    }
    
	/* print the first part of the polynomial */
    if(i == 1) {
        printf("%dx", coeff[i]);
    }
    else if(i > 1) {
        printf("%dx^%d", coeff[i], i);
    }
    else {
        printf("%d", coeff[i]);
		return;
    }
    
    for(; i >= 0; i--){ /* print the rest of the polynomial */
        /* print the seperator */
        if(coeff[i] > 0) { 
            printf(" + ");
        } 
        else if(coeff[i] < 0) {
            printf(" - ");
        }
        else {
            continue;
        }
        /* print the coefficients */
        if(i > 1 && abs(coeff[i]) == 1) {
            printf("x^%d", i);
        }
		else if(i > 1 && abs(coeff[i]) != 1) {
            printf("%dx^%d", abs(coeff[i]), i);
        }
        else if(i == 1 && abs(coeff[i]) == 1){
            printf("x");
        }
		else if(i == 1 && abs(coeff[i]) != 1){
			printf("%dx", abs(coeff[i]));
		}
        else {
            printf("%d", abs(coeff[i]));
        }
    }
    return;
}

/* evaluate a polinomial in terms of the polinomial given, the degree and value of x */
double evalPoly(int coeff[], int degree, double x) {
    int i, j;
    int sum = 0;
    int exponent = 0;
    if(!x) return 0;
    for(i = degree; i >= 0; i--){
        if(!coeff[i]) {
			continue;
		}
        exponent = 1;
        for(j = i; j >= 0; j--){
            exponent *= x;
        }
        sum += coeff[i] * exponent;
    }
    return sum;
}

/* function header - replace with a description of the function */
double integratePoly(int coeff[], int degree, double low, double high) {
    return 0;
}

/* multiplies two polyinomial and constructs a new polyinomial */
int multPoly(int c1[], int d1, int c2[], int d2, int *c3, int d3) {
    int i, j; /* declare variables */
	
	if(d1 + d2 > d3) { /* if combined polyinomial is too big */
        return 1;
    } 
	
    for(i = d1 - 1; i >= 0; i--){ /* multiple coefficients and add polynomials */
		if(i == (d1 - 1)){
			for(j = d2; j >= 0; j--){
				c3[i+j] = c1[i] * c2[j];
			}
		}
		else {
			for(j = d2 - 1; j >= 0; j--){
				c3[i+j] += c1[i] * c2[j];
			}
		}
	}
    return 0;
}

/* function header - replace with a description of the function */
int genPoly(int *c, int d, int r[], int n) {
	int i, j, flag;
	int factor[2] = {0};
	flag = 0;
	
	if(n > d) return 1;

	for(j = n - 1; j >= 0; j--){
		factor[1] = -r[j];
		flag = multPoly(c, j, factor, 1, c, d);
		if(flag) return 1;
	}
    return 0;
}