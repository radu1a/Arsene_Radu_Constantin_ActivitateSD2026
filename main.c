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

Cuptor* copiazaPrimeleNElemente(Cuptor* vector, int nrElemente, int* n) {
    *n = (*n < nrElemente) ? *n : nrElemente;

    Cuptor* vectorNou = malloc(sizeof(Cuptor) * (*n));
    
    for (int i = 0; i < *n; i++)
    {
        vectorNou[i].marca = malloc(strlen(vector[i].marca) + 1);
        strcpy(vectorNou[i].marca, vector[i].marca);

        vectorNou[i].id = vector[i].id;
        vectorNou[i].pret = vector[i].pret;
        vectorNou[i].categorie = vector[i].categorie;
    }
    
    return vectorNou;
}

Cuptor* copiazaElementeMaiIeftineDe(Cuptor* vector, int nrElemente, int pret, int* n) {
    int vectorIndex[nrElemente + 1];
    int j = 0;

    for (int i = 0; i < nrElemente; i++)
    {
        if (vector[i].pret < pret)
        {
            vectorIndex[j] = i;
            j++;
        }
    }

    *n = j;
    Cuptor* vectorNou = malloc(sizeof(Cuptor) * (*n));

    for (int i = 0; i < *n; i++)
    {
        vectorNou[i].marca = malloc(strlen(vector[vectorIndex[i]].marca) + 1);
        strcpy(vectorNou[i].marca, vector[vectorIndex[i]].marca);

        vectorNou[i].id = vector[vectorIndex[i]].id;
        vectorNou[i].pret = vector[vectorIndex[i]].pret;
        vectorNou[i].categorie = vector[vectorIndex[i]].categorie;
    }
    
    return vectorNou;
}

void afisare(Cuptor c) {
    printf("Id:         %d\n", c.id);
    printf("Marca:      %s\n", c.marca);
    printf("Pret:       %f\n", c.pret);
    printf("Categorie:  %c\n", c.categorie);
    printf("\n");
}

void afisareVector(Cuptor* vector, int nrElemente) {
    for (int i = 0; i < nrElemente; i++)
    {
        printf("Cuptorul %d\n", i);
        printf("Id:         %d\n", vector[i].id);
        printf("Marca:      %s\n", vector[i].marca);
        printf("Pret:       %f\n", vector[i].pret);
        printf("Categorie:  %c\n", vector[i].categorie);
        printf("\n");
    }
}

void modificaPret(Cuptor* c, float pretNou) {
    (*c).pret = pretNou;
    //sau c->pret = pretNou
}

void dezalocare(Cuptor* c) {
    free((*c).marca);
}

void dezalocareVector(Cuptor** vector, int* nrElemente) {
    for (int i = 0; i < *nrElemente; i++)
    {
        free((*vector)[i].marca);
    }
    
    free(*vector);
    *vector = NULL;
    *nrElemente = 0;
}

int main() {
	Cuptor c1, c2, c3, c4;
    Cuptor* vector;

    printf("Afisare initiala\n\n");

    c1 = initializare("awdawdaw", 34.5, 'A');
    afisare(c1);

    c2 = initializare("bgregerg", 456, 'B');
    afisare(c2);

    c3 = initializare("qweqweqw", 678, 'C');
    afisare(c3);

    c4 = initializare("drlerlg", 400, 'D');
    afisare(c4);

    // modificaPret(&c1, 789.99);
    // afisare(c1);

    // vector
    vector = malloc(sizeof(Cuptor) * nrCuptoare);
    vector[0] = c1;
    vector[0].marca = malloc(strlen(c1.marca) + 1);
    strcpy(vector[0].marca, c1.marca);
    vector[1] = c2;
    vector[1].marca = malloc(strlen(c2.marca) + 1);
    strcpy(vector[1].marca, c2.marca);
    vector[2] = c3;
    vector[2].marca = malloc(strlen(c3.marca) + 1);
    strcpy(vector[2].marca, c3.marca);
    vector[3] = c4;
    vector[3].marca = malloc(strlen(c4.marca) + 1);
    strcpy(vector[3].marca, c4.marca);

    printf("Afisare vector initial\n\n");
    afisareVector(vector, nrCuptoare);

    printf("Afisare vector primele n\n\n");
    int nrElementeCopiate = 2;
    Cuptor* vectorPrimeleNElemente = copiazaPrimeleNElemente(vector, nrCuptoare, &nrElementeCopiate);
    afisareVector(vectorPrimeleNElemente, nrElementeCopiate);
    dezalocareVector(vectorPrimeleNElemente, &nrElementeCopiate);

    printf("Afisare vector elemente mai ieftine de\n\n");
    Cuptor* vectorAnumiteElemente = copiazaElementeMaiIeftineDe(vector, nrCuptoare, 400, &nrElementeCopiate);
    afisareVector(vectorAnumiteElemente, nrElementeCopiate);
    dezalocareVector(vectorAnumiteElemente, &nrElementeCopiate);

    dezalocareVector(vector, &nrCuptoare);

    dezalocare(&c1);
    dezalocare(&c2);
    dezalocare(&c3);
    dezalocare(&c4);

	return 0;
}