/**
 * Biblioteca de funções do aeroporto
 **/

#ifndef AEROPORTO_HPP
#define AEROPORTO_HPP

#include <stdlib.h>
#include <stdio.h>
#include "fila-aviao.hpp"
#include "utilitario.hpp"

// Variáveis para levantamento de estatísticas
int numQuedas = 0, numPousados = 0, numDecolados = 0, numPousosEmergencia = 0;
int somaTempoAterrisagem = 0, somaTempoDecolagem = 0;


// Vetor de IDs existentes e tamanho do vetor
int *ids, numIds = 0;

/**
 * Gera os ID's dos aviões
 * 
 * @param int* ids (vetor de IDs existentes)
 * @param int numIds (tamanho do vetor)
 * 
 * @return id (ID gerado e verificado)
 */
int gerarId(int *ids, int &numIds) {
    int duplicado = 1;
    int id = rand() % 100000;
    numIds++;
    ids = (int *) realloc(ids, numIds * sizeof(int));

    while(duplicado) {
        duplicado = 0;
        for(int i = 0; i < numIds; i++) {
            if(ids[i] == id) {
                id = rand() % 100000;
                duplicado = 1;
            }
        }
    }
    
    ids[numIds - 1] = id;
    return id;
}

// Novos aviões
Aviao novosAvioesPouso[3]; // Aviões chegando para pouso
Aviao novosAvioesDecolagem[3]; // Aviões chegando para decolagem
int numAvioesPouso, numAvioesDecolagem; // Número de aviões para pouso e decolagem

/**
 * Gera uma quantidade aleatória de aviões para chegarem no aeroporto
 * 
 * @param Aviao novosAvioesPouso[] (vetor de aviões que chegaram nas filas de pouso)
 * @param Aviao novosAvioesDecolagem[] (vetor de aviões que chegaram nas filas de decolagem)
 * @param int *numAvioesPouso (número de aviões que chegaram nas filas de pouso)
 * @param int *numAvioesDecolagem (número de aviões que chegaram nas filas de decolagem)
 * 
 * @return void
 */
void gerarNovosAvioes(Aviao novosAvioesPouso[], Aviao novosAvioesDecolagem[], int *numAvioesPouso, int *numAvioesDecolagem, int ut) {
    Aviao novoAviao;
    *numAvioesPouso = rand() % 4;
    *numAvioesDecolagem = rand() % 4;
    
    for(int i = 0; i < *numAvioesPouso; i++) {
        novoAviao.id = gerarId(ids, numIds);
        novoAviao.combustivel = rand() % 20;
        novoAviao.criadoEm = ut;
        novosAvioesPouso[i] = novoAviao;
    }
    for(int i = 0; i < *numAvioesDecolagem; i++) {
        novoAviao.id = gerarId(ids, numIds);
        novoAviao.combustivel = 21;
        novoAviao.criadoEm = ut;
        novosAvioesDecolagem[i] = novoAviao;
    }
}

// Variáveis para controle de operação de filas
int prevEmOperacaoP1 = 0;
int prevEmOperacaoP2 = 0;
int pousoEmergenciaP1 = 0;
int pousoEmergenciaP2 = 0;

/**
 * Normaliza a operação das filas
 * 
 * @param Fila filas[] (vetor de filas)
 * 
 * @return void
 */
void normalizarOperacoes(Fila filas[]) {

    if(filas[0].emOperacao == 0 && filas[1].emOperacao == 0 && filas[2].emOperacao == 0) {
        if(prevEmOperacaoP1 == 0) {
            filas[2].emOperacao = 1;
        } else if(prevEmOperacaoP1 == 1) {
            filas[2].emOperacao = 1;
        } else if(prevEmOperacaoP1 == 2){
            filas[1].emOperacao = 1;
        } else {
            filas[0].emOperacao = 1;
        }
    }

    if(filas[0].emOperacao) {
        filas[0].emOperacao = 0;
        filas[2].emOperacao = 1;
        prevEmOperacaoP1 = 0;
    } else if(filas[1].emOperacao) {
        filas[1].emOperacao = 0;
        filas[2].emOperacao = 1;
        prevEmOperacaoP1 = 1;
    } else if(filas[2].emOperacao) {
        prevEmOperacaoP1 == 0 ? filas[1].emOperacao = 1, prevEmOperacaoP1 = 2 : filas[0].emOperacao = 1, prevEmOperacaoP1 = 3, 
        
        filas[2].emOperacao = 0;
    }
    
    if(filas[3].emOperacao == 0 && filas[4].emOperacao == 0 && filas[5].emOperacao == 0) {
        if(prevEmOperacaoP2 == 0) {
            filas[5].emOperacao = 1;
        } else if(prevEmOperacaoP2 == 1) {
            filas[4].emOperacao = 1;
        } else if(prevEmOperacaoP2 == 2){
            filas[4].emOperacao = 1;
        } else {
            filas[3].emOperacao = 1;
        }
    }

    if(filas[3].emOperacao) {
        filas[3].emOperacao = 0;
        filas[5].emOperacao = 1;
        prevEmOperacaoP2 = 0;
    } else if(filas[4].emOperacao) {
        filas[4].emOperacao = 0;
        filas[5].emOperacao = 1;
        prevEmOperacaoP2 = 1;
    } else if(filas[5].emOperacao) {
        prevEmOperacaoP2 == 0 ? filas[4].emOperacao = 1, prevEmOperacaoP2 = 2 : filas[3].emOperacao = 1, prevEmOperacaoP2 = 3, 
        
        filas[5].emOperacao = 0;
    }
    
    if(!filas[6].emOperacao) {
        filas[6].emOperacao =  1;
    }
}

