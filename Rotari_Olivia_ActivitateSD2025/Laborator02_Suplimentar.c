
#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int ram;
	char* producator; //sir de caractere
	float pret;
	char serie;//un singur caracter
};

//initializare articol Telefon
struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
	//initializare structura
	struct Telefon t;
	t.id = id;
	t.ram = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	//afisarea tuturor atributelor
	if (t.producator != NULL) {
		printf("%d. Tefonul %s seria %c are %d GB RAM si costa %5.2f RON. \n",
			t.id, t.producator, t.serie, t.ram, t.pret);

	}
	else
	{
		printf("%d. Tefonul din seria %c are %d GB RAM si costa %5.2f RON. \n",
			t.id, t.serie, t.ram, t.pret);
	}
}

void afisareVector(struct Telefon* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon *vectorNou=NULL;
	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		//shallow copy
		vectorNou[i] = vector[i];
		//deep copy
		vectorNou[i].producator = (char*)malloc(strlen(vector[i].producator)+1);
		strcpy_s(vectorNou[i].producator, strlen(vector[i].producator)+1, vector[i].producator);
	}
	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
	for (int i = 0; i < (*nrElemente); i++){
		if((*vector)[i].producator != NULL)
		{
			free((*vector)[i].producator);
		}

	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Telefon* vector, char nrElemente, float prag, struct Telefon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}
  
struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon t;
	t.id = 1;

	return t;
}
	


int main() {
	//declarare vector telefoane, decl pointer la structura telefon si alocam spatiu
	struct Telefon* telefoane = NULL;
	int nrTelefoane = 3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 512, "Motorola", 1500, 'M');
	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');
	
	afisareVector(telefoane, nrTelefoane);


	struct Telefon* primeleTelefoane = NULL;
	int nrPrimeleTelefoane = 2;
	primeleTelefoane =copiazaPrimeleNElemente(telefoane, nrTelefoane, nrPrimeleTelefoane);
	printf("\n\n Primele telefoane:\n ");
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
	dezalocare(&primeleTelefoane, &nrPrimeleTelefoane);
	afisareVector(primeleTelefoane, nrPrimeleTelefoane);
	return 0;
}