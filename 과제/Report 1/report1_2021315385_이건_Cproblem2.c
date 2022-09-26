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

void merge(int a[], int left, int middle, int right)
{   
    int i, j, k;
    int size1 = middle - left + 1; //size of arrays
    int size2 = right - middle;
    int leftarray[size1], rightarray[size2];

    //for loop for left array
    for(i = 0; i < size1; i++)
    {
        leftarray[i] = a[left + i];
    }
    //for loop for right array
    for(i = 0; i < size2; i++)
    {
        rightarray[i] = a[middle + 1 + i];
    }

    i = 0; //index for left array
    j = 0; //index for right array
    k = left; //index for merged array

    while(i < size1 && j < size2) //while both subarrays still have elements
    {
        n++; //increase comparison count
        if(leftarray[i] <= rightarray[j])//if left array has smaller value, insert it into a[]
        {
            a[k] = leftarray[i];
            i++;//insert then increase index
        }
        else    //right is smaller, input right then increase index
        {
            a[k] = rightarray[j];
            j++;//insert then increase index
        }
        k++; //increase a[] index
    }

    //if leftarray still has elements, copy it
    while(i < size1)
    {
        a[k] = leftarray[i];
        //increase indices
        i++;   
        k++;
    }

    //if rightarray still has elements, copy it
    while(j < size2)
    {
        a[k] = rightarray[j];
        //increase indices
        j++;   
        k++;
    }

}


void mergesort(int a[], int left, int right)
{
    if(left < right)    //if right index is still greater than the left
    {
        int middle = left + (right - left) / 2;    //find middle, and recursively call mergesort on left and right
        mergesort(a, left, middle);
        mergesort(a, middle + 1, right);

        merge(a, left, middle, right);  //merge arrays
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
        case 2: //already sorted in ascending order
        {
            for(i = 0; i < MAX; i++)
            {
                a[i] = i + 1;   //just input values
            }
            break;
        }
        case 3: //reversely sorted / descending array
        {
            for(i = 0; i < MAX; i++)
            {
                a[i] = MAX - i; //input values in reverse
            }
            break;
        }
    }


    printf("List before sorting:\n");   //print before sorting
    printarray(a);

    mergesort(a, 0, 99);   //merge sort

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