#include "util.h"

void PrintDeque (Deque* deque) {
    if (Deque_IsEmpty(deque))
    {
        printf("[  ]\n");
        return;
    }

    printf("[");
    if (deque->front == deque->back)
    {
        printf(" %d ]\n", deque->vector[deque->front]);
        return;
    }

    int front = deque->front;
    const int back = deque->back;

    while (front != back) {
        printf(" %d", deque->vector[front]);
        front++;
        if ((uint) front == deque->capacity)
            front = 0;
    }

    printf(" %d", deque->vector[back]);

    printf(" ]\n");
}
