/*
 * EX NO 4 - Part C: Mutual Exclusion with Semaphore and Monitor
 * (semaphore + mutex + condition variable)
 * Compile: gcc ex4_partC_semaphore_monitor.c -o partC -pthread
 * Run    : ./partC
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int seats[11] = {0};
sem_t s;
pthread_mutex_t m;
pthread_cond_t c;
char *names[] = {"Rahul", "Priya", "Amit", "Sneha"};

void *book(void *arg) {
    int i = *(int*)arg, seat = i + 1;
    sem_wait(&s);
    printf("%s got sem\n", names[i]);
    pthread_mutex_lock(&m);
    while (seats[seat]) {
        printf("%s wait\n", names[i]);
        pthread_cond_wait(&c, &m);
    }
    seats[seat] = 1;
    printf("Booked %s -> %d\n", names[i], seat);
    pthread_mutex_unlock(&m);
    sleep(1);
    pthread_mutex_lock(&m);
    seats[seat] = 0;
    pthread_cond_broadcast(&c);
    pthread_mutex_unlock(&m);
    sem_post(&s);
    return NULL;
}

int main() {
    pthread_t t[4];
    int id[] = {0, 1, 2, 3};
    sem_init(&s, 0, 3);
    pthread_mutex_init(&m, 0);
    pthread_cond_init(&c, 0);
    for (int i = 0; i < 4; i++)
        pthread_create(&t[i], 0, book, &id[i]);
    for (int i = 0; i < 4; i++)
        pthread_join(t[i], 0);
    return 0;
}
