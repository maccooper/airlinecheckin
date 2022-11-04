/*
 * pqueue.c
 * Priority Queue implementation using Linked List, built upon the LL from Assignment 1 csc360 Fall 2022
*/

#include "pqueue.h"

Customer *new_customer(int id, int travel_class, int arrival_time, int service_time) {
    Customer *temp = (struct Customer*)malloc(sizeof(struct Customer));
	temp->id = id;
	temp->travel_class = travel_class;
	temp->arrival_time = arrival_time;
    temp->service_time = service_time;
	temp->next = NULL;
	return temp;
}

Customer *enqueue(Customer *list, Customer *new) {
    if (list == NULL) {
        //Validate list is nonempty
		new->next = NULL;
		return new;
	}
	Customer *curr;
    Customer *prev = NULL;
	for (curr = list; curr->next!=NULL; curr = curr->next) {
        if(new->travel_class > curr->travel_class) { 
            new->next = curr;
            if(prev == NULL) {
                list = new;
            } else {
                prev->next = new;
            }
            return list;
        }
        prev = curr;
    }
    curr->next = new;
    new->next = NULL;
	return list;
}

void dequeue(Customer *list) {
    //Remove customer from the front of the queue
    Customer *temp = list;
    *list = *list->next;
    free(temp);

}

int is_empty(Customer *list) {
    return (list == NULL);
}

void print_queue(Customer *head) {
    Customer *curr = head; 
    int queue_length = 0;
    while (curr != NULL) { 
        queue_length++;
        printf("id:%i\ttc:%i\tat:%i\tst:%i\n", curr->id,curr->travel_class,curr->arrival_time,curr->service_time);
        curr = curr->next;
    }
}

void free_queue(Customer *head) {
	//Input: any allocated List
	//Output:	None
	//Frees memory for an entire list
	Customer *temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
}
