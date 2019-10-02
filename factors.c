/* 
*
* Read an integrer value from the user and print the factors
* T. Lee 9/1/2017 
*
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	/* print the prompt and save the value */
	printf("Enter an integer number: ");
	int value, i;
	scanf("%d", &value);
	
	/* print the factors prompt and factors */
	printf("The factors for %d are: \n", value);
	for(i = 1; i <= value; i += 1){
		if(!(value % i)) /* check if i goes into value evenly */
			printf("%d ", i); /* print factors + space */
	}

	return EXIT_SUCCESS;
}
