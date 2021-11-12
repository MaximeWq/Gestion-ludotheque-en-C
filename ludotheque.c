/* programme : ludotheque.c
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : fichier proposant les fonctionalitées de la ludothèque (réservations, emprunts de jeux) et les fonctions de recherche / tri / suppression.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"ludotheque.h"

#define TAILLEMAX 100

/* FONCTIONNALITE 2 */


/*
Nom : affichageJeuxDunType

Finalité : affiche les jeux du type passé en paramètre.

Description générale :
	-On parcours les tableau de jeux avec une boucle for. Si le type de jeu passé en paramètre est égal à une type de jeu dans le tableau 
	et qu'il a encore des exemplaires en stock, on affiche le type, le nom et le nombre d'exemplaires du jeu.
	-Si le ytpe de jeu n'est pas trouvé ou si les stocks sont vides, on retourne le compteur.

Paramètres en entrée :
  	-**tJeux tableau de pointeur de la structure jeux, qui contient leurs informations.
	-nbJeux : entier. Taille logique du tableau de jeux.

Valeur retournée :
  	compteur, le nombre de jeux affichés.

Variables locales :
	-i, entier renvoyé en sortie pour connaître le nombre d'affichages réalisés.
	-compteur, le nombre de jeux affichés.
*/

int affichageJeuxDunType(Jeu *tJeux[], int nbJeux, char *typeJeu)
{
	int i, compteur = 0;

	for (i = 0; i < nbJeux; i++)
	{
		if (strcmp(tJeux[i]->typeJeu, typeJeu) == 0 && tJeux[i]->nbExemplaire != 0)
		{
			printf("%-10s\t\t%-30s\t\t%d\n", tJeux[i]->typeJeu, tJeux[i]->nomJeu, tJeux[i]->nbExemplaire);
			compteur++;
		}
	}
	return compteur;
}

/*
Nom : affichageJeuxDisponibles

Finalité : affiche touts les jeux disponibles, classés par types.

Description générale :
	-La fonction trie le tableaux de jeux avec la fonction triJeuxParNom.
	-La focntion appel plusieurs fois affichageJeuxDunType avec à chaque fois un type différent en paramètres pour afficher touts les jeux 
	en stock pour chaque type
	-On compte le nombre de jeux affichés avec une variable compteur. Si aucun jeu est affiché, un message qui l'indique apparait.

Paramètres en entrée :
  	-**tJeux tableau de pointeur de la structure jeux, qui contient leurs informations.
	-nbJeux : entier. Taille logique du tableau de jeux.

Valeur retournée :
  	-Aucune

Variables locales :
	-compteur, le nombre de jeux affichés.
*/

void affichageJeuxDisponibles(Jeu *tJeux[], int nbJeux)
{
	int compteur = 0;
	triJeuxParNom(tJeux, nbJeux);
	printf("\nTYPE\t\t\tNOM\t\t\t\t\tSTOCK\n");

	compteur = affichageJeuxDunType(tJeux, nbJeux, "carte");
	compteur = affichageJeuxDunType(tJeux, nbJeux, "construction") + compteur;
	compteur = affichageJeuxDunType(tJeux, nbJeux, "logique") + compteur;
	compteur = affichageJeuxDunType(tJeux, nbJeux, "plateau") + compteur;
	compteur = affichageJeuxDunType(tJeux, nbJeux, "tuile") + compteur;

	if (compteur == 0)
		printf("Il ne semble pas y avoir de jeux disponibles pour le moment.\n");

	printf("\n");
}

/* FONCTIONNALITE 3 */

/*
Nom : affichageEmpruntEnCours

Finalité : affiche la liste des emprunts de la ludothèque.

Description générale :
	-Cette fonction parcour le tableau des emprunts.
	-A chaque itération , elle récupère les informations de l'adhérent qui a un emprunt, en appellant la fonction correspondante.
	-Elle récupère également les informations du jeu (son nom, entre autre), en appellant une fonction de recherche.
	-Elle affiche le tout sur plusieur lignes.
	-Elle recommence jusqu'à arriver au bout du tableau.

Paramètres en entrée :
  	-**tJeux tableau de pointeur de la structure jeux, qui contient leurs informations.
  	-nbEmp, entier. Taille logique du tableau des emprunts.
  	-**tAdh tableau de pointeur de la structure adhérent, qui contient leurs informations.
	-nbAdh, entier. Nombre d'adhérents inscrits (taille logique).
	-**tEmp tableau de pointeur de la structure Emprunt, qui contient leurs informations.
	-nbEmp : entier. Taille logique du tableau d'emprunts.

Valeur retournée :
  	entier i, permettant de savoir le nombre d'affichages réalisés.

Variables locales :
	-i, entier renvoyé en sortie pour connaître le nombre d'affichages réalisés.
	-erreur : entier servant la reception des valeurs des autres fonctions de recherche appellées.
	-jouet : variable de type Jeu, où sont receptionnées les informations du jeu de la réservations, depuis une fonction de recherche.
	-adh : variable de type Adherent; où sont receptionnées les informations de l'adhérent, depuis une fonction de recherche.
*/

