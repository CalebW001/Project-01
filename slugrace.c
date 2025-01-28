#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(){
    FILE *file = fopen("seed.txt", "r"); //begin reading from seed.txt for rand() seeds

    char current_seed[50];

    //in the case that a file is missing, check if fgets() returns NULL
    while(fgets(current_seed, sizeof(current_seed), file) != NULL){
        int seed = atoi(current_seed);
        srand(seed);
        printf("Read seed value (converted to integer): %d\n", seed);
    }

    int currentID;
    char* parameter;
    int timestamps[4]; 
    
    for(int i = 0; i < 4; i++){
        currentID = fork(); //start child process 
        timestamps[i] = clock_gettime(); //get timestamp

        if(currentID == 0){//if process is a child
            parameter = itoa(i+1); 
            char* argv[] = {"slug", parameter, NULL}; //build command line args
            if (execvp("slug", argv) == -1){
                printf("Slug initiation failed"); //execute slug.c with built args
            }
            exit(i); //give exitcode related to iteration # to tell parent process which process finished 
            //(also exits before iteration to avoid grandchildren)
        }
    }//only parent iterates through loop
    while(){
        //check if any children have exited/finished
        //if child exited, print that it finished and info on how long it took
        //check next child
        //if haven't exited,
        //wait .33 seconds
        //print slugs that are still currently racing
    }
}