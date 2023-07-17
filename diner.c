#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>
int main(int argc, char * argv[]){
	if(argc != 2){
		printf("You must input the number of patrons!\n");
		exit(-1);
	}
	num_patrons = atoi(argv[1]);

}