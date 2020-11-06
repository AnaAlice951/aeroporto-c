/**
 * Biblioteca de funções utilitárias
 **/

#ifndef UTILITARIO_HPP
#define UTILITARIO_HPP

#include <stdlib.h>
#include <stdio.h>
#include "fila-aviao.hpp"

/**
 * Lista e descreve cada uma das filas existentes
 * 
 * @param Fila filas[] (vetor de filas)
 * 
 * @return void
 */
void mostrarFilas(Fila filas[]) {
    for(int i = 0; i < 7; i++) {
        if(i == 0) {
            printf("\n\t\tPISTA 1\n\n");
        } else if(i == 3) {
            printf("\n\t\tPISTA 2\n\n");
        } else if(i == 6){
            printf("\n\t\tPISTA 3\n\n");
        }

        if(filas[i].tipo % 2 == 0) {
            if(filas[i].emOperacao == 1) {
                printf("++++++++++ * Fila de pouso * ++++++++++\n");
            } else {
                printf("++++++++++++ Fila de pouso ++++++++++++\n");
            }
            
        } else {
            if(filas[i].emOperacao == 1) {
                printf("++++++++ * Fila de decolagem * ++++++++\n");
            } else {
                printf("++++++++++ Fila de decolagem ++++++++++\n");
            }
        }

        listar(&filas[i]);
        printf("+++++++++++++++++++++++++++++++++++++++\n\n");
    }
    
    printf("\n");
}

/**
 * Retorna a fila de aterrisagem com menor comprimento
 * 
 * @param Fila *fila1 (fila de aterrisagem)
 * @param Fila *fila2 (fila de aterrisagem)
 * @param Fila *fila3 (fila de aterrisagem)
 * @param Fila *fila4 (fila de aterrisagem)
 * 
 * @return int menorFila
 */
int menorFilaAterrisagem(Fila *fila1, Fila *fila2, Fila *fila3, Fila *fila4) {
    int indice1 = 0, indice2 = 0, menor1 = 0, menor2 = 0;

    if(fila1->comprimento < fila2->comprimento) {
        menor1 = fila1->comprimento;
        indice1 = 0;
    } else {
        menor1 = fila2->comprimento;
        indice1 = 1;
    }

    if(fila3->comprimento < fila4->comprimento) {
        menor2 = fila3->comprimento;
        indice2 = 2;
    } else {
        menor2 = fila4->comprimento;
        indice2 = 3;
    }

    if(menor1 < menor2) {
        return indice1;
    }

    return indice2;
}

/**
 * Retorna a fila de decolagem com menor comprimento
 * 
 * @param Fila *fila1 (fila de decolagem)
 * @param Fila *fila2 (fila de decolagem)
 * @param Fila *fila3 (fila de decolagem)
 * 
 * @return int menorFila
 */
int menorFilaDecolagem(Fila *fila1, Fila *fila2, Fila *fila3) {
    if(fila1->comprimento <= fila2->comprimento && fila1->comprimento <= fila3->comprimento) {
        return 0;
    } else if(fila2->comprimento <= fila1->comprimento && fila2->comprimento <= fila3->comprimento) {
        return 1;
    }

    return 2;
}

#endif
