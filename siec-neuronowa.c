#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/neuro.h"

int main(const int argc, 
  const char * const * const argv)
{
  FILE * const file = fopen("iris.csv", "r");
  fseek(file, 0, SEEK_END);
  const int d = ftell(file);
  fseek(file, 0, SEEK_SET);
  char * const bufor = malloc(d);
  fread(bufor, 1, d, file);
  fclose(file);
  
  float * * const X = malloc(150 * sizeof(float*));
  for(int i = 0; i < 150; ++i)
  {
    *(X + i) = malloc(7 * sizeof(float));
  }
  
  const char *wiersz = strtok(bufor, ",\n");
  int i = 0;
  while(NULL != wiersz)
  {
    *(*(X + i) + 0) = atof(wiersz);
    *(*(X + i) + 1) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 2) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 3) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 4) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 5) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 6) = atof(strtok(NULL, ",\n"));
    wiersz = strtok(NULL, ",\n");
    ++i;
  }
  
  free(bufor);
  
  int * const L = malloc(2 * sizeof(int));
  *(L + 0) = 4;
  *(L + 1) = 3;
  
  float * * * const net = neuro(L, 4, 
    (const float * const * const)X);
  float * * const spr = sprawdz(L, 4, 
    (const float * const * const * const)net, 
    (const float * const * const)X);
  
  printf("wynik: %f\n", *(*(spr + 148) + 0));
  printf("wynik: %f\n", *(*(spr + 148) + 1));
  printf("wynik: %f\n", *(*(spr + 148) + 2));
  
  for(int l = 0; l < 2; ++l)
  {
    for(int n = 0; n < *(L + l); ++n)
    {
      free(*(*(net + l) + n));
    }
    free(*(net + l));
  }
  free(net);
  
  for(int i = 0; i < 2; ++i)
  {
    free(*(spr + i));
  }
  free(spr);
	
	/*lista *list = nowa_lista();
	dodaj(list, "jeden");
	dodaj(list, "dwa");
	dodaj(list, "trzy");
	dodaj(list, "cztery");
	printf((char*)wez(list, 0));*/
  
  return EXIT_SUCCESS;
}