int affichageEmpruntEnCours(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp)
{
	int i, erreur;
	Jeu jouet;
	Adherent adh;

	//Parcour des emprunts.
	for(i = 0; i < nbEmp; i++)
	{
		erreur = rechercheIdentiteAdherent(tAdh, nbAdh, tEmp[i]->idAdherent, &adh);
		if (erreur == -1)			//Ne devrait JAMAIS arriver, seulement si un adhérent à été supprimé alors qu'il avait encore des emprunts.
			return i;
		
		erreur = rechercheInfosJeu2(tJeux, nbJeux, tEmp[i]->idJeu, &jouet);
		if (erreur == -1)						//Ne devrait JAMAIS arriver, seulement si un jeu a été supprimé alors qu'il était emprunté.
			strcpy(jouet.nomJeu, "Jeu inexistant");		

		//Affichage.

		printf("\nDate d'emprunt : %02d/%02d/%04d\nNom du jeu : %s\nEmprunteur : %s %s %s\n", tEmp[i]->dateEmprunt.jour, tEmp[i]->dateEmprunt.mois, 
			tEmp[i]->dateEmprunt.annee, jouet.nomJeu, adh.civilite, adh.nom, adh.prenom);
	}
	return i;
}

/*
Nom : saisieEmpAffichage

Finalité : fonction principale de l'affichage des emprunts, qui appele la fonction d'affichage de ceux-ci.

Description générale : 
	-Cette fonction appelle la fonction d'affichage des emprunts.
	-Si le nombre d'affichages vaut 0 (il n'y pas eu d'affichage dans la fonction appellée = il n'y a pas d'emprunt), alors on affiche un message
	expliquant que la base de données est vide.
  
Paramètres en entrée :
	-**tJeux tableau de pointeur de la structure jeux, qui contient leurs informations.
  	-nbEmp, entier. Taille logique du tableau des emprunts.
  	-**tAdh tableau de pointeur de la structure adhérent, qui contient leurs informations.
	-nbAdh, entier. Nombre d'adhérents inscrits (taille logique).
	-**tEmp tableau de pointeur de la structure Emprunt, qui contient leurs informations.
	-nbEmp : entier. Taille logique du tableau d'emprunts.

Valeur retournée : Aucune.

Variables locales :
  	-nbAffichages, entier. Nombre d'affichage que la fonction affichageEmpruntEnCours a effectuée. Si ce nombre vaut 0 alors on affiche une phrase pour le préciser. 
*/

void saisieEmpAffichage(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp)
{
	int nbAffichages;

	nbAffichages = affichageEmpruntEnCours(tJeux, nbJeux, tAdh, nbAdh, tEmp, nbEmp);

	if (nbAffichages == 0)
		printf("Il ne semble pas y avoir d'emprunts dans la ludothèque.\n");

	printf("\n");
}

/* FONCTIONNALITE 4 */

/*
Nom : affichageReservationsPourUnJeu

Finalité : Fonction affichant des réservations avec la civilité, le nom et le prénom de l'emprunteur et la date de 
réservation, pour un jeu donné.

Description générale :
	-Cette fonction récursive vérifie que la liste de réservations n'est pas vide (ou qu'on est pas à la fin de la liste).
	-Si l'id de jeu passé en paramètre est égal à un id de jeu dans la liste des réservation, on recherche les informations de l'adhérent avec 
	rechercheIdentiteAdherent puis la fonction affiche la réservtion : civilité, le nom et le prénom de l'emprunteur et la date de réservation.
	-La fonction incrémente i puis se retourne elle même "+i", en passant au maillon suivant. La valeur retournée à la fin sera donc le nombre d'affichages qui ont eu lieux.
	-La fonction recommence donc jusqu'à arriver en bout de liste, ou elle retournera alors la somme des affichages réalisés.

Paramètres en entrée : 
	-la liste de réservations lr
	-idJeux: l'id du jeu recherché, entier.
	-**tAdh: un tableau de pointeurs d'adhérents.
	-nbAdh, le nombre d'adhérents (taille logique)

Valeur retournée : Nombres d'emprunts.

Variables locales: 
	-i, entier. Vaut 0 sauf si le jeu du maillon est égal au jeu passé en paramètre, vaut alors 1. La somme des i est le nombre d'affichages réalisés.
	-erreur: entier où est stocké le résultat de la recherche de rechercheIdentiteAdherent
	-adh: variable adhérent où est stocké les donnés d'un emprunteur.
*/


int affichageReservationsPourUnJeu(ListeReservation lr, int idJeux, Adherent **tAdh, int nbAdh)
{
	int i = 0, erreur; 
	Adherent adh;

	if (lr == NULL)
		return 0;

	if (lr->r.idJeux == idJeux)
	{
		erreur = rechercheIdentiteAdherent(tAdh, nbAdh, lr->r.idAdherent, &adh);
		//Ne devrait JAMAIS arriver, uniquement si on supprime un adhérent alors qu'il possède encore des réservations.
		if (erreur == -1)					
			return affichageReservationsPourUnJeu(lr->suivant, idJeux, tAdh, nbAdh) + i;

		printf("%s\t%-30s\t%-30s\t%02d/%02d/%04d\n", adh.civilite, adh.nom, adh.prenom,
			lr->r.dateReservation.jour, lr->r.dateReservation.mois, lr->r.dateReservation.annee);
		i++;
	}
	return affichageReservationsPourUnJeu(lr->suivant, idJeux, tAdh, nbAdh) + i;
}

