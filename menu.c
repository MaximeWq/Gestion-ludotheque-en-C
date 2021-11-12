/* programme : menu.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : fichier contenant les fonctions des menus, fonctions d'affichages des menus. Il contient aussi la fonction globale (principale) qui réalise les chargements / enregistrements et appelle le menu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ludotheque.h"

#define TAILLEMAX 10000

/*
Nom : calibrage
Finalité : fonction qui invite l'utilisateur à redimensionner sa fenêtre afin d'avoir un meilleur affichage.

Description générale :
	-Cette fonction efface le contenu du Terminal.
	-Elle affiche des message invitant l'utilisateur à redimensionner sa fenêtre.
	-Elle attend qu'il appuie sur entrée lorsqu'il a terminé.

Paramètres en entrée : Aucuns

Valeur retournée : Aucune

Variables locales: Aucune
*/

void calibrage(void)
{
	system("clear");
	printf("Pour un affichage optimal, nous vous conseillons de redimensionner le terminal de telle sorte que la ligne ci-dessous remplisse la fenêtre dans toute sa largeur.\n\n");

	printf("Appuyez sur entrée lorsque vous avez fini.\n\n");

	printf("**********************************************************************************\n");

	getchar();
}

/*
Nom : affichageSousMenuJeux
Finalité : fonction permettant l'affichage des données du sous menu de l'affichage des jeux.

Description générale :
	-Cette fonction est appelée depuis le sous-menu.
	-Elle affiche les différents choix possibles du sous menu des jeux.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: Aucune 
*/

void affichageSousMenuJeux(void)
{
	system("clear");
	printf("\n**********************************************************************************\n");
	printf("\t\t\t1-Afficher les jeux de type carte\n");
	printf("\t\t\t2-Afficher les jeux de type construction\n");
	printf("\t\t\t3-Afficher les jeux de type logique\n");
	printf("\t\t\t4-Afficher les jeux de type plateau\n");
	printf("\t\t\t5-Afficher les jeux de type tuile\n");
	printf("\t\t\t6-Afficher tous les types de jeux\n");
	printf("\t\t\t9-Menu Principal\n");
	printf("**********************************************************************************\n");
	printf("Quel est votre choix ? ");
}

/*
Nom : sousMenuJeux
Finalité : fonction du sous-menu qui gère les entrées de l'utilisateur et appelle les fonctions demandées (d'affichages).

Description générale :
	-Cette fonction est appelée depuis la fonction menu et reçoit les différentes données.
	-Elle appelle une fonction d'affichage.
	-Elle récupère l'entrée de l'utilisateur et appelle diverses fonctions en conséquence (jusqu'à ce qu'il quitte).

Paramètres en entrée : 
	-Jeu **tJeux : un tableau de pointeurs de type Jeu, contenant les données des Jeux.
	-int nbJeux : la taille logique de ce tableau de pointeur.

Valeur retournée : Aucune.

Variables locales: choix : entier. Choix de l'utilisateur dans le sous-menu, récupéré depuis une entrée. 

Constantes :
	choix1, choix2, choix3, choix4, choix5, choix6, choix9 : valeurs entières de choix prédéfinies.
*/

void sousMenuJeux(Jeu **tJeux, int nbJeux)
{
	int choix, compteur;
	int choix1 = 1, choix2 = 2, choix3 = 3, choix4 = 4, choix5 = 5, choix6 = 6, choix9 = 9, pasDAffichage = 0;

	affichageSousMenuJeux();
	scanf("%d%*c", &choix);

	while (choix != choix9)
	{
		if (choix == choix1)
		{
			printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");
			compteur = affichageJeuxDunType(tJeux, nbJeux, "carte");
			if (compteur == pasDAffichage)
				printf("Il ne semble pas y avoir de jeux pour ce type...\n");
		}

		else if (choix == choix2)
		{
			printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");
			compteur = affichageJeuxDunType(tJeux, nbJeux, "construction");
			if (compteur == pasDAffichage)
				printf("Il ne semble pas y avoir de jeux pour ce type...\n");
		}

		else if (choix == choix3)
		{
			printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");
			compteur = affichageJeuxDunType(tJeux, nbJeux, "logique");
			if (compteur == pasDAffichage)
				printf("Il ne semble pas y avoir de jeux pour ce type...\n");
		}

		else if (choix == choix4)
		{
			printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");
			compteur = affichageJeuxDunType(tJeux, nbJeux, "plateau");
			if (compteur == pasDAffichage)
				printf("Il ne semble pas y avoir de jeux pour ce type...\n");
		}

		else if (choix == choix5)
		{
			printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");
			compteur = affichageJeuxDunType(tJeux, nbJeux, "tuile");
			if (compteur == pasDAffichage)
				printf("Il ne semble pas y avoir de jeux pour ce type...\n");
		}

		else if (choix == choix6)
		{
			affichageJeuxDisponibles(tJeux, nbJeux);
		}

		else
			printf("Veuillez faire un choix correct\n");

		printf("\nAppuyez sur entrée pour continuer...\n");
		getchar();

		affichageSousMenuJeux();
		scanf("%d%*c", &choix);
	}
}

