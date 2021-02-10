#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function
#include <pthread.h>		// Threading
#include <unistd.h>		// usleep()

int i;
int j;

pthread_t stopwatch;										// Define Stopwatch Thread
pthread_t crier;										// Define Crier Thread
pthread_t ding;											// Define Ding Thread

unsigned int intervalLength = 5;
unsigned int intervalCount = 2;
unsigned int intervalCountTemp;

unsigned char hoursLeftFormat[] = " ";
unsigned char minutesLeftFormat[] = " ";
unsigned char secondsLeftFormat[] = " ";

unsigned int hoursLeft;
unsigned int minutesLeft; 
unsigned int secondsLeft;
unsigned int intervalsLeft;

unsigned char intervalRemain[BUFSIZ];

// Define Threads

void *timekeeper(void *args) {

	// Loop through each interval
	for (i = 1; i <= intervalCount; ++i){

		// Loop through each interval time
		for (j = intervalLength; j > 0; --j){
			usleep(1000000);
		}
	}	

	// Kill other threads allowing the program to exit
	pthread_cancel(crier);
	pthread_cancel(ding);
	
	return NULL;
}

void *announcer(void *args) {

	for(;;){
		secondsLeft = j;
		usleep(50000);
		// Check Time Change
		if (secondsLeft != j){
			secondsLeft = j;
			minutesLeft = j / 60;
			hoursLeft = minutesLeft / 60;

			hoursLeftFormat[0] = '\0';
			minutesLeftFormat[0] = '\0';
			secondsLeftFormat[0] = '\0';


			if (minutesLeft != 0) {secondsLeft = secondsLeft - 60 * minutesLeft;}
			if (hoursLeft != 0) {minutesLeft = minutesLeft - 60 * hoursLeft;}

			if (hoursLeft < 10) {hoursLeftFormat[0] = '0';}
			if (minutesLeft < 10) {minutesLeftFormat[0] = '0';}
			if (secondsLeft < 10) {secondsLeftFormat[0] = '0';}

			system("clear");

	 		snprintf(intervalRemain, sizeof(intervalRemain), "figlet '%s%d:%s%d:%s%d'", hoursLeftFormat, hoursLeft, minutesLeftFormat, minutesLeft, secondsLeftFormat, secondsLeft);	// Parse figlet
	 		system(intervalRemain);																				// Execute figlet
		}
	}
	return NULL;
}

void *megaphone(void *args) {
	
	for (;;){
		intervalsLeft = i;
		usleep(100000);
		if (intervalsLeft != i){
				system("aplay -q ./ding.wav &");
		}
	}
	
	return NULL;
}

// Define functions

int main(){

	// Define variables
		
	int stopwatchr;
	int crierr;
	int dingr;

	// User enters length of each interval

	//printf("Enter the length in seconds of each interval:");
	//scanf("%d", &intervalLength);

	// User enters number of intervals to run through
	
	//printf("\nEnter the count of intervals:");
	//scanf("%d", &intervalCount);
	
	// Begin intervals

	// Clear console
	printf("\e[?25l");

	// Start Threads

	crierr = pthread_create(&crier, NULL, announcer, NULL);						// Spawn Announcer's Crier
	stopwatchr = pthread_create(&stopwatch, NULL, timekeeper, NULL);				// Spawn Timekeeper's Stopwatch
	dingr = pthread_create(&ding, NULL, megaphone, NULL);						// Spawn Megaphone's Ding

	// Wait for all threads to finish

	pthread_join(stopwatch, NULL);
	pthread_join(crier, NULL);
	pthread_join(ding, NULL);

	//system("aplay -q ./ding.wav &");

	printf("\e[?25h");

	return 0;
}
