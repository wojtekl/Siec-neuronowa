#ifndef NEURO_H
#define NEURO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float*** neuro(const int * const L, const int in, 
  const float * const * const X);

float** sprawdz(const int * const L, const int in, 
  const float * const * const * const w, 
  const float * const * const X);

float los(const float min, const float max);

#endif

