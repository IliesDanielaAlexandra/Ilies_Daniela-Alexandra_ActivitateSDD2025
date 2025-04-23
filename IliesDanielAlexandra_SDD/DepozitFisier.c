#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Depozit {
	int id;
	char* denumire;
	int capacitate;
	char* locatie;

};
typedef struct Depozit Dep;


void afisareDepozit2(struct Depozit d) {
	if (d.denumire != NULL) {
		if (d.locatie != NULL) {
			printf("%d. Depozitul %s are capacitatea de %d tone si se afla in %s. \n", d.id, d.denumire, d.capacitate, d.locatie);
		}
		else {
			printf("%d. Depozitul %s are capacitatea de %d tone  si este ****FARA LOCATEIE***. \n", d.id, d.denumire, d.capacitate, d.locatie);
		}

	}
	else {
		if (d.locatie != NULL) {
			printf("%d.  Depozitul ***NON-NAME*** are capacitatea de %d tone si se afla in %s. \n", d.id, d.denumire, d.capacitate, d.locatie);
		}
		else {
			printf("%d.  Depozitul ***NON-NAME*** are capacitatea de %d tone si este  ****FARA LOCATEIE***. \n", d.id, d.capacitate);
		}
	}
}

void afisareVectorDepozite (Dep* verctorD, int nrDepozite){
	for (int i = 0; i < nrDepozite; i++) {
		afisareDepozit(verctorD[i]);
	}
}


void adaugareDepoziteInVector(Dep** depozite , int* nrDepozite, Dep depozitNou){
	Dep* aux = (Dep*)malloc(sizeof(Dep) * ((*nrDepozite) + 1));
	for (int i = 0; i < *nrDepozite; i++) {
		aux[i] = (*depozite)[i];
	}
	aux[(*nrDepozite)] = depozitNou;
	free(*depozite);
	(*depozite) = aux;
	(*nrDepozite)++;
}

Dep citireDepozitDinFisier(FILE *file) {
	Dep d;
	char buffer[100];
	char sep[4] = ",;\n";
	fgets(buffer, 100, file);

	d.id = atoi(strtok(buffer, sep));

	char* aux;
	aux = strtok(NULL, sep);
	d.denumire = (char*)malloc(strlen(aux) + 1);
	strcpy(d.denumire, aux);

	d.capacitate = atoi(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	d.locatie = (char*)malloc(strlen(aux) + 1);
	strcpy(d.locatie, aux);

	return d;
}
Dep* citireVectorDepoziteDinFisier(const char* numeFisier, int* nrDepoziteCitite) {
	FILE* file = fopen(numeFisier, "r");
	Dep* depozit = NULL;
	(*nrDepoziteCitite) = 0;
	while (!feof(file)) {
		adaugareDepoziteInVector(&depozit, nrDepoziteCitite, citireDepozitDinFisier(file));
	}
	fclose(file);
	return depozit;
}

void dezalocareVectorDepozite(Dep** depozite, int* nrDepozite) {
	for (int i = 0; i < *nrDepozite; i++) {

		if ((*depozite)[i].denumire != NULL) {
			free((*depozite)[i].denumire);
		}

		if ((*depozite)[i].locatie != NULL) {
			free((*depozite)[i].locatie);
		}


	}

	free(*depozite);
	(*depozite) = NULL;
	(*nrDepozite) = 0;
}


int main(){

	int nrDepozite = 0;
	Dep* depozite = citireVectorDepoziteDinFisier("depozite.txt", &nrDepozite);
	afisareVectorDepozite(depozite, nrDepozite);

	dezalocareVectorDepozite(&depozite, &nrDepozite);

	return 0;
}

