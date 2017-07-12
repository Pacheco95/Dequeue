#ifndef TESTCASE_H
#define TESTCASE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deque.h"

void GetUserInput (Deque *deque);
void GetUserInput (Deque *deque)
{
    puts("\nu -> Insert a random value into the right");
    puts("i -> Pop the value into the right");
    puts("o -> Pop the value into the left");
    puts("p -> Insert a random value into the left");
    puts("c -> Clear Deque\n");

    srand(time(NULL));
    char op;

    int x;
    int done = 0;

    while (!done)
    {
        fflush(stdin);
        op = getchar();
        switch (op) {
        case 'u':
            Deque_PushBack(deque, rand() % 10);
            break;
        case 'i':
            Deque_PopBack(deque, &x);
            break;
        case 'p':
            Deque_PushFront(deque, rand() % 10);
            break;
        case 'o':
            Deque_PopFront(deque, &x);
            break;
        case 'c':
            Deque_Clear(deque);
            break;
        case '\n':
            break;
        default:
            done = 1;
            break;
        }
    }
}

#endif // TESTCASE_H
