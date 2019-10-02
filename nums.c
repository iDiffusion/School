/* 
*
*  This program will convert a base-N number, where N ranges from 2 to 36,
*	 to decimal, hexadecimal and binary. 
*
*  T. Lee, 4 June 2018
*/

#include <stdio.h>
#include <stdlib.h>

int main() {

	/* intializae variables */
	int base, number, val, flag;
	char c;
	
	while(1) { /* repeat until break */
	
		/* reset variables */
		base = 0;
		
		/* print prompt for base */
		printf ("Enter the base (2-36, 0 to quit): ");
		
		/* scan charactes in for base number */
		do { 
			scanf ("%c", &c);
			if(c >= '0' && c <= '9') {
				base = (base * 10); 
				base += (c - 48);
			}
		} while(c != '\n');
		
		/* check if user desire to quit */
		if(base == 0) { 
			return EXIT_SUCCESS;
		}
		/* check if valid base */
		else if(base < 2 || base > 36){ 
			continue;
		}
		
		/* resest variables */
		flag = 0;
		number = 0;

    /* print prompt for number */
		printf ("Enter the base %d value: ", base);
		scanf ("%c", &c);
		do {
			/* calculate character value */
			if(c >= '0' && c <= '9') {
				val = c - 48;
			} 
			else if(c >= 'a' && c <= 'z') {
				val = c - 97 + 10;
			} 
			else if(c >= 'A' && c <= 'Z') {
				val = c - 65 + 10;
			}
			else if(c == '\n') {
				flag = 32;
			}
			else {
				flag = flag == 0 ? c : flag;
			}
			
			/* check if the value of the character is too big */
			if(val >= base){
				flag = flag == 0 ? c : flag;
			}
			/* perform base math to obtain decimal value */
			else {
				number = number * base + val;
			}
	
			/* scan in next character */
			scanf ("%c", &c);
		} while(c != '\n');
		
		/* check if input was valid */
		if(flag != 0){ 
			printf ("Bogus character %c -- value ignored.\n", flag);	
		}
		/* check if decmail number is to big */
	  else if(number > 65536 || number < -65536){ 
			printf("ERROR: value out of range\n");
		}
		/* print decimal, hexadecimal and binary to console */
		else {
			/* print decimal value */
			printf ("Decimal: %d\n", number);
			
			/* print hexadecimal value */
			printf ("Hexadecimal: 0x%x\n", number);
			
			/* print binary value */
			printf ("Binary: ");
			val = 65536;
			while(val != 1){
				printf ("%d", (number & val) > 0 ? 1: 0);
				val /= 2;
			}
			printf ("%d\n", (number & val) > 0 ? 1: 0);
		}
	}
}