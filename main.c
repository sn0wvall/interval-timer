#include <stdio.h> 		// Standard IO
#include <stdlib.h> 		// System function
#include <pthread.h>		// Threading
#include <unistd.h>		// usleep()
#include <string.h>		// strcmp()

unsigned int i;
unsigned int j;

pthread_t stopwatch;										// Define Stopwatch Thread
pthread_t crier;										// Define Crier Thread
pthread_t ding;											// Define Ding Thread

unsigned int warmupTime;
unsigned int intervalLength;
unsigned int intervalCount;

unsigned char hoursLeftFormat[] = " ";
unsigned char minutesLeftFormat[] = " ";
unsigned char secondsLeftFormat[] = " ";

unsigned int hoursLeft;
unsigned int minutesLeft; 
unsigned int secondsLeft;
unsigned int intervalsLeft;

unsigned int opt;
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

int main(int argc, char** argv){

	// Define variables
		
	int stopwatchr;
	int crierr;
	int dingr;
  	
	// If no arguments, exit with error

	// Help Message
	if(argc == 2 && strcmp(argv[1], "--help")==0 || strcmp(argv[1], "-h")==0) {
		printf("HELP:\n\
			\r--help, -h: Displays help text\n\
			\r--version, -v: Displays version\n\
			\r--warmup, -w: Set Warmup Time\n\
			\rSYNTAX:\n\
			\rcommand [flags] [interval length][interval count]\n");
		return 0;
	}

	if(argc == 2 && strcmp(argv[1], "--version")==0 || strcmp(argv[1], "-v")==0) {
		printf("1.0\n");
		return 0;
	}
  	
	// Process flags
	while((opt = getopt(argc, argv, "w:")) != -1)  
 	{  
        	switch(opt)  
        	{  
            		case 'w':  
				warmupTime = atoi(optarg);
                		break;  
            		case ':':  
                		printf("option needs a value\n");  
				break;
            		case '?':  
                		printf("unknown option: %c\n", optopt); 
                		break;  
        	}  
    	}  

	// Begin intervals
	
	// Check Length and Count Arguments are present

	if (argc - optind < 2){printf("Please include an interval length and count in your command; see --help for more.\n"); return 2;}

	// Extract Length and Count from remaining arguments	

	intervalLength = atoi(argv[optind]);
	intervalCount = atoi(argv[optind + 1]);

	// Clear console
	printf("\e[?25l");

	// Start Output Threads
	crierr = pthread_create(&crier, NULL, announcer, NULL);						// Spawn Announcer's Crier
	dingr = pthread_create(&ding, NULL, megaphone, NULL);						// Spawn Megaphone's Ding
	
	// Warmup Period

	for (j = warmupTime; j > 0; --j){
		usleep(1000000);
	}

	// Start Timekeeper

	stopwatchr = pthread_create(&stopwatch, NULL, timekeeper, NULL);				// Spawn Timekeeper's Stopwatch

	// Wait for all threads to finish

	pthread_join(stopwatch, NULL);
	pthread_join(crier, NULL);
	pthread_join(ding, NULL);

	printf("\e[?25h");

	return 0;
}
