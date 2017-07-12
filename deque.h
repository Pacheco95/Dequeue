/**
 *  @author     Suzane Ferreira
 *  @brief      Esse arquivo contém a definição da estrutura de dados
 *              Deque, que é uma abstração de uma fila duplamente encadeada,
 *              e das funções que a manipulam.
 *
 *  @copyright  LGPL v3.0
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h>
#include <limits.h>

#define DEQUE_EMPTY (INT_MIN + 0)
#define DEQUE_FULL  (INT_MIN + 1)
#define DEQUE_OK    (INT_MIN + 2)
#define DEQUE_NULL  (INT_MIN + 3)

typedef unsigned uint;

typedef struct
{
    int* vector;
    int front;          // Left position
    int back;           // Right position
    unsigned capacity;
} Deque;

/**
 *  @brief  Essa função cria uma nova Deque dinamicamente,
 *          portanto não esqueca de chamar Deque_Destroy()
 *          após sua utilização.
 *  @param  size a quantidade de dados máxima desejada para a Deque.
 *  @return Retorna um ponteiro para a Deque se size for > 0 e se houver memória suficiente,
 *          NULL se houver falha.
 */
Deque*  Deque_Create      (uint capacity);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Insere um valor na ponta direita da fila, se houver espaço.
 *  @param  deque A fila a ser utilizada.
 *  @param  value O valor a ser insrido
 *  @return DEQUE_FULL se a fila estiver cheia,
 *          DEQUE_NULL se deque for NULL
 *          DEQUE_OK em caso de sucesso.
 */
uint    Deque_PushBack    (Deque* deque, int  value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Remove um valor na ponta direita da fila, se houver algum.
 *  @param  deque A fila a ser utilizada.
 *  @param  value Um ponteiro para um inteiro que receberá o valor removido.
 *  @return DEQUE_EMPTY se a fila estiver vazia,
 *          DEQUE_NULL se deque for NULL,
 *          DEQUE_OK em caso de sucesso.
 */
uint    Deque_PopBack     (Deque* deque, int* value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Insere um valor na ponta esquerda da fila, se houver espaço.
 *  @param  deque A fila a ser utilizada.
 *  @param  value O valor a ser inserido.
 *  @return DEQUE_FULL se a fila estiver cheia,
 *          DEQUE_FULL se deque for NULL,
 *          DEQUE_OK em caso de sucesso.
 */
uint    Deque_PushFront   (Deque* deque, int  value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Remove um valor na ponta esquerda da fila, se houver algum.
 *  @param  deque A fila a ser utilizada.
 *  @param  value Um ponteiro para um inteiro que receberá o valor removido.
 *  @return DEQUE_EMPTY se a fila estiver vazia,
 *          DEQUE_NULL se deque for NULL,
 *          DEQUE_OK em caso de sucesso.
 */
uint    Deque_PopFront    (Deque* deque, int* value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Verifica se a fila está vazia.
 *  @param  deque A fila a ser utilizada.
 *  @return true se deque estiver vazia, false caso contrário.
 */
bool    Deque_IsEmpty     (const Deque* deque);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Verifica se a fila está cheia.
 *  @param  deque A fila a ser utilizada.
 *  @return retorna true se deque estiver cheia, false caso contrário.
 */
bool    Deque_IsFull      (const Deque* deque);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Esvazia a fila.
 */
void    Deque_Clear       (Deque* deque);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Retorna a quantidade atual de dados na fila.
 *  @param  deque A fila a ser utilizada.
 *  @return Retorna um valor >= 0 para o tamanho da fila e -1 se deque for NULL
 */
int     Deque_Size        (Deque* deque);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Retorna o índice do primeiro valor da fila, da esquerda para a direita, cujo
 *          valor seja igual ao valor fornecido
 *  @param  deque A fila a ser utilizada.
 *  @param  value Valor a ser procurado na fila.
 *  @return Retorna um índice inteiro >= 0 que indica a posição de
 *          value na fila. Retorna -1 se value não estiver presente ou deque for NULL.
 */
int     Deque_Index       (Deque* deque, int value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Desaloca toda a memória utilizada pela fila e
 *          altera o ponteiro para NULL.
 *  @param  deque Endereço do ponteiro que aponta para a fila a ser desalocada.
 */
void    Deque_Destroy     (Deque** deque);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Retorna o elemento à esquerda na fila, caso exista.
 *  @param  deque A fila a ser utilizada.
 *  @param  deque Endereço de um inteiro que receberá o valor, caso exista.
 *  @return retorna DEQUE_EMPTY se a fila estiver vazia,
 *          DEQUE_NULL se deque for NULL,
 *          DEQUE_OK caso contrário.
 */
int     Deque_Front     (Deque* deque, int* value);

// ------------------------------------------------------------------------------------------------

/**
 *  @brief  Retorna o elemento à direita na fila, caso exista.
 *  @param  deque A fila a ser utilizada.
 *  @param  deque Endereço de um inteiro que receberá o valor, caso exista.
 *  @return retorna DEQUE_EMPTY se a fila estiver vazia,
 *          DEQUE_NULL se deque for NULL,
 *          DEQUE_OK caso contrário.
 */
int     Deque_Back      (Deque* deque, int* value);

#endif // DEQUE_H
