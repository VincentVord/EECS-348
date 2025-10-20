// EECS 348 Assignment 5
// Email Priority queue using a Maxheap with a list-based implementation. This is a recreation of Assingment 1 in C using the function-oriented design paradigm.
// Inputs: test file labeled test.txt
// Output: Next email and number of unread emails
// Collaborators: None
// My Assignment1.py file, w3schools, stackoverflow, ChatGPT
// Vincent Vordtriede
// 10/19/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//====Structs====//

typedef struct { //define the Email struct type -- chatgpt suggested that I could use structs to act as as the classes I had in assingment 1, and I can have functions that access the maxheap and email structs using pointers
    char sender_category[32];
    char subject_line[128];
    char date[16];
    int priority_number;
    char formatted_date[9]; // YYYYMMDD + '\0'
} Email;

typedef struct { //define the Maxheap struct type
    Email *heap; //create a pointer called heap that can point to Email structs
    int size;
    int capacity;
} MaxHeap;


//====Function prototypes====//

int compare_email(const Email *a, const Email *b);

//====MaxHeap functions====//

//reminder:
// pointer->struct_method = 
// (*pointer).struct_method

void maxheap_init(MaxHeap *h, int capacity) {
    h->heap = malloc(sizeof(Email) * capacity); //allocates the correct amount of memory to the maxheap
    h->size = 0;
    h->capacity = capacity;
}

int maxheap_count(MaxHeap *h) { //function for returning the size of the maxheap (how many emails there currently are)
    return h->size;
}

void swap(Email *a, Email *b) { //define the logic for swapping two email index values
    Email temp = *a;
    *a = *b;
    *b = temp;
}

void upheap(MaxHeap *h, int index) {
    if (index == 0) {
        return;
    } 
    int parent = (index - 1) / 2; //define parent index

    if (compare_email(&h->heap[parent], &h->heap[index]) < 0) { //if the parent is less than the child index (compare_email will return a negative number)
        swap(&h->heap[parent], &h->heap[index]); //swap the values of the parent and child indices
        upheap(h, parent); //recursively call upheap again
    }
}

void downheap(MaxHeap *h, int index) {
    int left = 2 * index + 1; //define the left child index
    if (left >= h->size) { //if the left child's index is out of range...
        return; //do nothing
    }
    int right = left + 1; //define the right child index
    int largest = left; //initialize the largest index to the left

    if (right < h->size && compare_email(&h->heap[left], &h->heap[right]) < 0) //if the right index is in bounds and the left index is is less than the right index...
        largest = right; //the right index is now the largest

    if (compare_email(&h->heap[index], &h->heap[largest]) < 0) { //if the current index is less than the larger index...
        swap(&h->heap[index], &h->heap[largest]); //swap thwe values
        downheap(h, largest); //and recursively call downheap
    }
}

void maxheap_add(MaxHeap *h, Email entry) {
    if (h->size >= h->capacity) { //if the heap size is over the capacity
        h->capacity *= 2; //double the capacity
        h->heap = realloc(h->heap, sizeof(Email) * h->capacity); //allocate more memory to store additional emails
    } //otherwise...
    h->heap[h->size] = entry; //add the entry to the last index of the list
    h->size++; //increment the maxheap size by one
    upheap(h, h->size); //upheap starting at the last index of the list
}

Email maxheap_remove(MaxHeap *h) {
    if (h->size == 0) {
        printf("Heap empty\n");
        Email empty = {0}; //empty struct
        return empty;
    }
    Email root = h->heap[0]; //declare an email struct called root which is mapped to the first element in the heap list
    h->heap[0] = h->heap[h->size - 1]; //assign the list entry of the heap list to the root
    h->size--; //decrement the size of the heap list by 1
    downheap(h, 0); //call downheap at the new root index (0)
    return root; //return the value of the new root
}

Email *maxheap_peek(MaxHeap *h) {
    if (h->size == 0){ //if the heap list is empty
        return NULL; //return null
    }
    return &h->heap[0]; //otherwise return the email at the beginning of the list (the root)
}


