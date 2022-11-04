/* pqueue.h
 * Header file for a Priority Queue class
 * Using Linked List data structure to record members of the queue'
*/

#ifndef _PQUEUE_H_
#define __PQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Customer {
	int id;
	int travel_class;
	int arrival_time;
    int service_time;
	struct Customer *next;
} Customer;

Customer *new_customer(int id, int travel_class, int arrival_time, int service_time);
Customer *enqueue(Customer *list, Customer *new);
void dequeue(Customer *list);
int is_empty(Customer *list);
void print_queue(Customer *head);
void free_queue(Customer *head);

#endif
