/* programme : testLudotheque.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : fonctions de tests et fonction principale qui proposent plusieurs services au sein d'une ludothèque (réservations, emprunts de jeux).
*/

#include <stdio.h>
#include <stdlib.h>
#include"ludotheque.h"

#define TAILLEMAX 10000

/*
Nom : testChargementReservations
Finalité : fonction de test qui charge, affiche et enregistre les données des réservations.

Description générale :
	-Cette fonction crée une liste vide de réservations.
	-Elle appelle la fonction de chargement depuis le fichier régulier.
	-Elle appelle la fonction d'affichage de cette liste.
	-Elle enregistre les données finalement chargées dans un fichier régulier.
	-Elle appelle une fonction qui libère la mémoire.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: 
	-erreur : entier. Variable qui reçoit la valeur retournée par la fonction d'enregistrement. 
	Si elle vaut -1, il y a eu un problème de sauvegarde.
	-lr, une liste de réservation. Initialisée avec la fonction creerListeVide, elle est ensuite remplie de données depuis la fonction de chargement.
*/

void testChargementReservations(void)
{
	int erreur;
	ListeReservation lr;

	lr = creerListeVide();

	lr = chargementReservation(lr);
	if (lr == NULL)
		return;

	printf("\nRESERVATIONS :\n\n");

	affichageReservations(lr);

	printf("\n\n");

	erreur = enregistrementReservation(lr);
	if (erreur == -1)
		return;

	lr = suppressionListe(lr);
}

/*
Nom : testChargementAdherent
Finalité : fonction de test qui charge, enregistre et affiche les données des adhérents. 
Elle permet de tester les fonctions de sauvegarde, de chargement, et d'affichage.

Description générale :
	-Cette fonction crée deux tableaux de pointeurs sur des structures d'adhérents.
	-Elle appelle la fonction de chargement depuis le fichier régulier.
	-Elle appelle la fonction d'affichage de ce tableau.
	-Elle enregistre les données finalement chargées dans un fichier binaire.
	-Elle charge ces nouvelles données depuis un autre tableau de pointeurs.
	-Elle les affiche et libère enfin la mémoire.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: 
	-erreur : entier. Variable qui reçoit la valeur retournée par la fonction d'enregistrement.
	Si elle vaut -1, il y a eu un problème de sauvegarde.
	-nbAdh, la taille logique du tableau de pointeurs, renvoyé par les fonctions de chargement. Si elle vaut -1, il y a eu un problème de chargement.
	-**tAdh et **tAdh2 : des tableaux de pointeurs sur la structure Adherent. Le premier est chargé depuis un fichier réglier, le second depuis un fichier binaire.
	-i : compteur de boucle pour libérer la mémoire.
*/

void testChargementAdherent(void)
{
	int nbAdh, erreur;
	Adherent *tAdh[TAILLEMAX];
	Adherent *tAdh2[TAILLEMAX];

	nbAdh = chargementAdherent(tAdh);
	if (nbAdh == -1)
		return;

	printf("ADHERENT :\n\n");

	affichageAdherent(tAdh, nbAdh);
	printf("\n\n");

	erreur = enregistrementAdherent(tAdh, nbAdh);
	if (erreur == -1)
		return;

	printf("\nVERSION FICHIER BINAIRE :\n\n");

	nbAdh = chargementAdherentBin(tAdh2);
	if (nbAdh == -1)
		return;

	affichageAdherent(tAdh2, nbAdh);

	for (int i = 0; i < nbAdh; i++)
	{
		free(tAdh[i]);
		free(tAdh2[i]);
	}
}

