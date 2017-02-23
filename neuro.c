#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "lista.c"

float*** neuro(int *L, int in, float **X)
{
  int rozDanych = sizeof(float);
  int rozWskaz = sizeof(void*);
  int liczWar = 2;

  int l;
  
  int *I = malloc(sizeof(int) * liczWar);
  *(I + 0) = in + 1;
  for(l = 1; l < liczWar; ++l)
  {
    *(I + l) = *(L + l - 1) + 1;
  }
  
  float ***w = malloc(rozWskaz * liczWar);
  for(l = 0; l < liczWar; ++l)
  {
    int liczNer = *(L + l);
    *(w + l) = malloc(rozWskaz * liczNer);
    int n;
    for(n = 0; n < liczNer; ++n)
    {
      int liczWejs = *(I + l);
      *(*(w + l) + n) = malloc(rozDanych * *(I + l));
      int i;
      for(i = 0; i < liczWejs; ++i)
      {
        *(*(*(w + l) + n) + i) = los(0.1, 0.8);
      }
    }
  }
  
  float **S = malloc(rozWskaz * liczWar);
  float **Y = malloc(rozWskaz * liczWar);
  float **FP = malloc(rozWskaz * liczWar);
  float **D = malloc(rozWskaz * liczWar);
  for(l = 0; l < liczWar; ++l)
  {
    *(S + l) = malloc(sizeof(float) * *(L + l));
    *(Y + l) = malloc(sizeof(float) * *(L + l));
    *(FP + l) = malloc(sizeof(float) * *(L + l));
    *(D + l) = malloc(sizeof(float) * *(L + l));
  }
  
  int liczEpok = 10000;
  int liczProbek = 150;
  float a = 0.2f;
  
  int e;
  for(e = 0; e < liczEpok; ++e)
  {
    int p;
    for(p = 0; p < liczProbek; ++p)
    {

      int liczWejsc = *(I + 0) - 1;
      int n;
      for(n = 0; n < *(L + 0); ++n)
      {
        *(*(S + 0) + n) = *(*(*(w + 0) + n) + liczWejsc);
        int i;
        for(i = 0; i < liczWejsc; ++i)
        {
          *(*(S + 0) + n) = *(*(S + 0) + n) + *(*(*(w + 0) + n) + i) * *(*(X + p) + i);
        }
        *(*(Y + 0) + n) = (1.0f / (1.0f + exp(-*(*(S + 0) + n))));
      }
      
      int l = 0;
      for(l = 1; l < liczWar; ++l)
      {
        int popWar = l - 1;
        int liczWejsc = *(I + l) - 1;
        int n = 0;
        for(n = 0; n < *(L + l); ++n)
        {
          *(*(S + l) + n) = *(*(*(w + l) + n) + liczWejsc);
          int i;
          for(i = 0; i < liczWejsc; ++i)
          {
            *(*(S + l) + n) = *(*(S + l) + n) + *(*(*(w + l) + n) + i) * *(*(Y + popWar) + i);
          }
          *(*(Y + l) + n) = (1.0f / (1.0f + exp(-*(*(S + l) + n))));
        }
      }
      
      liczWejsc = *(I + 0) - 1;
      for(n = 0; n < *(L + liczWar - 1); ++n)
      {
        *(*(FP + liczWar - 1) + n) = *(*(Y + liczWar - 1) + n) * (1.0f - *(*(Y + liczWar - 1) + n));
        float ggg = *(*(X + p) + liczWejsc + n) - *(*(Y + liczWar - 1) + n);
        *(*(D + liczWar - 1) + n) = ggg * *(*(FP + liczWar - 1) + n);
      }
      
      for(l = liczWar - 2; l > -1; --l)
      {
        int nasWar = l + 1;
        float SD = 0.0f;
        for(n = 0; n < *(L + nasWar); ++n)
        {
          int i;
          for(i = 0; i < *(I + nasWar); ++i)
          {
            SD = SD + *(*(D + nasWar) + n) * *(*(*(w + nasWar) + n) + i);
          }
        }
        for(n = 0; n < *(L + l); ++n)
        {
          *(*(FP + l) + n) = *(*(Y + l) + n) * (1.0f - *(*(Y + l) + n));
          *(*(D + l) + n) = SD * *(*(FP + l) + n);
        }
      }
      
      for(l = liczWar -1; l > 0; --l)
      {
        int popWar = l - 1;
        int liczWejsc = *(I + l) - 1;
        for(n = 0; n < *(L + l); ++n)
        {
          int i;
          for(i = 0; i < liczWejsc; ++i)
          {
            *(*(*(w + l) + n) + i) = *(*(*(w + l) + n) + i) + a * *(*(D + l) + n) * *(*(Y + popWar) + i);
          }
          *(*(*(w + l) + n) + liczWejsc) = *(*(*(w + l) + n) + liczWejsc) + a * *(*(D + l) + n);
        }
      }
      
      int tem = *(I + 0) - 1;
      for(n = 0; n < *(L + 0); ++n)
      {
        *(*(*(w + 0) + n) + tem) = *(*(*(w + 0) + n) + liczWejsc) + a * *(*(D + 0) + n);
        int i;
        for(i = 0; i < tem; ++i)
        {
          *(*(*(w + 0) + n) + i) = *(*(*(w + 0) + n) + i) + a * *(*(D + 0) + n) * *(*(X + p) + i);
        }
      }
    }
  }
  
  for(l = 0; l < liczWar; ++l)
  {
    free(*(S + l));
    free(*(Y + l));
    free(*(FP + l));
    free(*(D + l));
  }
  free(D);
  free(FP);
  free(Y);
  free(S);
  
  free(I);
  
  return w;

}

