#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StructuraMasina Masina;
typedef struct Nod Nod;

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

struct Nod {
    Masina masina;
    Nod* next;
};

void afisareMasina(Masina masina) {
	printf("Id:          %d\n", masina.id);
	printf("Numar usi:   %d\n", masina.nrUsi);
	printf("Pret:        %.2f\n", masina.pret);
	printf("Model:       %s\n", masina.model);
	printf("Nume:        %s\n", masina.numeSofer);
	printf("Serie:       %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* head) {
    while (head != NULL)
    {
        afisareMasina(head->masina);
        head = head->next;
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

void adaugaMasinaInLista(Nod** head, Masina m) {
    Nod* nodNou = malloc(sizeof(Nod));

    nodNou->masina.id = m.id;
    nodNou->masina.nrUsi = m.nrUsi;
    nodNou->masina.pret = m.pret;

    nodNou->masina.model = malloc(strlen(m.model) + 1);
    strcpy(nodNou->masina.model, m.model);

    nodNou->masina.numeSofer = malloc(strlen(m.numeSofer) + 1);
    strcpy(nodNou->masina.numeSofer, m.numeSofer);

    nodNou->masina.serie = m.serie;
    nodNou->next = NULL;

    if(*head == NULL) {
        *head = nodNou;
        return;
    }

    Nod* temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = nodNou;
}

void adaugaLaInceputInLista(Nod** head, Masina m) {
    Nod* nodNou = malloc(sizeof(Nod));

    nodNou->masina.id = m.id;
    nodNou->masina.nrUsi = m.nrUsi;
    nodNou->masina.pret = m.pret;

    nodNou->masina.model = malloc(strlen(m.model) + 1);
    strcpy(nodNou->masina.model, m.model);

    nodNou->masina.numeSofer = malloc(strlen(m.numeSofer) + 1);
    strcpy(nodNou->masina.numeSofer, m.numeSofer);

    nodNou->masina.serie = m.serie;

    nodNou->next = *head;

    *head = nodNou;
}

void stergeMasiniDinSeria(Nod** head, char serieCautata) {
    if ((*head) == NULL)
    {
        return;
    } else if ((*head)->next == NULL && (*head)->masina.serie == serieCautata) {
        *head = NULL;
        return;
    }

    Nod* prev = *head;
    Nod* current = prev->next;

	while (current != NULL)
    {
        if (current->masina.serie == serieCautata) {
            Nod* temp = current;
            prev->next = current->next;
            current = current->next;
            free(temp->masina.model);
            free(temp->masina.numeSofer);
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

Nod* citireListaMasiniFisier(const char* numeFisier) {
    FILE* f;
    Nod* head = NULL;
    int ok = 1;

    f = fopen(numeFisier, "r");

    if (f == NULL)
    {
        return head;
    }
    
    Masina m = citireMasinaFisier(f, &ok);
    while (ok) {
        adaugaMasinaInLista(&head, m);

        m = citireMasinaFisier(f, &ok);
    }

    fclose(f);

    return head;
}

float calculeazaPretMediu(Nod* head) {
    float total = 0;
    int i = 0;

    while (head != NULL)
    {
        total += head->masina.pret;
        head = head->next;
        i++;
    }
    
	return total / i;
}

void dezalocareListaMasini(Nod** head) {
    Nod* temp;

    while (*head != NULL)
    {
        temp = *head;
        free(temp->masina.model);
        free(temp->masina.numeSofer);

        *head = (*head)->next;
        free(temp);
    }
    
    *head = NULL;
}

int main() {
    Nod* head;
    FILE* f;

    head = citireListaMasiniFisier("masini.txt");
    afisareListaMasini(head);

    float pretMediu = calculeazaPretMediu(head);
    printf("Pret mediu: %.2f\n", pretMediu);

    dezalocareListaMasini(&head);
    return 0;
}