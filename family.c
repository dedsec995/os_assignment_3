#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>
#include<unistd.h>
unsigned int num_family_members;
int main(int argc, char * argv[]){
	if(argc != 2){
		printf("You must input the number of family members!\n");
		exit(-1);
	}
	num_family_members = atoi(argv[1]);
}