/*
Nom : saisieJeuPourAffichageReservations

Finalité : Fonction principale de l'affichage des réservations. C'est ici que l'utilisteur entre le jeu et qu'on appelle la fonction d'affichage.

Description générale :
	-Cette fonction demande à l'utilisateur d'entrer un nom de jeu et récupère ce nom dans une variable nomJeu.
	-On vérifie que le jeu entré existe dans le tableau des jeux avec la fonction rechercheInfoJeux. Si le jeu n'est pas trouvé la fonction s'arrête en affichant un message.
	-Sinon, la fonction appelle affichageReservationsPourUnJeu qui affiche la civilité, le nom et le prénom et la date de réservation 
	pour chaque réservations qui ont le même id que le jeu entré par l'utilisateur.
	-Si cette fonction retourne 0, on affiche un message disant qu'il n'y a pas de réservations pour ce jeu...

Paramètres en entrée : 
	-Un tableau de pointeurs de jeux tJeux
	-nbJeux le nombre de jeux (taille logique du tableau précédent)
	-la liste de réservations lr
	-un tableau de pointeurs d'adhérents tAdh
	-nbAdh, le nombre d'adhérents (taille logique du tableau précédent)

Valeur retournée : Aucune.

Variables locales: 
	-longueurMax: la longueur maximum du nom du jeu entré par l'utilisateur
	-longueur: la longueur du nom lu
	-nbAffichages: le nombre de réservations affichées
	-erreur: variable entière vérifiant que le jeu existe.
	-jeuChoisi: variable de type Jeu, ou seront stockées les informations du jeu entré par la personne. 
	-nomJeu[]: chaine de charactères où sera stockée le nom du jeu.
*/

void saisieJeuPourAffichageReservations(Jeu **tJeux, int nbJeux, ListeReservation lr, Adherent **tAdh, int nbAdh)
{
	int longueurMax = 30;
	int longueur, nbAffichages, erreur;
	Jeu jeuChoisi;

	char nomJeu[longueurMax];

	//On lit le nom du jeu qui peut être composé.
	printf("Donnez le nom du jeu dont vous voulez consulter les réservations : ");
	fgets(nomJeu, longueurMax, stdin);
	longueur = strlen(nomJeu);
	if (nomJeu[longueur - 1] == '\n')
		nomJeu[longueur - 1] = '\0';

	//On recherche le jeu dans le tableau en appellant la fonction correspondante. Si elle retourne -1 le jeu n'existe pas.
	//Si elle le trouve, elle enregistre toutes les informations de ce jeu dans la struture passée par adresse.
	erreur = rechercheInfosJeux(tJeux, nbJeux, nomJeu, &jeuChoisi);

	if (erreur == -1)
	{
		printf("Le jeu entré n'existe pas. Vérifiez l'orthographe et réessayez.\n");
		return;
	}

	printf("\nCIV\tNOM\t\t\t\tPRENOM\t\t\t\tDATE RESER\n");

	nbAffichages = affichageReservationsPourUnJeu(lr, jeuChoisi.idJeu, tAdh, nbAdh);

	//Si il y a pas de réservations pour ce jeu, on le dit.
	if (nbAffichages == 0)
		printf("Il ne semble pas y avoir de réservations pour ce jeu.\n");

	printf("\n");
}

/*******************************************************************/
/* FONCTIONNALITE 5 */



