#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Function prototypes
void printToFile(int sideSize, int numbersOrSpiral);
void printToConsole(int sideSize, int numbersOrSpiral);
void createArray(int sideSize);
bool checkForPrime(int number);
void primesSpiral(int sideSize);

#define MAX_SIDE_SIZE 301 //Can be modified (chosen for visibility in .txt file)

// Array of numbers and characters for the spiral declared as global vars (accessed from multiple functions)
int array[MAX_SIDE_SIZE][MAX_SIDE_SIZE];
char spiral[MAX_SIDE_SIZE][MAX_SIDE_SIZE];

int main()
{
    int sideSize;
    printf("Enter side size for spiral (must be uneven, positive integer between 3 and 301) : ");
    scanf("%d", &sideSize);
    while((sideSize < 3) || (sideSize > MAX_SIDE_SIZE)){
        printf("\nError. Please enter correct side size : ");
        scanf("%d", &sideSize);
    }
    createArray(sideSize);
    primesSpiral(sideSize);
    printf("\n");
    printToFile(sideSize, 0);
    printf("The file UlamSpiral.txt has been created/updated.\n");
    return 0;
}

void printToConsole(int sideSize, int numbersOrSpiral){

    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(numbersOrSpiral == 0){
                printf("%d\t", array[i][j]);
            }else if(numbersOrSpiral == 1){
                printf(" %c ", spiral[i][j]);
            }
        }
        if(numbersOrSpiral == 0){
            printf("\n\n\n");
        }else if(numbersOrSpiral == 1){
            printf("\n");
        }
    }
}

void printToFile(int sideSize, int numbersOrSpiral){
    FILE *filePtr;
    filePtr = fopen("UlamSpiral.txt", "w+");

    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(numbersOrSpiral == 0){
                fprintf(filePtr, "%d\t", array[i][j]);
            }else if(numbersOrSpiral == 1){
                fprintf(filePtr, " %c ", spiral[i][j]);
            }
        }
        if(numbersOrSpiral == 0){
            fprintf(filePtr, "\n\n\n");
        }else if(numbersOrSpiral == 1){
            fprintf(filePtr, "\n");
        }
    }

    fclose(filePtr);
}

void createArray(int sideSize){
    int rowIndex = 0;
    int rowSize = sideSize;
    int colIndex = 0;
    int colSize = sideSize;
    int n = sideSize * sideSize;

    while((rowIndex < rowSize) && (colIndex < colSize)){

        for(int i = (rowSize - 1); i >= rowIndex; i--){
            array[rowSize - 1][i] = n--;
        }
        colSize--;
        for(int j = (colSize - 1); j >= colIndex; j--){
            array[j][colIndex] = n--;
        }
        rowSize--;

        if((colIndex + 1) < colSize){
            for(int k = rowIndex + 1; k <= rowSize; k++){
                array[rowIndex][k] = n--;
            }
        }
        rowIndex++;

        if((rowIndex) < rowSize){
            for(int l = rowIndex; l < colSize; l++){
                array[l][colSize] = n--;
            }
        }
        colIndex++;

    }
}

bool checkForPrime(int number){
    bool flag = false;
    for(int i = 2; i <= (number/2); ++i){
        if((number % i) == 0){
            flag = true;
            break;
        }
    }
    return flag;
}

void primesSpiral(int sideSize){
    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(array[i][j] != 1){
                if(!checkForPrime(array[i][j])){
                    spiral[i][j] = 'x';
                }else{
                    spiral[i][j] = '-';
                }
            }
        }
    }
}
