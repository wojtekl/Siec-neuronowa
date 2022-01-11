#ifndef NEURO_H
#define NEURO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* new_tabi(const int length);

float* new_tabf(const int length);

void* new_tabt(const int length);

typedef struct ssn
{
  int l;
  int* in;
  int* t;
  float*** w;
} ssn;

float ssn_los();

float ssn_aktywacja(const float suma);

ssn new_ssn(const int inputs, const int layers, int* const topology);

void delete_ssn(ssn s);

const char* save_ssn(ssn s);

void teach_ssn(ssn s, const float * const * const X);

float** ask_ssn(ssn s, const int liczbaProbek, const float *const *const probki);

#endif