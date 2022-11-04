#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <readline/readline.h>
#include <unistd.h>
#include "pqueue.h"
#include <sys/types.h>
#include <sys/time.h>

Customer *queue = NULL;
struct timeval initial_time;

void init_customers(char *file_name) {
    //Initializes our customers by opening the file and reading their data from our textfile
    int num_customers;
    int length_economy = 0;
    int length_business = 0;
    char buff[64];
    int temp_id; //id
    int temp_tc; //travel_class
    int temp_ac; //arrival_time
    int temp_st; //service_time
    FILE *file = fopen(file_name, "r");
    fgets(buff, 64, file);
    num_customers = atoi(buff);
    for(int i = 0; i < num_customers; i++) {
        //Init our customers here
        fgets(buff, 64, file);
        temp_id= atoi(strtok(buff, ":"));
        temp_tc = atoi(strtok(NULL, ","));
        temp_ac = atoi(strtok(NULL, ","));
        temp_st = atoi(strtok(NULL, ","));
        Customer *n = new_customer(temp_id,temp_tc,temp_ac,temp_st);
        printf("A customer arrives: customer ID: %2d. \n", temp_id); 
        queue = enqueue(queue, n);
        if(temp_tc == 1) {
            length_business++;
            printf("A customer enters a queue: the queue ID %1d, their position is number %1d. \n", temp_tc, length_business); //Design doc specifies printing the length of the queue, but I'm not sure if I was supposed to output length prior to them entering, so I changed the output to remove ambiguity. If you want the answer for lenght prior to entry, could just move enum to below print.
        } else {
            length_economy++;
            printf("A customer enters a queue: the queue ID %1d, their position is number %1d. \n", temp_tc, length_economy);
        }
    }
    fclose(file);
}

void dispatch() {
}

int num_customers(char *file_name) {
    char buff[64];
    int num_customers;
    FILE *file = fopen(file_name, "r");
    fgets(buff,64,file);
    num_customers = atoi(buff);
    return num_customers;

}

int main(int argc, char* argv[]){
    //Init
    gettimeofday(&initial_time,NULL);
    int n_customers = num_customers(argv[1]);
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    //Mutex
    //pthread_mutex_init(&customer_mutex[i], NULL);
    //pthread_cond_init(&clerk_ready,NULL);
    if(argc > 1) {
    init_customers(argv[1]);
    } else {
        printf("Invalid input\n");
        return -1;
    }
    print_queue(queue);
}
