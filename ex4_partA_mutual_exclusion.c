/*
 * EX NO 4 - Part A: Mutual Exclusion using a mutex (concurrent seat booking)
 * Compile: gcc ex4_partA_mutual_exclusion.c -o partA -pthread
 * Run    : ./partA   (enter a seat number 0-10 when asked for each person)
 */
#include <stdio.h>
#include <pthread.h>

int seats[11] = {0};
pthread_mutex_t m;

void* b(void* n) {
    int s;
    pthread_mutex_lock(&m);
    printf("%s seat: ", (char*)n);
    scanf("%d", &s);
    if (!seats[s]) {
        seats[s] = 1;
        printf("Booked %s→%d\n", (char*)n, s);
    } else {
        printf("Taken!\n");
    }
    pthread_mutex_unlock(&m);
    return 0;
}

int main() {
    pthread_t t[3];
    pthread_mutex_init(&m, 0);
    char* n[] = {"Rahul", "Priya", "Amit"};
    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], 0, b, n[i]);
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], 0);
    return 0;
}