/*
Nom : testChargementJeux
Finalité : fonction de test qui charge, enregistre et affiche les données des jeux. 
Elle permet de tester les fonctions de sauvegarde, de chargement, et d'affichage.

Description générale :
	-Cette fonction crée deux tableaux de pointeurs sur des structures de Jeu.
	-Elle appelle la fonction de chargement depuis le fichier régulier.
	-Elle appelle la fonction d'affichage de ce tableau.
	-Elle enregistre les données finalement chargées dans un fichier binaire.
	-Elle charge ces nouvelles données depuis un autre tableau de pointeurs.
	-Elle les affiche et libère enfin la mémoire.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: 
	-erreur : entier. Variable qui reçoit la valeur retournée par la fonction d'enregistrement.
	Si elle vaut -1, il y a eu un problème de sauvegarde.
	-nbJeux, la taille logique du tableau de pointeurs, renvoyé par les fonctions de chargement. Si elle vaut -1, il y a eu un problème de chargement.
	-**tJeux et **tJeux2 : des tableaux de pointeurs sur la structure Jeu. Le premier est chargé depuis un fichier réglier, le second depuis un fichier binaire.
	-i : compteur de boucle pour libérer la mémoire.
*/

void testChargementJeux(void)
{
	int nbJeux, erreur;
	Jeu *tJeux[TAILLEMAX];
	Jeu *tJeux2[TAILLEMAX];

	nbJeux = chargementJeux(tJeux);
	if (nbJeux == -1)
		return;

	printf("JEUX :\n\n");

	affichageJeux(tJeux, nbJeux);

	erreur = enregistrementJeux(tJeux, nbJeux);
	if (erreur == -1)
		return;

	printf("\nVERSION FICHIER BINAIRE :\n\n");

	nbJeux = chargementJeuxBin(tJeux2);
	if (nbJeux == -1)
		return;

	affichageJeux(tJeux2, nbJeux);
	printf("\n\n");

	for (int i = 0; i < nbJeux; i++)
	{
		free(tJeux[i]);
		free(tJeux2[i]);
	}
}

/*
Nom : testChargementEmprunt
Finalité : fonction de test qui charge, enregistre et affiche les données des emprunts. 
Elle permet de tester les fonctions de sauvegarde, de chargement, et d'affichage.

Description générale :
	-Cette fonction crée deux tableaux de pointeurs sur des structures de Emprunt.
	-Elle appelle la fonction de chargement depuis le fichier régulier.
	-Elle appelle la fonction d'affichage de ce tableau.
	-Elle enregistre les données finalement chargées dans un fichier binaire.
	-Elle charge ces nouvelles données depuis un autre tableau de pointeurs.
	-Elle les affiche et libère enfin la mémoire.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: 
	-erreur : entier. Variable qui reçoit la valeur retournée par la fonction d'enregistrement.
	Si elle vaut -1, il y a eu un problème de sauvegarde.
	-nbEmp, la taille logique du tableau de pointeurs, renvoyé par les fonctions de chargement. Si elle vaut -1, il y a eu un problème de chargement.
	-**tEmp et **tEmp2 : des tableaux de pointeurs sur la structure Emprunt. Le premier est chargé depuis un fichier réglier, le second depuis un fichier binaire.
	-i : compteur de boucle pour libérer la mémoire.
*/

void testChargementEmprunt(void)
{
	int erreur, nbEmp;
	Emprunt *tEmp[TAILLEMAX];
	Emprunt *tEmp2[TAILLEMAX];

	nbEmp = chargementEmprunt(tEmp);
	if (nbEmp == -1)
		return;

	printf("EMPRUNT : \n\n");

	affichageEmprunt(tEmp, nbEmp);

	erreur = enregistrementEmprunt(tEmp, nbEmp);
	if (erreur == -1)
		return;

	printf("\nVERSION FICHIER BINAIRE :\n\n");

	nbEmp = chargementEmpruntBin(tEmp2);
	if (nbEmp == -1)
		return;

	affichageEmprunt(tEmp2, nbEmp);
	printf("\n\n");

	for (int i = 0; i < nbEmp; i++)
	{
		free(tEmp[i]);
		free(tEmp2[i]);
	}
}

