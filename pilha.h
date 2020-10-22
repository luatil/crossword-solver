#ifndef PILHA_H
#define PILHA_H
#include "game_move.h"

typedef game_move item;

typedef struct {
    item * v;
    int topo;
    int tam;
} pilha;

pilha * criaPilha(int tam);
void destroiPilha(pilha * p);
void empilha(pilha *p, item x);
item desempilha(pilha *p);
int pilhaVazia(pilha *p);
item topoDaPilha(pilha *p);
pilha * aumentaPilha(pilha *p);

#endif // PILHA_H
