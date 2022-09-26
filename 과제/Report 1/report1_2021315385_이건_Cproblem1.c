#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//max elements in array
#define MAX 100

int n = 0;

void printarray(int a[])
{
    int i;
    //for loop to print all the values
    for(i = 0; i < MAX; i++)
    {
        printf("%d\t", a[i]);
        if((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}

//selection sort algorithm (descending order)
void selectionsort(int a[], int max)
{
    int i, j, maxindex;
    //sorting
    for(i = 0; i < max - 1; i++)
    {
        maxindex = i;   //set max index one by one as we slowly move up
        for(j = i + 1; j < max; j++)
        {
            n++; //increase comparison count
            if(a[j] > a[maxindex])  //find max index
            {
                maxindex = j;
            }
        }
        //if max index is not sorted, swap it to the right position
        if(maxindex != i)
        {
            //swap
            int temp = a[i];
            a[i] = a[maxindex];
            a[maxindex] = temp;
        }
    }
}

void fillarray(int a[], int choice) //fills array values
{
    int i, j;  //for loop variable
    int repeatindex = 0; //to keep track of repeat array
    int repeat[100] = {-1, -1, -1,};  //to eliminate repetitions
    srand(time(NULL));//random seed

    switch(choice)  //switch case for cases
    {
        case 1: //randomly filled values
        {
            for(i = 0; i < MAX; i++)
            {
                a[i] = rand() % 1000; //random values
                for(j = 0; j < 100; j++)    //loop to check for repetitions
                {
                    if(a[i] == repeat[j])   //if repetition exists, redo iteration
                    {
                        i--;
                        break;
                    }
                }
                if(j < 100) //if repetition exists (if code broke out from loop)
                {
                    continue; //just continue
                }
                else    //no repetition, add new value into repeat array
                {
                    repeat[repeatindex] = a[i];
                    repeatindex++;
                }
            }
            break;
        }
        case 2: //already sorted / descending array
        {
            for(i = 0; i < MAX; i++)
            {
                a[i] = MAX - i; //input values in reverse
            }
            break;
        }
        case 3: //reversely sorted in ascending order
        {
            for(i = 0; i < MAX; i++)
            {
                a[i] = i + 1;   //just input values
            }
            break;
        }
    }


    printf("List before sorting:\n");   //print before sorting
    printarray(a);

    selectionsort(a, MAX);  //selection sort

    printf("List after sorting:\n");    //print after sorting
    printarray(a);

    printf("Number of comparisons: %d\n", n);//print number of comparisons
}

int main()
{
    int choice = 0; //choosing case type
    int a[MAX]; //array of 100 elements

    while(choice != 4)
    {
        printf("Choose array type:\n\
        1) A[100]: filled with random values\n\
        2) A[100]: Already sorted array\n\
        3) A[100]: Reversely sorted array\n\
        4) Exit\nEnter Choice: "); //ask for input type
        scanf("%d", &choice);   //scan input

        if(choice > 4 || choice < 1)    //if choice valid, ask for another input
        {
            printf("Error! Not a valid choice. Please try again.\n\n");
        }
        else if(choice == 4)    //if 4, exit
        {
            printf("Goodbye! See you next time!\n");
        }
        else    //if choice between 1-3, function call on fillarray
        {
            n = 0;  //refresh comparison count
            fillarray(a, choice);
        }
    }

    return 0;
}