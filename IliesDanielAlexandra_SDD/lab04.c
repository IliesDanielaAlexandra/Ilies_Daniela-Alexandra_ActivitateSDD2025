#define _CRT_SECURE_NO_WARNINGS
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

struct Nod {
	Masina info;
	struct Nod* next;

};

typedef struct Nod Nod;



Masina citireMasinaDinFisie(FILE* file) {
	char buffer[100];
	char sep[4] = ",;\n ";
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
	printf("Model:%s\n", masina.model);
	printf("Nume Sofer:%s\n", masina.numeSofer);
	printf("Serie:%d\n\n", masina.serie);

}

void afisareListaMasini(Nod* cap){
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}

}
void adaugareMasiniInListaFinal(Nod* *cap , Masina masinaNoua){
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua ; 
	nou->next = NULL;
	if (*cap) {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {

		*cap = nou;
	}
}

void adaugareMasinaInListaInceput(Nod* *cap, Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	*cap = nou;
}

Nod* citireListaMasiniDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		while (!feof(f)) {
			// creem lista cu inserare la sfarsit
			adaugareMasiniInListaFinal(&cap, citireMasinaDinFisie(f));
		}
	}
	fclose(f);
	return cap;
}

void dezalocareLista(Nod* *cap){
	while (*cap) {
		Nod* p = *cap;
		(*cap) = (*cap)->next;
		if (p->info.model) {
			free(p->info.model);
		}
		if (p->info.numeSofer) {
			free(p->info.numeSofer);
		}

		free(p);

	}
}




int main(){

	Nod* cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	dezalocareLista(&cap);

	return 0;
}
