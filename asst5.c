#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#include "forky_thready.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int num_things = 0;
    int pat_num = 0;
    int count = 0;

    sscanf(argv[1], "%d", &num_things);
    sscanf(argv[2], "%d", &pat_num);

    if (pat_num == 1) {
        pattern1(num_things);
    } else if (pat_num == 2) {
        pattern2(num_things, count);
    } else {
        printf("Invalid pattern!\n");
    }

    return 0;
}