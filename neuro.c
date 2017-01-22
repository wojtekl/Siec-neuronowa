#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "lista.c"

float*** neuro(float *L, int in, float **X)
{
	
	int lc = 2;
	int ec = 1000;
	int sc = 150;
	float a = 0.2f;
	int *I = malloc(sizeof(int) * lc);
	*(I + 0) = in + 1;
    int l;
	for(l = 1; l < lc; ++l)
	{
		*(I + l) = *(L + l - 1) + 1;
	}
	float ***w = malloc(sizeof(float**) * lc);
	for(l = 0; l < lc; ++l)
	{
		*(w + l) = malloc(sizeof(float*) * *(L + l));
		int n;
		for(n = 0; n < *(L + l); ++n)
		{
			*(*(w + l) + n) = malloc(sizeof(float) * *(I + l));
			int i;
			for(i = 0; i < *(I + l); ++i)
			{
				*(*(*(w + l) + n) + i) = los(0.05, 0.95);
			}
		}
	}
	
	float **S = malloc(sizeof(float*) * lc);
	float **Y = malloc(sizeof(float*) * lc);
	float **FP = malloc(sizeof(float*) * lc);
	float **D = malloc(sizeof(float*) * lc);
	int i;
	for(i = 0; i < lc; ++i)
	{
		*(S + i) = malloc(sizeof(float) * *(L + i));
		*(Y + i) = malloc(sizeof(float) * *(L + i));
		*(FP + i) = malloc(sizeof(float) * *(L + i));
		*(D + i) = malloc(sizeof(float) * *(L + i));
	}
	
	int e;
	for(e = 0; e < ec; ++e)
	{
		int r;
		for(r = 0; r < sc; ++r)
		{
			int temp = *I - 1;
			int n = 0;
			for(n = 0; n < *(L + 0); ++n)
			{
				*(*(S + 0) + n) = *(*(*(w + 0) + n) + *(I + 0));
				int i;
				for(i = 0; i < temp; ++i)
				{
					*(*(S + 0) + n) = *(*(S + 0) + n) + *(*(*(w + 0) + n) + i) * *(*(X + r) + i);
				}
				*(*(Y + 0) + n) = (1.0f / (1.0f + exp(-*(*(S + 0) + n))));
			}
			
			int l;
			for(l = 1; l < lc; ++l)
			{
				int temp = l - 1;
				int temp2 = *(I + l) - 1;
				int n = 0;
				for(n = 0; n < *(L + l); ++n)
				{
					*(*(S + l) + n) = *(*(*(w + l) + n) + *(I + l));
					int i;
					for(i = 0; i < temp2; ++i)
					{
						*(*(S + l) + n) = *(*(S + l) + n) + *(*(*(w + l) + n) + i) * *(*(Y + temp) + i);
					}
					*(*(Y + l) + n) = (1.0f / (1.0f + exp(-*(*(S + l) + n))));
				}
			}
			
			temp = *(I + 0) - 1;
			for(n = 0; n < *(L + lc - 1); ++n)
			{
				*(*(FP + lc - 1) + n) = *(*(Y + lc - 1) + n) * (1.0f - *(*(Y + lc - 1) + n));
				float temp2 = *(*(X + r) + temp + n) - *(*(Y + lc - 1) + n);
				*(*(D + lc - 1) + n) = temp2 * *(*(FP + lc - 1) + n);
			}
			
			for(l = lc - 2; l > -1; --l)
			{
				int temp = l + 1;
				float SD = 0.0f;
				for(n = 0; n < *(L + temp); ++n)
				{
					for(i = 0; i < *(I + temp); ++i)
					{
						SD = SD + *(*(D + temp) + n) * *(*(*(w + temp) + n) + i);
					}
				}
				for(n = 0; n < *(L + l); ++n)
				{
					*(*(FP + l) + n) = *(*(Y + l) + n) * (1.0f - *(*(Y + l) + n));
					*(*(D + l) + n) = SD * *(*(FP + l) + n);
				}
			}
			
			for(l = lc -1; l > 0; --l)
			{
				int temp = l - 1;
				int temp2 = *(I + l) - 1;
				for(n = 0; n < *(L + l); ++n)
				{
					for(i = 0; i < temp2; ++i)
					{
						*(*(*(w + l) + n) + i) = *(*(*(w + l) + n) + i) + a * *(*(D + l) + n) * *(*(Y + temp) + i);
					}
					*(*(*(w + l) + n) + *(I + l)) = *(*(*(w + l) + n) + *(I + l)) + a * *(*(D + l) + n);
				}
			}
			
			temp = *(I + 0) - 1;
			for(n = 0; n < *(L + 0); ++n)
			{
				for(i = 0; i < temp; ++i)
				{
					*(*(*(w + 0) + n) + i) = *(*(*(w + 0) + n) + i) + a * *(*(D + 0) + n) * *(*(X + r) + i);
				}
				*(*(*(w + 0) + n) + *(I + 0)) = *(*(*(w + 0) + n) + *(I + 0)) + a * *(*(D + 0) + n);
			}
		}
	}
	
	for(i = 0; i < lc; ++i)
	{
		free(*(S + i));
		free(*(Y + i));
		free(*(FP + i));
		free(*(D + i));
	}

	free(D);
	free(FP);
	free(Y);
	free(S);
	free(I);
	
	return w;
	
}

