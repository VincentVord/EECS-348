// EECS 348 Assignment 5
// Email Priority queue using a Maxheap with a list-based implementation. This is a recreation of Assingment 1 in C using the function-oriented design paradigm.
// Inputs: test file labeled Assignment5_Test_File.txt,
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
    char sender_category[32]; // allocate a sender array - up to 32 chars
    char subject_line[128]; //allocate a subject array - up to 128 characters
    int priority_number; //allocate a priority number int
    char date[11]; // MM-DD-YYYY + '\0'
    char formatted_date[9]; // YYYYMMDD + '\0'
} Email; //name of the struct

typedef struct { //define the Maxheap struct type
    Email *heap; //create a pointer called heap that can point to Email structs
    int size; //allocate a size int
    int capacity; //allocate a capacity int
} MaxHeap; //name of the struct


//====Function prototypes====//

int compare_email(const Email *a, const Email *b); //create this prototype here so that the compiler sees it before it is used in the maxheap functions

//====MaxHeap functions====//

//reminder:
// pointer->struct_method = 
// (*pointer).struct_method

void maxheap_init(MaxHeap *h, int capacity) { //maxheap init function takes in a maxheap pointer and a capacity
    h->heap = malloc(sizeof(Email) * capacity); //allocates the correct amount of memory to the maxheap
    h->size = 0; //initialize the starting size to 0
    h->capacity = capacity; //initialize the starting capacity to the input capacity
}

int maxheap_count(MaxHeap *h) { //function for returning the size of the maxheap (how many emails there currently are)
    return h->size; //return the size of the maxheap
}

void swap(Email *a, Email *b) { //define the logic for swapping two email index values
    Email temp = *a; //store the first email as temp
    *a = *b; //set first email to second email's value
    *b = temp; //set sencond email to first email's value
}

void upheap(MaxHeap *h, int index) { //maxheap upheap function takes in an index
    if (index == 0) { //if it is 0
        return; //you cannot upheap any more
    } 
    int parent = (index - 1) / 2; //define parent index

    if (compare_email(&h->heap[parent], &h->heap[index]) < 0) { //if the parent is less than the child index (compare_email will return a negative number)
        swap(&h->heap[parent], &h->heap[index]); //swap the values of the parent and child indices
        upheap(h, parent); //recursively call upheap again
    }
}

