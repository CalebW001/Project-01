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

    //locals
    int currentID;
    char directories[6][10] = {"/home", "/proc", "/proc/sys", "/usr", "/usr/bin", "/bin"};
    char selection[50];
    char directory[50];
    int exitcode;

    printf("It's time to see the world/file system!\n");
    for(int i = 0; i < 5; i++){

        *selection = directories[rand() % 6]; //randomly select file path using rand()
        chdir(selection); //change file path to the randomly selected one
        *directory = cwd(); //capture current working directory
        printf("Selection #%d: %s", i+1, selection);

        //check if the change in directory worked
        if(strcmp(selection, directory) == 0){
            printf(" [SUCCESS]\n");
        } else {
            printf(" [FAILURE]\n");
        }

        printf("Current reported directory: %s", directory);

        currentID = fork();
        
        if(currentID == 0){ //child process
            printf("[Child, PID: %d]: Executing 'ls -tr' command...", getpid());
            char* argv[] = {"ls", "-tr", NULL};
            if(execvp("ls", argv) == -1){
                exit(-1);//exits with status -1 if command fails
            }
            exit(0); //exits with status 0 if command runs correctly
            
        } else { //parent process
            printf("[Parent]: I am waiting for PID %d to finish.\n", currentID);
            waitpid(currentID, &exitcode, 0); //wait for child to finish and collect exit code

            exitcode = WEXITSTATUS(exitcode); //decode manual exit code
            if(exitcode != 0){//if child status is not 0 then it failed, and parent exits
                printf("[Parent]: Child %d failed with status code %d. Exiting.", currentID, exitcode);
                exit(0);
            }
            printf("[Parent]: Child %d finished with status code %d. Onward!", currentID, exitcode);
        }

    }
}