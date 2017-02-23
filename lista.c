typedef struct tablica
{
	void **elementy;
	struct tablica *nastepna;
}tablica;

typedef struct lista
{
	int dlugosc;
	struct tablica *poczatek;
}lista;

lista* nowa_lista()
{
	lista *l = malloc(sizeof(lista));
	l->poczatek = (tablica*)malloc(sizeof(tablica));
	l->poczatek->elementy = (void**)malloc(sizeof(void*) * 3);
	l->poczatek->nastepna = NULL;
	l->dlugosc = 0;
	return l;
}

void dodaj(lista *l, void *e)
{
	int tab = l->dlugosc / 3;
	int off = l->dlugosc - tab * 3;
	tablica *c = l->poczatek;
	int j;
	for(j = 0; j < tab; ++j)
	{
		if(NULL == c->nastepna)
		{
			c->nastepna = (tablica*)malloc(sizeof(tablica));
			c->nastepna->elementy = (void**)malloc(sizeof(void*) * 3);
			c->nastepna->nastepna = NULL;
		}
		c = c->nastepna;
	}
	c->elementy[off] = e;
	/*if(2 < l->dlugosc)
	{
		l->poczatek->nastepna = (tablica*)malloc(sizeof(tablica));
		l->poczatek->nastepna->elementy = (void**)malloc(sizeof(void*) * 3);
		l->poczatek->nastepna->elementy[l->dlugosc - 3] = e;
	}
	else
	{
		l->poczatek->elementy[l->dlugosc] = e;
	}*/
	++l->dlugosc;
}

void* wez(lista *l, int i)
{
	/*if(i >= (l->dlugosc-1))
	{
		return l->poczatek->nastepna->elementy[i-3];
	}
	else
	{
		return l->poczatek->elementy[i];
	}*/
	int tab = i / 3;
	int off = i - (tab * 3);
	tablica *c = l->poczatek;
	int j;
	for(j = 0; j < tab; ++j)
	{
		c = c->nastepna;
	}
	return c->elementy[off];
}

void** tablicy(lista *l)
{
	void** t = (void**)malloc(sizeof(void**) * l->dlugosc);
	int tab = l->dlugosc / 3;
	int off = l->dlugosc - (tab * 3);
	if(off > 0)
	{
		++tab;
	}
	tablica *c = l->poczatek;
	int j;
	for(j = 0; j < tab; ++j)
	{
		int k;
		int d = 3;
		if(j == (tab))
		{
			d = off;
		}
		for(k = 0; k < d; ++k)
		{
			t[j * 3 + k] = c->elementy[k];
		}
		c = c->nastepna;
	}
	return t;
}

float los(float min, float max)
{
	/* srand(time(NULL)); */
    /* float losowa = rand(); */
	return (rand() / RAND_MAX) * (max - min) + min;
}

