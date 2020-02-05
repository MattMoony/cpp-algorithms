#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "quick_sort.h"
#include "../tools/tools.h"

#define SIZE 10
#define MAX 100

int main()
{
    srand(time(NULL));

    int* a = (int*) malloc(sizeof(int)*SIZE);
    for (int i = 0; i < SIZE; i++) a[i] = rand()%MAX;

    printa(a, SIZE);
    quick_sort(a, 0, SIZE-1);
    printa(a, SIZE);

    return 0;
}