/*
Nom : affichageSousMenu
Finalité : fonction permettant l'affichage des données du sous menu principal.

Description générale :
	-Cette fonction est appelée depuis le sous-menu.
	-Elle affiche les différents choix possibles du sous menu.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: Aucune 
*/

void affichageSousMenu(void)
{
	system("clear");
	printf("\n**********************************************************************************\n");
	printf("\t\t\t1-Afficher la liste des Jeux disponibles\n");
	printf("\t\t\t2-Afficher la liste des emprunts\n");
	printf("\t\t\t3-Afficher la liste des réservations d'un jeu\n");
	printf("\t\t\t9-Menu Principal\n");
	printf("**********************************************************************************\n");
	printf("Quel est votre choix ? ");
}

/*
Nom : sousMenu
Finalité : fonction du sous-menu qui gère les entrées de l'utilisateur et appelle les fonctions demandées (d'affichages).

Description générale :
	-Cette fonction est appelée depuis la fonction menu et reçoit les différentes données.
	-Elle appelle une fonction d'affichage.
	-Elle récupère l'entrée de l'utilisateur et appelle diverses fonctions en conséquence (jusqu'à ce qu'il quitte).

Paramètres en entrée : 
	-ListeReservation lr : la liste chaînée de réservations.
	-Jeu **tJeux : un tableau de pointeurs de type Jeu, contenant les données des Jeux.
	-int nbJeux : la taille logique de ce tableau de pointeur.
	-Adherent **tAdherent : un tableau de pointeurs de type Adherent contenant les données des adhérents.
	-int nbAdh : la taille logique de ce tableau de pointeurs.
	-Emprunt **tEmp : un tableau de pointeurs de type Emprunt, contenant les données des emprunts.
	-int nbEmp : la taille logique de ce tableau de pointeurs.

Valeur retournée : Aucune.

Variables locales: choix : entier. Choix de l'utilisateur dans le sous-menu, récupéré depuis une entrée. 

Constantes :
	choix1, choix2, choix3, choix9 : valeurs entières de choix prédéfinies.
*/

void sousMenu(ListeReservation lr, Jeu *tJeux[], int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp)
{
	int choix, erreur;
	int choix1 = 1, choix2 = 2, choix3 = 3, choix9 = 9;

	affichageSousMenu();
	scanf("%d%*c", &choix);

	while (choix != choix9)
	{
		if (choix == choix1)
			sousMenuJeux(tJeux, nbJeux);

		else if (choix == choix2)
			saisieEmpAffichage(tJeux, nbJeux, tAdh, nbAdh, tEmp, nbEmp);

		else if (choix == choix3)
			saisieJeuPourAffichageReservations(tJeux, nbJeux, lr, tAdh, nbAdh);

		else
			printf("Veuillez faire un choix correct\n");

		if (choix != choix1)
		{
			printf("Appuyez sur entrée pour continuer...\n");
			getchar();
		}

		affichageSousMenu();
		scanf("%d%*c", &choix);
	}
}

/*
Nom : affichageMenu
Finalité : fonction permettant l'affichage des données du menu principal.

Description générale :
	-Cette fonction est appelée depuis le menu.
	-Elle affiche les différents choix possibles du menu.

Paramètres en entrée : Aucun

Valeur retournée : Aucune

Variables locales: Aucune 
*/

void affichageMenu(void)
{
	system("clear");
	printf("\n**********************************************************************************\n");
	printf("\t\t\t1-Informations\n");
	printf("\t\t\t2-Faire un emprunt\n");
	printf("\t\t\t3-Rendre un jeu\n");
	printf("\t\t\t4-Annuler une réservation\n");
	printf("\t\t\t9-Quitter\n");
	printf("**********************************************************************************\n");
	printf("Quel est votre choix ? ");
}

/*
Nom : menu
Finalité : fonction de menu principal qui gère les entrées de l'utilisateur et appelle les fonctions demandées.

Description générale :
	-Cette fonction est appelée depuis la fonction globale et reçoit les données chargées.
	-Elle appelle une fonction d'affichage.
	-Elle récupère l'entrée de l'utilisateur et appelle diverses fonctions en conséquence (jusqu'à ce qu'il quitte).

Paramètres en entrée : 
	-ListeReservation lr : la liste chaînée de réservations.
	-Jeu **tJeux : un tableau de pointeurs de type Jeu, contenant les données des Jeux.
	-int nbJeux : la taille logique de ce tableau de pointeur.
	-Adherent **tAdherent : un tableau de pointeurs de type Adherent contenant les données des adhérents.
	-int *nbAdh : un pointeur sur la taille logique de ce tableau de pointeurs.
	-Emprunt **tEmp : un tableau de pointeurs de type Emprunt, contenant les données des emprunts.
	-int *nbEmp : un pointeur sur la taille logique de ce tableau de pointeurs.

Valeur retournée : Une Liste de réservation qui a peut-être changée (valeurs supprimées ou ajoutées).

Variables locales: choix : entier. Choix de l'utilisateur dans le menu, révupéré depuis une entrée. 

Constantes :
	choix1, choix2, choix3, choix4, choix9 : valeurs entières de choix prédéfinies.
*/

