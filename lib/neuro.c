#include "neuro.h"

void teach_ssn(ssn s, const float * const * const X)
{
  float ** const S = new_tabt(s.l);
  float ** const Y = new_tabt(s.l);
  float ** const FP = new_tabt(s.l);
  float ** const D = new_tabt(s.l);
  for(int i = 0; i < s.l; ++i)
  {
    S[i] = new_tabf(s.t[i]);
    Y[i] = new_tabf(s.t[i]);
    FP[i] = new_tabf(s.t[i]);
    D[i] = new_tabf(s.t[i]);
  }
  
  const int liczEpok = 10000;
  const int liczProbek = 150;
  const float a = 0.2f;
  const int liczWejsc = s.in[0] - 1;
  
  for(int e = 0; e < liczEpok; ++e)
  {
    int p;
    for(p = 0; p < liczProbek; ++p)
    {
      for(int n = 0; n < s.t[0]; ++n)
      {
        S[0][n] = s.w[0][n][liczWejsc];
        int i;
        for(i = 0; i < liczWejsc; ++i) S[0][n] = S[0][n] + s.w[0][n][i] * X[p][i];
        Y[0][n] = ssn_aktywacja(S[0][n]);
      }
      
      for(int l = 1; l < s.l; ++l)
      {
        const int popWar = l - 1;
        const int liczWejsc = s.in[l] - 1;
        int n;
        for(n = 0; n < s.t[l]; ++n)
        {
          S[l][n] = s.w[l][n][liczWejsc];
          int i;
          for(i = 0; i < liczWejsc; ++i) S[l][n] = S[l][n] + s.w[l][n][i] * Y[popWar][i];
          Y[l][n] = ssn_aktywacja(S[l][n]);
        }
      }
      
      for(int n = 0; n < s.t[s.l - 1]; ++n)
      {
        FP[s.l - 1][n] = Y[s.l - 1][n] * (1.0f - Y[s.l - 1][n]);
        const float ggg = X[p][liczWejsc + n] - Y[s.l - 1][n];
        D[s.l - 1][n] = ggg * FP[s.l - 1][n];
      }
      
      for(int l = s.l - 2; l > -1; --l)
      {
        int n;
        
        const int nasWar = l + 1;
        float SD = 0.0f;
        for(n = 0; n < s.t[nasWar]; ++n)
        {
          int i;
          for(i = 0; i < s.in[nasWar]; ++i) SD = SD + D[nasWar][n] * s.w[nasWar][n][i];
        }
        for(n = 0; n < s.t[l]; ++n)
        {
          FP[l][n] = Y[l][n] * (1.0f - Y[l][n]);
          D[l][n] = SD * FP[l][n];
        }
      }
      
      for(int l = s.l -1; l > 0; --l)
      {
        const int popWar = l - 1;
        const int liczWejsc = s.in[l] - 1;
        int n;
        for(n = 0; n < s.t[l]; ++n)
        {
          int i;
          for(i = 0; i < liczWejsc; ++i) s.w[l][n][i] = s.w[l][n][i] + a * D[l][n] * Y[popWar][i];
          s.w[l][n][liczWejsc] = s.w[l][n][liczWejsc] + a * D[l][n];
        }
      }
      
      const int tem = s.in[0] - 1;
      for(int n = 0; n < s.t[0]; ++n)
      {
        s.w[0][n][tem] = s.w[0][n][liczWejsc] + a * D[0][n];
        int i;
        for(i = 0; i < tem; ++i) s.w[0][n][i] = s.w[0][n][i] + a * D[0][n] * X[p][i];
      }
    }
  }
  
  for(int i = 0; i < s.l; ++i)
  {
    free(S[i]);
    free(Y[i]);
    free(FP[i]);
    free(D[i]);
  }
  free(D);
  free(FP);
  free(Y);
  free(S);
}

