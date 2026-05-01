#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

typedef struct Nod {
    Masina info;
    struct Nod* next;
    struct Nod* prev;
} Nod;

typedef struct ListaDubla {
    Nod* head;
    Nod* tail;
} ListaDubla;

Masina citireMasinaDinFisier(FILE* file, int* success) {
	Masina m;
    char buffer[100];
    char separator[3] = ",\n";
    char* aux;

    if (!fgets(buffer, 100, file))
    {
        *success = 0;
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

    *success = 1;
    return m;
}

void adaugaMasinaInLista(ListaDubla* lista, Masina masinaNoua) {
    Nod* nodNou = malloc(sizeof(Nod));

    nodNou->info = masinaNoua;
    nodNou->prev = lista->tail;
    nodNou->next = NULL;

    if (lista->tail == NULL)
    {
        lista->head = nodNou;
        lista->tail = nodNou;
    } else {
        lista->tail->next = nodNou;
        lista->tail = nodNou;
    }
}

ListaDubla* citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f;
    ListaDubla* lista = (ListaDubla*)malloc(sizeof(ListaDubla));
    lista->head = NULL;
    lista->tail = NULL;
    int ok = 1;

    f = fopen(numeFisier, "r");

    if (f == NULL)
    {
        return lista;
    }

    Masina m = citireMasinaDinFisier(f, &ok);
    while (ok)
    {
        adaugaMasinaInLista(lista, m);
        m = citireMasinaDinFisier(f, &ok);
    }

    fclose(f);

    return lista;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(ListaDubla* lista) {
    Nod* temp = lista->head;
	
    while (temp != NULL)
    {
        afisareMasina(temp->info);
        temp = temp->next;
    }
}

void dezalocareLista(ListaDubla* lista) {
    Nod* temp = lista->head;

    while (temp != NULL) {
        Nod* aux = temp->next;

        free(temp->info.model);
        free(temp->info.numeSofer);
        free(temp);

        temp = aux;
    }

    free(lista);
}

void main() {
    ListaDubla* lista = citireLDMasiniDinFisier("masini.txt");

    afisareListaMasini(lista);

    dezalocareLista(lista);
}
