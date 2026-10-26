/*
 * EX NO 4 - Part B: Mutual Exclusion with Semaphore (max 3 threads at a time)
 * Compile: gcc ex4_partB_semaphore.c -o partB -pthread
 * Run    : ./partB
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int seats[11] = {0};
sem_t sem;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *book(void *arg) {
    int i = *(int*)arg, seat = i + 1;
    sem_wait(&sem);
    printf("%s got sem\n", i == 0 ? "Rahul" : i == 1 ? "Priya" : i == 2 ? "Amit" : "Sneha");
    pthread_mutex_lock(&m);
    if (seats[seat] == 0) {
        seats[seat] = 1;
        printf("Booked -> seat %d\n", seat);
    } else
        printf("Taken\n");
    pthread_mutex_unlock(&m);
    sleep(1);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t t[4];
    int id[] = {0, 1, 2, 3};
    sem_init(&sem, 0, 3);
    for (int i = 0; i < 4; i++)
        pthread_create(&t[i], 0, book, &id[i]);
    for (int i = 0; i < 4; i++)
        pthread_join(t[i], 0);
    sem_destroy(&sem);
    return 0;
}