float** ask_ssn(ssn s, const int liczbaProbek, const float *const *const probki)
{
  float * *const Y = new_tabt(s.l);
  for(int i = 0; i < s.l; ++i) Y[i] = new_tabf(s.t[i]);
  
  float * *const E = new_tabt(liczbaProbek);
  const int liczWejsc = s.in[0] - 1;
  const int liczWyjsc = s.t[s.l - 1];
  for(int p = 0; p < liczbaProbek; ++p)
  {
    for(int i = 0; i < s.t[0]; ++i)
    {
      float s2 = s.w[0][i][liczWejsc];
      for(int j = 0; j < liczWejsc; ++j) s2 = s2 + s.w[0][i][j] * probki[p][j];
      Y[0][i] = ssn_aktywacja(s2);
    }
    
    for(int i = 1; i < s.l; ++i)
    {
      const int popWar = i - 1;
      const int liczWejsc = s.in[i] - 1;
      for(int j = 0; j < s.t[i]; ++j)
      {
        float s2 = s.w[i][j][liczWejsc];
        for(int k = 0; k < liczWejsc; ++k) s2 = s2 + s.w[i][j][k] * Y[popWar][k];
        Y[i][j] = ssn_aktywacja(s2);
      }
    }
    
    E[p] = new_tabf(liczWyjsc);
    printf("%d.", p + 1);
    for(int i = 0; i < liczWyjsc; ++i)
    {
      E[p][i] = Y[s.l - 1][i];
      printf("  %f" , E[p][i]);
    }
    printf("\n");
  }
  
  for(int i = 0; i < s.l; ++i) free(Y[i]);
  
  return E;
}

int* new_tabi(const int length)
{
  return malloc(sizeof(int) * length);
}

float* new_tabf(const int length)
{
  return malloc(sizeof(float) * length);
}

void* new_tabt(const int length)
{
  return malloc(sizeof(void*) * length);
}

float ssn_los()
{
	return (float)rand() / RAND_MAX * (0.9 - 0.1) + 0.1;
}

float ssn_aktywacja(const float suma)
{
  return 1.0f / (1.0f + exp(-suma));
}

ssn new_ssn(const int inputs, const int layers, int* const topology)
{
  ssn s = { .l = layers, .t = topology, .in = new_tabi(inputs), .w = new_tabt(layers) };
  s.in[0] = inputs + 1;
  int i;
  for(i = 1; i < s.l; ++i) s.in[i] = s.t[i - 1] + 1;
  
  srand(time(0));
  for(i = 0; i < s.l; ++i)
  {
    const int liczNer = s.t[i];
    s.w[i] = new_tabt(liczNer);
    const int liczWejs = s.in[i];
    int j;
    for(j = 0; j < liczNer; ++j)
    {
      s.w[i][j] = new_tabf(s.in[i]);
      int k;
      for(k = 0; k < liczWejs; ++k) s.w[i][j][k] = ssn_los();
    }
  }
  
  return s;
}

void delete_ssn(ssn s)
{
  for(int i = 0; i < s.l; ++i)
  {
    for(int j = 0; j < s.t[i]; ++j) free(s.w[i][j]);
    free(s.w[i]);
  }
  free(s.w);
  
  free(s.in);
}

const char* save_ssn(ssn s)
{
  char* buffer = malloc(sizeof(const char*) * 1024 * 1024);
  int beg = 0;
  
  for(int i = 0; i < s.l; ++i)
  {
    const int liczNer = s.t[i];
    const int liczWejs = s.in[i];
    for(int j = 0; j < liczNer; ++j)
    {
      for(int k = 0; k < liczWejs; ++k)
      {
        beg += sprintf(buffer + beg, "%f\t", s.w[i][j][k]);
      }
      beg += sprintf(buffer + beg, "\n");
    }
    beg += sprintf(buffer + beg, "\n");
  }
  buffer[beg] = '\0';
  
  return buffer;
}