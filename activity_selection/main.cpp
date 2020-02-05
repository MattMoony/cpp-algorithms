#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "../tools/tools.h"

#define SIZE 10
#define MAX 25

void sort_activities(int* start, int* end, int left, int right) {
    int p = end[right];
    int l = left, r = right;

    while (l < r) {
        while (l < r && end[l] <= p) l++;
        while (r > l && end[r] >= p) r--;

        int t = end[l];
        end[l] = end[r];
        end[r] = t;

        t = start[l];
        start[l] = start[r];
        start[r] = t;
    }

    end[right] = end[l];
    end[l] = p;

    int t = start[right];
    start[right] = start[l];
    start[l] = t;

    if (l - 1 - left > 0) sort_activities(start, end, left, l-1);
    if (right - l - 1 > 0) sort_activities(start, end, l+1, right);
}

int main()
{
    /*
     * activity_selection
     * ------------------
     *
     * Select the maximum number of activities that can be completed
     * if you're only allowed to work on one at a time.
     *
     */

    printf("activity_selection\n");
    tools::printl('=', 64);

    srand(time(NULL));

    int* start = (int*) malloc(sizeof(int)*SIZE);   // Contains the starting time of each activity
    int* end = (int*) malloc(sizeof(int)*SIZE);     // Contains the end time of each activity

    std::vector<int> picked = {};                   // Will contain all activities that can be completed

    for (int i = 0; i < SIZE; i++) {
        start[i] = rand()%MAX;
        end[i] = rand()%(MAX-start[i])+start[i]+1;
    }

    sort_activities(start, end, 0, SIZE-1);         // Sort activities by their end times

    printf(" Start:\t\t");
    tools::printa(start, SIZE);
    printf(" End:\t\t");
    tools::printa(end, SIZE);

    int lend = 0;
    for (int i = 0; i < SIZE; i++) {
        if (start[i]>=lend) {
            picked.push_back(i);
            lend = end[i];
        }
    }

    printf(" Picked:\t");
    tools::printv(picked);
    tools::printl('=', 64);

    return 0;
}
