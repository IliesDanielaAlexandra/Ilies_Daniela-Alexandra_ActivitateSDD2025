#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Farmacie {
	int id;
	char* denumire;
	float suprafata;
	unsigned char nrAngajati;
	char* adresa;

};
typedef struct Farmacie Farmacie;
struct Nod {
	 Farmacie info;
	struct Nod* next;
};

typedef struct Nod Nod; 

Farmacie citireFarmacieDinFisier(FILE* file) {
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);

	Farmacie f;
	f.id = atoi(strtok(buffer, sep));
	
	char* aux;

	aux = strtok(NULL, sep);
	f.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy(f.denumire, aux);

	f.suprafata = atoi(strtok(NULL, sep));
	f.nrAngajati = atoi(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	f.adresa = (char*)malloc(strlen(aux) + 1);
	strcpy(f.adresa, aux);

	return f;


}

void afisareFarmacie(Farmacie farmacie) {
	printf("ID: %d\n", farmacie.id);
	printf("Denumire: %s\n", farmacie.denumire);
	printf("Suprafata: %.2f\n", farmacie.suprafata);
	printf("Numar angajati: %d\n", farmacie.nrAngajati);
	printf("Adresa: %s\n", farmacie.adresa);
}

void afisareListaFarmacii(Nod* cap) {
	while (cap != NULL) {
		afisareFarmacie(cap->info);
		cap = cap->next;
	}
}

void adaugareFarmacieInListaFinal(Nod* *cap, Farmacie farmacie) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = farmacie;
	nou->next = NULL;

	if (*cap) {

		Nod* f = *cap;
		while (f->next) {
			f = f->next;
		}
		f->next = nou;
	}
	else {
		*cap = nou;

	}
}

void adaugareFarmacieInListaInceput(Nod** cap, Farmacie farmacie) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = farmacie;
	nou->next = *cap;
	*cap = nou;
}


Nod* citireListaFarmaciiDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if(f){
		while(!feof(f)) {
			adaugareFarmacieInListaFinal(&cap, citireFarmacieDinFisier(f));
		}
		fclose(f);

		return cap;
	}

}

void dezalocareLista(Nod* *cap){
	while (*cap) {
		Nod* f = *cap;
		(*cap) = (*cap)->next;
		if (f->info.denumire) {
			free(f->info.denumire);

		}
		if (f->info.adresa) {
			free(f->info.adresa);
		}
		free(f);
	}

}

int main() {

	Nod* cap = citireListaFarmaciiDinFisier("farmacii.txt");
	afisareListaFarmacii(cap);
	
	dezalocareLista(&cap);

	return 0;


}


