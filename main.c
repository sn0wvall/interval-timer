#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function

// Define functions
unsigned int sleep(unsigned int seconds);

int main(){
	// Define variables

	int intervalLength = 70;
	int intervalCount = 2;
   	
	int i;
	int j;
	int minutesLeft;
	int secondsLeft;
	char intervalRemain[BUFSIZ];

	// User enters length of each interval
	printf("Enter the length in seconds of each interval: ");
	//scanf("%s", &intervalLength);
	// Validate Input is not over 1 hour
	if (intervalLength > 3599){
		return 1;
	}
	printf("Interval Length set to: %ds\n", intervalLength);
	
	// User enters number of intervals to run through
	printf("\nEnter the count of intervals: ");
	//scanf("%s", &intervalCount);
	printf("Interval Count set to: %d\n", intervalCount);
	
	// Begin intervals

	// Clear console
	system("clear");

	// Loop through each interval
	for (i = 1; i <= intervalCount; ++i){

		// Loop through each interval time
		for (j = intervalLength; j > 0; --j){
			secondsLeft = j;
			minutesLeft = 0;
			do {
				if (secondsLeft >= 60 && minutesLeft*60 < secondsLeft){
					minutesLeft++;
					secondsLeft = secondsLeft - 60;
				}
			} while (secondsLeft > 59);
			snprintf(intervalRemain, sizeof(intervalRemain), "figlet '%d:%d'", minutesLeft, secondsLeft);			// Parse figlet command
			system(intervalRemain);												// Execute figlet command
			sleep(1);									
			system("clear");												// Clear console
		}
	}	

	return 0;
}
