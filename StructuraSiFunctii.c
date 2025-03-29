#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Depozit
{
	int id;
	char* denumire;
	int nrProduse;
	float* preturi;
};



struct Depozit citireDepozit() {
	struct Depozit depozit;
	printf("Id:");
	scanf("%d", &depozit.id);

	depozit.denumire = (char*)malloc(50 * sizeof(char));
	if (depozit.denumire == NULL) {
		printf("Erroare alocare memorie!");
		exit(1);

	}

	printf("Denumire depozit:");
	getchar();
	fgets(depozit.denumire, 50, stdin);

	depozit.denumire[strcspn(depozit.denumire, "\n")] = 0;

	printf("Numarul de produse:");
	scanf("%d", &depozit.nrProduse);

	depozit.preturi = (float*)malloc(depozit.nrProduse * sizeof(float));
	if (depozit.preturi == NULL) {
		printf("Erroare alocare memorie!");
		exit(1);

	}

	printf("Intriduceti preturile:\n");
	for (int i = 0; i < depozit.nrProduse; i++) {
		printf("Pretul produsului %d: ", i + 1);
		scanf("%f", &depozit.preturi[i]);

	}
	return depozit;
}

	void afisareDepozit(struct Depozit depozit){
		printf("\nDepozit:\n");
		printf("ID: %d\n", depozit.id);
		printf("Denumire: %s\n", depozit.denumire);
		printf("Numar Produse: %d\n", depozit.nrProduse);
		printf("Preturi produse:\n");
		for (int i = 0; i < depozit.nrProduse; i++) {
			printf("Produsul %d: %.2f\n", i + 1, depozit.preturi[i]);

		}

	}

// functie medie preturi prduse 

	float calculeazaMediePreturi(struct Depozit d) {
		float sum = 0.0;
		for (int i = 0; i < d.nrProduse; i++) {
			sum += d.preturi[i];

	}
		return sum / d.nrProduse;
	}
 
	// Modificare denumire depozit 

	void modificareDenumireDepozit(struct Depozit* depozit, const char* denumireNoua){
		free(depozit->denumire);
		depozit->denumire = (char*)malloc(strlen(denumireNoua) + 1);
		if (depozit->denumire == NULL) {
			printf("Erroare alocare memorie nume!\n");
			exit(1);
		}
		strcpy(depozit->denumire, denumireNoua);
	}


	void modificarePretProdus(struct Depozit* depozit, int indexProdus, float pretNou) {
		if (indexProdus >= 0 && indexProdus < depozit->nrProduse) {
			depozit->preturi[indexProdus] = pretNou;
			printf("Pretul produsului %d a fost actualizar la %.2f\n", indexProdus + 1, pretNou);
		}
		else {
			printf("Index invalid!\n");
		}
	}

	struct Depozit* filtreazaDepozite(struct Depozit* depozite, int nrDepozite, int* nrFiltrate) {
		struct Depozit* depoziteFiltrate = (struct Depozit*)malloc(nrDepozite * sizeof(struct Depozit));
		if (depoziteFiltrate != NULL) {
			int dep = 0;
			for (int i = 0; i < nrDepozite; i++) {
				if (depozite[i].nrProduse < 5) {
					depoziteFiltrate[dep] = depozite[i];
					dep++;
				}
			}
		
		*nrFiltrate = dep;
		return depoziteFiltrate;
	}

	}

	// Modificare pret produs 

	int  main() {
		struct Depozit depozit = citireDepozit();
		afisareDepozit(depozit);

		float mediePreturiDepozit = calculeazaMediePreturi(depozit);
		printf("Media preturilor pe depozitul :%.2f\n", mediePreturiDepozit);


		modificareDenumireDepozit(&depozit, "AltexNou");

		modificarePretProdus(&depozit, 2, 150.5);

		afisareDepozit(depozit);


		// tasck 2 Vectori

		int nrDepozite = 5;

		struct Depozit* depozite = (struct Depozit*)malloc(nrDepozite * sizeof(struct Depozit));

		if (depozite != NULL) {
			for (int i = 0; i < nrDepozite; i++) {
				printf("Introduceti datele depozitului %d:\n", i + 1);
				depozite[i] = citireDepozit();
			}

		}
		else {
			printf("erroare alocare depozit");
			exit(1);
		}
		for (int i = 0; i < nrDepozite; i++) {
			printf("\nInformatii depozit %d:\n", i + 1);
			afisareDepozit(depozite[i]);
		}

		for (int i = 0; i < nrDepozite; i++) {
			free(depozite[i].denumire);
			free(depozite[i].preturi);
		}

		int depFiltrate = 0;
		struct Depozit* depoziteFiltrate = filtreazaDepozite(depozite, nrDepozite, &depFiltrate);

		printf("\nDepozite filtrate:\n");
		for (int i = 0; i < depFiltrate; i++) {
			afisareDepozit(depoziteFiltrate[i]);
		}


		free(depozite);
		free(depoziteFiltrate);

		free(depozit.denumire);
		free(depozit.preturi);
		return 0;
	}

