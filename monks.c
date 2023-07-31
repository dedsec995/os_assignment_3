#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <assert.h>
#include <semaphore.h>
unsigned int num_mugs;
unsigned int num_kegs;
unsigned int servings_left; // To keep track of the remaining servings in the current keg

sem_t keg_available; // Semaphore to check if a keg is available
pthread_mutex_t monk_mutex; // Mutex to protect shared variables and critical sections

// Function to represent drinking beer
void drink() {
    // Simulating drinking time
    usleep(rand() % 100);
}

// Function to represent fetching a new keg
void fetch_new_keg() {
    // Simulating time taken to fetch a new keg
    usleep(rand() % 1000);
}

// Function for a monk thread
void *monk_thread(void *monk_id) {
    int monk_num = *(int *)monk_id;
    int drank_mugs = 0;

    while (drank_mugs < num_mugs * num_kegs) {
        sem_wait(&keg_available); // Wait for a keg to be available

        pthread_mutex_lock(&monk_mutex);
        if (servings_left == 0) {
            printf("Monk #%d fetched a new keg.\n", monk_num);
            fetch_new_keg();
            servings_left = num_mugs;
        }
        printf("Monk #%d drank!\n", monk_num);
        drank_mugs++;
        servings_left--;
        pthread_mutex_unlock(&monk_mutex);

        drink();
    }

    printf("Monk #%d drank %d mugs of beer\n", monk_num, drank_mugs);
    return NULL;
}

int main(int argc, char * argv[]){
	if(argc != 3){
		printf("You must input number of mugs per keg and number of kegs\n");
		exit(-1);
	}
	num_mugs = atoi(argv[1]);
	num_kegs = atoi(argv[2]);
	pthread_t monks[10];
    int monk_ids[10];

    servings_left = 0;

    sem_init(&keg_available, 0, num_kegs); // Initialize the keg semaphore
    pthread_mutex_init(&monk_mutex, NULL); // Initialize the monk mutex

    for (int i = 0; i < 10; i++) {
        monk_ids[i] = i + 1;
        pthread_create(&monks[i], NULL, monk_thread, &monk_ids[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(monks[i], NULL);
    }

    sem_destroy(&keg_available);
    pthread_mutex_destroy(&monk_mutex);

    return 0;
}