float** sprawdz(int *L, int in, float ***w, float **X)
{
  
  int liczWarstw = 2;
  int l;
  
  int *I = malloc(sizeof(int) * liczWarstw);
  *(I + 0) = in + 1;
  for(l = 1; l < liczWarstw; ++l)
  {
    *(I + l) = *(L + l - 1) + 1;
  }
  
  float **Y = malloc(sizeof(float*) * liczWarstw);
  for(l = 0; l < liczWarstw; ++l)
  {
    *(Y + l) = malloc(sizeof(float) * *(L + l));
  }
  
  int liczProbek = 150;
  float **E = malloc(sizeof(float*) * liczProbek);
  int p;
  for(p = 0; p < liczProbek; ++p)
  {
    
    *(E + p) = malloc(sizeof(float) * 3);
    
    int liczWejsc = *(I + 0) - 1;
    int n = 0;
    for(n = 0; n < *(L + 0); ++n)
    {
      float s = *(*(*(w + 0) + n) + liczWejsc);
      int i;
      for(i = 0; i < liczWejsc; ++i)
      {
        s = s + *(*(*(w + 0) + n) + i) * *(*(X + p) + i);
      }
      *(*(Y + 0) + n) = (1.0f / (1.0f + exp(-s)));
    }
    
    int l;
    for(l = 1; l < liczWarstw; ++l)
    {
      int popWar = l - 1;
      int liczWejsc = *(I + l) - 1;
      int n = 0;
      for(n = 0; n < *(L + l); ++n)
      {
        float s = *(*(*(w + l) + n) + liczWejsc);
        int i;
        for(i = 0; i < liczWejsc; ++i)
        {
          s = s + *(*(*(w + l) + n) + i) * *(*(Y + popWar) + i);
        }
        *(*(Y + l) + n) = (1.0f / (1.0f + exp(-s)));
      }
    }
    
    *(*(E + p) + 0) = *(*(Y + liczWarstw - 1) + 0);
    *(*(E + p) + 1) = *(*(Y + liczWarstw - 1) + 1);
    *(*(E + p) + 2) = *(*(Y + liczWarstw - 1) + 2);
    
    printf("%f , %f, %f\n" ,*(*(E + p) + 0), *(*(E + p) + 1), *(*(E + p) + 2));
  
  }
  
  for(l = 0; l < liczWarstw; ++l)
  {
    free(*(Y + l));
  }
  
  free(I);
  
  return E;

}

int main()
{
  
  srand(time(0));
  
  FILE *plik = fopen("iris.csv", "r");
  fseek(plik, 0, SEEK_END);
  int rozmiar = ftell(plik);
  fseek(plik, 0, SEEK_SET);
  char *zawartosc = malloc(rozmiar);
  fread(zawartosc, 1, rozmiar, plik);
  fclose(plik);
  
  float **X = malloc(sizeof(float*) * 150);
  int i;
  for(i = 0; i< 150; ++i)
  {
    *(X + i) = malloc(sizeof(float) * 7);
  }
  
  char *tet = strtok(zawartosc, ",\n");
  i = 0;
  while(NULL != tet)
  {
    *(*(X + i) + 0) = atof(tet);
    *(*(X + i) + 1) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 2) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 3) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 4) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 5) = atof(strtok(NULL, ",\n"));
    *(*(X + i) + 6) = atof(strtok(NULL, ",\n"));
    tet = strtok(NULL, ",\n");
    ++i;
  }
  free(zawartosc);
  
  int *L = malloc(sizeof(int) * 2);
  *(L + 0) = 4;
  *(L + 1) = 3;
  
  float ***net = neuro(L, 4, X);
  float **spr = sprawdz(L, 4, net, X);
  
  printf("wynik: %f\n", *(*(spr + 148) + 0));
  printf("wynik: %f\n", *(*(spr + 148) + 1));
  printf("wynik: %f\n", *(*(spr + 148) + 2));
  
  int l;
  for(l = 0; l < 2; ++l)
  {
    int n;
    for(n = 0; n < *(L + l); ++n)
    {
      free(*(*(net + l) + n));
    }
    free(*(net + l));
  }
  free(net);
  
  for(i = 0; i < 2; ++i)
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
  
  return 0;
}

