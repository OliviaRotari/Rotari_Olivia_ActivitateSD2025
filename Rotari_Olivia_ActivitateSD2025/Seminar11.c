#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector



void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	if ((*stiva) != NULL)
	{
		nou->next = (*stiva);
	}
	else {
		nou->next = NULL;
	}
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {

	if (*stiva != NULL)
	{
		Nod* aux = (*stiva);
		Masina m = (*stiva)->info;
		(*stiva) = (*stiva)->next;
		free(aux);

		return m;
	}

	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

unsigned char isemptyStack(Nod* stiva) {
	return stiva == NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Nod* stiva = { NULL };
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		pushStack(&stiva, m);
	}
	fclose(f);
	return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva) {
	while (*stiva)
	{
		Masina m = popStack(stiva);
		free(m.model);
		free(m.numeSofer);
	}
}

int size(Nod* stiva) {
	int count = 0;
	while (stiva)
	{
		count++;
		stiva = stiva->next;
	}
	return count;
}

//QUEUE
struct NodDublu {
	Masina info;
	struct NodDublu* prev;
	struct NodDublu* next;
};
typedef struct NodDublu NodDublu;

struct Coada {
	NodDublu* front;
	NodDublu* rear;
};
typedef struct Coada Coada;
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector



void enqueue(Coada* coada, Masina masina) {
	NodDublu* nou = malloc(sizeof(NodDublu));
	nou->info = masina;
	nou->next = NULL;
	nou->prev = coada->rear;
	if (coada->rear)
	{
		coada->rear->next = nou;
	}
	else
	{
		coada->front = nou;
	}
	coada->rear = nou;
}

Masina dequeue(Coada* coada) {
	if (coada->front)
	{
		NodDublu* aux = coada->front;
		Masina m = aux->info;
		coada->front = aux->next;
		free(aux);
		if (coada->front == NULL)
		{
			coada->rear = NULL;
		}
		else {
			coada->front->prev = NULL;
		}
		return m;
	}
	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}

Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Coada coada;
	coada.front = NULL;
	coada.rear = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		enqueue(&coada, m);
	}
	fclose(f);
	return coada;
}

void dezalocareCoadaDeMasini(Coada* coada) {
	while (coada->front)
	{
		Masina m = dequeue(coada);
		if (m.numeSofer != NULL)
		{
			free(m.numeSofer);
		}
		if (m.model != NULL)
		{
			free(m.model);
		}
	}
}



Masina getMasinaByIDQueue(Coada coada, int id) {
	NodDublu* curent = coada.front;
	while (curent) {
		if (curent->info.id == id)
			return curent->info;
		curent = curent->next;
	}
	return (Masina) { -1, 0, 0, NULL, NULL, '-' };
}


float calculeazaPretTotal(Nod** stiva)
{
	Nod* temp = NULL;
	float suma = 0;
	while (!isemptyStack(*stiva))
	{
		Masina m = popStack(stiva);
		suma += m.pret;
		pushStack(&temp, m);
	}

	while (!isemptyStack(temp))
	{
		pushStack(stiva, popStack(&temp));
	}

	return suma;
}

int main() {

	Nod* stiva = citireStackMasiniDinFisier("masini1.txt");
	Masina m = popStack(&stiva);
	afisareMasina(m);

	Coada coada = citireCoadaDeMasiniDinFisier("masini1.txt");
	Masina m1 = dequeue(&coada);
	afisareMasina(m1);
	float suma = calculeazaPretTotal(&stiva);
	printf("Afisare pret total : %.2f", suma);


	printf("\nCautare masina  ID=3 in coada:\n");
	Masina mc = getMasinaByIDQueue(coada, 3);
	if (mc.id != -1)
		afisareMasina(mc);

	dezalocareStivaDeMasini(&stiva);
	dezalocareCoadaDeMasini(&coada);
	free(m.model);
	free(m.numeSofer);
	free(m1.model);
	free(m1.numeSofer);
	return 0;
}