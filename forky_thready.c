#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int rand_num(void) {
    int max = 8;
    int min = 1;
    int range = max - min;
    return min + (rand() % range);
}

int pattern1(int num_things) {
    for (int ix = 0; ix < num_things; ++ix) {
        int time = rand_num();
        int pid = fork();

        if (pid < 0) {
            printf("Fork failed!\n");
            exit(1);
        } else if (pid == 0) {
            printf("Parent (%d) created process %d (%d)\n",
                    getppid(), ix + 1, getpid());
            printf("Child Process %d starting: sleeping for %d seconds\n",
                    ix + 1, time);
            sleep(time);
            printf("Child Process %d (%d) exiting...\n", ix + 1, getpid());
            exit(0);
        }
    }

    for (int ix = 0; ix < num_things; ++ix) {
        int status;
        wait(&status);
    }
    printf("Parent process done waiting...\n");

    return 0;
}

int child_pattern2 (int num_things, int count) {
    int time = rand_num();

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child Process %d (%d) starting...\n",
                count + 1, getpid());

        // check if current child is the last one or not
        if (count < (num_things - 1)) {
            child_pattern2(num_things, count + 1);
            exit(0);
        } else {
            printf("Child Process %d (%d) sleeping for %d seconds "
                    "[no child created]\n", count + 1, getpid(), time);
            sleep(time);
            printf("Child Process %d (%d) exiting\n", count + 1, getpid());
            exit(0);
        }
    } else {
        printf("Child Process %d (%d) sleeping for %d seconds after "
            "creating child %d (%d)\n", count, getpid(), time,
            count + 1, pid);
        sleep(time);
        printf("Child Process %d (%d) waiting for child %d (%d)\n",
                count, getpid(), count + 1, pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Child process %d (%d) exiting\n", count, getpid());
    }
    return 0;
}

int pattern2(int num_things, int count) {  
    int  time = rand_num();

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    } else if (pid == 0) {
        printf("Child Process %d (%d) starting...\n", count, getpid());
        child_pattern2(num_things, count);
        exit(0);
    } else {
        printf("Parent created child 0 (%d)\n", pid);
        int status;
        waitpid(pid, &status, 0);
        printf("Child 0 (%d) has exited\nAll children exited\n",
                pid);
    }
    return 0;
}