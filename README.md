# Projet gestion d'une ludothèque en C

Projet de 1ère année de DUT informatique réalisé en C.

Fonctionnalités:

1. chargement des quatre fichiers en mémoire ;
2. affichage de la liste des jeux disponibles triée par type de Jeux, puis par ordre alphabétique
de leur nom;
3. affichage de la liste des emprunts en cours en mentionnant : le nom du jeu, l’identité de
l’emprunteur ainsi que la date de l’emprunt ;
4. affichage de la liste des réservations pour un jeu donné ;
5. saisie et enregistrement d’un nouvel emprunt ou d’une réservation
◦ création de l’adhérent si nouveau (avec contrôle de saisie) ;
◦ enregistrement de l’emprunt ou de la réservation si possible ;
6. retour d’un jeux. Le retour déclenche l’examen des réservations pour peut être transformer
une réservation en emprunt et faire parvenir le jeu à l’adhérent l’ayant réservé.
7. annulation d’une réservation 
8. sauvegarde de l’ensemble des données dans les quatre fichiers

Fichiers de donnés:

• un fichier jeux qui référence tous les jeux de la ludothèque. Pour chaque jeux il y a : idJeux,
nom du jeux, type du jeux (construction, plateau, tuile, carte, logique), nombre
d’exemplaires.
• un fichier adherents qui référence tous les adhérents de la ludothèque. Pour chaque
adhérent il y a : idAdherent, civilité (Mr, Mme), nom, prénom, date d’inscription. Ce fichier
est trié selon l’idAdherent.
• un fichier emprunts qui référence tous les emprunts en cours : idEmprunt, idAdherent,
idJeux, date d’emprunt. Ce fichier est trié par ordre croissant des dates d’emprunt.
• Un fichier reservations qui référence les réservations de jeux : idResa, idAdherent, idJeux,
date de réservation.

Ces fichiers sont sous format simple et binaire.


