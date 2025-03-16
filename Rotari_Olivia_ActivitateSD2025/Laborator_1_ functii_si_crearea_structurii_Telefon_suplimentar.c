//#include<stdio.h>
//#include<stdlib.h>
//
//struct Telefon {
//	int id;
//	int ram;
//	char* producator; //sir de caractere
//	float pret;
//	char serie;//un singur caracter
//};
//
////initializare articol Telefon
//struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
//	//initializare structura
//	struct Telefon t;
//	t.id =id;
//	t.ram = ram;
//	t.producator = (char*)malloc(sizeof(char)*(strlen(producator)+1));
//	strcpy_s(t.producator, strlen(producator) + 1, producator);
//	t.pret = pret;
//	t.serie = serie;
//	return t;
//}
//
//void afisare(struct Telefon t) {
//	//afisarea tuturor atributelor
//	if (t.producator != NULL) {
//		printf("%d. Tefonul %s seria %c are %d GB RAM si costa %5.2f RON. \n",
//			t.id, t.producator, t.serie, t.ram, t.pret);
//
//	}
//	else
//	{
//		printf("%d. Tefonul din seria %c are %d GB RAM si costa %5.2f RON. \n",
//			t.id, t.serie, t.ram, t.pret);
//	}
//}
//
//void modificaPret(struct Telefon* t, float noulPret) {
//	//modificarea unui atribut
//	//verificare
//	if (noulPret > 0)
//	{
//		(*t).pret=noulPret;
//		//t->pret = noulPret;
//	}
//}
//
//void dezalocare(struct Telefon* t) {
//	//dezalocarea campurilor alocate dinamic
//	if (t->producator != NULL)
//	{
//		free(t->producator);
//		t->producator = NULL;
//	}
//}
//
//int main() {
//	struct Telefon t;
//	t=initializare(1, 256, "Samsung", 2000.5, 'A');
//	afisare(t);
//	modificaPret(&t, 1000);
//	afisare(t);
//	dezalocare(&t);
//	afisare(t);
//	return 0;
//}