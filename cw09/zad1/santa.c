#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_REINDEER 9
#define NUM_ELVES 10

pthread_mutex_t santa_mutex;
pthread_cond_t reindeer_cond, elves_cond;
int waiting_reindeer = 0;
int waiting_elves = 0;

void *santa_claus(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&santa_mutex);

        // Sprawdzenie, czy są wszystkie renifery i elfy zgłaszające problemy
        if (waiting_reindeer == NUM_REINDEER && waiting_elves >= 3)
        {
            printf("Mikołaj: budzę się\n");

            // Rozwiązanie problemów elfów
            printf("Mikołaj: rozwiązuje problemy elfów");
            for (int i = 0; i < 3; i++)
            {
                printf(" %d", i);
            }
            printf("\n");

            waiting_elves -= 3;

            // Mikołaj pomaga elfom przez 1-2 sekundy
            sleep(rand() % 2 + 1);

            printf("Mikołaj: zasypiam\n");
        }
        else
        {
            pthread_cond_wait(&reindeer_cond, &santa_mutex);
        }

        pthread_mutex_unlock(&santa_mutex);
    }

    return NULL;
}

void *reindeer(void *arg)
{
    int reindeer_id = *(int *)arg;

    // Renifery są na wakacjach
    sleep(rand() % 6 + 5);

    pthread_mutex_lock(&santa_mutex);
    waiting_reindeer++;
    printf("Renifer: czeka %d reniferów na Mikołaja, %d\n", waiting_reindeer, reindeer_id);

    // Jeśli jest dziewiątym reniferem, budzi Mikołaja
    if (waiting_reindeer == NUM_REINDEER)
    {
        printf("Renifer: wybudzam Mikołaja, %d\n", reindeer_id);
        pthread_cond_signal(&reindeer_cond);
    }

    pthread_mutex_unlock(&santa_mutex);

    // Dostarczenie zabawek przez 2-4 sekundy
    sleep(rand() % 3 + 2);

    // Renifery idą na wakacje
    printf("Renifer: lecę na wakacje, %d\n", reindeer_id);

    return NULL;
}

void *elf(void *arg)
{
    int elf_id = *(int *)arg;

    // Elf pracuje przez losowy okres czasu (2-5s)
    sleep(rand() % 4 + 2);

    pthread_mutex_lock(&santa_mutex);
    if (waiting_elves < 3)
    {
        waiting_elves++;
        printf("Elf: czeka %d elfów na Mikołaja, %d\n", waiting_elves, elf_id);

        // Jeśli jest trzecim elfem, wybudza Mikołaja
        if (waiting_elves == 3)
        {
            printf("Elf: wybudzam Mikołaja, %d\n", elf_id);
            pthread_cond_signal(&reindeer_cond);
        }
    }
    else
    {
        printf("Elf: samodzielnie rozwiązuję swój problem, %d\n", elf_id);
    }

    pthread_mutex_unlock(&santa_mutex);

    // Jeśli jest trzecim elfem, spotyka się z Mikołajem
    if (waiting_elves == 3)
    {
        printf("Elf: Mikołaj rozwiązuje problem, %d\n", elf_id);
        // Mikołaj pomaga elfom przez 1-2 sekundy
        sleep(rand() % 2 + 1);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t santa_thread, reindeer_threads[NUM_REINDEER], elf_threads[NUM_ELVES];

    pthread_mutex_init(&santa_mutex, NULL);
    pthread_cond_init(&reindeer_cond, NULL);
    pthread_cond_init(&elves_cond, NULL);

    // Stworzenie wątku dla Mikołaja
    pthread_create(&santa_thread, NULL, santa_claus, NULL);

    // Stworzenie wątków dla reniferów
    int reindeer_ids[NUM_REINDEER];
    for (int i = 0; i < NUM_REINDEER; i++)
    {
        reindeer_ids[i] = i + 1;
        pthread_create(&reindeer_threads[i], NULL, reindeer, &reindeer_ids[i]);
    }

    // Stworzenie wątków dla elfów
    int elf_ids[NUM_ELVES];
    for (int i = 0; i < NUM_ELVES; i++)
    {
        elf_ids[i] = i + 1;
        pthread_create(&elf_threads[i], NULL, elf, &elf_ids[i]);
    }

    // Oczekiwanie na zakończenie wątku Mikołaja
    pthread_join(santa_thread, NULL);

    // Oczekiwanie na zakończenie wątków reniferów
    for (int i = 0; i < NUM_REINDEER; i++)
    {
        pthread_join(reindeer_threads[i], NULL);
    }

    // Oczekiwanie na zakończenie wątków elfów
    for (int i = 0; i < NUM_ELVES; i++)
    {
        pthread_join(elf_threads[i], NULL);
    }

    pthread_mutex_destroy(&santa_mutex);
    pthread_cond_destroy(&reindeer_cond);
    pthread_cond_destroy(&elves_cond);

    return 0;
}