//====Email Functions====//

Email create_email(const char *sender, const char *subject, const char *date) {
    Email email; //create instance of the Email struct
    strncpy(email.sender_category, sender, sizeof(email.sender_category)-1); //copies the sender to the email struct
    email.sender_category[sizeof(email.sender_category)-1] = '\0'; //ensure that the sender category is null termianted

    strncpy(email.subject_line, subject, sizeof(email.subject_line)-1); //copies the subject to the email struct
    email.subject_line[sizeof(email.subject_line)-1] = '\0'; //ensure that the subject line is null termianted

    char temp[16]; //create temp string
    strncpy(temp, date, sizeof(temp)-1); //copy the input date to the temp string
    temp[sizeof(temp)-1] = '\0'; //ensure that the temp string is null terminated

    char *month = strtok(temp, "-"); // Split the string using strtok
    char *day   = strtok(NULL, "-");
    char *year  = strtok(NULL, "-");

    char formatted_date[9] = ""; //create empty string will null terminator
    strcat(formatted_date, year); //concatenate the YYYY first
    strcat(formatted_date, month); //then MM
    strcat(formatted_date, day); //then DD (now it is in the format YYYYMMDD)

    strncpy(email.formatted_date, formatted_date, sizeof(email.formatted_date)-1); //copies the date to the email struct

    if (strcmp(sender, "Boss") == 0) { //strcmp returns 0 if two strings are the same
        email.priority_number = 5;
    } else if (strcmp(sender, "Subordinate") == 0) {
        email.priority_number = 4;
    } else if (strcmp(sender, "Peer") == 0) {
        email.priority_number = 3;
    } else if (strcmp(sender, "ImportantPerson") == 0) {
        email.priority_number = 2;
    } else if (strcmp(sender, "OtherPerson") == 0) {
        email.priority_number = 1;
    }

    return email;
}

int compare_email(const Email *a, const Email *b) {
    if (a->priority_number != b->priority_number)
        return a->priority_number - b->priority_number;
    return strcmp(a->formatted_date, b->formatted_date);
}

//====main function====//

int main() {
    MaxHeap priorityqueue;
    maxheap_init(&priorityqueue, 10); //setting the capacity of the priority queue to 10 emails

    FILE *file; //create a file pointer called file
    file = fopen("test.txt", "r"); //file points to the text file

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; //strspn finds the first occurance of the newline and then it is replaced with a null terminator
        if (strncmp(line, "EMAIL", 5) == 0) { //search the first 5 characters of the line for 'EMAIL'
            char temp[256];

            strncpy(temp, line, sizeof(temp)-1); //copy the input date to the temp string
            temp[sizeof(temp)-1] = '\0'; //ensure that the temp string is null terminated

            char *sender = strtok(temp, ","); // Split the string using strtok
            char *subject   = strtok(NULL, ",");
            char *date  = strtok(NULL, ",");

            Email email = create_email(sender, subject, date); 
            maxheap_add(&priorityqueue, email);

        } else if (strcmp(line,"COUNT") == 0) {
            int count = maxheap_count(&priorityqueue);
            printf("There are %d emails to read.\n", count);

        } else if (strcmp(line,"NEXT") == 0) {
            Email *next = maxheap_peek(&priorityqueue);
            if (maxheap_count(&priorityqueue) > 0) {
                printf("Next email:\n");
                printf("\tSender: %s\n\tSubject: %s\n\tDate: %s", next->sender_category, next->subject_line, next->date);
            } else {
                printf("No emails to read.\n");
            }
        } else if (strcmp(line,"READ") == 0) {
            if (maxheap_count(&priorityqueue) > 0) {
                maxheap_remove(&priorityqueue);
            } else {
                printf("No emails to read.\n");
            }
        }
    }

    fclose(file); //close the file
    free(priorityqueue.heap); //free the memory allocated by the heap
    return 0; //end main
}
