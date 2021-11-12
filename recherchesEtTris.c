/* programme : recherchesEtTris.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : fonctions de recherches, de tri, de modification, d'ajout, de suppression des données de la ludothèque.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ludotheque.h"

#define TAILLEMAX 10000

/* FONCTIONS DE TRIS */

void triJeuxParNom(Jeu *tJeux[], int nbJeux)
{
	int k, rmin;
	for (k = 0; k < nbJeux - 1; k++)
	{
		rmin = rechercheRMin(tJeux, k, nbJeux);
		permutation(tJeux, k, rmin);
	}
}

int rechercheRMin(Jeu *tJeux[], int i, int n)
{
	int rmin = i, j;
	for (j = i + 1; j < n; j++)
	{
		if (strcmp(tJeux[j]->nomJeu, tJeux[rmin]->nomJeu) < 0)
			rmin = j;
	}
	return rmin;
}

void permutation(Jeu *tJeux[], int i, int j)
{
	Jeu permutation;
	permutation = *tJeux[i];
	*tJeux[i] = *tJeux[j];
	*tJeux[j] = permutation;
}

void triRapideEmpruntsParId(Emprunt **tEmp, int nbEmp)
{
	int mur, courant, pivot;
	Emprunt emp1, emp2;

	if (nbEmp <= 1)
		return;

	mur = courant = 0;
	pivot = tEmp[nbEmp - 1]->idEmprunt;
	while (courant < nbEmp)
	{
		if (tEmp[courant]->idEmprunt <= pivot)
		{
			if (mur != courant)
			{
				emp1 = *tEmp[courant];
				*tEmp[courant] = *tEmp[mur];
				*tEmp[mur] = emp1;
			}
			mur++;
		}
		courant++;
	}

	triRapideEmpruntsParId(tEmp, mur - 1);
	triRapideEmpruntsParId(tEmp + mur - 1, nbEmp - mur + 1);

	return;
}

/* FONCTIONS DE RECHERCHES */

int rechercheIdentiteAdherent(Adherent **tAdh, int nbAdh, int idAdherent, Adherent *adh)
{
	int i;

	for (i = 0; i < nbAdh; i++)
	{
		if (tAdh[i]->idAdherent == idAdherent)
		{
			strcpy(adh->nom, tAdh[i]->nom);
			strcpy(adh->prenom, tAdh[i]->prenom);
			strcpy(adh->civilite, tAdh[i]->civilite);
			adh->dateInscription.jour = tAdh[i]->dateInscription.jour;
			adh->dateInscription.mois = tAdh[i]->dateInscription.mois;
			adh->dateInscription.annee = tAdh[i]->dateInscription.annee;
			adh->idAdherent = tAdh[i]->idAdherent;
			return i;
		}

		if (tAdh[i]->idAdherent > idAdherent)
			return -1;
	}
	return -1;
}

int rechercheInfosJeux(Jeu **tJeux, int nbJeux, char nomJeu[], Jeu *jouet)
{
	int i;

	for (i = 0; i < nbJeux; i++)
	{
		if (strcmp(tJeux[i]->nomJeu, nomJeu) == 0)
		{
			jouet->idJeu = tJeux[i]->idJeu;
			jouet->nbExemplaire = tJeux[i]->nbExemplaire;
			strcpy(jouet->nomJeu, tJeux[i]->nomJeu);
			strcpy(jouet->typeJeu, tJeux[i]->typeJeu);
			return i;
		}

		if (strcmp(tJeux[i]->nomJeu, nomJeu) > 0)
			return -1;
	}

	return -1;
}

int rechercheInfosJeu2(Jeu **tJeux, int nbJeux, int idJeux, Jeu *jouet)
{
	int i;

	for (i = 0; i < nbJeux; i++)
	{
		if (tJeux[i]->idJeu == idJeux)
		{
			printf("%d", i);
			jouet->idJeu = tJeux[i]->idJeu;
			jouet->nbExemplaire = tJeux[i]->nbExemplaire;
			strcpy(jouet->nomJeu, tJeux[i]->nomJeu);
			strcpy(jouet->typeJeu, tJeux[i]->typeJeu);
			return i;
		}
	}
	return -1;
}

