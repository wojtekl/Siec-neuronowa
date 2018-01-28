#include "lista.h"

lista* lista_nowa()
{
  lista * const l = malloc(sizeof(lista));
  l->poczatek = (tablica*)malloc(sizeof(tablica));
  l->poczatek->elementy = (void**)malloc(3 
    * sizeof(void*));
  l->poczatek->nastepna = NULL;
  l->dlugosc = 0;
  return l;
}

void lista_dodaj(lista * const l, void * const e)
{
  const int tab = l->dlugosc / 3;
  tablica *c = l->poczatek;
  for(int j = 0; j < tab; ++j)
  {
    if(NULL == c->nastepna)
    {
      c->nastepna = (tablica*)malloc(sizeof(tablica));
      c->nastepna->elementy = (void**)malloc(3 
        * sizeof(void*));
      c->nastepna->nastepna = NULL;
    }
    c = c->nastepna;
  }
  const int off = l->dlugosc - tab * 3;
  c->elementy[off] = e;
  /*if(2 < l->dlugosc)
  {
    l->poczatek->nastepna = (tablica*)malloc(sizeof(
      tablica));
    l->poczatek->nastepna->elementy = (void**)malloc(
      3 * sizeof(void*));
    l->poczatek->nastepna->elementy[l->dlugosc - 3] = 
      e;
  }
  else
  {
    l->poczatek->elementy[l->dlugosc] = e;
  }*/
  ++l->dlugosc;
}

void* lista_wez(const lista * const l, const int i)
{
  /*if(i >= (l->dlugosc-1))
  {
    return l->poczatek->nastepna->elementy[i-3];
  }
  else
  {
    return l->poczatek->elementy[i];
  }*/
  const int tab = i / 3;
  const tablica *c = l->poczatek;
  for(int j = 0; j < tab; ++j)
  {
    c = c->nastepna;
  }
  const int off = i - (tab * 3);
  return c->elementy[off];
}

void** lista_tablica(const lista * const l)
{
  int tab = l->dlugosc / 3;
  const int off = l->dlugosc - (tab * 3);
  if(off > 0)
  {
    ++tab;
  }
  const tablica *c = l->poczatek;
  void ** const t = (void ** const )malloc(l->dlugosc 
    * sizeof(void**));
  for(int j = 0; j < tab; ++j)
  {
    int d = 3;
    if(j == (tab))
    {
      d = off;
    }
    for(int k = 0; k < d; ++k)
    {
      t[j * 3 + k] = c->elementy[k];
    }
    c = c->nastepna;
  }
  return t;
}

