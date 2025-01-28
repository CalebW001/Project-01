#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define SLUGS_NUM 4
#define DELAY 330000



int main(){
    FILE *file = fopen("seed.txt", "r"); //begin reading from seed.txt for rand() seeds

    char current_seed[50];
    int status[SLUGS_NUM] = {0};
    pid_t pids[SLUGS_NUM];
    struct timespec start_time, end_time;

    //in the case that a file is missing, check if fgets() returns NULL
    while(fgets(current_seed, sizeof(current_seed), file) != NULL){
        int seed = atoi(current_seed);
        srand(seed);
        printf("Read seed value (converted to integer): %d\n", seed);
    }

    char* parameter;
    int timestamps[4]; 
    clock_gettime(CLOCK_MONOTONIC, &start_time); //get timestamp
    
    for(int i = 0; i < SLUGS_NUM; i++){
        pids[i] = fork(); //start child process 
        

        if(pids[i] == 0){//if process is a child
            parameter = (char*)malloc(10 * sizeof(char));
            snprintf(parameter, sizeof(parameter), "%d", i + 1);
            char* argv[] = {"./slug", parameter, NULL}; //build command line args
             if (execvp(argv[0], argv) == -1) {
                perror("Slug initiation failed");
            }
            exit(i); //give exitcode related to iteration # to tell parent process which process finished 
            //(also exits before iteration to avoid grandchildren)
        }
    }//only parent iterates through loop
    int finished = 0;
    while( finished < SLUGS_NUM){
        for(int i = 0; i < SLUGS_NUM; i++){
            if(status[i] == 0){
                pid_t result = waitpid(pids[i], NULL, WNOHANG);
                if(result == pids[i]){
                    //process finished
                    clock_gettime(CLOCK_MONOTONIC, &end_time);
                    long sec = end_time.tv_sec - start_time.tv_sec;
                    long msec = end_time.tv_nsec - start_time.tv_nsec;

                    if (msec < 0) {
                        msec += 1000000000;
                        sec--;
                    }

                    //convert nanoseconds to milliseconds
                    msec = msec / 1000000;
                    printf("Slug %d finished! Time elapsed: %d seconds and %d milliseconds.\n", i+1, sec, msec);
                    status[i] = 1;
                    finished++;
                    if(finished == SLUGS_NUM){
                        printf("The Race Finished! It last %d seconds and %d miliseconds!\n", sec, msec);
                    }
                }
            }        
        }

        if(finished < SLUGS_NUM){
            printf ("Racing Slugs: ");
            for(int i = 0; i < SLUGS_NUM; i++){
                if (status[i] == 0){
                    printf("Slug %d ", i+1);
                }
            }
            printf("\n");
            usleep(DELAY);
        }
        //check if any children have exited/finished
        //if child exited, print that it finished and info on how long it took
        //check next child
        //if haven't exited,
        //wait .33 seconds
        //print slugs that are still currently racing
    }

    return 0;
}