int rechercheIdResa(ListeReservation lr, int indice)
{
	if (lr == NULL)
		return indice;

	if (lr->r.idResa != indice)
		return indice;

	rechercheIdResa(lr->suivant, indice + 1);
}

int rechercheInfoResa(ListeReservation lr, int idResa, Reservation *reserv)
{
	if (lr == NULL)
		return 0;

	if (lr->r.idResa == idResa)
	{
		reserv->idJeux = lr->r.idJeux;
		reserv->idAdherent = lr->r.idAdherent;
		reserv->dateReservation.jour = lr->r.dateReservation.jour;
		reserv->dateReservation.mois = lr->r.dateReservation.mois;
		reserv->dateReservation.annee = lr->r.dateReservation.annee;
		return 1;
	}

	return rechercheInfoResa(lr->suivant, idResa, reserv);
}

void rechercherReservationPlusAncienne(ListeReservation lr, Emprunt **tEmp, int nbEmp, Date *dateResa, Reservation *reserv, int idJeux, Date dateActu)
{
	if (lr == NULL)
		return;

	printf("%d %d ** %d ** %d ** %d\n", idJeux, lr->r.idJeux, comparaisonDates(*dateResa, lr->r.dateReservation), compteNbEmp(tEmp, nbEmp, lr->r.idAdherent), rechercheDateEmpruntDepasse(tEmp, nbEmp, lr->r.idAdherent, dateActu));

	if (lr->r.idJeux == idJeux && comparaisonDates(*dateResa, lr->r.dateReservation) == 0)
		if (compteNbEmp(tEmp, nbEmp, lr->r.idAdherent) < 3 && rechercheDateEmpruntDepasse(tEmp, nbEmp, lr->r.idAdherent, dateActu) != 1)
		{
			printf("%d marche nickel\n", lr->r.idResa);
			*reserv = lr->r;
			*dateResa = lr->r.dateReservation;
		}

	rechercherReservationPlusAncienne(lr->suivant, tEmp, nbEmp, dateResa, reserv, idJeux, dateActu);
}

int rechercheIdEmprunt(Emprunt **tEmp, int nbEmp)
{
	int i;

	for (i = 0; i < nbEmp; i++)
	{
		if (i != tEmp[i]->idEmprunt)
			return i;
	}
	return i;
}

int rechercheEmprunt(Emprunt **tEmp, int nbEmp, int idEmp, Emprunt *emp)
{
	int i;

	for (i = 0; i < nbEmp; i++)
	{
		if (tEmp[i]->idEmprunt == idEmp)
		{
			emp->idJeu = tEmp[i]->idJeu;
			emp->idAdherent = tEmp[i]->idAdherent;
			emp->dateEmprunt.jour = tEmp[i]->dateEmprunt.jour;
			emp->dateEmprunt.mois = tEmp[i]->dateEmprunt.mois;
			emp->dateEmprunt.annee = tEmp[i]->dateEmprunt.annee;

			return i;
		}
	}
	return -1;
}

int rechercheDateEmpruntDepasse(Emprunt **tEmp, int nbEmp, int idAdherent, Date dateActu)
{
	int i;

	for (i = 0; i < nbEmp; i++)
	{
		if (tEmp[i]->idAdherent == idAdherent && validiteDateEmp(dateActu, tEmp[i]->dateEmprunt) == 1)
			return 1;
	}

	return 0;
}

int compteNbEmp(Emprunt **tEmp, int nbEmp, int idAdherent)
{
	int i, compteur = 0;

	for (i = 0; i < nbEmp; i++)
		if (tEmp[i]->idAdherent == idAdherent)
			compteur++;

	return compteur;
}











