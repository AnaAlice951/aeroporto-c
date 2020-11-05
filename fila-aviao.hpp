/**
 * Biblioteca para manipulação de filas de aviões
 **/

#ifndef FILA_AVIAO_HPP
#define FILA_AVIAO_HPP
#define COMBUSTIVEL_MAX 20

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>

/**
 * Informações do avião
 */
typedef struct Aviao {
    int id;
    int criadoEm;
    int combustivel;
} Aviao;

/**
 * Nó da fila de aviões
 */
typedef struct No {
    Aviao aviao;
    No *prox;
} No;

/**
 * Cabeçalho da fila de aviões
 */
typedef struct Fila {
    No *primeiro;
    No *ultimo;
    int comprimento;
    int tipo; // 0: pouso | 1: decolagem | 2: decolagem (emergência)
    int emOperacao; // 0: não | 1: sim
} Fila;

/**
 * Inicializa uma fila em uma variável do tipo Fila
 * 
 * @param int tipo (define se a pista é de decolagem ou de pouso)
 * @param int emOperacao (define se a pista está em operação no turno atual)
 * 
 * @return Fila novaFila (fila inicializada)
 */
Fila criarFila(char tipo, int emOperacao) {
    Fila novaFila;
    novaFila.primeiro = NULL;
    novaFila.ultimo = NULL;
    novaFila.comprimento = 0;
    novaFila.tipo = tipo;
    novaFila.emOperacao = emOperacao;
    return novaFila;
}

// Declaração das filas
Fila filas [7] = {
    criarFila(10, 1), // [0] Pista 1 - aterrisagem
	criarFila(10, 0), // [1] Pista 1 - aterrisagem
	criarFila(11, 0), // [2] Pista 1 - decolagem
    criarFila(20, 1), // [3] Pista 2 - aterrisagem
	criarFila(20, 0), // [4] Pista 2 - aterrisagem
	criarFila(21, 0), // [5] Pista 2 - decolagem
    criarFila(31, 1)  // [6] Pista 3 - decolagem
};

/**
 * Enfileira um novo avião em uma fila
 * 
 * @param Fila *fila (ponteiro para a fila de aviões)
 * @param Aviao aviao (informações do avião que será enfileirado)
 * 
 * @return bool status (0 para sucesso e 1 para falha na operação)
 */
int enfileirar(Fila *fila, Aviao aviao) {
    No * novoAviao;

    novoAviao = (No *) malloc(sizeof(No));

    if(!novoAviao){
        return 1;
    }

    novoAviao->aviao = aviao;
    novoAviao->prox = NULL;

    if(!fila->primeiro) {
        fila->primeiro = novoAviao;
    } else {
        fila->ultimo->prox = novoAviao;
    }

    fila->ultimo = novoAviao;
    fila->comprimento++;
    
    return 0;
}

/**
 * Desenfileira um avião em uma fila
 * 
 * @param Fila *fila (ponteiro para a fila de aviões)
 * 
 * @return int id_deletado (ID do avião deletado para sucesso e -1 para erro na operação)
 */
int desenfileirar(Fila *fila) {
    No *delAviao;

    if(!fila->primeiro) {
        return -1;
    }

    delAviao = fila->primeiro;
    int id_deletado = delAviao->aviao.id;
    fila->primeiro = fila->primeiro->prox;
    free(delAviao);
    fila->comprimento--;

    return id_deletado;
}

/**
 * Lista os aviões de uma fila
 * 
 * @param Fila *fila (ponteiro para a fila de aviões)
 * 
 * @return void
 */
void listar(Fila *fila) {
    No *nodo = fila->primeiro;

    if(!fila->primeiro) {
        printf("Fila vazia.\n");
    }

    int cont = 1;
    while(nodo) {
        if(nodo->aviao.combustivel == 21) {
            printf("%d. ID %d\n", cont, nodo->aviao.id);
        } else {
            printf("%d. ID %d (%d de combustivel)\n", cont, nodo->aviao.id, nodo->aviao.combustivel);

        }
        
        nodo = nodo->prox;
        cont++;
    }
}

/**
 * Desenfileira um avião na posição X de uma fila (emergencialmente)
 * 
 * @param Fila *fila (ponteiro para a fila de aviões)
 * @param int x (posição a ser desenfileirada)
 * 
 * @return void
 */
int desenfileirarPorId(Fila *fila, int id) {
    No *nodo = fila->primeiro;
    No *delAviao;

    if(!fila->primeiro) {
        return -1;
    }

    if(nodo->aviao.id == id) {
        delAviao = nodo;
        fila->primeiro = nodo->prox;
        free(delAviao);
        return delAviao->aviao.id;
    }

    while(nodo) {
        
        if(nodo->prox->aviao.id == id) {
            delAviao = nodo->prox;
            nodo->prox = nodo->prox->prox;
            free(delAviao);
            return delAviao->aviao.id;
        }

        nodo = nodo->prox;
    }

    return -2;
}

#endif