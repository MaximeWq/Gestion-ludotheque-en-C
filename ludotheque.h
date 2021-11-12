/* programme : ludotheque.h
   auteurs : Jérémy TREMBLAY, Adrien COUDOUR, Maxime WISSOCQ
   date début: 17/12/2020
   date dernière modifiction : 06/01/2021
   Finalité : déclarer les fonctions proposant plusieurs services au sein d'une ludothèque (réservations, emprunts de jeux).
*/

typedef struct 
{
	int jour;
	int mois;
	int annee;
} Date;

typedef struct
{
	int idJeu;
	char nomJeu[30];
	char typeJeu[13];
	int nbExemplaire;
} Jeu;

typedef struct
{
	int idAdherent;
	char civilite[4];
	char nom[30];
	char prenom[30];
	Date dateInscription;
} Adherent;

typedef struct
{
	int idEmprunt;
	int idAdherent;
	int idJeu;
	Date dateEmprunt;
} Emprunt;

typedef struct reservation
{
	int idResa;
	int idAdherent;
	int idJeux;
	Date dateReservation;
} Reservation;

typedef struct liste
{
	Reservation r;
	struct liste *suivant;
} Maillon, *ListeReservation;

/*Chargement et sauvegarde des réservations*/
ListeReservation creerListeVide(void);
ListeReservation ajouterMaillon(ListeReservation lr, Reservation reserv);
ListeReservation InsertionEnTete(ListeReservation lr, Reservation reserv);
Reservation lireReservation(FILE *fe);
ListeReservation chargementReservation(ListeReservation lr);
void affichageReservations(ListeReservation lr);
int enregistrementReservation(ListeReservation lr);
void ecritureFichierReservation(ListeReservation lr, FILE *flot);
ListeReservation suppressionListe(ListeReservation lr);

/*Chargement et sauvegarde des jeux*/
Jeu lireJeu(FILE *flot);
int chargementJeux(Jeu *tJeux[]);
void affichageJeux(Jeu **tabJeu, int nbJeux);
int enregistrementJeux(Jeu **tJeux, int nbJeux);
int chargementJeuxBin(Jeu **tJeux);

/*Chargement et sauvegarde des adhérents*/
Adherent lireAdherent(FILE *fe);
int chargementAdherent(Adherent *tAdh[]);
void affichageAdherent(Adherent **tAdh, int nbAdh);
int enregistrementAdherent(Adherent **tAdh, int nbAdh);
int chargementAdherentBin(Adherent **tAdh);

/*Chargement et sauvegarde des emprunts*/
Emprunt lireEmprunt(FILE *fe);
int chargementEmprunt(Emprunt *tEmp[]);
void affichageEmprunt(Emprunt **tEmp, int nbEmp);
int enregistrementEmprunt(Emprunt **tEmp, int nbEmp);
int chargementEmpruntBin(Emprunt **tEmp);

/*Fonctions de tri*/
void triJeuxParNom(Jeu *tJeux[], int nbJeux);
int rechercheRMin(Jeu *tJeux[], int i, int n);
void permutation(Jeu *tJeux[], int i, int j);
void triRapideEmpruntsParId(Emprunt **tEmp, int nbEmp);

/*Fonctions de recherche*/
int rechercheInfosJeux(Jeu **tJeux, int nbJeux, char nomJeu[], Jeu *jouet);
int rechercheInfosJeu2(Jeu **tJeux, int nbJeux, int idJeux, Jeu *jeu);
int rechercheIdentiteAdherent(Adherent **tAdh, int nbAdh, int idAdherent, Adherent *adh);
int rechercheEmprunt(Emprunt **tEmp, int nbEmp, int idEmp, Emprunt *emp);
int rechercheInfoResa(ListeReservation lr, int idResa, Reservation *reserv);
int rechercheIdEmprunt(Emprunt **tEmp, int nbEmp);
int rechercheIdResa(ListeReservation lr, int indice);
void rechercherReservationPlusAncienne(ListeReservation lr, Emprunt **tEmp, int nbEmp, Date *dateResa, Reservation *reserv, int idJeux, Date dateActu);
int compteNbEmp(Emprunt **tEmp, int nbEmp, int idAdherent);
int rechercheDateEmpruntDepasse(Emprunt **tEmp, int nbEmp, int idAdherent, Date dateActu);


/*Fonctions d'affichage*/
int affichageJeuxDunType(Jeu *tJeux[], int nbJeux, char *typeJeu);
void affichageJeuxDisponibles(Jeu *tJeux[], int nbJeux);
int affichageEmpruntEnCours(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp);
int affichageReservationsPourUnJeu(ListeReservation lr, int idJeux, Adherent **tAdh, int nbAdh);

/*Suppression / ajouts*/
ListeReservation suppressionDuneReservation(ListeReservation lr, int idResa);
ListeReservation suppressionEnTete(ListeReservation lr);
void suppressionEmprunt(Emprunt **tEmp, int *nbEmp, int indice);
ListeReservation transformationResaEnEmprunt(ListeReservation lr, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int positionJeu);
int ajoutDunAdherent(Adherent **tAdh, int *nbAdh);
int ajoutDunEmprunt(Emprunt **tEmp, int *nbEmp, int idAdherent, int idJeux, Date dateActu);
void decalageADroite(Emprunt ** tEmp, int nbEmp, int i);

/*Dates*/
int comparaisonDates(Date date1, Date date2);
Date recupererDateActuelle(void);
int validiteDateInscription(Date dateActu,Date dateInscription);
int validiteDateEmp(Date dateActu, Date datemEmp);



/*Fonctionalité 3*/
void saisieEmpAffichage(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp);

/*Fonctionalité 4*/
void saisieJeuPourAffichageReservations(Jeu **tJeux, int nbJeux, ListeReservation lr, Adherent **tAdh, int nbAdh);

/*Fonctionalité 5*/
ListeReservation emprunterEtReserver(Adherent **tAdh, int *nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int nbJeux, ListeReservation lr);

/*Fonctionalité 6*/
ListeReservation retourDunJeu(ListeReservation lr, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int *nbEmp, Jeu **tJeux, int nbJeux);

/*Fonctionalité 7*/
ListeReservation suppressionReservation(Jeu **tJeux, int nbJeux, Adherent **tAdh, int nbAdh, ListeReservation lr);

/*Menu*/
void globale(void);
void affichageMenu(void);
ListeReservation menu(ListeReservation lr, Jeu **tJeux, int nbJeux, Adherent **tAdh, int *nbAdh, Emprunt **tEmp, int *nbEmp);
void affichageSousMenu(void);
void sousMenu(ListeReservation lr, Jeu *tJeux[], int nbJeux, Adherent **tAdh, int nbAdh, Emprunt **tEmp, int nbEmp);
void affichageSousMenuJeux(void);
void sousMenuJeux(Jeu **tJeux, int nbJeux);

/*Fonctions utilitaires*/
void restaurationDonneesFichiers(void);
void calibrage(void);

/*Fonctions de tests*/
void testChargementReservations(void);
void testChargementAdherent(void);
void testChargementJeux(void);
void testChargementEmprunt(void);
void testTriJeux(void);
void testTriEmprunts(void);
void testRechercheEtCompDates(void);


void triJeuxParId(Jeu **tJeux, int nbJeux);
void separation(Jeu **tJeux1, Jeu **tJeux2, Jeu **tJeux3, int nbJeux, int *nombre1, int *nombre2);
int interclassement(Jeu **tJeux2, Jeu **tJeux3, Jeu **tJeux1, int *nombre1, int *nombre2);