/*
Nom : emprunterEtReserver

Finalité : Fonction principale de l'ajout des emprunts et des réservations. On demande si l'utilisateur est un nouveau adhérent ou non 
puis on lui ajoute un emprunt ou une réservation.

Description générale :
	-Cette fonction demande à l'utilisateur s'il est un nouvel adhérent.Si non on lui demande son id et son nom. Avec la fonction 
	rechercheIdentiteAdherent on vérifie si l'id et le nom existe puis s'ils vont de paire. Si ce n'est pas le cas on retourne la liste de
	réservations.
	-La fonction vérifie ensuite si la date d'adhésion est toujours valide en appelant la fonction validiteDateInscription. 
	Si ce n'est pas le cas, elle propose à l'utilisateur de se ré-inscrire. Si l'utilisateur répond oui, sa date d'inscription est 
	changée à la date du jour. Sinon la fonction retourne lr.
	-La fonction demande ensuite quel jeu l'utilisateur souhaite emprunter. Sa réponse est stockée dans la variable nomJeu.
	Elle recherche ensuite ce Jeu en appelant la fonction rechercheInfosJeux. Si le jeux n'est pas trouvé, elle retourne la liste
	de réservations.
	-Si le jeu est trouvé la fonction vérifie que le stock du jeu n'est pas nulle. S'il n'est pas nulle la fonction demande à l'utilisateur
	s'il souhaite emprunter le jeu. S' il répond oui, un id d'emprunt lui est assigné en appelant la fonction ajoutDunEmprunt.
	-La fonction réduit ensuite de 1 le nombre d'exemplaires du jeu emprunté et retourne la liste de réservations.
	- Si l'utilisateur est nouveau, la fonction appel ajoutDunAdherent puis affichageAdherent pour ajouter cette adhérent et l'afficher.
	La fonction communique l'id de l'adhérent créé à l'utilisateur et retourne la liste de réservation.

Paramètres en entrée : 
	-tAdh: un tableau de pointeurs d'adhérents.
	-nbAdh: le nombre d'adhérents 
	-tEmp: un tableau de pointeurs d'emprunts
	-nbEmp: le nombre d'emprunts
	-tJeux: un tableau de pointeurs de jeux
	-nbJeux le nombre de jeux 
	-la liste de réservations lr
	

Valeur retournée : la liste d'adhérents lr.

Variables locales: 
	-longueurMax: la longueur maximum du nom du jeu entré par l'utilisateur
	-longueur: la longueur du nom lu
	-verifAdherent: un charactère contenant une réponse de l'utilisateur(oui/non) à la question "Etes-vous un nouvel adhérent".
	-choixSeReInscrire: un charactère contenant une réponse de l'utilisateur(oui/non) à la question 
	"Souhaitez vous vous ré-inscrire pour un an ?".
	-choixEmprunter: un charactère contenant une réponse de l'utilisateur(oui/non) à la question 'Souhaitez vous emprunter un jeu?'
	-choixReserver: un charactère contenant une réponse de l'utilisateur(oui/non) à la question 'Souhaitez vous réserver un jeu?'
	-nom[]: nom de l'utilisateur.
	-nomJeu: nom du jeu que l'utilisateur souhaite emprunter.
	-adh: variable de type Adherent contant les donnés d'un adhérent.
	-dateActu: date actuelle.
	-jouet: variable de type Jeu contant les donnés d'un jeu.
	-idAdherent: id de l'adhérent créé ou qui souhaite emprunter un jeu.
	-position: position du jeu recherché dans le tableau de jeux.
	-longueur: longueur d'un nom
	-erreur: variable contenant le résultat de différentes fonctions, est utilisé pour vérifier si les fonctions ont retournées une erreur.
	-idEmprunt: id de l'emprunt effectué.
	-compteurEmp: nombre d'emprunts effectués par un adhérent.

*/





ListeReservation emprunterEtReserver(Adherent **tAdh, int *nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int nbJeux, ListeReservation lr)
{
	int longueurMax = 30;
	char verifAdherent, choixSeReInscrire, choixEmprunter, choixReserver;
	char nom[longueurMax], nomJeu[longueurMax];
	Adherent adh;
	Date dateActu = recupererDateActuelle();
	Jeu jouet;
	int idAdherent, position, longueur, erreur, idEmprunt, compteurEmp = 0;

	printf("Etes-vous un nouvel adhérent (o/n) ? : ");
	scanf("%c%*c", &verifAdherent);

	if (verifAdherent == 'n')
	{
		printf("Pour vous connecter, merci de rentrer votre id : ");
		scanf("%d%*c", &idAdherent);
		position = rechercheIdentiteAdherent(tAdh, *nbAdh, idAdherent, &adh);

		if(position == -1)
		{
			printf("Désolé mais cet identifiant n'existe pas. Vérifiez vos données puis réessayez.\n");
			return lr;
		}

		printf("Pour la sécurisation de vos données, nous vous demandons de rentrer votre nom : \n");
		fgets(nom, longueurMax, stdin);
		longueur = strlen(nom);
		if (nom[longueur - 1] == '\n')
			nom[longueur - 1] = '\0';

		if (strcmp(nom, adh.nom) != 0)
		{
			printf("Désolé mais le couple identifiant/nom est incorrect. Si vous avez perdu votre ID, vous pouvez en faire la réclamation sur le site ludotheque.com\n");
			return lr;
		}
		
		if(validiteDateInscription(dateActu, adh.dateInscription) == 1)
		{
			printf("Votre inscription a expirée, vous ne pouvez plus emprunter / réserver. Souhaitez vous vous ré-inscrire pour un an ? 15€ seront prélevés sur votre compte.\n");
			printf("Se ré-inscrire (o/n) ? ");
			scanf("%c%*c", &choixSeReInscrire);

			if (choixSeReInscrire == 'o')
			{
				tAdh[position]->dateInscription.annee = dateActu.annee;
				tAdh[position]->dateInscription.mois = dateActu.mois;
				tAdh[position]->dateInscription.jour = dateActu.jour;
				printf("Vous vous êtes bien réinscris.\n");
			}

			else
			{
				printf("Inscription annulée\n");
				return lr;
			}
		}

		printf("Bienvenue %s %s %s\n", adh.civilite, adh.nom, adh.prenom);
		printf("Entrez le nom du jeu que vous voulez emprunter : ");
		fgets(nomJeu, longueurMax, stdin);
		longueur = strlen(nomJeu);
		if (nomJeu[longueur - 1] == '\n')
			nomJeu[longueur - 1] = '\0';

		position = rechercheInfosJeux(tJeux, nbJeux, nomJeu, &jouet);

		if (position == -1)
		{
			printf("Jeu inconnu. Emprunt annulé.\n");
			return lr;
		}

		if (tJeux[position]->nbExemplaire > 0)
		{
			printf("Le jeu %s (type %s) est disponible. L'emprunter (o/n)?", jouet.nomJeu, jouet.typeJeu);
			scanf("%c%*c", &choixEmprunter);

			if (choixEmprunter == 'o')
			{

				idEmprunt = ajoutDunEmprunt(tEmp, nbEmp, idAdherent, jouet.idJeu, dateActu);

				if (idEmprunt == -1)
				{
					printf("Désolé mais une erreur est survenue lors de la création de votre compte. Veuillez réessayer ou contacter un support technique.\n");
					return lr;
				}

				else if (idEmprunt == -2)
					return lr;

				tJeux[position]->nbExemplaire = tJeux[position]->nbExemplaire - 1;

				printf("Le jeu %s a bien été emprunté !\n", nomJeu);
				printf("Veuillez le retourner dans 1 mois au plus tard, sans quoi vous ne pourrez plus emprunter / réserver.\n");
				printf("Votre ID d'emprunt est %04d. Ne le perdez pas, il vous servira à retourner votre jeu.\n", idEmprunt);
				return lr;
			}

			else
			{
				printf("Emprunt annulé\n");
				return lr;
			}
		}
		printf("Le jeu n'est pas encore disponible. Vous pouvez néanmoins le réserver.\n");
		printf("Dès qu'un exemplaire sera disponible nous vous le ferons parvenir. Voulez-vous le réserver (o/n)? ");
		scanf("%c%*c", &choixReserver);

		if (choixReserver == 'o')
		{
			Reservation reserv;
			reserv.idResa = rechercheIdResa(lr, 0);
			reserv.idAdherent = adh.idAdherent;
			reserv.idJeux = jouet.idJeu;
			reserv.dateReservation.jour = dateActu.jour;
			reserv.dateReservation.mois = dateActu.mois;
			reserv.dateReservation.annee = dateActu.annee;

			lr = ajouterMaillon(lr, reserv);

			affichageReservations(lr);

			printf("Réservation réussie, nous vous tiendrons informé lorsqu'il sera disponible.\n");
			printf("Votre ID de réservation est %04d. Gardez le précieusement, il vous servira à annuler la réservation.\n", reserv.idResa);
			return lr;
		}
		printf("Réservation annulée.\n");
		return lr;
	}

	else if (verifAdherent == 'o')
	{
		erreur = ajoutDunAdherent(tAdh, nbAdh);

		affichageAdherent(tAdh, *nbAdh);

		if (erreur == -1)
		{
			printf("Désolé mais une erreur est survenue lors de la création de votre compte. Veuillez réessayer ou contacter un support technique.\n");
			return lr;
		}

		printf("Inscription réalisée avec succès. Vous pouvez désormais emprunter / réserver des jeux.\n");
		printf("Votre ID d'adhérent est %04d. Ne le perdez pas, il vous servira à vous connecter pour faire des emprunts/réservations.\n", tAdh[*nbAdh - 1]->idAdherent);
		return lr;
	}

	else
		printf("Veuillez faire un choix correct\n");
}

