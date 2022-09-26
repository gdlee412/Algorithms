#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 60  //max for testing

//counting number of nodes in the list
int nodecount = 0;

//structure named node, contains num and pointer for next node
typedef struct node 
{
    int num;
    struct node* next;
}linkedlist;

//insert function
void insert(linkedlist** list, int num) 
{
    //temporary node
    linkedlist* newnode;
    //dynamically allocate memory for the node
    newnode = (linkedlist*)malloc(sizeof(linkedlist));
    //give the values of the new node
    newnode->num = num;
    newnode->next = NULL;
    //temporary node
    linkedlist* temp;
    temp = *list;
    //if list is empty, then just insert new node
    if ((*list) == NULL) 
    {
        *list = newnode;
    }
    //if list not empty, connect the new node to the list by giving its address to the previous node
    else 
    {  
        //while we are not at the last node yet, keep moving to the next node
        while (temp->next) 
        {
            temp = temp->next;
        }
        //once we reach last node, give address to this node
        temp->next = newnode;
    }
    //increase nodecount
    nodecount++;
}

//delete function
void delete(linkedlist *list)
{
    //temporary node
    linkedlist* temp;
    temp = list;
    //if list does not exist or if list does not have a third last element, just leave
    if(list == NULL || list->next == NULL || list->next->next == NULL)
    {
        return;
    }
    //if it exists, find the third last element and delete it
    else
    { 
        //while the current temp is still has a 5th element beyond it, move temp one node
        while(temp->next->next->next->next)
        {
            temp = temp->next;
        }
        //then free the 3rd last element
        free(temp->next);
        //once we reached the 4th last element, connect it to the 2nd last element
        temp->next = temp->next->next;  
    } 
    //decrease node count
    nodecount--;
}

//print function
void printNode(linkedlist *list) 
{
    linkedlist* temp;
    temp = list;
    int linenumber = 1, currentnodenum = 1;
    //variables for dividing into 3 lines
    int divider = nodecount / 3;
    //for specific division
    int remainder = nodecount % 3; 
    //print cases depending on how equally the list can be divided
    //completely equal, just print equally
    while (temp) 
    {
        //print then go to the next node
        printf("-> %d ", temp->num);
        temp = temp->next;
        //if a third of the list is in the line but remainder is not equal to 0 yet, print an extra variable
        if((currentnodenum % divider) == 0 && remainder != 0 && linenumber < 3)
        {
            printf(" -> %d\n", temp->num);
            temp = temp->next;
            linenumber++;
            remainder--;
        }
        //if a third is in the line and remainder is equal to 0, just print new line
        else if((currentnodenum % divider) == 0 && remainder == 0 && linenumber < 3)
        {
            printf("\n");
            linenumber++;
        }
        currentnodenum++;
    }
    printf("\n");
}

int main() 
{
    linkedlist* list;
    list = NULL;
    //array to receive the randomly generated values
    int arr[MAX]; 
    //loop iteration variables
    int i, j;
    //choice variable
    int choice = 0;
    //variable for insert
    int num;
    //random seed
    srand(time(NULL));

    //for loop for random generating
    for(i = 0; i < MAX; i++)
    {
        //get random value
        arr[i] = rand() % 1000;
        //for loop to check for repetitions
        for(j = 0; j < i - 1; j++)
        {
            //if repeated, redo the iteration
            if(arr[j] == arr[i])
            {
                i--;
                break;
            }
        }
    }
    
    //using insert function to insert the variables of the randomly filled array
    for(i = 0; i < MAX; i++)
    {
        insert(&list, arr[i]);
    }

    //print current list
    printf("Problem 3: Linked Lists\n\n");
    printf("Current content:\n");
    printNode(list);

    //loop for choices
    while (choice != 4) 
    {
        //ask for input
        printf("\nWhat would you like to do?\n1) Insert an integer at the end\n2) Delete the 3rd last integer\n3) Print linked list contents\n4) Exit\nEnter your choice: ");
        scanf("%d", &choice);
        //if choice is 1, ask for integer input and insert in the front
        if(choice == 1)
        {
            printf("Input the integer you want to insert: ");
            scanf("%d", &num);
            insert(&list, num);
        }
        //choice = 2, delete 2nd last integer and print this integer
        else if(choice == 2)
        {
            delete(list);
        }
        //choice = 3, print list
        else if(choice == 3)
        {
            printNode(list);
        }
        //choice = 4, exit loop
        else if(choice == 4)
        {
            break;
        }
        //not part of choice, ask for another input
        else
        {
            printf("Error! Try again!!!\n\n");
        }
    }

    printf("Goodbye and have a great day!\n");

    return 0;
}