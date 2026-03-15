#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct Cuptor Cuptor;

int nrCuptoare = 0;

struct Cuptor {
	int id;
	char* marca;
	float pret;
	char categorie;
};

Cuptor initializare(const char* marca, float pret, char categorie) {
	Cuptor c;
    nrCuptoare++;

    c.marca = malloc(strlen(marca) + 1);
    strcpy(c.marca, marca);

	c.id = nrCuptoare;
    c.pret = pret;
    c.categorie = categorie;

	return c;
}

void afisare(Cuptor c) {
    printf("Id:         %d\n", c.id);
    printf("Marca:      %s\n", c.marca);
    printf("Pret:       %f\n", c.pret);
    printf("Categorie:  %c\n", c.categorie);
    printf("\n");
}

void modificaPret(Cuptor *c, float pretNou) {
    (*c).pret = pretNou;
    //sau c->pret = pretNou
}

void dezalocare(Cuptor *c) {
    free((*c).marca);
}

int main() {
	Cuptor c1, c2;

    c1 = initializare("awdawdaw", 34.5, 'A');
    afisare(c1);

    c2 = initializare("bgregerg", 456, 'B');
    afisare(c2);

    modificaPret(&c1, 789.99);
    afisare(c1);

    dezalocare(&c1);
    dezalocare(&c2);

	return 0;
}