/* programme : donnees.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : fichier contenant les fonctions de chargement et de sauvegarde des données (réservations, emprunts, adhérents et jeux), ainsi que les fonctions d'affichages (debogage).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ludotheque.h"

#define TAILLEMAX 10000

/*
Nom : creerListeVide

Finalité : fonction permettant la création d'une liste vide.

Description générale :
	-Cette fonction est appelée lors du chargement des données des réservations.
	-Elle retourne NULL de manière à créer une liste vide.

Paramètres en entrée : Aucun

Valeur retournée : Une Liste de réservations (qui vaut NULL)

Variables locales: Aucune 
*/

ListeReservation creerListeVide(void)
{
	return NULL;
}

/*
Nom : ajouterMaillon

Finalité : chercher un emplacement où ajouter un maillon, des données dans la liste des réservations.

Description générale :
	-Cette fonction récursive est appellée lorsque l'on souhaite ajouter des données dans la liste des réservations (lors du chargement des données et lorsqu'on crée une réservation).
	-Elle parcours la liste chaînée afin de trouver un emplacement où insérer ce nouveau maillon. Elle appelle alors la fonction qui va insérer ce maillon.
	-La fonction ajoute le maillon dans un emplacement libre d'un id de réservation (un id qui n'existe pas). Elle l'insère dans l'odre chronologique.
	-On se retrouve avec une liste chaînée "triée" (elle n'est pas réellemment triée, les valeurs sont seulement ajoutées aux bons endroits) en fonction de l'id de réservation.
	-Si elle ne trouve pas de "place" où l'ajouter, elle l'ajoute à la fin.

Paramètres en entrée : 
	-une liste de réservation lr ou des données cont être insérées.
	-une réservation reserv qui va être insérée dans le nouveau maillon.

Valeur retournée : Une liste de réservation ou a été ajouté un maillon.

Variables locales : Aucune.
*/

ListeReservation ajouterMaillon(ListeReservation lr, Reservation reserv)
{
	if (lr == NULL)
		return InsertionEnTete(lr, reserv);
	if (lr->r.idResa > reserv.idResa)
		return InsertionEnTete(lr, reserv);
	lr->suivant = ajouterMaillon(lr->suivant, reserv);
	return lr;
}

/*
Nom : InsertionEnTete

Finalité : ajouter un maillon, des données dans la liste des réservations.

Description générale :
	-Cette fonction est appellée par la fonction ajouterMaillon.
	-Elle lui fournit l'emplacement ou ajouter le maillon dans la liste des réservations.
	-Cette fonction crée donc un maillon, l'alloue dynamiquement, retoune NULL en cas de problème d'allocation.
	-Elle intègre à ce maillon une réservation supplémentaire.
	-Elle fait pointer ce maillon sur le reste de la liste et retourne le tout.

Paramètres en entrée : 
	-une liste de réservation lr où des données vont être insérées.
	-Une réservation reserv qui va être ajoutée au maillon.

Valeur retournée : Une liste de réservation ou a été ajouté un maillon.

Variables locales : 
	-un maillon mail, alloué, puis rempli de données, et qui pointe sur la liste.
*/

ListeReservation InsertionEnTete(ListeReservation lr, Reservation reserv)
{
	Maillon *mail;
	mail = (Maillon *) malloc(sizeof(Maillon));
	if (mail == NULL)
	{
		printf("Problème d'allocation dynamique avec malloc dans les données des réservations!\n");
		return NULL;
	}
	mail -> r = reserv;
	mail -> suivant = lr;
	return mail;
}

/*
Nom : lireReservation

Finalité : Lis une ligne du fichier des réservations. Lit les composants d'une structure Réservation dans le fichier de réservations et la retourne.

Description générale : 
	-Crée une variable de structure Reservation.
	-Lit une ligne et ajoute ces données (id de réservation, id de jeu, id d'adherent, date de réservation) à la réservation créée.
	-Retourne finalement la structure Reservation lue qui sera intégrée à la liste chaînée ensuite.

Variables en entrée:
	fe : flot d'entrée qui permet de lire la ligne depuis le fichier de réservations.

Valeur retournée : la réservation précédemment créée et complétée.

Variables:
	-reserv(Reservation): Une Reservation qui va être complétée de données qui seront lues.
*/

Reservation lireReservation(FILE *fe)
{
	Reservation reserv;
	fscanf(fe, "%d %d %d %d/%d/%d", &reserv.idResa, &reserv.idAdherent, &reserv.idJeux, 
		&reserv.dateReservation.jour, &reserv.dateReservation.mois, &reserv.dateReservation.annee);
	return reserv;
}

