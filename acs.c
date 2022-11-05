#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <readline/readline.h>
#include <unistd.h>
#include "pqueue.h"
#include <sys/types.h>
#include <sys/time.h>


#define SCALE 10000
#define CLERKS 5

Customer *queue = NULL;
Customer customer_list[64];

struct clerk_info {
    int clerk_id;
};

struct timeval init_time;
pthread_mutex_t mqueue;
int len[] = {0,0}; //Stores the length of our queues
                   
void init_customers(char *file_name) {
    //Initializes our customers by opening the file and reading their data from our textfile
    int num_customers;
    char buff[64];
    int temp_id; //id
    int temp_tc; //travel_class
    int temp_at; //arrival_time
    int temp_st; 
    FILE *file = fopen(file_name, "r");
    fgets(buff, 64, file);
    num_customers = atoi(buff);
    for(int i = 0; i < num_customers; i++) {
        //Init our customers here
        fgets(buff, 64, file);
        temp_id = atoi(strtok(buff, ":"));
        temp_tc = atoi(strtok(NULL, ","));
        temp_at = atoi(strtok(NULL, ","));
        temp_st = atoi(strtok(NULL, ","));
        if(temp_id < 0 || temp_tc < 0 || temp_at < 0 || temp_st < 0) {
            printf("negative value in input file\n");
            exit(-1);
        }
        customer_list[i].id = temp_id;
        customer_list[i].travel_class = temp_tc;
        customer_list[i].arrival_time = temp_at;
        customer_list[i].service_time = temp_st;
    }
    fclose(file);
}

int fetch_time() {
    //Calculates simulation time
    struct timeval curr_time;
    gettimeofday(&curr_time, NULL);
    int start = (init_time.tv_sec * SCALE) + init_time.tv_usec;
    int curr = (curr_time.tv_sec * SCALE) + curr_time.tv_usec;
    return (curr - start) / SCALE;
}

void *customer_t_worker(void *p) {
    Customer *person = (Customer *)p;
    //Functionality for customer handled:
    //service time   
    usleep(person->arrival_time * SCALE);
    printf("A customer arrives: customer ID %2d\n",person->id);
    pthread_mutex_lock(&mqueue);
        queue = enqueue(queue,person);
        printf("A customer enters a queue: the queue ID %1d, and length of the queue %2d.\n", person->travel_class, len[person->travel_class]);
        len[person->travel_class]++;
    pthread_mutex_unlock(&mqueue);
    pthread_exit(NULL);
    
}

void *clerk_t_worker(void *clerk_id) {
    struct clerk_info *clerk = (struct clerk_info *)clerk_id;
    int c_id = clerk->clerk_id;
    while(!is_empty(queue)) {
        pthread_mutex_lock(&mqueue);
        //Consume
        pthread_mutex_lock(&mqueue);
    }
    
    pthread_exit(NULL);
    
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
    if(argc > 1) {
    init_customers(argv[1]);
    } else {
        printf("Invalid input\n");
        return -1;
    }
    gettimeofday(&init_time,NULL);
    int n = num_customers(argv[1]);
    pthread_t customer_threads[n];
    pthread_t clerk_threads[CLERKS];
    struct clerk_info clerks[CLERKS];

    for(int i = 0; i < n; i++) {
        //Initialize Customer threads
        pthread_create(&customer_threads[i], NULL, customer_t_worker, (void *)&customer_list[i]);
    }
    for(int i = 0; i < CLERKS; i++) {
        //Initialize Clerk threads
        pthread_create(&clerk_threads[i], NULL, clerk_t_worker, &clerks[i]);
    }
    for(int i = 0; i < n; i++) {
        pthread_join(customer_threads[i],NULL);
    }
    pthread_exit(NULL);
    print_queue(queue);
    free_queue(queue);
}