int ajoutDunEmprunt(Emprunt **tEmp, int *nbEmp, int idAdherent, int idJeux, Date dateActu)
{
	Emprunt emp;
	int compteurEmp;

	compteurEmp = compteNbEmp(tEmp, *nbEmp, idAdherent);
	if (compteurEmp >= 3)
	{
		printf("Vous ne pouvez pas réserver et/ou emprunter plus de 3 jeux. Veuillez supprimer des réservations ou retourner des jeux.\n");
		return -2;
	}

	if (rechercheDateEmpruntDepasse(tEmp, *nbEmp, idAdherent, dateActu) == 1)
	{
		printf("Vous avez emprunté un jeu il y a plus d'un mois.\n");
		printf("Tant que vous ne le retournerez pas, vous ne pourrez pas emprunter de nouveau.\n");
		return -2;
	}

	if (*nbEmp == TAILLEMAX)
	{
		printf("Tableau des emprunts trop petit. Emprunt annulé.\n");
		return -1;
	}

	emp.idAdherent = idAdherent;
	emp.idJeu = idJeux;
	emp.idEmprunt = rechercheIdEmprunt(tEmp, *nbEmp);
	emp.dateEmprunt.jour = dateActu.jour;
	emp.dateEmprunt.mois = dateActu.mois;
	emp.dateEmprunt.annee = dateActu.annee;

	tEmp[*nbEmp] = (Emprunt *)malloc(sizeof(Emprunt));
	if (tEmp[emp.idEmprunt] == NULL)
	{
		printf("Problème avec malloc durant l'allocation dynamique\n");
		return -1;
	}

	decalageADroite(tEmp, *nbEmp, emp.idEmprunt);

	*tEmp[emp.idEmprunt] = emp;
	(*nbEmp)++;

	return emp.idEmprunt;
}

void decalageADroite(Emprunt ** tEmp, int nbEmp, int i)
{
	int j;

	for (j = nbEmp - 1; j >= i; j--)
		*tEmp[j + 1] = *tEmp[j];
}

