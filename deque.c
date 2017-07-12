#include "deque.h"

#include <malloc.h>

#ifdef DEQUE_DEBUG
    #include "util.h"
#endif

Deque* Deque_Create (uint capacity)
{
    if (capacity < 1) {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Deque size (%u)\n", __FILE__, __LINE__, size);
#endif
        return NULL;
    }

    Deque* deque = (Deque*) malloc(sizeof(Deque));

    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stderr, "ERROR (File: %s | Line: %d): Failed to allocate memory for \"Deque\"\n", __FILE__, __LINE__);
#endif
        return NULL;
    }

    deque->vector = (int*) malloc(sizeof(int) * capacity);

    if (deque->vector == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stderr, "ERROR (File: %s | Line: %d): Failed to allocate memory for \"Deque->vector[%u]\"\n", __FILE__, __LINE__, size);
#endif
        Deque_Destroy(&deque);
        return NULL;
    }

    deque->capacity = capacity;
    deque->front = deque->back = -1;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

    return deque;
}

uint Deque_PushBack (Deque* deque, int value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }

    if(Deque_IsFull(deque))
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Trying to PushBack into a full Deque\n", __FILE__, __LINE__);
        PrintDeque(deque);
#endif
        return DEQUE_FULL;
    }

    if(Deque_IsEmpty(deque))
    {
        deque->front = deque->back = 0;
        deque->vector[0] = value;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

        return DEQUE_OK;
    }

    unsigned newBackPos = deque->back + 1;
    if (newBackPos >= deque->capacity)
        newBackPos = 0;
    deque->vector[newBackPos] = value;
    deque->back = newBackPos;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

    return DEQUE_OK;
}

uint Deque_PopBack (Deque* deque, int *value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }

    if (Deque_IsEmpty(deque))
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Trying to PopBack into an empty Deque\n", __FILE__, __LINE__);
        PrintDeque(deque);
#endif
        return DEQUE_EMPTY;
    }

    if (deque->back == deque->front)
    {
        *value = deque->vector[deque->back];
        deque->back = deque->front = -1;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

        return DEQUE_OK;
    }

    int newBackPos = deque->back - 1;
    if (newBackPos == -1)
        newBackPos = deque->capacity - 1;

    *value = deque->vector[deque->back];
    deque->back = newBackPos;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

    return DEQUE_OK;
}

uint Deque_PushFront (Deque* deque, int value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }

    if(Deque_IsFull(deque))
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Trying to PushFront into a full Deque\n", __FILE__, __LINE__);
        PrintDeque(deque);
#endif
        return DEQUE_FULL;
    }

    if(Deque_IsEmpty(deque))
    {
        deque->front = deque->back = 0;
        deque->vector[0] = value;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

        return DEQUE_OK;
    }

    int newFrontPos = deque->front - 1;
    if (newFrontPos == -1)
        newFrontPos = deque->capacity - 1;
    deque->vector[newFrontPos] = value;
    deque->front = newFrontPos;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

    return DEQUE_OK;
}

uint Deque_PopFront (Deque* deque, int *value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }

    if (Deque_IsEmpty(deque))
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Trying to PopFront into an empty Deque\n", __FILE__, __LINE__);
        PrintDeque(deque);
#endif
        return DEQUE_EMPTY;
    }

    if (deque->front == deque->back)
    {
        *value = deque->vector[deque->front];
        deque->back = deque->front = -1;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

        return DEQUE_OK;
    }

    int newFrontPos = deque->front + 1;
    if ((uint) newFrontPos == deque->capacity)
        newFrontPos = 0;

    *value = deque->vector[deque->front];
    deque->front = newFrontPos;

#ifdef DEQUE_DEBUG
        PrintDeque(deque);
#endif

    return DEQUE_OK;
}

bool Deque_IsEmpty (const Deque *deque)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return true;
    }

    if (deque->front == -1 && deque->back == -1)
    {
        return true;
    }
    else
        return false;
}

bool Deque_IsFull(const Deque *deque)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return true;
    }
    int nextBackPos = deque->back + 1;
    if ((uint) nextBackPos == deque->capacity)
        nextBackPos = 0;
    if (nextBackPos == deque->front)
        return true;
    return false;
}

void Deque_Clear (Deque* deque)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return;
    }

    deque->front = deque->back = -1;

#ifdef DEQUE_DEBUG
    if (deque->vector == NULL)
        fprintf(stdout, "WARNING (File: %s | Line: %d): Deque->vector is a null pointer\n", __FILE__, __LINE__);
    PrintDeque(deque);
#endif
}

void Deque_Destroy (Deque** deque)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return;
    }

    if (*deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): *deque is a null pointer\n", __FILE__, __LINE__);
#endif
        return;
    }

    Deque *p_deque = *(deque);
    if (p_deque->vector)
        free(p_deque->vector);
    else
    {
        fprintf(stdout, "WARNING (File: %s | Line: %d): *(deque)->vector is a null pointer\n", __FILE__, __LINE__);
    }

    free(p_deque);
    (*deque) = NULL;
}

int Deque_Size(Deque *deque)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return -1;
    }

    if (Deque_IsEmpty(deque))
        return 0;

    if (deque->front == deque->back)
        return 1;

    int size = 0;

    int front = deque->front;
    const int back = deque->back;

    while (front != back) {
        size++;
        front++;
        if ((uint) front == deque->capacity)
            front = 0;
    }
    size++;
    return size;
}

int Deque_Index(Deque *deque, int value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return -1;
    }

    if (Deque_IsEmpty(deque))
        return -1;

    if (deque->front == deque->back)
    {
        if (deque->vector[deque->front] == value)
            return 0;
        else return -1;
    }

    int index = 0;

    int front = deque->front;
    const int back = deque->back;

    while (front != back) {
        int x = deque->vector[front];
        if (x == value)
            return index;
        index++;
        front++;
        if ((uint) front == deque->capacity)
            front = 0;
    }

    if (deque->vector[deque->back] == value)
        return index;
    else return -1;
}

int Deque_Front(Deque *deque, int *value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }
    if (Deque_IsEmpty(deque))
        return DEQUE_EMPTY;
    *value = deque->vector[deque->front];
    return DEQUE_OK;
}

int Deque_Back(Deque *deque, int *value)
{
    if (deque == NULL)
    {
#ifdef DEQUE_DEBUG
        fprintf(stdout, "WARNING (File: %s | Line: %d): Invalid Argument (null pointer)\n", __FILE__, __LINE__);
#endif
        return DEQUE_NULL;
    }
    if (Deque_IsEmpty(deque))
        return DEQUE_EMPTY;
    *value = deque->vector[deque->back];
    return DEQUE_OK;
}
