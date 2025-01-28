#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]){
int max_time = 6;
int min_time = 2;
int test = 0;
FILE *fptr;
if(strcmp(argv[1],"1") == 0){
fptr = fopen("seed_slug_1.txt", "r");
}
else if(strcmp(argv[1],"2") == 0){
fptr = fopen("seed_slug_2.txt", "r");
}
else if(strcmp(argv[1],"3") == 0){
fptr = fopen("textttseed_slug_3.txt", "r");
}
else if(strcmp(argv[1],"4") == 0){
fptr = fopen("seed_slug_4.txt", "r");
}

char string[100];
fgets(string,100,fptr);
int seed = atoi(string);
srand(seed); //real srand
//srand(12345); //test srand

int seconds = (rand() % (max_time - min_time + 1)) + min_time;
printf("Waiting for: %d\n", seconds);
sleep(seconds);
int coin_flip = (rand() % (1 - 0 + 0)) + 0;
printf("Coin Flip: %d\n", coin_flip);

if(coin_flip == 0){
    char cmd[100];
    strcpy(cmd,"last -i -x");
    system(cmd);
}
else{
    char cmd[100];
    strcpy(cmd,"id --group");
    system(cmd);
}

return 0;
}