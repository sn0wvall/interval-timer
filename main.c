#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function
#include <time.h>		// Clock Timing
#include <pthread.h>		// Threading

// Define Threads

void *timekeeper(void *args) {
	// Loop through each interval
	for (i = 1; i <= intervalCount; ++i){

		// Loop through each interval time
		for (j = intervalLength; j > 0; --j){
			printf("\nintervalLength");
			usleep(1000000);
		}
	}

	return NULL;
}

void *presenter(void *args) {
	return NULL;
}

// Define functions

int main(){

	// Define variables

	unsigned int intervalLength = 5;
	unsigned int intervalCount = 2;

	register int i;
	register int j;
	unsigned int minutesLeft;
	unsigned int secondsLeft;
	
	struct timekeeperArgs {}
	
	int stopwatchr;

	double formatTime;
	unsigned int timeSleep;
	
	unsigned char minutesLeftFormat[] = " ";
	unsigned char secondsLeftFormat[] = " ";

	unsigned char intervalRemain[BUFSIZ];

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
	printf("\e[?25l");
	//system("clear");
	
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

	// Start Timekeeper

	pthread_t stopwatch;

	stopwatchr = pthread_create(&stopwatch, NULL, timekeeper, timekeeperArgs);
	pthread_join(stopwatch, NULL);

	// Loop through each interval
	for (i = 1; i <= intervalCount; ++i){

		// Loop through each interval time
		for (j = intervalLength; j > 0; --j){
			
			clock_t formatBegin = clock();															// Begin Timing

			//system("clear");																// Clear console

			secondsLeft = j;
			minutesLeft = 0;

			minutesLeftFormat[0] = '\0';
			secondsLeftFormat[0] = '\0';

			while (secondsLeft > 59);{
				if (secondsLeft >= 60 && minutesLeft*60 < secondsLeft){
					minutesLeft++;
					secondsLeft = secondsLeft - 60;
				}
			} 
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

	//printf("\e[?25h");

	return 0;
}
