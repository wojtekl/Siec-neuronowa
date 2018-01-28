#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>

typedef struct tablica
{
  void ** elementy;
  struct tablica *nastepna;
}tablica;

typedef struct lista
{
  int dlugosc;
  struct tablica *poczatek;
}lista;

lista* lista_nowa();

void lista_dodaj(lista * const l, void * const e);

void* lista_wez(const lista * const l, const int i);

void** lista_tablica(const lista * const l);

#endif

