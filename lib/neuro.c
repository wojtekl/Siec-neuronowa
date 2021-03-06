#include "neuro.h"

float*** neuro(const int * const L, const int in, 
  const float * const * const X)
{
  const int rozDanych = sizeof(float);
  const int rozWskaz = sizeof(void*);
  const int liczWar = 2;
  
  int l;
  
  int * const I = malloc(sizeof(int) * liczWar);
  *(I + 0) = in + 1;
  for(l = 1; l < liczWar; ++l)
  {
    *(I + l) = *(L + l - 1) + 1;
  }
  
  srand(time(0));
  float *** const w = malloc(rozWskaz * liczWar);
  for(l = 0; l < liczWar; ++l)
  {
    const int liczNer = *(L + l);
    *(w + l) = malloc(rozWskaz * liczNer);
    const int liczWejs = *(I + l);
    int n;
    for(n = 0; n < liczNer; ++n)
    {
      *(*(w + l) + n) = malloc(rozDanych * *(I + l));
      int i;
      for(i = 0; i < liczWejs; ++i)
      {
        *(*(*(w + l) + n) + i) = los(0.1, 0.9);
      }
    }
  }
  
  float ** const S = malloc(rozWskaz * liczWar);
  float ** const Y = malloc(rozWskaz * liczWar);
  float ** const FP = malloc(rozWskaz * liczWar);
  float ** const D = malloc(rozWskaz * liczWar);
  for(l = 0; l < liczWar; ++l)
  {
    *(S + l) = malloc(sizeof(float) * *(L + l));
    *(Y + l) = malloc(sizeof(float) * *(L + l));
    *(FP + l) = malloc(sizeof(float) * *(L + l));
    *(D + l) = malloc(sizeof(float) * *(L + l));
  }
  
  const int liczEpok = 10000;
  const int liczProbek = 150;
  const float a = 0.2f;
  const int liczWejsc = *(I + 0) - 1;
  
  int e;
  for(e = 0; e < liczEpok; ++e)
  {
    int p;
    for(p = 0; p < liczProbek; ++p)
    {
      int n;
      
      for(n = 0; n < *(L + 0); ++n)
      {
        *(*(S + 0) + n) = *(*(*(w + 0) + n) 
          + liczWejsc);
        int i;
        for(i = 0; i < liczWejsc; ++i)
        {
          *(*(S + 0) + n) = *(*(S + 0) + n) 
            + *(*(*(w + 0) + n) + i) * *(*(X + p) 
            + i);
        }
        *(*(Y + 0) + n) = (1.0f / (1.0f + exp(
          -*(*(S + 0) + n))));
      }
      
      int l;
      
      for(l = 1; l < liczWar; ++l)
      {
        const int popWar = l - 1;
        const int liczWejsc = *(I + l) - 1;
        int n;
        for(n = 0; n < *(L + l); ++n)
        {
          *(*(S + l) + n) = *(*(*(w + l) + n) 
            + liczWejsc);
          int i;
          for(i = 0; i < liczWejsc; ++i)
          {
            *(*(S + l) + n) = *(*(S + l) + n) 
              + *(*(*(w + l) + n) + i) * *(*(Y 
              + popWar) + i);
          }
          *(*(Y + l) + n) = (1.0f / (1.0f + exp(
            -*(*(S + l) + n))));
        }
      }
      
      for(n = 0; n < *(L + liczWar - 1); ++n)
      {
        *(*(FP + liczWar - 1) + n) = *(*(Y 
          + liczWar - 1) + n) * (1.0f - *(*(Y 
          + liczWar - 1) + n));
        const float ggg = *(*(X + p) + liczWejsc 
          + n) - *(*(Y + liczWar - 1) + n);
        *(*(D + liczWar - 1) + n) = ggg * *(*(FP 
          + liczWar - 1) + n);
      }
      
      for(l = liczWar - 2; l > -1; --l)
      {
        int n;
        
        const int nasWar = l + 1;
        float SD = 0.0f;
        for(n = 0; n < *(L + nasWar); ++n)
        {
          int i;
          for(i = 0; i < *(I + nasWar); ++i)
          {
            SD = SD + *(*(D + nasWar) + n) 
              * *(*(*(w + nasWar) + n) + i);
          }
        }
        for(n = 0; n < *(L + l); ++n)
        {
          *(*(FP + l) + n) = *(*(Y + l) + n) 
            * (1.0f - *(*(Y + l) + n));
          *(*(D + l) + n) = SD * *(*(FP + l) + n);
        }
      }
      
      for(l = liczWar -1; l > 0; --l)
      {
        const int popWar = l - 1;
        const int liczWejsc = *(I + l) - 1;
        int n;
        for(n = 0; n < *(L + l); ++n)
        {
          int i;
          for(i = 0; i < liczWejsc; ++i)
          {
            *(*(*(w + l) + n) + i) = *(*(*(w + l) 
              + n) + i) + a * *(*(D + l) + n) 
              * *(*(Y + popWar) + i);
          }
          *(*(*(w + l) + n) + liczWejsc) = *(*(*(w 
            + l) + n) + liczWejsc) + a * *(*(D 
            + l) + n);
        }
      }
      
      const int tem = *(I + 0) - 1;
      for(n = 0; n < *(L + 0); ++n)
      {
        *(*(*(w + 0) + n) + tem) = *(*(*(w + 0) 
          + n) + liczWejsc) + a * *(*(D + 0) + n);
        int i;
        for(i = 0; i < tem; ++i)
        {
          *(*(*(w + 0) + n) + i) = *(*(*(w + 0) 
            + n) + i) + a * *(*(D + 0) + n) 
            * *(*(X + p) + i);
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

float** ssn_sprawdz(const int liczbaWarstw, 
  const int *const warstwy, const int in, 
  const float *const *const *const ssn, 
  const int liczbaProbek, 
  const float *const *const probki)
{
  int *const I = malloc(liczbaWarstw * sizeof(int));
  *(I + 0) = in + 1;
  for(int w = 1; w < liczbaWarstw; ++w)
  {
    *(I + w) = *(warstwy + w - 1) + 1;
  }
  
  float * *const Y = malloc(liczbaWarstw 
    * sizeof(float*));
  for(int w = 0; w < liczbaWarstw; ++w)
  {
    *(Y + w) = malloc(*(warstwy + w) 
      * sizeof(float));
  }
  
  float * *const E = malloc(liczbaProbek 
    * sizeof(float*));
  const int liczWejsc = *(I + 0) - 1;
  const int liczWyjsc = *(warstwy + liczbaWarstw 
    - 1);
  for(int p = 0; p < liczbaProbek; ++p)
  {
    for(int n = 0; n < *(warstwy + 0); ++n)
    {
      float s = *(*(*(ssn + 0) + n) + liczWejsc);
      for(int i = 0; i < liczWejsc; ++i)
      {
        s = s + *(*(*(ssn + 0) + n) + i) 
          * *(*(probki + p) + i);
      }
      *(*(Y + 0) + n) = (1.0f / (1.0f + exp(-s)));
    }
    
    for(int w = 1; w < liczbaWarstw; ++w)
    {
      const int popWar = w - 1;
      const int liczWejsc = *(I + w) - 1;
      for(int n = 0; n < *(warstwy + w); ++n)
      {
        float s = *(*(*(ssn + w) + n) + liczWejsc);
        for(int i = 0; i < liczWejsc; ++i)
        {
          s = s + *(*(*(ssn + w) + n) + i) * *(*(Y 
            + popWar) + i);
        }
        *(*(Y + w) + n) = (1.0f / (1.0f + exp(-s)));
      }
    }
    
    *(E + p) = malloc(liczWyjsc * sizeof(float));
    printf("%d.", p + 1);
    for(int n = 0; n < liczWyjsc; ++n)
    {
      *(*(E + p) + n) = *(*(Y + liczbaWarstw - 1) + n);
      printf("  %f" ,*(*(E + p) + n));
    }
    printf("\n");
  }
  
  for(int w = 0; w < liczbaWarstw; ++w)
  {
    free(*(Y + w));
  }
  
  free(I);
  
  return E;
}

void ssn_usun(const int liczbaWarstw, 
  const int *const warstwy, float * * *const ssn)
{
  for(int w = 0; w < liczbaWarstw; ++w)
  {
    for(int n = 0; n < *(warstwy + w); ++n)
    {
      free(*(*(ssn + w) + n));
    }
    free(*(ssn + w));
  }
  free(ssn);
}

float los(const float min, const float max)
{
	return (float)rand() / RAND_MAX * (max - min) 
	  + min;
}

