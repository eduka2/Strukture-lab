#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Polinom* pozicija;

typedef struct Polinom
{
	int Koef;
	int Eks;
	pozicija next;
}Polinom;

int CitanjeDatoteke(char*, pozicija);
int IspisPolinoma(char*, pozicija);
int ZbrojPolinoma(pozicija, pozicija, pozicija);
int UmnozakPolinoma(pozicija, pozicija, pozicija);

int main()
{
	pozicija POL1 = NULL;
	POL1 = (pozicija)malloc(sizeof(Polinom));
	POL1->next = NULL;

	pozicija POL2 = NULL;
	POL2 = (pozicija)malloc(sizeof(Polinom));
	POL2->next = NULL;

	pozicija suma = NULL;
	suma = (pozicija)malloc(sizeof(Polinom));
	suma->next = NULL;

	pozicija umnozak = NULL;
	umnozak = (pozicija)malloc(sizeof(Polinom));
	umnozak->next = NULL;

	CitanjeDatoteke("Polinom1.txt", POL1);
	CitanjeDatoteke("Polinom2.txt", POL2);

	printf("Ispis prvog polinoma:\n");
	printf("Ispis drugog polinoma:\n");
	IspisPolinoma("Polinom2.txt", POL2->next);


	printf("Zbroj polinoma:\n\n P(x) = ");
	ZbrojPolinoma(POL1, POL2, suma);
	printf("Umnozak polinoma:\n\n P(x) = ");
	UmnozakPolinoma(POL1, POL2, umnozak);

	return 0;
	system("pause");
}

int CitanjeDatoteke(char* FileName, pozicija p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Polinom));
	pozicija tmp = NULL;

	if (q == NULL)
	{
		printf("Nema mjesta u memoriji!\n\n");
		return -1;
	}

	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fscanf(FileName, "%d %d", &q->Koef, &q->Eks );
	}

	tmp = p;

	while (tmp->next != NULL && tmp->next->Eks > q->Eks)
		tmp = tmp->next;

	if (tmp->next != NULL && tmp->next->Eks == q->Eks)
	{
		tmp->next->Koef += q->Koef;
		free(q);

		if (tmp->next->Koef == 0)
		{
			q = tmp->next;
			tmp->next = q->next;
			free(q);
		}
	}
	else
	{
		q->next = tmp->next;
		tmp->next = q;
	}

	fclose(fp);
	return 0;
}
int ZbrojPolinoma(pozicija p1, pozicija p2, pozicija r)
{
	pozicija q = NULL, tmp = NULL;
	q = (pozicija)malloc(sizeof(Polinom));
	if (q == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}
	tmp = (pozicija) malloc(sizeof(Polinom));
	if (tmp == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}

	while (p1 != NULL && p2 != NULL) {

		if (p1->Eks < p2->Eks) {
			q->Eks = p2->Eks;
			q->Koef = p2->Koef;
			p2 = p2->next;
		}

		else if (p1->Eks > p2->Eks) {
			q->Eks = p1->Eks;
			q->Koef = p1->Koef;
			p1 = p1->next;
		}

		else {
			q->Eks = p1->Eks;
			q->Koef = p1->Koef + p2->Koef;
			p1 = p1->next;
			p2 = p2->next;
		}
		q->next = r->next;
		r->next = q;
		r = q;
	}

	if (p1 == NULL)
		tmp = p2;
	else tmp = p1;

	while (tmp != NULL) {

		q->Eks = tmp->Eks;
		q->Koef = tmp->Koef;

		q->next = r->next;
		r->next = q;
		r = q;
		tmp = tmp->next;
	}
	return 0;
}
int UmnozakPolinoma(pozicija p1, pozicija p2, pozicija r)
{
	pozicija q = NULL, tmp = NULL;
	q = (pozicija)malloc(sizeof(Polinom));
	if (q == NULL)
	{
		printf("Nema slobodnog mjesta u memoriji!\n");
		return -1;
	}
	tmp = (pozicija)malloc(sizeof(Polinom));
	if (tmp == NULL)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}
	while (p1 != NULL)
	{
		while (p2 != NULL)
		{

			q->Eks = p1->Eks + p2->Eks;
			q->Koef = p1->Koef * p2->Koef;

			q = q->next;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	tmp = r;

	while (tmp->next != NULL && tmp->next->Eks > q->Eks)
			tmp = tmp->next;

	if (tmp->next != NULL && tmp->next->Eks == q->Eks)
	{
			tmp->next->Koef += q->Koef;
			free(q);

		if (tmp->next->Koef == 0)
		{
				q = tmp->next;
				tmp->next = q->next;

				free(q);
		}
		else {
			q->next = tmp->next;
			tmp->next = q;
		}
	}

	return 0;
}