#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/neuro.h"
/*#include "lib/lista.h"*/

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
  
  const int liczbaProbek = 150;
  float * *const probki = malloc(liczbaProbek 
    * sizeof(float*));
  for(int p = 0; p < liczbaProbek; ++p)
  {
    *(probki + p) = malloc(7 * sizeof(float));
  }
  
  const char *wiersz = strtok(bufor, ",\n");
  int p = 0;
  while(NULL != wiersz)
  {
    *(*(probki + p) + 0) = atof(wiersz);
    *(*(probki + p) + 1) = atof(strtok(NULL, ",\n"));
    *(*(probki + p) + 2) = atof(strtok(NULL, ",\n"));
    *(*(probki + p) + 3) = atof(strtok(NULL, ",\n"));
    *(*(probki + p) + 4) = atof(strtok(NULL, ",\n"));
    *(*(probki + p) + 5) = atof(strtok(NULL, ",\n"));
    *(*(probki + p) + 6) = atof(strtok(NULL, ",\n"));
    wiersz = strtok(NULL, ",\n");
    ++p;
  }
  
  free(bufor);
  
  const int liczbaWarstw = 2;
  int * const warstwy = malloc(liczbaWarstw 
    * sizeof(int));
  *(warstwy + 0) = 4;
  *(warstwy + 1) = 3;
  
  float * * *const ssn = neuro(warstwy, 4, 
    (const float *const *const)probki);
  float * *const wynik = ssn_sprawdz(liczbaWarstw, 
    warstwy, 4, 
    (const float *const *const *const)ssn, 
    liczbaProbek, (const float *const *const)probki);
  
  printf("wynik: %f\n", *(*(wynik + 148) + 0));
  printf("wynik: %f\n", *(*(wynik + 148) + 1));
  printf("wynik: %f\n", *(*(wynik + 148) + 2));
  
  ssn_usun(liczbaWarstw, warstwy, ssn);
  
  for(int w = 0; w < liczbaWarstw; ++w)
  {
    free(*(wynik + w));
  }
  free(wynik);
  free(warstwy);
	
	/*lista *list = lista_nowa();
	lista_dodaj(list, "jeden");
	lista_dodaj(list, "dwa");
	lista_dodaj(list, "trzy");
	lista_dodaj(list, "cztery");
	printf((char*)lista_wez(list, 0));*/
  
  return EXIT_SUCCESS;
}