/*
Nom : chargementReservation

Finalité : ouvrir un fichier pour pouvoir charger les données des réservations dans une liste chaînée.

Description générale :
	-Cette fonction est appellée lorsque l'on veut charger les données, en début de traitement donc. 
	-Elle ouvre un flot d'entrée pour le fichier des réservations.
	-Elle vérifie qu'il s'est bien ouvert ou retourne -1 si problème.
	-Elle appelle la fonction qui lit une ligne puis celle qui va ajouter un maillon à la liste (=enregistrer une ligne dans la liste), en envoyant la réservation lue.
	-Elle fait cela jusqu'à avoir lu le fichier en entier.
	-Elle ferme le fichier et se termine en retournant la liste créée.

Paramètres en entrée : une liste de réservation lr (qui normalement est déjà vide et vaut NULL).

Valeur retournée : une liste de réservation lr (qui cette fois est normalement remplie de données).

Variables locales : 
	-un flot d'entrée fe qui sert à lire les données du fichier.
	-Une réservation reserv : contient les données (idResa, idJeux, idAdherent et date de réservation) d'UNE réservation.
	-La liste de réservation lr qui est complétée par les ajouts de maillons.
*/

ListeReservation chargementReservation(ListeReservation lr)
{
	Reservation reserv;
	FILE *fe;

	fe = fopen("reservations.don", "r");
	if (fe == NULL)
	{
		printf("Problème lors de l'ouverture du fichier reservations.don");
		return NULL;
	}

	reserv = lireReservation(fe);

	while(feof(fe) == 0)
	{
		lr = ajouterMaillon(lr, reserv);
		
		reserv = lireReservation(fe);
	}

	fclose(fe);
	return lr;
}

/*
Nom : ecritureFichierReservation

Finalité : enregistrer les données de la liste chaînée dans un fichier régulier.

Description générale :
	-Cette fonction récursive est appellée depuis la fonction de chargement où l'on a ouvert le fichier.
	-Elle parcours chaque maillon de la liste et écrit son contenu dans le fichier à partir du flot de sortie.
	-Quand elle arrive au bout de la liste (valeur NULL), elle se termine. Tout a été enregistré.

Paramètres en entrée : 
	-une liste de réservation lr (données à sauvegarder).
	-un flot de sortie flot qui sert lors de l'écriture des données.

Valeur retournée : Aucune

Variables locales : Aucune.
*/

void ecritureFichierReservation(ListeReservation lr, FILE *flot)
{
	if (lr == NULL)
		return;
	fprintf(flot, "%04d\t\t%04d\t\t%04d\t\t%02d/%02d/%04d\n", lr->r.idResa, lr->r.idAdherent, lr->r.idJeux, 
		lr->r.dateReservation.jour, lr->r.dateReservation.mois, lr->r.dateReservation.annee);
	ecritureFichierReservation(lr->suivant, flot);
}

/*
Nom : enregistrementReservation

Finalité : ouvrir un fichier pour pouvoir enregistrer les réservations dans un fichier régulier (le même fichier que celui de chargement).

Description générale :
	-Cette fonction est appellée lorsque l'on veut enregistrer les données, en fin de traitement donc. 
	-Elle ouvre un flot de sortie pour le fichier des réservations.
	-Elle vérifie qu'il s'est bien ouvert ou retourne -1 si problème.
	-Elle appelle la fonction qui va écrire les données dedans.
	-Elle ferme le fichier et se termine.

Paramètres en entrée : une liste de réservation lr.

Valeur retournée : un entier qui indique si l'enregistrement a été effectué (0) ou non (1).

Variables locales : un flot FS qui sert à écrire les données dans le fichier.
*/

int enregistrementReservation(ListeReservation lr)
{
	FILE *fs;
	fs = fopen("reservations.don", "w");
	if (fs == NULL)
	{
		printf("Problème lors de l'enregistrement des données du fichier reservations.don");
		return -1;
	}

	ecritureFichierReservation(lr, fs);
	
	fclose(fs);
	return 0;
}

/*
Nom : affichageReservations

Finalité : afficher la liste des réservations.

Description générale :
	-Cette fonction récursive est appellée afin de vérifier le contenu enregistré dans une liste chaînée de réservations. 
	-Elle parcours la liste chaînée jusqu'à arriver à sa fin (NULL).
	-En même temps, elle affiche les données de chaque maillon.

Paramètres en entrée : une liste de réservation lr.

Valeur retournée : Aucune

Variables locales : Aucune.
*/

void affichageReservations(ListeReservation lr)
{
	if (lr == NULL)
		return;

	printf("%04d\t%04d\t%04d\t\t%02d/%02d/%04d\n", lr->r.idResa, lr->r.idAdherent, lr->r.idJeux, 
		lr->r.dateReservation.jour, lr->r.dateReservation.mois, lr->r.dateReservation.annee);
	affichageReservations(lr->suivant);
}

