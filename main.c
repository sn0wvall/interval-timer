#include <stdio.h>

int main(){
	// Define variables
	unsigned int sleep(unsigned int seconds);

	int intervalLength;
	int intervalCount;

	int i;
	int j;

	// User enters length of each interval
	printf("Enter the length in seconds of each interval: ");
	scanf("%d", &intervalLength);
	printf("Interval Length set to: %ds\n", intervalLength);

	// User enters number of intervals to run through
	printf("\nEnter the count of intervals: ");
	scanf("%d", &intervalCount);
	printf("Interval Count set to: %d\n", intervalCount);
	
	// Begin Counting

	for (i = 1; i <= intervalCount; ++i){
		for (j = intervalLength; j > 0; --j){
			printf("\r%d", j);
			fflush(stdout);
			sleep(1);
		}
	}	

	return 0;
}
