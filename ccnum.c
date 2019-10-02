/* 
*
*  The program will check the validity of a 16-digit credit card number, using the Luhn Algorithm.
*  It will also be able to calculate the final digit should it be given the first 15-digits only.
*
*  T. Lee, 15 September 2017
*/

#include <stdio.h>
#include <stdlib.h>

int main() {

	/* intializae variables */
  char c;
	int value, check, count, temp;

  printf("Enter number, or 'q' to quit:\n");  /* prompt the user */
    
	while(1) { /* repeat until break */
	
		/* reset variables */
		check = -1;
		value = 0;
		count = 0;

		c = getchar();/* wait for user input */
		
		while(c != '\n' ) { /* check all characters entered */
			if(count == 0 && c == 'q') { /* check for q being the first digit */
				return EXIT_SUCCESS;
			}
			else if(count == 15 && c == 'x') { /* check if x is the 16th digit */
				count++;
			}
			else if(c == 32) { /* check for spaces in number */
				;
			}
			else if(c < '0' || c > '9') { /* check for illegal characters in number */
				while(c != '\n'  || c == 32) c = getchar(); /* get rid of everything after an illegal character */
				c = 'b';
				break;
			} 
			else if(count == 15) { /* check for checksum digit */
				value += c - 48;
				count++;
				check = c - 48;
			} 
			else if(count & 1) { /* add number to checksum */
				count++;
				value += c - 48;
			}
			else { /* add double the number to checksum */
				count++;
				temp = 2 * (c - 48);
				if(temp >= 10) temp -= 9;
				value += temp;
			}
      c = getchar(); /* load next digit */
    }
    if(count != 16) { /* check for 16 valid digits only */
			printf("  bad\n");
		}
    else if(c == 'b') { /* check for failed validity */
			printf("  bad\n");
		}
    else if(check != -1) { /* check and print validity */
      int temp = 10 - ((value - check) % 10);
      if(temp == 10) temp = 0;
      if(temp == check) printf("  ok\n");
      else printf("  bad\n");
    }
    else { /* calculate checksum value */
      check = 10 - (value % 10);
      if(check == 10) check = 0;
      printf("  %d\n", check);
    }
  }
}
/* Last Edited September  6, 2017 @  6:00pm */
/* Last Edited September  8, 2017 @  1:00pm */
/* Last Edited September 11, 2017 @  6:00pm */
