#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//for parameter declaration
int arr_size;
//number of computations
int addition = 0;
int subtraction = 0;
int multiplication = 0;

//print matrix (size * size)
void printmatrix(int arr[arr_size][arr_size])
{
    int i, j;

    //for loop to print a matrix
    for(i = 0; i < arr_size; i++)
    {
        for(j = 0; j < arr_size; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

//print half matrix (size /2 * size / 2)
void printhalfmatrix(int arr[arr_size / 2][arr_size / 2])
{
    int i, j;

    //for loop to print a matrix
    for(i = 0; i < arr_size / 2; i++)
    {
        for(j = 0; j < arr_size / 2; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

//multiply matrix (size * size)
void standardmatrixmult(int a[arr_size][arr_size], int b[arr_size][arr_size])
{
    //product matrix
    int c[arr_size][arr_size];
    //iteration variables
    int i, j, k;

    //finding product
    for(i = 0; i < arr_size; i++)
    {
        for(j = 0; j < arr_size; j++)
        {
            ///initialize elements to 0
            c[i][j] = 0;
            //cumulatively add the products
            for(k = 0; k < arr_size; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
                //increase number of multiplication and addition
                multiplication++;
                addition++;
            }
            //subtract one addition for the 0 to first element
            addition--;
        }
    }

    //print product matrix
    printf("Resulting Matrix after standard matrix multiplication:\n");
    printmatrix(c);
    //print number of computations
    printf("Number of computations:\n");
    printf("Number of Additions = %d\n", addition);
    printf("Number of Subtractions = %d\n", subtraction);
    printf("Number of Multiplications = %d\n\n", multiplication);
}

//divide and conquer matrix
void divideandconquer(int a[arr_size][arr_size], int b[arr_size][arr_size])
{
    //half the size for the 4 small array
    int halfsize = arr_size / 2;
    //4 matrices for the 4 different parts
    int topleft[halfsize][halfsize];
    int topright[halfsize][halfsize];
    int bottomleft[halfsize][halfsize];
    int bottomright[halfsize][halfsize];
    //last product matrix
    int c[arr_size][arr_size];
    //iteration variables
    int i, j, k;

    //for loop for multiplication
    for(i = 0; i < halfsize; i++)
    {
        for(j = 0; j < halfsize; j++)
        {
            //initialize elements to 0
            topleft[i][j] = 0;
            topright[i][j] = 0;
            bottomleft[i][j] = 0;
            bottomright[i][j] = 0;
            //last for loop for Multiplication
            for(k = 0; k < halfsize; k++)
            {
                //multiply and cumulatively add to the arrays
                //adjust the array indices depending on the quadrant
                //first quadrant
                topleft[i][j] += a[i][k] * b[k][j]; //A11 * B11
                topleft[i][j] += a[i][k + halfsize] * b[k + halfsize][j]; //A12 * B21
                //second quadrant
                topright[i][j] += a[i][k] * b[k][j + halfsize]; //A11 * B12
                topright[i][j] += a[i][k + halfsize] * b[k + halfsize][j + halfsize]; //A12 * B22
                //third quadrant
                bottomleft[i][j] += a[i + halfsize][k] * b[k][j]; //A21 * B11
                bottomleft[i][j] += a[i + halfsize][k + halfsize] * b[k + halfsize][j]; //A22 * B21
                //last quadrant
                bottomright[i][j] += a[i + halfsize][k] * b[k][j + halfsize]; //A21 * B12
                bottomright[i][j] += a[i + halfsize][k + halfsize] * b[k + halfsize][j + halfsize]; //A22 * B22
                //add to computation for addition and multiplication
                addition += 8;
                multiplication += 8;
            }
            //subtract 4 to remove the 0 + first product addition
            addition -= 4;
        }
    }

    //print the sub matrices
    printf("First Quadrant Matrix:\n");
    printhalfmatrix(topleft);
    printf("\n");
    printf("Second Quadrant Matrix:\n");
    printhalfmatrix(topright);
    printf("\n");
    printf("Third Quadrant Matrix:\n");
    printhalfmatrix(bottomleft);
    printf("\n");
    printf("Fourth Quadrant Matrix:\n");
    printhalfmatrix(bottomright);
    printf("\n");

    //connect all the 4 quadrants into c
    for(i = 0; i < halfsize; i++)
    {
        for(j = 0; j < halfsize; j++)
        {
            c[i][j] = topleft[i][j];
            c[i][j + halfsize] = topright[i][j];
            c[i + halfsize][j] = bottomleft[i][j];
            c[i + halfsize][j + halfsize] = bottomright[i][j];
        }
    }

    //print product matrix
    printf("Resulting Matrix after the divide-and-conquer algorithm:\n");
    printmatrix(c);
    //print number of computations
    printf("Number of computations:\n");
    printf("Number of Additions = %d\n", addition);
    printf("Number of Subtractions = %d\n", subtraction);
    printf("Number of Multiplications = %d\n\n", multiplication);
}

void strassen(int a[arr_size][arr_size], int b[arr_size][arr_size])
{
    //half the size for the 4 small array
    int halfsize = arr_size / 2;
    //product matrix
    int c[arr_size][arr_size];
    //7 recursive mults
    int p1[halfsize][halfsize];
    int p2[halfsize][halfsize];
    int p3[halfsize][halfsize];
    int p4[halfsize][halfsize];
    int p5[halfsize][halfsize];
    int p6[halfsize][halfsize];
    int p7[halfsize][halfsize];
    //4 matrices for the 4 different parts
    int topleft[halfsize][halfsize];
    int topright[halfsize][halfsize];
    int bottomleft[halfsize][halfsize];
    int bottomright[halfsize][halfsize];
    //loop iteration variables
    int i, j, k;

    //for loop tosolve the 7 recursive mults
    for(i = 0; i < halfsize; i++)
    {
        for(j = 0; j < halfsize; j++)
        {
            //initialize elements to 0
            p1[i][j] = 0;
            p2[i][j] = 0;
            p3[i][j] = 0;
            p4[i][j] = 0;
            p5[i][j] = 0;
            p6[i][j] = 0;
            p7[i][j] = 0;
            //addition and multiplication
            for(k = 0; k < halfsize; k++)
            {
                //also add computations for every addition, subtraction, and multiplication
                p1[i][j] += a[i][k] * (b[k][j + halfsize] - b[k + halfsize][j + halfsize]); //a11 * (b12 - b22)
                addition++;
                subtraction++;
                multiplication++;
                p2[i][j] += (a[i][k] + a[i][k + halfsize]) * b[k + halfsize][j + halfsize]; //(a11 + a12) * b22
                addition += 2;
                multiplication++;
                p3[i][j] += (a[i + halfsize][k] + a[i + halfsize][k + halfsize]) * b[k][j]; //(a21 + a22) * b11
                addition += 2;
                multiplication++;
                p4[i][j] += a[i + halfsize][k + halfsize] * (b[k + halfsize][j] - b[k][j]); //a22 * (b21 - b11)
                addition++;
                subtraction++;
                multiplication++;
                p5[i][j] += (a[i][k] + a[i + halfsize][k + halfsize]) * (b[k][j] + b[k + halfsize][j + halfsize]); //(a11 + a22) * (b11 + b22)
                addition += 3;
                multiplication++;
                p6[i][j] += (a[i][k + halfsize] - a[i + halfsize][k + halfsize]) * (b[k + halfsize][j] + b[k + halfsize][j + halfsize]); //(a12 - a22) * (b21 + b22)
                addition += 2;
                subtraction++;
                multiplication++;
                p7[i][j] += (a[i][k] - a[i + halfsize][k]) * (b[k][j] + b[k][j + halfsize]); //(a11 - a21) * (b11 + b12)
                addition += 2;
                subtraction++;
                multiplication++;
            }
            //remove the 0 + first element
            addition -= 7;
        }
    }      

    //print the recursive mults
    printf("Here are the recursive mults:\n");
    printf("Matrix of P1:\n");
    printhalfmatrix(p1);
    printf("\n");
    printf("Matrix of P2:\n");
    printhalfmatrix(p2);
    printf("\n");
    printf("Matrix of P3:\n");
    printhalfmatrix(p3);
    printf("\n");
    printf("Matrix of P4:\n");
    printhalfmatrix(p4);
    printf("\n");
    printf("Matrix of P5:\n");
    printhalfmatrix(p5);
    printf("\n");
    printf("Matrix of P6:\n");
    printhalfmatrix(p6);
    printf("\n");
    printf("Matrix of P7:\n");
    printhalfmatrix(p7);
    printf("\n");

    //for loop to find the 4 quadrants 
    for(i = 0; i < halfsize; i++)
    {
        for(j = 0; j < halfsize; j++)
        {
            topleft[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
            addition += 2;
            subtraction++;
            topright[i][j] = p1[i][j] + p2[i][j];
            addition++;
            bottomleft[i][j] = p3[i][j] + p4[i][j];
            addition++;
            bottomright[i][j] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j];
            addition++;
            subtraction -= 2;
        }
    }

    //print the 4 sub matrices
    printf("\nNow here are the quadrants:\n");
    printf("First Quadrant Matrix:\n");
    printhalfmatrix(topleft);
    printf("\n");
    printf("Second Quadrant Matrix:\n");
    printhalfmatrix(topright);
    printf("\n");
    printf("Third Quadrant Matrix:\n");
    printhalfmatrix(bottomleft);
    printf("\n");
    printf("Fourth Quadrant Matrix:\n");
    printhalfmatrix(bottomright);
    printf("\n");

    //connect all the 4 quadrants into c
    for(i = 0; i < halfsize; i++)
    {
        for(j = 0; j < halfsize; j++)
        {
            c[i][j] = topleft[i][j];
            c[i][j + halfsize] = topright[i][j];
            c[i + halfsize][j] = bottomleft[i][j];
            c[i + halfsize][j + halfsize] = bottomright[i][j];
        }
    }

    //print product matrix
    printf("Resulting Matrix after the strassen algorithm:\n");
    printmatrix(c);
    //print number of computations
    printf("Number of computations:\n");
    printf("Number of Additions = %d\n", addition);
    printf("Number of Subtractions = %d\n", subtraction);
    printf("Number of Multiplications = %d\n\n", multiplication);
}  

int main()
{
    //iteration variables
    int i, j;
    int choice;
    int size;
    srand(time(NULL));
    printf("Problem 4: Matrix Multiplication\n\n");
    do
    {
        //ask for matrix size (4x4 or 8x8)
        printf("What size would you want the arrays to be?\n1) 4x4\n2) 8x8\nEnter your Choice: ");
        scanf("%d", &choice);
        if(choice == 1)
        {
            size = 4;
            break;
        }
        else if(choice == 2)
        {
            size = 8;
            break;
        }
        else
        {
            printf("Not a valid choice! Input again!\n");
        }
    }while(choice != 1 || choice != 2);
    //declare arrays
    int a[size][size], b[size][size], c[size][size];
    arr_size = size;

    //for loop to randomize a and b's elements
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            a[i][j] = rand() % 1000;
            b[i][j] = rand() % 1000;
        }
    }

    //show first array
    printf("First Matrix:\n");
    printmatrix(a);
    printf("\n");

    //show second array
    printf("Second Matrix:\n");
    printmatrix(b);
    printf("\n");

    //while loop to get type of multiplication
    do
    {
        //initialize to 0
        subtraction = 0;
        addition = 0;
        multiplication = 0;
        printf("Choose the type of matrix multiplication:\n1) Standard multiplication\n2) Divide-and-Conquer algorithm\n3) Strassen algorithm\n4) Exit\nInput your choice: ");
        scanf("%d", &choice);
        //if choice = 1, use standard multiplication
        if(choice == 1)
        {
            standardmatrixmult(a, b);
        }
        //if choice = 2, use divide and conquer algorithm
        else if(choice == 2)
        {
            divideandconquer(a, b);
        }
        //if choice = 3, use strassen algorithm
        else if(choice == 3)
        {
            strassen(a, b);
        }
        //if choice = 4, just break out
        else if(choice == 4)
        {
            break;
        }
        //if choice not part of 1 - 3, ask for another choice input 
        else
        {
            printf("Not a valid choice! Input again!\n");
        }
        
    }while(choice != 4);

    printf("Goodbye! Have a great day!\n");

    return 0;
}