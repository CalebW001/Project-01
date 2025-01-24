#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

main(){
	FILE *fptr;
	int min_child = 8;
	int max_child = 13;
	fptr = fopen("seed.txt", "r");
	char string[100];
	fgets(string,100,fptr);
	int seed = atoi(string);
	srand(12345);	//test srand
	//srand(seed);  //real srand
	int counter = 0;
	int random_num = (rand() % (max_child - min_child + 1)) + min_child;
	int randarray[random_num];
	for(int i = 0; i < random_num; i++){
		randarray[i] = rand();
	}
	for(int i = 0; i < random_num; i++){
		int forknum;
		int pid;
		int exitcode;
		forknum = fork();
		if(forknum < 0){ printf("eror with fork");}
		else if(forknum == 0){
			int myvalue = randarray[counter];
                	int code = ((myvalue % 50)+1);
                	int wait = ((myvalue % 3)+1);
			pid = getpid();
			printf("Child Number: %d\n",i);
			printf("PID: %d  ", pid);
			printf("Waits: %d  ", wait);
			printf("Code: %d\n", code);
			printf("Exiting!\n");
			sleep(wait);
			exit(code);
		}
		else{
			waitpid(forknum,&exitcode,0);
			if(WIFEXITED(exitcode)){
				printf("Exited with code: %d\n\n\n", WEXITSTATUS(exitcode));
				counter++;		
				wait();
			}
		}
	}
}
