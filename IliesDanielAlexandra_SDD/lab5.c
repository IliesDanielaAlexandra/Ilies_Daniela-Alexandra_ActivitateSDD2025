#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Masina{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;

};

typedef struct Masina Masina;

struct Nod {
	Masina masina;
	struct Nod* next;
	struct Nod* prev;
};

typedef struct Nod Nod;

struct ListaDubla {
	Nod* first; 
	Nod* last;
	int nrNoduri;
};

typedef struct ListaDubla ListaDubla;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);

	Masina m;
	m.id = atoi(strtok(buffer, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));

	char* aux;
	aux = strtok(NULL, sep);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m.model, aux);

	aux = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m.numeSofer, aux);

	m.serie = strtok(NULL, sep)[0];

	return m; 


}


void afisareMasina(Masina masina) {

	printf("ID:%d\n", masina.id);
	printf("Numar usi:%d\n", masina.nrUsi);
	printf("Pret:%.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume Sofer: %s\n", masina.numeSofer);
	printf("Serie:%c\n\n", masina.serie);
}

void afisareListaMasiniDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->masina);
		p = p->next;
	}
}
void afisareListaMasinaDeLaFinal(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->masina);
		p = p->prev;
	}
}

void adaugareMasinaInListaFinal(ListaDubla* lista, Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = NULL;
	nou->prev = lista->last;
	if(lista->last!=NULL){
		lista->last->next = nou;}
	else {
		lista->first = nou;
	}
	
    lista->last = nou;
	lista->nrNoduri++;

}
void adaugareMasinaInListaInceput(ListaDubla* lista, Masina masinaNoua){
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->next = lista->first;
	nou->prev = NULL;
	if(lista->first!=NULL){
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;

}


ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;
	while (!feof(f)) {

		adaugareMasinaInListaFinal(&lista, citireMasinaDinFisier(f));

	}
	fclose(f);
	return lista;

}

void dezalocareListaDubla(ListaDubla* lista){
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->masina.model) {
			free(aux->masina.model);
		}
		if (aux->masina.numeSofer) {
			free(aux->masina.numeSofer);
		}

		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;


}

float calculeazaPretMediu(ListaDubla lista) {
	if (lista.nrNoduri > 0) {
		float suma = 0;
		Nod* p = lista.first;
		while (p) {
			suma += p->masina.pret;
				p = p->next;
		}
		return suma / lista.nrNoduri;
	}
}

int main(){

	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniDeLaInceput(lista);

	printf("//////       /// \n");
	afisareListaMasinaDeLaFinal(lista);

	printf("//////       /// \n");
	

	float pretMediu = calculeazaPretMediu(lista);
	printf("Pret mediu este : %.2f\n", pretMediu);


	printf("//////       /// \n");
	dezalocareListaDubla(&lista);
	return 0;
}