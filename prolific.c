#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

main(){
	int min_child = 8;
	int max_child = 13;
	unsigned int seed = time(0);
	int random_num = rand_r(&seed) % (max_child - min_child + 1) + min_child;
	for(int i = 1; i <= random_num; i++)
	{
		int j,k;
		if (fork() == 0){
			k=wait();
		exit(0);
}
		printf("Child Number %d\n",i);
		printf("Current Child's PID: %d\n\n",k);
}
}