/*
Nom : suppressionListe

Finalité : supprimer une liste chaînée afin de libérer la mémoire.

Description générale :
	-Cette fonction est appellé en fin de traitement, lorsqu'on souhaite libérer la mémoire et vider la liste.
	-A chaque appel de cette fonction récursive, on défini le premier maillon de la liste que l'on va supprimer (celui qui est en tête). 
	On commence donc par la "fin" de la liste (l'élément qui se trouve le plus loin).
	-Une fois la liste parcourue (on atteint la valeur NULL), on va sucessivement libérer les maillons déclarés.
	-A la fin on retourne une liste vide (NULL).

Paramètres en entrée : une liste de réservation lr.

Valeur retournée : une liste de réservation lr (qui vaut NULL cette fois).

Variables locales :
	-tete : un maillon de la liste de réservation que l'on va ensuite supprimer.
*/

ListeReservation suppressionListe(ListeReservation lr)
{
	ListeReservation tete = lr;

	if (lr == NULL)
		return NULL;

	lr = suppressionListe(lr->suivant);

	free(tete);
	return lr;

}

/*
Nom : lireJeu

Finalité : Lis une ligne du fichier de jeux. Lit les composants d'une structure Jeu dans le fichier de jeux et la retourne.

Description générale : 
	-Crée une variable de structure Jeu.
	-Lit une ligne et ajoute ces données (id de jeu, type de jeu, nombre d'exemplaires) au jeu crée.
	-Lit le nom du jeu composé, remplace un saut de ligne à la fin du nom du jeu s'il y en a un et le remplace par un '\0'.
	-Retourne finalement la structure Jeu lue qui sera intégrée au tableau de pointeurs **tJeux.

Variables en entrée:
	flot : flot d'entrée qui permet de lire la ligne depuis le fichier de jeux.

Valeur retournée : le jeu précédemment crée et complété.

Variables:
	-jouet(Jeu): Un Jeu qui va être complété de données qui seront lues.
	-longueur(entier): longueur de la chaîne de charactères nomJeu.

Constantes : maxLongueur de valeur 30, qui est la taille maximale du nom du jeu récupéré par fgets.
*/

Jeu lireJeu(FILE* flot)
{
	Jeu jouet;
	int longueur, maxLongueur = 30;

	fscanf(flot,"%d %s %d ", &jouet.idJeu, jouet.typeJeu, &jouet.nbExemplaire);
	fgets(jouet.nomJeu, maxLongueur, flot);
	longueur = strlen(jouet.nomJeu);
	if (jouet.nomJeu[longueur - 1] == '\n')
		jouet.nomJeu[longueur - 1] = '\0';
	return jouet;
}

/*
Nom : chargementJeux
Finalité : Charger les données de jeu.don dans un tableau dynamique.

Description générale : 
	-Ouvre le fichier jeu.don en lecture à partir d'un flot d'entrée, en retournant -1 en acs de soucis d'ouverture.
	-Lit une ligne du fichier avec la fonction lireJeu. On vérifie que le tableau n'est pas plein.
	-Une allocation de mémoire est faite pour l'insertion du Jeu dans le tableau tJeux.
	-On recommence ensuite jusqu'à ce qu'il n'y est plus de lignes à lire. On retourne enfin i, la taille du tableau. 

Variables en entrée:
	*tJeux[](Jeu): Tableau de pointeurs contenant les données du fichier de Jeux.

Valeur retournée : un 

Variables:
	FILE *fe : flot d'entrée du fichier. Permet d'ouvrir le fichier régulier correspondant en mode lecture et le lire.
	i(entier): Nombre d'éléments du tableau (taille logique)
	jouet(Jeu): Caractéristiques d'un jeu
*/

