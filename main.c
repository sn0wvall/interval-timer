#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function
#include <time.h>		// Clock Timing

// Define functions

int main(){
	// Define variables

	int intervalLength = 5;
	int intervalCount = 2;

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
	//printf("Enter the length in seconds of each interval:");
	//scanf("%d", &intervalLength);

	// Validate Input is not over 1 hour
	if (intervalLength >= 3599) { printf("\nInterval Length is over 3599"); return 1;}	
	
	// User enters number of intervals to run through
	//printf("\nEnter the count of intervals:");
	//scanf("%d", &intervalCount);

	// Begin intervals

	// Clear console
	system("clear");
	printf("\e[?25l");
	
	// Warm Up Period
	// for (j = 10; j >= 0; --j){

	// 		clock_t formatBegin = clock();			// Begin Warmup Timing

	// 		system("clear");				// Clear console
	// 		secondsLeft = j;

	// 		secondsLeftFormat[0] = '\0';

	// 		// Format Seconds

	// 		if (secondsLeft <= 9) { secondsLeftFormat[0] = '0'; }	
			
	// 		snprintf(intervalRemain, sizeof(intervalRemain), "figlet '00:%s%d'", secondsLeftFormat, secondsLeft);						// Parse figlet command
	// 		system(intervalRemain);																// Execute figlet command

	// 		clock_t formatEnd = clock();															// End Timing
			
	// 		formatTime = (double)(formatEnd - formatBegin) / CLOCKS_PER_SEC * 10000000;									// Adjust 1 second for CPU processing time
	// 		timeSleep = 1000000 - formatTime * 2;

	// 		usleep(timeSleep);
	// }

	// system("aplay -q ./ding.wav &");

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

			if (minutesLeft <= 9) { minutesLeftFormat[0] = '0'; }	
			if (secondsLeft <= 9) { secondsLeftFormat[0] = '0'; }	

			snprintf(intervalRemain, sizeof(intervalRemain), "figlet '%s%d:%s%d'", minutesLeftFormat, minutesLeft, secondsLeftFormat, secondsLeft);		// Parse figlet command
			system(intervalRemain);																// Execute figlet command

			clock_t formatEnd = clock();															// End Timing
			
			timeSleep = 1000000 - (double)(formatEnd - formatBegin) / CLOCKS_PER_SEC * 10000000 * 3;							// Adjust 1 second for CPU processing time

			usleep(timeSleep);
		}

	system("aplay -q ./ding.wav &");

	}	

	return 0;
}