int ajoutDunAdherent(Adherent **tAdh, int *nbAdh)
{
	int longueurMax = 30;

	Adherent adh;
	Date dateActu = recupererDateActuelle();

	int longueur;

	printf("Nous allons créer votre compte adhérent\n");
	printf("Entrez votre civilité (Mr)/(Mme) : ");
	scanf("%s%*c", adh.civilite);

	while (strcmp(adh.civilite, "Mr" ) != 0 && strcmp(adh.civilite, "Mme" ) != 0)
	{
		printf("%s\n", adh.civilite);
		printf("Erreur lors de l'entrée de la civilité.\nEntrez votre civilité (Mr)/(Mme) : ");
		scanf("%s%*c", adh.civilite);
	}
	
	printf("Entrez votre nom : ");
	fgets(adh.nom, longueurMax, stdin);
	longueur = strlen(adh.nom);
	if (adh.nom[longueur - 1] == '\n')
		adh.nom[longueur - 1] = '\0';

	while (longueur == 1)
	{
		printf("Erreur. Entrez un nom valide : ");
		fgets(adh.nom, longueurMax, stdin);
		longueur = strlen(adh.nom);
		if (adh.nom[longueur - 1] == '\n')
			adh.nom[longueur - 1] = '\0';
	}

	printf("Entrez votre prénom : ");
	scanf("%s%*c", adh.prenom);
	
	adh.idAdherent = *nbAdh;
	adh.dateInscription.jour = dateActu.jour;
	adh.dateInscription.mois = dateActu.mois;
	adh.dateInscription.annee = dateActu.annee;

	if (*nbAdh == TAILLEMAX)
	{
		printf("Tableau des adhérents trop petit. Inscription annulée.\n");
		return -1;
	}

	tAdh[*nbAdh] = (Adherent *)malloc(sizeof(Adherent));
	if (tAdh[*nbAdh] == NULL)
	{
		printf("Problème avec malloc durant l'allocation dynamique\n");
		return -1;
	}

	*tAdh[*nbAdh] = adh;
	(*nbAdh)++;

	return 0;
}

/*
Nom : dateActuel

Finalité : fonction qui créé un fichier .txt et écrit dedans la date actuel au format jj/mm/aaaa grâce à une fonction shell.
Cette date est ensuite lue et retournée.

Description générale :
	-Cette fonction crée un fichier "date.txt" dans lequel il marque la date du jour.
	-Elle ouvre le fichier "date.txt" en lecture.
	-Elle lit le jour, le mois et l'année de la date dans "date.txt"
	-Elle retourne finalement la date lu.

Paramètres en entrée : Aucuns

Valeur retournée : la Date d du jour.  

Variables locales: 
	-FILE*flot: flot d'entrée du fichier lu. Permet de lire le fichier contenant la date du jour.
	- d Date: variable où sera stockée la date du jour
*/

Date recupererDateActuelle(void)
{
	FILE *flot;
	Date d;
	system("date +%d/%m/%Y > date.txt");
	flot = fopen("date.txt", "r");
	fscanf(flot, "%d/%d/%d", &d.jour, &d.mois, &d.annee);
	fclose(flot);
	return d;
}

/*
Nom : validiteDateEmp

Finalité : fonction qui vérifie si un emprunt a été effectué il y a plus d'un mois. La fonction retourne 1 si oui et 0 si non.

Description générale :
	-Cette fonction vérifie si la différence entre les 2 dates est supérieur  à 1. Si c'est le cas la fonction retourne 1.
	-Elle vérifie si l'année actuelle est supérieur à l'année d'emprunt. Si c'est le cas, elle vérifie que le mois d'emprunt était décembre
	et que le mois actuel est janvier. Elle vérifie aussi que le jour d'emprunts était supérieur au jour actuel. Si toutes ces conditions 
	sont vérifiées, la fonction retourne 0.
	-Si le mois actuel et le mois de la date d'emprunt sont les même, elle retourne 0. Sinon elle vérifie si la différence entre les 2 mois est 
	supérieur  à 1. Si c'est le cas, elle retourne 1. Enfin si aucune des deux conditions précédentes sont remplis, elle vérifie enfin 
	si le jour actuel est inférieur ou égal au jour d'emprunt. Si c'est le cas, on retourne 0. 
	-Si aucune des conditions ci dessus n'est remplie, l'emprunt n'est pas terrminé, on retourne 1.

Paramètres en entrée : Date dateActu qui contient la date actuel et dateEmprunt qui contient une date d'emprunt.

Valeur retournée : 0 si l'emprunt est toujours autorisé, 1 dans le cas contraire.

Variables locales: 
	-Aucune
*/

int validiteDateEmp(Date dateActu, Date dateEmprunt)
{
	if (dateActu.annee - dateEmprunt.annee > 1)
		return 1;
	if (dateActu.annee > dateEmprunt.annee)
		if (dateEmprunt.mois == 12)
			if (dateActu.mois == 1)
				if (dateActu.jour <= dateEmprunt.jour)
					return 0;
			else 
				return 1;
		else
			return 1;
		
	if(dateActu.mois == dateEmprunt.mois)
		return 0;
	else if (dateActu.mois - dateEmprunt.mois > 1)
		return 1;
	else
		if(dateActu.jour <= dateEmprunt.jour)
				return 0;

	return 1;
}

