#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(){
    FILE *file = fopen("seed.txt", "r");
    char current_seed[50];
    while(fgets(current_seed, sizeof(current_seed), file) != NULL){
        srand(current_seed);
    }
    int lifespan = (rand() % 8) + 5;
    int exitcode = -1;
    printf("Time to mee the kids/grandkids/great grandkids/...\n");
    while(lifespan > 0){
        int ID = fork();
        if(ID == 0){
            printf("[Child, PID: %d]: I was called with descendant count=%d. I'll have %d descendant(s).\n", getpid(), lifespan, lifespan-1);
        } else {
            printf("[Parent, PID: %d]: I am waiting for PID %d to finish.\n", getpid(), ID);
            waitpid(ID, &exitcode, 0);
            printf("[Parent, PID: %d]: Child %d finished with status code %d. It's now my turn to exit.\n", getpid(), ID, WEXITSTATUS(exitcode));
            exitcode = WEXITSTATUS(exitcode);
            exit(++exitcode);
        }
        lifespan--;
    }
    exit(++exitcode);

}