// Número de aviões com combustível esgotado
int numAvioesEmRisco = 0;

/**
 * Enfileira apropriadamente os novos aviões que chegaram
 * 
 * @param Aviao novosAvioesPouso[] (vetor de aviões que chegaram nas filas de pouso)
 * @param Aviao novosAvioesDecolagem[] (vetor de aviões que chegaram nas filas de decolagem)
 * @param Fila filas[] (vetor de filas)
 * @param int numAvioesPouso (número de aviões que chegaram nas filas de pouso)
 * @param int numAvioesDecolagem (número de aviões que chegaram nas filas de decolagem)
 * 
 * @return void
 */
void enfileirarNovosAvioes(Aviao novosAvioesPouso[], Aviao novosAvioesDecolagem[], Fila filas[], int numAvioesPouso, int numAvioesDecolagem) {
    int menorFila;

    for(int i = 0; i < numAvioesPouso; i++) {
        if(novosAvioesPouso[i].combustivel == 0) {
            numAvioesEmRisco++;
        } else {
            menorFila = menorFilaAterrisagem(&filas[0], &filas[1], &filas[3], &filas[4]);
            switch(menorFila) {
                case 0:
                    enfileirar(&filas[0], novosAvioesPouso[i]);
                break;
                case 1:
                    enfileirar(&filas[1], novosAvioesPouso[i]);
                break;
                case 2:
                    enfileirar(&filas[3], novosAvioesPouso[i]);
                break;
                case 3:
                    enfileirar(&filas[4], novosAvioesPouso[i]);
                break;
            }
        }
    }

    for(int i = 0; i < numAvioesDecolagem; i++) {
        menorFila = menorFilaDecolagem(&filas[2], &filas[5], &filas[6]);
        switch(menorFila) {
            case 0:
                enfileirar(&filas[2], novosAvioesDecolagem[i]);
            break;
            case 1:
                enfileirar(&filas[5], novosAvioesDecolagem[i]);
            break;
            case 2:
                enfileirar(&filas[6], novosAvioesDecolagem[i]);
            break;
        }
    }
}

/**
 * Aterrisa e/ou decola os aviões considerando as pistas em operação
 * 
 * @param Fila filas[] (vetor de filas)
 * 
 * @return void
 */
void aterrisaDecolaAvioes(Fila filas[], int ut) {
    Aviao aux;

    if(numAvioesEmRisco == 1) {
        filas[6].emOperacao = 0;
    } else if(numAvioesEmRisco == 2) {
        filas[6].emOperacao = 0;
        filas[0].emOperacao = 0;
        filas[1].emOperacao = 0;
        filas[2].emOperacao = 0;
    } else if(numAvioesEmRisco >= 3) {
        filas[6].emOperacao = 0;
        filas[0].emOperacao = 0;
        filas[1].emOperacao = 0;
        filas[2].emOperacao = 0;
        filas[3].emOperacao = 0;
        filas[4].emOperacao = 0;
        filas[5].emOperacao = 0;
    }

    int id_deletado;

    for(int i = 0; i < 7; i++) {
        if(filas[i].emOperacao) {
            if(filas[i].primeiro)
                aux = filas[i].primeiro->aviao;

            id_deletado = desenfileirar(&filas[i]);

            if(filas[i].tipo % 2 == 0 && id_deletado != -1) {
                numPousados++;
                somaTempoAterrisagem += ut - aux.criadoEm;
            } else if(id_deletado != -1){
                numDecolados++;
                somaTempoDecolagem += ut - aux.criadoEm;
            }
        }
    }

    for(int i = 0; i < numAvioesEmRisco; i++){
        i < 3 ? numPousosEmergencia++ : numQuedas++;
    }

    numAvioesEmRisco = 0;
}

/**
 * Decrementa o combustivel dos aviões no ar
 * 
 * @param Fila filas[] (vetor de filas)
 * 
 * @return void
 */
void decrementarCombustivel(Fila filas[]){
    No *nodo;
    Aviao aviaoAux;
    for(int i = 0; i < 7; i++) {
        if(filas[i].tipo % 2 == 0) {
            nodo = filas[i].primeiro;

            while(nodo) {
                nodo->aviao.combustivel--;

                if(nodo->aviao.combustivel == 0) {
                    desenfileirarPorId(&filas[i], nodo->aviao.id);
                    numAvioesEmRisco++;
                }

                nodo = nodo->prox;
            }
        }
    }
}

#endif