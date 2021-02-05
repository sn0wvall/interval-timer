#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function
#include <time.h>		// Clock Timing

// Define functions
unsigned int sleep(unsigned int seconds);
int nanosleep(const struct timespec *req, struct timespec *rem);

int main(){
	// Define variables

	int intervalLength = 60;
	int intervalCount = 1;
   	
	int i;
	int j;
	int minutesLeft;
	int secondsLeft;

	double formatTime;
	int timeSleep;
	
	char minutesLeftFormat[] = " ";
	char secondsLeftFormat[] = " ";

	char intervalRemain[BUFSIZ];

	// User enters length of each interval
	printf("Enter the length in seconds of each interval: \n");
	//scanf("%s", &intervalLength);
	// Validate Input is not over 1 hour
	if (intervalLength > 3599){
		return 1;
	}
	
	// User enters number of intervals to run through
	printf("Enter the count of intervals: \n");
	//scanf("%s", &intervalCount);
	
	// Begin intervals

	// Clear console
	system("clear");

	// Loop through each interval
	for (i = 1; i <= intervalCount; ++i){

		// Loop through each interval time
		for (j = intervalLength; j > 0; --j){
			
			clock_t formatBegin = clock();															// Begin Timing

			system("clear");																// Clear console

			secondsLeft = j;
			minutesLeft = 0;

			minutesLeftFormat[0] = '\0';
			secondsLeftFormat[0] = '\0';

			do {
				if (secondsLeft >= 60 && minutesLeft*60 < secondsLeft){
					minutesLeft++;
					secondsLeft = secondsLeft - 60;
				}
			} while (secondsLeft > 59);

			// Format Numbers

			if (minutesLeft <= 9){
				minutesLeftFormat[0] = '0';
			}
			if (secondsLeft <= 9){
				secondsLeftFormat[0] = '0';
			}
			
			snprintf(intervalRemain, sizeof(intervalRemain), "figlet '%s%d:%s%d'", minutesLeftFormat, minutesLeft, secondsLeftFormat, secondsLeft);		// Parse figlet command
			system(intervalRemain);																// Execute figlet command

			clock_t formatEnd = clock();															// End Timing
			
			formatTime = (double)(formatEnd - formatBegin) / CLOCKS_PER_SEC * 10000000;									// Adjust 1 second for CPU processing time
			timeSleep = 1000000 - formatTime * 2;

			usleep(timeSleep);
		}
	}	

	return 0;
}
