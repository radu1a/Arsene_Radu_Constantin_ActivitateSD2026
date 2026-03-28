#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraMasina Masina;

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

void afisareMasina(Masina masina) {
	printf("Id:          %d\n", masina.id);
	printf("Numar usi:   %d\n", masina.nrUsi);
	printf("Pret:        %.2f\n", masina.pret);
	printf("Model:       %s\n", masina.model);
	printf("Nume:        %s\n", masina.numeSofer);
	printf("Serie:       %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int n) {
    for (int i = 0; i < n; i++)
    {
        printf("Masina %d\n", i);
        afisareMasina(masini[i]);
    }
}

Masina citireMasinaFisier(FILE* file, int* succes) {
	Masina m;
    char buffer[100];
    char separator[3] = ",\n";
    char* aux;

    if (!fgets(buffer, 100, file))
    {
        *succes = 0;
        return m;
    }
    
    aux = strtok(buffer, separator);
    m.id = atoi(aux);

    aux = strtok(NULL, separator);
    m.nrUsi = atoi(aux);

    aux = strtok(NULL, separator);
    m.pret = atof(aux);

    aux = strtok(NULL, separator);
    m.model = malloc(strlen(aux) + 1);
    strcpy(m.model, aux);

    aux = strtok(NULL, separator);
    m.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m.numeSofer, aux);

    aux = strtok(NULL, separator);
    m.serie = *aux;

    return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
    FILE* f;
    Masina* masini = NULL;
    int ok = 1;

    f = fopen(numeFisier, "r");

    if (f == NULL)
    {
        return NULL;
    }
    
    *nrMasiniCitite = 0;
    Masina m = citireMasinaFisier(f, &ok);
    while (ok) {
        (*nrMasiniCitite)++;
        masini = realloc(masini, sizeof(Masina) * (*nrMasiniCitite));

        masini[*nrMasiniCitite - 1].id = m.id;
        masini[*nrMasiniCitite - 1].nrUsi = m.nrUsi;
        masini[*nrMasiniCitite - 1].pret = m.pret;

        masini[*nrMasiniCitite - 1].model = malloc(strlen(m.model) + 1);
        strcpy(masini[*nrMasiniCitite - 1].model, m.model);

        masini[*nrMasiniCitite - 1].numeSofer = malloc(strlen(m.numeSofer) + 1);
        strcpy(masini[*nrMasiniCitite - 1].numeSofer, m.numeSofer);

        masini[*nrMasiniCitite - 1].serie = m.serie;

        m = citireMasinaFisier(f, &ok);
    }

    fclose(f);

    return masini;
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
    *masini = realloc(*masini, (*nrMasini + 1) * sizeof(Masina));
    (*nrMasini)++;

    (*masini)[*nrMasini - 1].id = masinaNoua.id;
    (*masini)[*nrMasini - 1].nrUsi = masinaNoua.nrUsi;
    (*masini)[*nrMasini - 1].pret = masinaNoua.pret;

    (*masini)[*nrMasini - 1].model = malloc(strlen(masinaNoua.model) + 1);
    strcpy((*masini)[*nrMasini - 1].model, masinaNoua.model);

    (*masini)[*nrMasini - 1].numeSofer = malloc(strlen(masinaNoua.numeSofer) + 1);
    strcpy((*masini)[*nrMasini - 1].numeSofer, masinaNoua.numeSofer);

    (*masini)[*nrMasini - 1].serie = masinaNoua.serie;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
    for (int i = 0; i < *nrMasini; i++) {
        free((*vector)[i].model);
        free((*vector)[i].numeSofer);
    }

    free((*vector));
    *nrMasini = 0;
    (*vector) = NULL;
}

int main() {
    Masina* vector;
    Masina m;
    FILE* f;
    int nrMasini;

    m.id = 100;
    m.nrUsi = 5;
    m.pret = 45645;

    m.model = malloc(strlen("asdaw") + 1);
    strcpy(m.model, "asdaw");

    m.numeSofer = malloc(strlen("abcd") + 1);
    strcpy(m.numeSofer, "abcd");

    m.serie = 'D';

    vector = citireVectorMasiniFisier("masini.txt", &nrMasini);
    afisareVectorMasini(vector, nrMasini);

    adaugaMasinaInVector(&vector, &nrMasini, m);
    afisareVectorMasini(vector, nrMasini);

    dezalocareVectorMasini(&vector, &nrMasini);
    free(m.model);
    free(m.numeSofer);

    return 0;
}