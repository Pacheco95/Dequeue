/**
 *  @author Suzane Ferreira
 */

// Includes padrões
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Includes locais
#include "deque.h"
#include "util.h"

//! Descomente o #define abaixo para obter um feedback das
//! operações feitas nas filas.
//#define DEQUE_DEBUG

#define INVALID_PLATE INT_MIN
#define INVALID_CAR   INT_MIN + 1
#define SIZE 10

typedef struct
{
    int plate;
    int movements;
} Car;

void InsertCar(Car* list, int plate);
int  RemoveCar(Car* list, int plate);
void IncrementCarMovements(Car* list, int plate);

int main2()
{
    const char* fileName = "teste.txt";
    // Redireciona a entrada para o arquivo
    FILE *file = freopen(fileName, "r", stdin);
    if (file == NULL) {
        printf("Falha ao abrir o arquivo \"%s\"", fileName);
        return -1;
    }

    Car cars[SIZE];

    for (int i = 0; i < SIZE; ++i)
    {
        cars[i].plate = INVALID_PLATE;
        cars[i].movements = 0;
    }

    Deque *deque = Deque_Create(SIZE);
    Deque *buffer = Deque_Create(SIZE);

    while (true)
    {
        char option; // c(chegada) ou p(partida)
        Car c = {INVALID_PLATE, 0};
        scanf("%c %d", &option, &c.plate);

        option = tolower(option);

        if (option != 'c' && option != 'p')
        {
            fprintf(stderr, "Comando invalido. Saindo...\n");
            break;
        }

        switch (option) {

        case 'c':
            if (Deque_IsFull(deque))
            {
                puts("\nEstacionamento cheio");
                PrintDeque(deque);
            } else
            {
                printf("\nCarro %d estacionando...\n", c.plate);
                InsertCar(cars, c.plate);
                Deque_PushBack(deque, c.plate);
                PrintDeque(deque);
            }

            break;
        case 'p':

            if (Deque_Index(deque, c.plate) == -1)
            {
                printf("\nO carro %d nao se encontra no estacionamento!\n", c.plate);
                break;
            }

            /*  Enquanto o carro desejado não estiver na entrada, ou seja,
                outros carros estiverem empedindo sua saída, o carro da entrada
                é inserido em um estacionamento virtual. Após o carro desejado sair,
                os demais voltam na mesma ordem em que estavam anteriormente.
             */

            int car;
            while (true)
            {
                Deque_PopBack(deque, &car);
                if (car == c.plate)
                {
                    printf("\nCarro %d saiu do estacionamento\n", car);
                    int numMovements = RemoveCar(cars, car);
                    printf("O carro %d foi manobrado %d vezes\n", car, numMovements);
                    break;
                } else
                {
                    // Coloca o carro na fila virtual
                    Deque_PushBack(buffer, car);
                    IncrementCarMovements(cars, car);
                }
            }

            // Retorna os carros da fila virtual para a original
            while (!Deque_IsEmpty(buffer))
            {
                Deque_PopBack(buffer, &car);
                Deque_PushBack(deque, car);
            }

            PrintDeque(deque);

            break;
        }

        // Consome o caractere '/n' que fica no buffer do teclado
        getchar();
    }

    // Limpa a memória
    Deque_Destroy(&deque);
    Deque_Destroy(&buffer);
    return 0;
}

void InsertCar(Car* list, int plate)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (list[i].plate == INVALID_PLATE)
        {
            list[i].plate = plate;
            list[i].movements = 0;
            return;
        }
    }
}

int  RemoveCar(Car* list, int plate)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (list[i].plate == plate)
        {
            int movements = list[i].movements;
            list[i].plate = INVALID_PLATE;
            list[i].movements = 0;
            return movements;
        }
    }
    return INVALID_CAR;
}

void IncrementCarMovements(Car* list, int plate)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (list[i].plate == plate)
        {
            list[i].movements++;
            return;
        }
    }
}
