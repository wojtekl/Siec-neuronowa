#ifndef NEURO_H
#define NEURO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float*** neuro(const int * const L, const int in, 
  const float * const * const X);

float** ssn_sprawdz(const int liczbaWarstw, 
  const int *const warstwy, const int in, 
  const float *const *const *const ssn, 
  const int liczbaProbek, 
  const float *const *const probki);

void ssn_usun(const int liczbaWarstw, 
  const int *const warstwy, float * * *const ssn);

float los(const float min, const float max);

#endif