/*
Nom : testTriJeux
Finalité : fonction de test qui crée un tableau de jeux, le charge, l'affiche, le trie, et l'affiche à nouveau.

Description générale :
	-Cette fonction crée un tableau de pointeurs sur une structure de Jeu.
	-Elle appelle la fonction de chargement depuis le fichier binaire.
	-Elle appelle la fonction d'affichage de ce tableau.
	-Elle appelle ensuite la fonction qui va trier ce tableau par ordre alphabétique du nom des jeux.
	-Elle appelle à nouveau la fonction d'affichage.
	-Elle libère enfin la mémoire.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: 
	-nbJeux, la taille logique du tableau de pointeurs, renvoyé par la fonction de chargement. Si elle vaut -1, il y a eu un problème de chargement.
	-**tJeux : un tableau de pointeurs sur la structure Jeu. Il est chargé depuis un fichier binaire.
	-i : compteur de boucle pour libérer la mémoire.
*/

void testTriJeux(void)
{
	Jeu *tJeux[TAILLEMAX];
	int nbJeux, i;
	nbJeux = chargementJeuxBin(tJeux);
	if (nbJeux == -1)
		return;

	affichageJeux(tJeux, nbJeux);
	printf("\n\n");


	triJeuxParNom(tJeux, nbJeux);
	affichageJeux(tJeux, nbJeux);

	for (i = 0; i < nbJeux; i++)
		free(tJeux[i]);
}

void testRechercheEtCompDates(void)
{
	int resultatComp, idJeux = 1;
	ListeReservation lr;
	Date d1 = {03, 05, 1970};
	Date d2 = {18, 07, 2002};
	Date d3 = {32, 13, 10000};
	Reservation reserv;

	lr = creerListeVide();

	lr = chargementReservation(lr);
	if (lr == NULL)
		return;

	resultatComp = comparaisonDates(d1, d2);

	if (resultatComp == 0)
		printf("La date %02d/%02d/%04d est plus grande que la date %02d/%02d/%04d\n", d1.jour, d1.mois, d1.annee, d2.jour, d2.mois, d2.annee);
	else if (resultatComp == 1)
		printf("La date %02d/%02d/%04d est plus petite que la date %02d/%02d/%04d\n", d1.jour, d1.mois, d1.annee, d2.jour, d2.mois, d2.annee);
	else
		printf("La date %02d/%02d/%04d est égale à la date %02d/%02d/%04d\n", d1.jour, d1.mois, d1.annee, d2.jour, d2.mois, d2.annee);

	//rechercherReservationPlusAncienne(lr, &d3, &reserv, idJeux);

	printf("La date de réservation la plus ancienne pour le jeu %d est : %02d/%02d/%04d\n", idJeux, d3.jour, d3.mois, d3.annee);
	printf("%d %d %d\n", reserv.idResa, reserv.idAdherent, reserv.idJeux);

	lr = suppressionListe(lr);
}

void testTriEmprunts(void)
{
	Emprunt *tEmp[TAILLEMAX];
	int nbEmp, i;
	nbEmp = chargementEmpruntBin(tEmp);
	if (nbEmp == -1)
		return;

	affichageEmprunt(tEmp, nbEmp);
	printf("\n\n");


	triRapideEmpruntsParId(tEmp, nbEmp);
	affichageEmprunt(tEmp, nbEmp);

	for (i = 0; i < nbEmp; i++)
		free(tEmp[i]);
}

/*
Nom : main
Finalité : fonction principale qui appelle la fonction globale.

Description générale :
	-Cette fonction est appellée au lancement du programme.
	-Elle appelle la fonction globale.

Paramètres en entrée : Aucun

Valeur retournée : 0 (tout s'est bien fini)

Variables locales: Aucune
*/

int main(void)
{
	restaurationDonneesFichiers();
	globale();
	//testTriJeux();
	//testTriEmprunts();
	return 0;
}