int chargementJeux(Jeu *tJeux[])
{
	FILE *fe;
	int i = 0;
	Jeu jouet;
	fe = fopen("jeu.don", "r");
	if (fe == NULL)
	{
		printf("Problème lors de l'ouverture du fichier jeu.don\n");
		return -1;
	}
	jouet = lireJeu(fe);
	
	while(!feof(fe))
	{
		if (i == TAILLEMAX)
		{
			printf("Tableau des jeux trop petit\n");
			fclose(fe);
			return -1;
		}

		tJeux[i]=(Jeu *)malloc(sizeof(Jeu));
		if (tJeux[i] == NULL)
		{
			printf("Problème avec malloc durant l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}

		*tJeux[i] = jouet;
		i = i + 1;
		jouet = lireJeu(fe);

	}
	fclose(fe);
	return i;
}

/*
Nom : affichageJeux
Finalité : Afficher le contenu du tableau tJeux

Description générale : 
	-Ecrit une première ligne avec tous les éléments de la structure Jeu.
	-Ecrit ensuite en dessous tout le contenu du tableau tJeux (pour chaque Jeu).

Variables en entrée:
	**tJeux[](Jeu): Tableau de pointeurs contenant les données de du fichier de Jeux.
	nbJeu(entier): Nombre de jeux (taille logique).

Valeur retournée : Aucune.

Variables:
	i(entier): Nombre d'éléments du tableau (compteur pour la boucle).
*/

void affichageJeux(Jeu **tJeux, int nbJeu)
{
	int i;
	printf("ID\tNOM\t\t\t\tTYPE\tNB EXEMPLAIRES\n");
	for(i = 0; i < nbJeu; i++)
		printf("%04d\t%-30s\t%-10s\t%d\n", tJeux[i]->idJeu, tJeux[i]->nomJeu, 
			tJeux[i]->typeJeu, tJeux[i]->nbExemplaire);
}

/*
Nom : enregistrementJeux

Finalité : Enregister dans un fichier binaire les données du tableau tJeux.

Description générale : 
	-Ouvre le fichier de jeux en mode binaire. On vérifie qu'il n'y a pas de problème d'ouverture auquel cas on retourne -1.
	-On écrit ensuite dans le fichier les données de toutes les cases du tableau (avec une boucle).
	-Fermeture du fichier et terminaison de la fonction.

Valeur retournée : un entier. 0 si tout s'est bien passé, -1 en cas de problème d'ouverture du fichier.

Variables en entrée:
	FILE *fs : flot de sortie du fichier. Permet d'ouvrir le fichier binaire correspondant en mode écriture et le écrire dedans.
	**tJeux[](Jeu): Tableau contenant les données de du fichier de Jeux.
	nbJeu(entier): Nombre de jeux (taille logique).
*/

int enregistrementJeux(Jeu **tJeux, int nbJeux)
{
	FILE *fs;
	fs = fopen("jeu.bin", "wb");
	if (fs == NULL)
	{
		printf("Problème lors de l'ouverture de jeu.bin");
		return -1;
	}

	for (int i = 0; i < nbJeux; i++)
		fwrite(tJeux[i], sizeof(Jeu), 1, fs);
	fclose(fs);
	return 0;
}

/*
Nom : enregistrementJeuxBin
Finalité : Charger depuis un fichier binaire les données du tableau tJeux.

Description générale : 
	-Ouvre le fichier jeu.bin en lecture binaire, retourne -1 en acs de problème d'ouverture.
	-Vérifie que le tableau n'est pas plein (si c'est le cas on retourne -1). 
	-On réalise une allocation dynamique et on lit le fichier jeux pour insérer les lignes dans le tableau Tjeux. 
	-On recommence jusqu'à ce qu'il n'y est plus de lignes à lire.
	-On ferme le fichier et on retourne la taille logique.

Variables en entrée:
	**tJeux[](Jeu): Tableau contenant les données du fichier de Jeux.

Valeur retournée : entier. -1 si problème d'ouverture / d'allocation / de taille, la taille logique du tableau de pointeurs sinon.
	
Variables:
	FILE *fe : flot d'entrée du fichier. Permet d'ouvrir le fichier binaire correspondant en mode lecture et le lire.
	i(entier): Nombre d'éléments du tableau (taille logique).
*/

int chargementJeuxBin(Jeu **tJeux)
{
	FILE *fe;
	int i = 0;
	fe = fopen("jeu.bin", "rb");
	if (fe == NULL)
	{
		printf("Problème lors de l'ouverture de jeu.bin");
		return -1;
	}

	while(feof(fe) == 0)
	{
		if (i == TAILLEMAX)
		{
			printf("Tableau des jeux trop petit\n");
			fclose(fe);
			return -1;
		}
		tJeux[i] = (Jeu *)malloc(sizeof(Jeu));
		if (tJeux[i] == NULL)
		{
			printf("Problème avec malloc lors de l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}
		fread(tJeux[i], sizeof(Jeu), 1, fe);
		
		i++;
	}
	fclose(fe);
	return i - 1;
}

/*
Nom : lireAdherent

Finalité : lit une ligne du fichier des adhérents.

Description générale :
	-On crée un adhérent.
	-On lit une ligne depuis le flot donné en paramètre.
	-On assigne les valeurs lues (id, nom, prénom, date d'inscription, civilité) à ce nouvel adhérent.
	-On lit le nom qui peut être composé, puis on retourne cet adhérent qui sera inséré depuis la fonction de chargement.

Paramètres en entrée:
	-FILE *fe : flot d'entrée du fichier. Il permet de lire les données depuis ce flot.

Valeur retournée :
  	-un Adherent. On renvoie un adhérent qui contient les données lues précédemment.

Variables locales :
  	-longueur, entier. Permet de connaître la longueur du nom lu.
  	-Adherent adh. Une variable de type adhérent qui contient les données lues. 

Constantes :
	-maxLongueur, entier de valeur 30. La longueur maximale du nom qui peut être lue depuis le fichier avec fgets.
*/

Adherent lireAdherent(FILE *fe)
{
	Adherent adh;
	int longueur, maxLongueur = 30;

	fscanf(fe,"%d%d/%d/%d%*c%s%*c%s ",&adh.idAdherent, &adh.dateInscription.jour, 
		&adh.dateInscription.mois, &adh.dateInscription.annee, adh.civilite, adh.prenom);
	fgets(adh.nom, maxLongueur, fe);
	longueur = strlen(adh.nom);
	if (adh.nom[longueur - 1] == '\n')
		adh.nom[longueur - 1] = '\0';
	return adh;
}

/*
Nom : chargementAdherent

Finalité : remplir un tableau de données depuis un fichier adhérents.

Description générale :
	-Ouverture du fichier adhérent en mode lecture.
	-Vérification si le fichier s'est bien ouvert et retourne -1 en cas de problème. 
	-On appelle la fonction qui va lire une ligne du fichier.
	-On vérifie si le tableau n'est pas trop petit.
	-Vérification si l'allouement dynamique c'est bien déroulé (-1 auquel cas) et ajout dans le tableau.
	-On lit à nouveau... On réalise cette opération de lecture jusqu'à atteindre la fin du fichier, ou n'avoir plus de place dans le tableau.
    -Fermeture du fichier, et renvoie de la taille logique.
	
Paramètres en entrée:
  	-*tAdh[], tableau de pointeur de la structure adhérent, rempli à partir des informations qu'il y a dans le fichier.

Valeur retournée :
  	Entier, permettant de renvoyer si la fonction s'est mal déroulé (-1), renvoie la taille logique du tableau rempli sinon.

Variables locales :
  	FILE *fe : flot d'entrée du fichier. Permet d'ouvrir le fichier régulier correspondant en mode lecture et le lire.
  	i, entier. Variable qui servira de compteur de ligne lors de la lecture, permet de connaître la taille logique. 
  	adh : Adherent retourné par la fonction de lecture et ajouté au tableau.
*/

int chargementAdherent(Adherent *tAdh[])
{
	FILE *fe;
	int i = 0;
	Adherent adh;
	fe = fopen("adherent.don", "r");
	if (fe == NULL)
	{
		printf("Problème lors de l'ouverture du fichier adherent.don\n");
		return -1;
	}
	adh = lireAdherent(fe);
	
	while(!feof(fe))
	{
		
		if (i == TAILLEMAX)
		{
			printf("Tableau des adherents trop petit\n");
			fclose(fe);
			return -1;
		}
		tAdh[i] = (Adherent *)malloc(sizeof(Adherent));
		if (tAdh[i] == NULL)
		{
			printf("Problème avec malloc lors de l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}
		*tAdh[i] = adh;
		i = i + 1;
		adh = lireAdherent(fe);
	}

	fclose(fe);
	return i;
}

/*
Nom : affichageAdherent

Finalité : affichage du contenu du tableau de pointeurs des adhérents.

Description générale : 
	-Fonction d'affichage, permet de vérifier que tout fonctionne.
	-Parcours le tableau des adhérent avec une boucle et affiche tout ce qu'il y a dans le tableau.

Paramètres en entrée:
	-**tAdh tableau de pointeurs de la structure adhérent, contient les informations des données des adhérents que l'on va afficher.
	-nbAdh, taille logique du tableau de pointeurs Adhérent.

Paramètre en sortie: Aucun.

Variables locales :
  	i : entier. Variable qui servira de compteur dans la boucle de parcours du tableau.
*/

void affichageAdherent(Adherent **tAdh, int nbAdh)
{
	int i;
	printf("ID\tDATE INS\tCIVIL\tNOM\t\t\t\tPRENOM\n");
	for (i = 0; i < nbAdh; i++)
		printf("%04d %02d/%02d/%04d %s\t%-30s\t%s\n", tAdh[i]->idAdherent, tAdh[i]->dateInscription.jour, tAdh[i]->dateInscription.mois, 
			tAdh[i]->dateInscription.annee, tAdh[i]->civilite, tAdh[i]->nom, tAdh[i]->prenom);
}

/*
Nom : enregistrementAdherent

Finalité : enregistrer les données du tableau de pointeurs des adhérents dans un fichier binaire.

Description générale : 
	-Fonction qui permet de sauvegarder les informations qui composent le fichier régulier dans un fichier binaire.
	-Ouverture du fichier en mode écriture, on vérifie le bon déroulement de l'ouverture, sinon on retourne -1.
	-On enregistre les données dedans, en parcourant le tableau avec une boucle.
	-Fermeture du fichier en fin de traitement.

 Paramètres en entrée:
	-**tAdh tableau de pointeur de la structure adhérent, ces informations sont enregistrées dans le fichier.
	-nbAdh : entier. Taille logique du fichier d'adhérent.

Valeur retournée :
  	-entier permettant de savoir si la fonction s'est bien ou mal déroulé.

Variables locales :
	FILE *fs : flot de sortie qui permet d'ouvrir le fichier binaire correspondant en mode écriture et d'écrire dedans.
	i : entier. Compteur de boucle lors de l'écriture des données.
*/

int enregistrementAdherent(Adherent **tAdh, int nbAdh)
{
	FILE *fs;
	fs = fopen("adherent.bin", "wb");
	if (fs == NULL)
	{
		printf("problème d'ouverture de adherent.bin");
		return -1;
	}

	for (int i = 0; i < nbAdh; i++)
		fwrite(tAdh[i], sizeof(Adherent), 1, fs);
	fclose(fs);
	return 0;
}

/*
Nom : chargementAdherentBin

Finalité : charger des données d'adhérents dans un tableau de pointeurs depuis un fichier binaire.
  
Description générale : 
	-Chargement du fichier adhérent en format binaire, comprend l'ouverture du fichier en mode lecture.
	-Vérification si le fichier s'est bien ouvert et retourne -1 en cas de problème. 
	-Lit le fichier jusqu'à sa fin, et vérifie si le tableau n'est pas trop petit.
	-Vérification si l'allouement dynamique c'est bien déroulé (-1 auquel cas) et ajout dans le tableau.
    -Fermeture du fichier, et renvoie de la taille logique
  
Paramètres en entrée:
	-**tAdh tableau de pointeur de la structure adhérent, permet de stocker les informations qu'il y a dans le fichier.

Valeur retournée :
  	Un entier qui permet de savoir si la fonction c'est bien ou mal déroulé (-1 auquel cas), permet aussi de renvoyer la taille logique.

Variables locales :
	-FILE *fe : flot d'entrée du fichier lu. Permet d'ouvrir le fichier binaire correspondant en mode lecture.
	-int i, entier qui servira de compteur et permet de connaître la taille logique. 
*/

int chargementAdherentBin(Adherent **tAdh)
{
	FILE *fe;
	int i = 0;
	fe = fopen("adherent.bin", "rb");
	if (fe == NULL)
	{
		printf("problème d'ouverture de adherent.bin");
		return -1;
	}

	while(feof(fe) == 0)
	{
		if (i == TAILLEMAX)
		{
			printf("Tableau des adherents trop petit\n");
			fclose(fe);
			return -1;
		}
		tAdh[i] = (Adherent *)malloc(sizeof(Adherent));
		if (tAdh[i] == NULL)
		{
			printf("Problème avec malloc lors de l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}
		fread(tAdh[i], sizeof(Adherent), 1, fe);
		
		i++;
	}
	fclose(fe);
	return i - 1;
}

/*
Nom : lireEmprunt

Finalité : lit une ligne du fichier des emprunts.

Description générale :
	-On crée un emprunt.
	-On lit une ligne depuis le flot donné en paramètre.
	-On assigne les valeurs lues (id de l'emprunt, id de l'adhérent, id du jeu, date de l'emprunt) à ce nouvel emprunt.
	-On retourne cet emprunt qui sera inséré depuis la fonction de chargement.

Paramètres en entrée:
	-FILE *fe : flot d'entrée du fichier. Il permet de lire les données depuis ce flot.

Valeur retournée :
  	-un Emprunt emp. On renvoie un emprunt qui contient les données lues précédemment.

Variables locales :
  	-Emprunt emp. Une variable de type emprunt qui contient les données lues. 
*/

Emprunt lireEmprunt(FILE *fe)
{
	Emprunt emp;
	fscanf(fe,"%d%d%d%d/%d/%d",&emp.idEmprunt, &emp.idAdherent, 
		&emp.idJeu, &emp.dateEmprunt.jour, &emp.dateEmprunt.mois, &emp.dateEmprunt.annee);
	return emp;
}

/*
Nom : chargementEmprunt

Finalité : remplir un tableau de données depuis un fichier emprunt.

Description générale :
	-Ouverture du fichier emprunts en mode lecture.
	-Vérification si le fichier s'est bien ouvert et retourne -1 en cas de problème. 
	-On appelle la fonction qui va lire une ligne du fichier.
	-On vérifie si le tableau n'est pas trop petit.
	-Vérification si l'allouement dynamique c'est bien déroulé (-1 auquel cas) et ajout dans le tableau.
	-On lit à nouveau... On réalise cette opération de lecture jusqu'à atteindre la fin du fichier, ou n'avoir plus de place dans le tableau.
    -Fermetrure du fichier, et renvoie de la taille logique.
	
Paramètres en entrée:
  	-*tEmp[], tableau de pointeur de la structure emprunt, rempli à partir des informations qu'il y a dans le fichier.

Valeur retournée :
  	Entier, permettant de renvoyer si la fonction s'est mal déroulé (-1), renvoie la taille logique du tableau rempli sinon.

Variables locales :
  	FILE *fe : flot d'entrée du fichier. Permet d'ouvrir le fichier régulier correspondant en mode lecture et le lire.
  	i, entier. Variable qui servira de compteur de ligne lors de la lecture, permet de connaître la taille logique. 
  	emp : Emprunt retourné par la fonction de lecture et ajouté au tableau.
*/

int chargementEmprunt(Emprunt *tEmp[])
{
	FILE *fe;
	int i = 0;
	Emprunt emp;
	fe = fopen("emprunt.don", "r");
	if (fe == NULL)
	{
		printf("Problème lors de l'ouverture du fichier emprunt.don\n");
		return -1;
	}
	emp = lireEmprunt(fe);
	while(!feof(fe))
	{
		if (i == TAILLEMAX)
		{
			printf("Tableau des emprunts trop petit\n");
			fclose(fe);
			return -1;
		}
		tEmp[i] = (Emprunt*)malloc(sizeof(Emprunt));
		if (tEmp[i] == NULL)
		{
			printf("Problème avec malloc lors de l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}
		*tEmp[i] = emp;
		i = i + 1;	
		emp = lireEmprunt(fe);

	}
	fclose(fe);
	return i;
}

/*
Nom : affichageEmprunt

Finalité : affichage du contenu du tableau de pointeurs des emprunts.

Description générale : 
	-Fonction d'affichage, permet de vérifier que tout fonctionne.
	-Parcours le tableau des emprunts avec une boucle et affiche tout ce qu'il y a dans le tableau.

Paramètres en entrée:
	-**tEmp tableau de pointeurs de la structure emprunt, contient les informations des données des emprunts que l'on va afficher.
	-nbEmp, taille logique du tableau de pointeurs Emprunt.

Valeur retournée : Aucune.

Variables locales :
  	i : entier. Variable qui servira de compteur dans la boucle de parcours du tableau.
*/

void affichageEmprunt(Emprunt **tEmp, int nbEmp)
{
	int i;
	
	printf("ID EMP\t\tID ADH\t\tID JEU\t\tDATE EMP\n");
	for (i = 0; i < nbEmp; i++)
		printf("%04d\t\t%04d\t\t%04d\t\t%02d/%02d/%04d\n",tEmp[i]->idEmprunt, 
			tEmp[i]->idAdherent, tEmp[i]->idJeu, tEmp[i]->dateEmprunt.jour, tEmp[i]->dateEmprunt.mois, tEmp[i]->dateEmprunt.annee);
}

/*
Nom : enregistrementEmprunt

Finalité : enregistrer les données du tableau de pointeurs des emprunts dans un fichier binaire.

Description générale : 
	-Fonction qui permet de sauvegarder les informations qui composent le fichier régulier dans un fichier binaire.
	-Ouverture du fichier en mode écriture, on vérifie le bon déroulement de l'ouverture, sinon on retourne -1.
	-On enregistre les données dedans, en parcourant le tableau avec une boucle.
	-Fermeture du fichier en fin de traitement.

 Paramètres en entrée:
	-**tEmp tableau de pointeur de la structure Emprunt, ces informations sont enregistrées dans le fichier.
	-nbEmp : entier. Taille logique du fichier des emprunts.

Valeur retournée :
  	-entier permettant de savoir si la fonction s'est bien ou mal déroulé.

Variables locales :
	FILE *fs : flot de sortie qui permet d'ouvrir le fichier binaire correspondant en mode écriture et d'écrire dedans.
	i : entier. Compteur de boucle lors de l'écriture des données.
*/

int enregistrementEmprunt(Emprunt **tEmp, int nbEmp)
{
	FILE *fs;
	fs = fopen("emprunt.bin", "wb");
	if (fs == NULL)
	{
		printf("problème d'ouverture de emprunt.bin");
		return -1;
	}

	for (int i = 0; i < nbEmp; i++)
		fwrite(tEmp[i], sizeof(Emprunt), 1, fs);
	fclose(fs);
	return 0;
}

/*
Nom : chargementEmpruntBin

Finalité : charger des données des emprunts dans un tableau de pointeurs depuis un fichier binaire.
  
Description générale : 
	-Chargement du fichier emprunts en format binaire, comprend l'ouverture du fichier en mode lecture.
	-Vérification si le fichier s'est bien ouvert et retourne -1 en cas de problème. 
	-Lit le fichier jusqu'à sa fin, et vérifie si le tableau n'est pas trop petit.
	-Vérification si l'allouement dynamique c'est bien déroulé (-1 auquel cas) et ajout dans le tableau.
    -Fermeture du fichier, et renvoie de la taille logique
  
Paramètres en entrée:
	-**tEmp tableau de pointeur de la structure Emprunt, permet de stocker les informations qu'il y a dans le fichier.

Valeur retournée :
  	Un entier qui permet de savoir si la fonction c'est bien ou mal déroulé (-1 auquel cas), permet aussi de renvoyer la taille logique.

Variables locales :
	-FILE *fe : flot d'entrée du fichier lu. Permet d'ouvrir le fichier binaire correspondant en mode lecture.
	-int i, entier qui servira de compteur et permet de connaître la taille logique. 
*/

int chargementEmpruntBin(Emprunt **tEmp)
{
	FILE *fe;
	int i = 0;
	fe = fopen("emprunt.bin", "rb");
	if (fe == NULL)
	{
		printf("problème d'ouverture de emprunt.bin");
		return -1;
	}

	while(feof(fe) == 0)
	{
		if (i == TAILLEMAX)
		{
			printf("Tableau des emprunts trop petit\n");
			fclose(fe);
			return -1;
		}
		tEmp[i] = (Emprunt *)malloc(sizeof(Emprunt));
		if (tEmp[i] == NULL)
		{
			printf("Problème avec malloc lors de l'allocation dynamique\n");
			fclose(fe);
			return -1;
		}
		fread(tEmp[i], sizeof(Emprunt), 1, fe);
		
		i++;
	}
	fclose(fe);
	return i - 1;
}

/*
Nom : restaurationDonneesFichiers

Finalité : fonction qui charge les données depuis les fichiers réguliers, et les enregistre en fichier binaire.
Cela permet de recharger les données des fichiers binaires une fois que l'on a fait une modification ou un ajout dans un fichier régulier.

Description générale :
	-Cette fonction crée un tableau de pointeurs sur chaque structure : Jeu, Adherent et Emprunt.
	-Elle crée une liste de réservation vide, puis elle appelle la fonction de chargement de cette liste.
	-Elle rempli les 3 tableaux de pointeurs en appellant les fonctions de chargements de fichier réguliers.
	-Elle appelle ensuite les fonctions pour ces trois tableaux qui vont enregistrer les données chargées dans des fichiers binaires. 
	-Elle libère la mémoire.

Paramètres en entrée : Aucuns

Valeur retournée : Aucune

Variables locales: 
	-erreur : entier. Variable qui reçoit la valeur retournée par les fonctions d'enregistrement.
	Si elle vaut -1, il y a eu un problème de sauvegarde.
	-nbJeux, nbEmp, nbAdh : la taille logique de chaque tableau de pointeurs, renvoyées par la fonction de chargement. Si elles valent -1, il y a eu un problème de chargement.
	-**tJeux, **tAdh, **tEmp: des tableaux de pointeurs sur les structure Jeu, Adherent et Emprunt. Il sont chargés depuis un fichier régulier.
	-i : compteur de boucle pour libérer la mémoire.
*/

void restaurationDonneesFichiers(void)
{
	int erreur, i;
	int nbEmp, nbJeux, nbAdh;

	Adherent *tAdh[TAILLEMAX];
	Emprunt *tEmp[TAILLEMAX];
	Jeu *tJeux[TAILLEMAX];

	nbJeux = chargementJeux(tJeux);
	if (nbJeux == -1)
		return;

	erreur = enregistrementJeux(tJeux, nbJeux);
	if (erreur == -1)
		return;

	nbEmp = chargementEmprunt(tEmp);
	if (nbEmp == -1)
		return;

	erreur = enregistrementEmprunt(tEmp, nbEmp);
	if (erreur == -1)
		return;

	nbAdh = chargementAdherent(tAdh);
	if (nbAdh == -1)
		return;

	erreur = enregistrementAdherent(tAdh, nbAdh);
	if (erreur == -1)
		return;

	for (i = 0; i < nbJeux; i++)
		free(tJeux[i]);

	for (i = 0; i < nbAdh; i++)
		free(tAdh[i]);

	for (i = 0; i < nbEmp; i++)
		free(tEmp[i]);
}