ListeReservation menu(ListeReservation lr, Jeu **tJeux, int nbJeux, Adherent **tAdh, int *nbAdh, Emprunt **tEmp, int *nbEmp)
{
	int choix;
	int choix1 = 1, choix2 = 2, choix3 = 3, choix4 = 4, choix9 = 9;

	affichageMenu();
	scanf("%d%*c", &choix);

	while (choix != choix9)
	{
		if (choix == choix1)
			sousMenu(lr, tJeux, nbJeux, tAdh, *nbAdh, tEmp, *nbEmp);

		else if (choix == choix2)
			lr = emprunterEtReserver(tAdh, nbAdh, tEmp, nbEmp, tJeux, nbJeux, lr);

		else if (choix == choix3)
			lr = retourDunJeu(lr, tAdh, *nbAdh, tEmp, nbEmp, tJeux, nbJeux);

		else if (choix == choix4)
			lr = suppressionReservation(tJeux, nbJeux, tAdh, *nbAdh, lr);

		else
			printf("Veuillez faire un choix correct\n");


		if (choix != choix1)
		{
			printf("Appuyez sur entrée pour continuer...\n");
			getchar();
		}

		affichageMenu();
		scanf("%d%*c", &choix);
	}

	printf("A bientôt !\n\n");
	return lr;
}

/*
Nom : globale

Finalité : fonction principale qui charge et enregistre les données, appelle la fonction menu, et gère donc tout le programme.

Description générale :
	-Cette fonction est appellé depuis la fonction main.
	-C'est la fonction principale. Elle crée trois tableau de pointeur sur des structures d'adhérents, d'emprunts et de jeux.
	-Elle appelle les fonctions qui les charge depuis un fichier binaire.
	-Elle crée une liste chaînée et la charge depuis le fichier régulier qui correspond (avec la fonction correspondante).
	-Elle appelle les fonctions qui trie les jeux par nom de jeu, et la fonction qui trie les emprunts par id d'emprunt.
	-Elle appelle la fonction de calibrage pour un meilleur affichage
	-Elle appelle enfin la fonction menu. 
	-Lorsque l'utilisateur décide de quitter le programme, cette fonction appelle la fonction qui trie les emprunts par dates d'emprunt.
	-Elle appelle également les fonctions de sauvegarde pour les 4 types de données (3 en binaires et la liste en fichier régulier).
	-Elle libère la mémoire des trois tableaux de pointeurs et de la liste chaînée, et se termine.

Paramètres en entrée : Aucun.

Valeur retournée : aucune.

Variables locales : 
	-erreur : entier. Sert à récupérer la valeur retournée par les fonctions lors de l'enregistrement (en cas d'un éventuel problème de sauvegarde).
	-Les tableaux de pointeurs *tAdh[], *tEmp[], *tJeux[] qui pointent sur des structures différentes et qui sont remplis par les fonctions de chargement.
	-La liste de réservation lr qui est créée, puis remplie.
	-nbEmp, nbJeux, nbAdh qui sont des entiers et qui correspondent aux tailles logiques des tableaux de pointeurs correspondants.
	-i, un entier qui est utilisé dans les boucle de fin pour libérer la mémoire.
*/

void globale(void)
{
	int erreur, i;
	int nbEmp, nbJeux, nbAdh;

	Adherent *tAdh[TAILLEMAX];
	Emprunt *tEmp[TAILLEMAX];
	Jeu *tJeux[TAILLEMAX];
	ListeReservation lr;

	lr = creerListeVide();

	lr = chargementReservation(lr);

	nbJeux = chargementJeuxBin(tJeux);
	if (nbJeux == -1)
		return;

	nbEmp = chargementEmpruntBin(tEmp);
	if (nbEmp == -1)
		return;

	nbAdh = chargementAdherentBin(tAdh);
	if (nbAdh == -1)
		return;

	calibrage();

	triJeuxParNom(tJeux, nbJeux);
	triRapideEmpruntsParId(tEmp, nbEmp);

	lr = menu(lr, tJeux, nbJeux, tAdh, &nbAdh, tEmp, &nbEmp);

	erreur = enregistrementReservation(lr);
	if (erreur == -1)
		return;

	erreur = enregistrementJeux(tJeux, nbJeux);
	if (erreur == -1)
		return;

	erreur = enregistrementAdherent(tAdh, nbAdh);
	if (erreur == -1)
		return;

	erreur = enregistrementEmprunt(tEmp, nbEmp);
	if (erreur == -1)
		return;

	lr = suppressionListe(lr);

	for (i = 0; i < nbJeux; i++)
		free(tJeux[i]);

	for (i = 0; i < nbAdh; i++)
		free(tAdh[i]);

	for (i = 0; i < nbEmp; i++)
		free(tEmp[i]);
}