void downheap(MaxHeap *h, int index) { //maxheap downheap function takes in an index
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

void maxheap_add(MaxHeap *h, Email entry) { //maxheap add function takes in an entry
    if (h->size >= h->capacity) { //if the heap size is over the capacity
        h->capacity *= 2; //double the capacity
        h->heap = realloc(h->heap, sizeof(Email) * h->capacity); //allocate more memory to the pre-existing heap to store additional emails
    } //otherwise...
    h->heap[h->size] = entry; //add the entry to the last index of the list
    h->size++; //increment the maxheap size by one
    upheap(h, h->size-1); //upheap starting at the last index of the list (has to be -1 because size just got incremented)
}

Email maxheap_remove(MaxHeap *h) { //define the maxheap remove function
    if (h->size == 0) { //if the size is 0
        printf("Heap empty\n"); //print that the heap is empty
        Email empty = {0}; //empty struct
        return empty; // return the empty struct
    } //otherwise...
    Email root = h->heap[0]; //declare an email struct called root which is mapped to the first element in the heap list
    h->heap[0] = h->heap[h->size - 1]; //assign the list entry of the heap list to the root
    h->size--; //decrement the size of the heap list by 1
    downheap(h, 0); //call downheap at the new root index (0)
    return root; //return the value of the new root
}

Email *maxheap_peek(MaxHeap *h) { //define the peek function
    if (h->size == 0){ //if the heap list is empty
        return NULL; //return null
    }
    return &h->heap[0]; //otherwise return the email at the beginning of the list (the root)
}


//====Email Functions====//

Email create_email(const char *sender, const char *subject, const char *date) { //function for generating the emails in the struct form
    Email email; //create instance of the Email struct
    strncpy(email.sender_category, sender, sizeof(email.sender_category)-1); //copies the sender to the email struct
    email.sender_category[sizeof(email.sender_category)-1] = '\0'; //ensure that the sender category is null termianted

    strncpy(email.subject_line, subject, sizeof(email.subject_line)-1); //copies the subject to the email struct
    email.subject_line[sizeof(email.subject_line)-1] = '\0'; //ensure that the subject line is null termianted

    strncpy(email.date, date, sizeof(email.date)-1); //copies the date  tp the email struct

    char temp[16]; //create temp string
    strncpy(temp, date, sizeof(temp)-1); //copy the input date to the temp string for parsing
    temp[sizeof(temp)-1] = '\0'; //ensure that the temp string is null terminated

    char *month = strtok(temp, "-"); // Split the string using strtok, stire the first part as the month
    char *day   = strtok(NULL, "-"); //store the day
    char *year  = strtok(NULL, "-"); //store the year

    char formatted_date[9] = ""; //create empty string will null terminator
    strcat(formatted_date, year); //concatenate the YYYY first
    strcat(formatted_date, month); //then MM
    strcat(formatted_date, day); //then DD (now it is in the format YYYYMMDD)

    strncpy(email.formatted_date, formatted_date, sizeof(email.formatted_date)-1); //copies the date to the email struct
    email.formatted_date[sizeof(email.formatted_date) - 1] = '\0'; //ensure that email.formatted_date is null-terminated

    if (strcmp(sender, "Boss") == 0) {                      //strcmp returns 0 if two strings are the same, so this block of code uses this fact to 
        email.priority_number = 5;                          //assign each sender type a unique priority number so that the Boss has the highest priority,
    } else if (strcmp(sender, "Subordinate") == 0) {        //then Subordinate, Peer, ImportantPerson, and finally Otherperson. It then assigns these to
        email.priority_number = 4;                          //the email struct's priority_number member
    } else if (strcmp(sender, "Peer") == 0) {
        email.priority_number = 3;
    } else if (strcmp(sender, "ImportantPerson") == 0) {
        email.priority_number = 2;
    } else if (strcmp(sender, "OtherPerson") == 0) {
        email.priority_number = 1;
    }

    return email; //return the email struct
}

int compare_email(const Email *a, const Email *b) { //define the compare email function, which helps the maxheap determine which heap index is greater than the other
    if (a->priority_number != b->priority_number) //if priority a is not the same as priority b
        return a->priority_number - b->priority_number; //return the difference of the two, this way if a is less than b, it will return a negative number
    return strcmp(a->formatted_date, b->formatted_date); //otherwise strcmp will return a negative number based on the most recent date
}

//====main function====//

int main() { //defines the main function for the system
    MaxHeap priorityqueue; //create instance of a maxheap 
    maxheap_init(&priorityqueue, 10); //setting the starting capacity of the priority queue to 10 emails -- can be modified

    FILE *file; //create a file pointer called file
    file = fopen("Assignment5_Test_File.txt", "r"); //file points to the text file

    char line[256]; //allocate 256 chars for each line of the file

    while (fgets(line, sizeof(line), file)) { //found this syntax on w3schools
        line[strcspn(line, "\n")] = '\0'; //strspn finds the first occurance of the newline and then it is replaced with a null terminator -- effectively strips the line of whitespace
        if (strncmp(line, "EMAIL", 5) == 0) { //search the first 5 characters of the line for 'EMAIL'
            char temp[256]; //create temp string

            strncpy(temp, line + 6, sizeof(temp) - 1); // Copy everything after "EMAIL " (5 chars + 1 space)
            temp[sizeof(temp) - 1] = '\0'; // ensure that temp is null terminated

            char *sender = strtok(temp, ","); // Split the string using strtok, store the sender as a pointer
            char *subject   = strtok(NULL, ","); // store the subject as a pointer
            char *date  = strtok(NULL, ","); //store the date as a pointer

            Email email = create_email(sender, subject, date); //create the email using those three parameters
            maxheap_add(&priorityqueue, email); //add the email to the heap

        } else if (strcmp(line,"COUNT") == 0) { //if the line is COUNT
            int count = maxheap_count(&priorityqueue); //then return the number of emails in the heap
            printf("\nThere are %d emails to read.\n", count); //print them out

        } else if (strcmp(line,"NEXT") == 0) { // if the line is NEXT
            Email *next = maxheap_peek(&priorityqueue); //look at the next email in the heap
            if (maxheap_count(&priorityqueue) > 0) { //if the heap is not empty
                printf("\nNext email:\n"); //print statement
                printf("\tSender: %s\n\tSubject: %s\n\tDate: %s\n", next->sender_category, next->subject_line, next->date); //print out the email in the same format as assignment 1
            } else { //otherwise
                printf("\nNo emails to read.\n"); //print that the heap is empty
            }
        } else if (strcmp(line,"READ") == 0) { //if the line is READ
            if (maxheap_count(&priorityqueue) > 0) { // if the heap is not empty
                maxheap_remove(&priorityqueue); //remove the from the top of the heap
            } else {
                printf("\nNo emails to read.\n"); //otherise print that the heap is empty
            }
        }
    }

    fclose(file); //close the file
    free(priorityqueue.heap); //free the memory allocated by the heap
    return 0; //end main
}
