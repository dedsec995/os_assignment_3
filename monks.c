#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <assert.h>
#include <semaphore.h>
unsigned int num_mugs;
unsigned int num_kegs;
int main(int argc, char * argv[]){
	if(argc != 3){
		printf("You must input number of mugs per keg and number of kegs\n");
		exit(-1);
	}
	num_mugs = atoi(argv[1]);
	num_kegs = atoi(argv[2]);
}