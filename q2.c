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

#define PrintState() \
    printf("\tEstacionamento: ");\
    PrintDeque(deque);\
    printf("\tFila de espera: ");\
    PrintDeque(buffer)

typedef struct
{
    int plate;
    int movements;
} Car;

void InsertCar(Car* list, int plate);
int  RemoveCar(Car* list, int plate);
void IncrementCarMovements(Car* list, int plate);

int main()
{
    // Redireciona a entrada para o arquivo
    const char* fileName = "teste.txt";
    FILE *file = freopen(fileName, "r", stdin);
    if (file == NULL) {
        printf("Falha ao abrir o arquivo \"%s\"", fileName);
        return -1;
    }

    // Uma lista para armazenar os carros e os seus movimentos
    Car cars[SIZE];

    for (int i = 0; i < SIZE; ++i)
    {
        cars[i].plate = INVALID_PLATE;
        cars[i].movements = 0;
    }

    Deque *deque = Deque_Create(SIZE);    // Estacionamento
    Deque *buffer = Deque_Create(SIZE);   // Fila de espera

    char option; // c(chegada) ou p(partida)

    Car newCar = {INVALID_PLATE, 0};

    while (true)
    {
        scanf("%c %d", &option, &newCar.plate);

        option = tolower(option);

        if (option != 'c' && option != 'p')
        {
            fprintf(stderr, "Comando invalido. Saindo...\n");
            break;
        }

        switch (option) {

            int car;

            case 'c':
            {
                // Estacionamento cheio
                if (Deque_IsFull(deque))
                {
                    // Verificando se a fila de espera tem vaga
                    puts("Estacionamento cheio!");
                    if (!Deque_IsFull(buffer)) {
                        printf("Carro %d entrando na fila de espera...\n", newCar.plate);
                        Deque_PushBack(buffer, newCar.plate);
                        PrintState();
                    } else
                    // A fila de espera não tem vaga
                    {
                        printf("Fila de espera cheia! Carro %d ignorado...\n", newCar.plate);
                        PrintState();
                    }
                }
                // Tem vaga no estacionameto
                else
                {
                    printf("Carro %d estacionando...\n", newCar.plate);
                    InsertCar(cars, newCar.plate);
                    Deque_PushBack(deque, newCar.plate);
                    PrintState();
                }
            }
                break; // Break case 'c'

            case 'p':
            {
                // Verificando se a placa fornecida pertence a algum carro
                int index;
                if ((index = Deque_Index(deque, newCar.plate)) == -1)
                {
                    printf("O carro %d nao se encontra no estacionamento!\n", newCar.plate);
                    PrintState();
                    break;
                }

                /*  Enquanto o carro desejado não estiver na saida, ou seja,
                    outros carros o estiverem empedindo, o carro da saída
                    sai e volta pela entrada.
                    Após o carro desejado sair, a fila anda de maneira
                    que a ordem dos carros permaneça a mesma antes da saída.
                 */

                while (true)
                {
                    Deque_PopFront(deque, &car);
                    // O carro da ponta é o desejado?
                    if (car == newCar.plate)
                    {
                        // Sim! Então apenas remova-o
                        printf("Carro %d saiu do estacionamento\n", car);
                        int numMovements = RemoveCar(cars, car);
                        printf("O carro %d foi manobrado %d vezes\n", car, numMovements + 1);
                        break;
                    } else
                    {
                        // O carro da ponta não é o desejado, portanto precisamos manobrar os
                        // Carros que estão impedindo sua saida
                        // Da a volta com o carro, e entra novamente no estacionamento
                        Deque_PushBack(deque, car);
                        IncrementCarMovements(cars, car);
                    }
                }

                // Rearranjando os carros para as posições corretas após a saida
                for (int i = 0; i < Deque_Size(deque) - index; ++i) {
                    Deque_PopFront(deque, &car);
                    Deque_PushBack(deque, car);
                }

                PrintState();

                // Como um carro saiu, precisamos verificar se tem algum na fila de espera
                // Para que este possa estacionar na nova vaga
                // Tem vaga para os carros na fila de espera
                if (!Deque_IsFull(deque) && !Deque_IsEmpty(buffer))
                {
                    puts("Ha vagas disponiveis para carros em espera...");
                    while (!Deque_IsFull(deque) && !Deque_IsEmpty(buffer))
                    {
                        Deque_PopFront(buffer, &car);
                        printf("Carro %d saindo da fila de espera e estacionando...\n", car);
                        InsertCar(cars, car);
                        Deque_PushBack(deque, car);
                        PrintState();
                    }
                    break;
                }
            }
                break; // Break Case 'p'
        } // End Switch

        // Consome o caractere '/n' que fica no buffer do teclado
        getchar();
    }

    // Limpa a memória
    Deque_Destroy(&deque);
    Deque_Destroy(&buffer);

    return 0;
}
