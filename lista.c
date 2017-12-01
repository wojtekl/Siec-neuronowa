typedef struct tablica
{
	void ** elementy;
	struct tablica *nastepna;
}tablica;

typedef struct lista
{
	int dlugosc;
	struct tablica *poczatek;
}lista;

lista* nowa_lista()
{
	lista * const l = malloc(sizeof(lista));
	l->poczatek = (tablica*)malloc(sizeof(tablica));
	l->poczatek->elementy = (void**)malloc(sizeof(void*) * 3);
	l->poczatek->nastepna = NULL;
	l->dlugosc = 0;
	return l;
}

void dodaj(lista * const l, void * const e)
{
	const int tab = l->dlugosc / 3;
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
	const int off = l->dlugosc - tab * 3;
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

void* wez(const lista * const l, const int i)
{
	/*if(i >= (l->dlugosc-1))
	{
		return l->poczatek->nastepna->elementy[i-3];
	}
	else
	{
		return l->poczatek->elementy[i];
	}*/
	const int tab = i / 3;
	const tablica *c = l->poczatek;
	int j;
	for(j = 0; j < tab; ++j)
	{
		c = c->nastepna;
	}
	const int off = i - (tab * 3);
	return c->elementy[off];
}

void** tablicy(const lista * const l)
{
	int tab = l->dlugosc / 3;
	const int off = l->dlugosc - (tab * 3);
	if(off > 0)
	{
		++tab;
	}
	const tablica *c = l->poczatek;
	void ** const t = (void ** const )malloc(sizeof(void**) * l->dlugosc);
	int j;
	for(j = 0; j < tab; ++j)
	{
		int d = 3;
		if(j == (tab))
		{
			d = off;
		}
		int k;
		for(k = 0; k < d; ++k)
		{
			t[j * 3 + k] = c->elementy[k];
		}
		c = c->nastepna;
	}
	return t;
}

float los(const float min, const float max)
{
	/* srand(time(NULL)); */
    /* float losowa = rand(); */
	return (float)rand() / RAND_MAX * (max - min) + min;
}