/*
Nom : validiteDateInscription

Finalité : fonction qui vérifie que moins d'un an s'est passé entre la date d'inscription de l'adhérent et la date du jour et donc qui 
vérifie si l'adhésion est toujours valide.

Description générale :
	-Cette fonction vérifie si l'année d'inscription est égale à l'année actuelle, si c'est le cas l'adhésion est toujours valide, on
	retourne 0.
	-Elle vérifie si la différence entre les 2 années est supérieur à 1. Si c'est le cas l'adhésion n'est plus valide, on retourne 1.
	-Elle vérifie ensuite si le mois actuel est supérieur au mois d'inscription. Si c'est le cas l'adhésion n'est plus valide, on retourne 1.
	-Si le mois actuel et le mois de la date s'inscription sont les même, elle vérifie que le jour de la date actuel est supérieur ou égal au
	jour de la date d'inscription. Si c'est le cas, on retourne 1. 
	-Si aucune des conditions ci dessus n'est remplie, l'adhésion est toujours  valide, on retourne 0.

Paramètres en entrée : Date dateActu qui contient la date actuel et dateInscription qui contient une date d'inscription.

Valeur retournée : 0 si l'adhésion est toujours valide, 1 dans le cas contraire.

Variables locales: 
	-Aucune
*/

int validiteDateInscription(Date dateActu, Date dateInscription)
{
	
	if(dateInscription.annee == dateActu.annee)
		return 0;
	if(dateActu.annee - dateInscription.annee > 1)
		return 1;
	if(dateActu.mois > dateInscription.mois)
		return 1;
	if(dateActu.mois == dateInscription.mois)
		if(dateActu.jour >= dateInscription.jour)
			return 1;
	return 0;
}

/*******************************************************************/
/* FONCTIONNALITE 6 */



//retourne 0 si date1 est plus grande que date 2
//1 si date2 est plus grande que date1
//2 sinon
int comparaisonDates(Date date1, Date date2)
{
	if (date1.annee > date2.annee)
		return 0;
	else if(date2.annee > date1.annee)
		return 1;

	if (date1.mois > date2.mois)
		return 0;
	else if(date2.mois > date1.mois)
		return 1;

	if (date1.jour > date2.jour)
		return 0;
	else if(date2.jour > date1.jour)
		return 1;

	return 2;
}

ListeReservation retourDunJeu(ListeReservation lr, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int nbJeux)
{
	int longueurMax = 30;
	int idEmprunt, positionJeu, erreur, present, longueur;
	char nomEntre[longueurMax], choixSuppression;
	Jeu jouet;
	Adherent adh;
	Emprunt emp;

	printf("Donnez votre id d'Emprunt: ");
	scanf("%d%*c", &idEmprunt);
	present = rechercheEmprunt(tEmp, *nbEmp, idEmprunt, &emp); 
	if (present == -1)		
	{
		printf("Le numéro d'emprunt n'existe pas. \n");
		printf("Si vous avez perdu votre identifiant d'emprunt, vous pouvez faire une demande de réclamation sur le site ludotheque.com\n");
		return lr;
	}

	printf("Pour nous assurer de la sécurité de vos emprunts, nous vous demandons de rentrer votre nom : ");
	fgets(nomEntre, longueurMax, stdin);
	longueur = strlen(nomEntre);
	if (nomEntre[longueur - 1] == '\n')
		nomEntre[longueur - 1] = '\0';

	erreur = rechercheIdentiteAdherent(tAdh, nbAdh, emp.idAdherent, &adh);
	if (erreur == -1)
	{
		printf("Une erreur inconnue est survenue, veuillez réssayer.\n");
		return lr;
	}

	if (strcmp(adh.nom, nomEntre) != 0)
	{
		printf("Le couple nom/identifiant de la réservation est incorrect. Vérifiez vos données puis réessayez.\n");
		return lr;
	}

	//je recherche le nom du jeu en fonction de son id
	positionJeu = rechercheInfosJeu2(tJeux, nbJeux, emp.idJeu, &jouet);
	printf("***%d***", positionJeu);
	if (positionJeu == -1)
	{
		printf("Une erreur inconnue est survenue, veuillez réssayer.\n");
		return lr;
	}

	printf("Récapitulatif de l'emprunt :\n");
	printf("Nom du jeu : %s\n", jouet.nomJeu);
	printf("Identité : %s %s %s\n", adh.civilite, adh.nom, adh.prenom);
	printf("Date de l'emprunt : %02d/%02d/%04d\n", emp.dateEmprunt.jour, emp.dateEmprunt.mois, emp.dateEmprunt.annee);
	printf("Voulez-vous confirmer le retour (o/n) ? ");
	scanf("%c%*c", &choixSuppression);

	if (choixSuppression == 'o')
	{
		suppressionEmprunt(tEmp, nbEmp, present);
		tJeux[positionJeu]->nbExemplaire = tJeux[positionJeu]->nbExemplaire + 1;

		printf("La suppression a bien été effectuée.\n");

		affichageEmprunt(tEmp, *nbEmp);
		printf("\nreservations\n");
		affichageReservations(lr);

		printf("%d", tJeux[positionJeu]->idJeu);

		if (tJeux[positionJeu]->nbExemplaire == 1)
		{
			lr = transformationResaEnEmprunt(lr, tAdh, nbAdh, tEmp, nbEmp, tJeux, positionJeu);
		}
	}
	else
		printf("Suppression annulée\n");
	return lr;
}