float** sprawdz(float *L, int in, float ***w, float **X)
{
	int lc = 2;
	int sc = 150;
	int *I = malloc(sizeof(int) * lc);
	*(I + 0) = in + 1;
    int l;
	for(l = 1; l < lc; ++l)
	{
		*(I + l) = *(L + l - 1) + 1;
	}
	float **S = malloc(sizeof(float*) * lc);
	float **Y = malloc(sizeof(float*) * lc);
	int i;
	for(i = 0; i < lc; ++i)
	{
		*(S + i) = malloc(sizeof(float) * *(L + i));
		*(Y + i) = malloc(sizeof(float) * *(L + i));
	}
	
	float **E = malloc(sizeof(float*) * sc);
	for(i = 0; i < sc; ++i)
	{
		E[i] = malloc(sizeof(float) * 3);
	}
	
	int r;
	for(r = 0; r < sc; ++r)
	{
		int temp = *(I + 0) - 1;
		int n = 0;
		for(n = 0; n < *(L + 0); ++n)
		{
			*(*(S + 0) + n) = *(*(*(w + 0) + n) + *(I + 0));
			int i;
			for(i = 0; i < temp; ++i)
			{
				*(*(S + 0) + n) = *(*(S + 0) + n) + *(*(*(w + 0) + n) + i) * *(*(X + r) + i);
			}
			*(*(Y + 0) + n) = (1.0f / (1.0f + exp(-*(*(S + 0) + n))));
		}
		
		int l;
		for(l = 1; l < lc; ++l)
		{
			int temp = l - 1;
			int temp2 = *(I + l) - 1;
			int n = 0;
			for(n = 0; n < *(L + l); ++n)
			{
				*(*(S + l) + n) = *(*(*(w + l) + n) + *(I + l));
				int i;
				for(i = 0; i < temp2; ++i)
				{
					*(*(S + l) + n) = *(*(S + l) + n) + *(*(*(w + l) + n) + i) * *(*(Y + temp) + i);
				}
				*(*(Y + l) + n) = (1.0f / (1.0f + exp(-*(*(S + l) + n))));
			}
		}
		
		E[r][0] = Y[lc - 1][0];
		E[r][1] = Y[lc - 1][1];
		E[r][2] = Y[lc - 1][2];
		
	}
	
	for(i = 0; i < lc; ++i)
	{
		free(*(S + i));
	}
	
	free(S);
	free(I);
	return E;
}

int main()
{
    
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
	
	float *L = malloc(sizeof(float) * 2);
	*(L + 0) = 4;
	*(L + 1) = 3;
	
	float ***net = neuro(L, 4, X);
	float **spr = sprawdz(L, 4, net, X);
	
	printf("wynik: %f\n", spr[2][2]);
	printf("wynik: %f\n", spr[148][1]);
	printf("wynik: %f\n", spr[33][0]);
	
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
