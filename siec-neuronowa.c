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
  float * *const probki = new_tabt(liczbaProbek);
  for(int i = 0; i < liczbaProbek; ++i) probki[i] = new_tabf(7);
  
  const char *wiersz = strtok(bufor, ",\n");
  int p = 0;
  while(NULL != wiersz)
  {
    probki[p][0] = atof(wiersz);
    probki[p][1] = atof(strtok(NULL, ",\n"));
    probki[p][2] = atof(strtok(NULL, ",\n"));
    probki[p][3] = atof(strtok(NULL, ",\n"));
    probki[p][4] = atof(strtok(NULL, ",\n"));
    probki[p][5] = atof(strtok(NULL, ",\n"));
    probki[p][6] = atof(strtok(NULL, ",\n"));
    wiersz = strtok(NULL, ",\n");
    ++p;
  }
  
  free(bufor);
  
  const int layers = 2;
  
  int* const topology = new_tabi(layers);;
  topology[0] = 4;
  topology[1] = 3;
  
  ssn s = new_ssn(4, layers, topology);
  teach_ssn(s, (const float *const *const)probki);
  float** const wynik = ask_ssn(s, liczbaProbek, (const float *const *const)probki);
  const char* str = save_ssn(s);
  FILE *f = fopen("siec.txt", "w+");
  fprintf(f, str);
  // fscanf
  printf("%s\n\n", str);
  delete_ssn(s);
  
  free(topology);
  
  printf("wynik: %f\n", wynik[148][0]);
  printf("wynik: %f\n", wynik[148][1]);
  printf("wynik: %f\n", wynik[148][2]);
  
  for(int i = 0; i < layers; ++i) free(wynik[i]);
  free(wynik);
	
	/*lista *list = lista_nowa();
	lista_dodaj(list, "jeden");
	lista_dodaj(list, "dwa");
	lista_dodaj(list, "trzy");
	lista_dodaj(list, "cztery");
	printf((char*)lista_wez(list, 0));*/
  
  return EXIT_SUCCESS;
}