ListeReservation transformationResaEnEmprunt(ListeReservation lr, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int positionJeu)
{
	Date dateResa = {32, 13, 30000};
	Date dateActu = recupererDateActuelle();
	Reservation reserv;
	Adherent adh;
	int erreur, idEmprunt;

	rechercherReservationPlusAncienne(lr, tEmp, *nbEmp, &dateResa, &reserv, tJeux[positionJeu]->idJeu, dateActu);

	if (dateResa.mois == 13)
		return lr;

	idEmprunt = ajoutDunEmprunt(tEmp, nbEmp, reserv.idAdherent, tJeux[positionJeu]->idJeu, dateActu);
	if (idEmprunt == -1)
	{
		printf("Il y a eu un problème lors de la création d'un nouvel emprunt.\n");
		return lr;
	}

	tJeux[positionJeu]->nbExemplaire = tJeux[positionJeu]->nbExemplaire - 1;

	lr = suppressionDuneReservation(lr, reserv.idResa);

	affichageEmprunt(tEmp, *nbEmp);
	printf("\nreservations\n");
	affichageReservations(lr);

	erreur = rechercheIdentiteAdherent(tAdh, nbAdh, reserv.idAdherent, &adh);
	if (erreur == -1)
	{
		printf("Une erreur inconnue est survenue, veuillez réssayer.\n");
		return lr;
	}

	printf("%s %s %s, votre emprunt pour le jeu %s commence maintenant.\n", adh.civilite, adh.nom, adh.prenom, tJeux[positionJeu]->nomJeu);
	printf("Pensez à le retourner avant un mois, sinon vous ne pourrez plus emprunter.\n");
	printf("Votre ID d'emprunt est %04d. Ne le perdez pas, il vous servira à retourner le jeu !\n", idEmprunt);
	return lr;
}

void suppressionEmprunt(Emprunt **tEmp, int *nbEmp, int indice)
{
	int i;

	if (*nbEmp != 1)
		for (i = indice; i <= *nbEmp - 2; i++)
			*tEmp[i] = *tEmp[i + 1];

	//free(tEmp[indice]);

	*nbEmp = *nbEmp - 1;
	affichageEmprunt(tEmp, *nbEmp);
}

/*******************************************************************/
/* FONCTIONNALITE 7 */

ListeReservation suppressionReservation(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, ListeReservation lr)
{
	int longueurMax = 30;
	int idResa, erreur, longueur;
	Reservation reserv;
	Adherent adh;
	Jeu jouet;

	char nomEntre[longueurMax], choix;

	printf("Rentrez l'id de la réservation que vous souhaitez supprimer : ");
	scanf("%d%*c", &idResa);

	erreur = rechercheInfoResa(lr, idResa, &reserv);

	if (erreur == 0)
	{
		printf("L'identifiant de la réservation entré n'existe pas.\n");
		printf("Si vous avez perdu votre identifiant de réservation, vous pouvez faire une demande de réclamation sur le site ludotheque.com\n");
		return lr;
	}

	printf("Pour nous assurer de la sécurité de vos réservations, nous vous demandons de rentrer votre nom : ");
	fgets(nomEntre, longueurMax, stdin);
	longueur = strlen(nomEntre);
	if (nomEntre[longueur - 1] == '\n')
		nomEntre[longueur - 1] = '\0';

	erreur = rechercheIdentiteAdherent(tAdh, nbAdh, reserv.idAdherent, &adh);
	if (erreur == -1)
	{
		printf("Une erreur inconnue est survenue, veuillez réssayer.\n");
		return lr;
	}

	if (strcmp(adh.nom, nomEntre) != 0)
	{
		printf("Le couple nom/identifiant de la réservation est incorrect. Vérifiez vos données puis réessayez.\n");
		return lr;
	}

	erreur = rechercheInfosJeu2(tJeux, nbJeux, reserv.idJeux, &jouet);

	printf("Récapitulatif de la réservation :\n");
	printf("Identité : %s %s %s\n", adh.civilite, adh.nom, adh.prenom);
	printf("Nom du jeu : %s\n", jouet.nomJeu);
	printf("Date de réservation : %02d/%02d/%04d\n", reserv.dateReservation.jour, reserv.dateReservation.mois, reserv.dateReservation.annee);
	printf("Voulez-vous supprimer cette réservation ? (o/n) : ");
	scanf("%c%*c", &choix);

	if (choix != 'o')
	{
		printf("La réservation n'a pas été supprimée !\n");
		return lr;
	}

	lr = suppressionDuneReservation(lr, idResa);

	printf("La réservation a bien été supprimée.\n");

	return lr;
}

ListeReservation suppressionEnTete(ListeReservation lr)
{
	Maillon *svt;
	svt = lr->suivant;
	free(lr);
	return svt;
}

ListeReservation suppressionDuneReservation(ListeReservation lr, int idResa)
{
	if (lr == NULL)
		return lr;

	if (lr->r.idResa == idResa)
	{
		return suppressionEnTete(lr);
	}
	if (lr->r.idResa > idResa)
		return lr;

	lr->suivant = suppressionDuneReservation(lr->suivant, idResa);
	return lr;
}