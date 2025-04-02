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

struct Depozit initializareD(int id, const char* denumire, int capacitate,const char* locatie){
	struct Depozit d;
	d.id = id;
	d.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy_s(d.denumire, strlen(denumire) + 1, denumire);
	d.capacitate = capacitate;
	d.locatie = (char*)malloc(sizeof(char) * (strlen(locatie) + 1));
	strcpy_s(d.locatie, strlen(locatie) + 1, locatie);

	return d;

}

void afisareDepozit(struct Depozit d) {
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

void modificareCapacitate(struct Depozit* d, int nouaCapacitate) {
	if (nouaCapacitate > 0) {
		d->capacitate=nouaCapacitate;
	}
}

void modificareLocatie(struct Depozit* d, const char* nouaLocatie){
	if(nouaLocatie!=NULL){
	 if (d->locatie !=NULL) {
		 free(d->locatie);
	 }
	 d->locatie = (char*)malloc(sizeof(char) * (strlen(nouaLocatie) + 1));
	 strcpy_s(d->locatie, strlen(nouaLocatie) + 1, nouaLocatie);

	}
}

void dezalocareDepozite(struct Depozit** depozite, int* nrDepozite) {
	for (int i = 0; i < (*nrDepozite); i++) {

		if ((*depozite)[i].denumire != NULL) {
			free((*depozite)[i].denumire);
		}
		if ((*depozite)[i].locatie != NULL) {
			free((*depozite)[i].locatie);
		}
	}
}




int main(){

	struct Depozit* depozite = NULL;
	int nrDepozite = 3;
	depozite = (struct Depozit*)malloc(sizeof(struct Depozit) * nrDepozite);
	depozite[0] = initializareD(1, "Depozit1", 1000, "Bucuresti");
	depozite[1] = initializareD(2, "Depozit2", 2000, "Brasov");
	depozite[2] = initializareD(3, "Depozit3", 2500, "Cluj");


	for (int i = 0; i < nrDepozite; i++) {
		afisareDepozit(depozite[i]);
	}

	printf("\n aplicam modificari :\n");
	modificareCapacitate(&depozite[1], 500);
	afisareDepozit(depozite[1]);
	modificareLocatie(&depozite[2], "Iasi");
	afisareDepozit(depozite[2]);


	dezalocareDepozite(&depozite, &nrDepozite);
	

	return 0;
}
