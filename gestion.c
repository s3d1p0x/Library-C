#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion.h"

#define MAX_LINE_LENGTH 500
#define MAX_COLUMNS 5

//=============================================================================
// fonctions implémentées
//=============================================================================

//Fonction qui affiche le nom du programme lors du lancement.
void initialisation(){
    
    system("clear");
    printf("  ╔═╗ ╦  ╦╔╗ ╦═╗╔═╗╦═╗╦ ╦\n");
    printf("  ║───║  ║╠╩╗╠╦╝╠═╣╠╦╝╚╦╝\n");
    printf("  ╚═╝ ╩═╝╩╚═╝╩╚═╩ ╩╩╚═ ╩\n");

    printf("Bienvenu dans le gestionnaire de bibliothèque !\n");
    printf("===============================================\n");
}

//=============================================================================
// Toutes les fonctions "menu"
//=============================================================================

//Fonction qui affiche le menu principal. Ce menu permet de choisir les differentes fonctions
void menu_choix(FILE *catalogue, FILE *utilisateurs){
    
    unsigned short int choix;
    printf("\nQue voulez-vous faire ?\n");
    printf("\n1. Ajouter/Modifier/Supprimer un livre\n2. Ajouter/Modifier/Supprimer un membre\n3. Rechercher un livre\n4. Emprunter/Retourner un livre\n0. Quitter le programme\n");   
    printf("\nTapez un numero : ");scanf ("%hd",&choix);

    switch(choix) {
        case 0: //Si l'utilisateur quitte le programme
            fclose(catalogue);
            fclose(utilisateurs);
            printf("\nMerci d'avoir utilisé le programme !");
            exit(0);
        case 1: //Menu gestion des livres
            system("clear");
            menu_gestion_livre(catalogue, utilisateurs);
            break;
        case 2: //Menu gestion des membres
            system("clear");
            menu_gestion_membre(catalogue, utilisateurs);
            break;
        case 3: //Menu de recherche
            system("clear");
            menu_recherche(catalogue, utilisateurs);
            break;
        case 4: //Emprunter/Retourner pas implémenté
            //menu_quatre();
            break;
        default:
            menu_choix(catalogue, utilisateurs);
    }
}

//Fonction qui permet la recherche des livres par titre, auteur et categorie
void menu_recherche(FILE *catalogue, FILE *utilisateurs){
    //Categorie categorie;
    unsigned short int choix;
    printf("\nQue voulez-vous faire ?\n");
    printf("\n1. Recherche par titre\n2. Recherche par auteur\n3. Recherche par catégorie\n0. Retour\n");   
    printf("\nTapez un numero : ");scanf ("%hd",&choix);

    switch(choix) {
        case 0: //Retour au menu principal
            initialisation();
            menu_choix(catalogue, utilisateurs);
            break;
        case 1: //Effectuer une recherche par titre
            rechercherTitre();
            menu_choix(catalogue, utilisateurs);
            //break;
        case 2: //Effectuer une recherche par auteur
            rechercherAuteur();
            menu_choix(catalogue, utilisateurs);
            //break;
        case 3: //Effectuer une recherche par categorie
            rechercheCategorie();
            menu_choix(catalogue, utilisateurs);
            //break;
        default:
            menu_choix(catalogue, utilisateurs);
            break;
    }
}

//Fonction qui permet la gestion des livres comme l'ajout, la modification et la suppression des livres.
void menu_gestion_livre(FILE *catalogue, FILE *utilisateurs){

    unsigned short int choix;
    Livre livre;
    printf("\nQue voulez-vous faire ?\n");
    printf("\n1. Ajouter un livre\n2. Modifier un livre\n3. Supprimer un livre\n0. Retour\n");   
    printf("\nTapez un numero : ");scanf ("%hd",&choix);

    switch(choix) {
        case 0://Retour au menu principal
            initialisation();
            menu_choix(catalogue, utilisateurs);    
        case 1: //Ajouter un livre au catalogue
            ajout_livre(catalogue,livre);
            break;
        case 2:
            break;
        case 3: //Supprimer un livre via son ID
            int livreID;
            printf("Saissisez l'ID du livre : ");scanf("%d",&livreID);
            supprimer_livre(catalogue,livreID);
            break;
        default:
            menu_gestion_livre(catalogue, utilisateurs);
    }
}

//Fonction permettant de gérer les membres comme l'ajout ou bien la suppression
void menu_gestion_membre(FILE *catalogue, FILE *utilisateurs){

    unsigned short int choix;
    Membre membre;
    printf("\nQue voulez-vous faire ?\n");
    printf("\n1. Ajouter un membre\n2. Modifier un membre\n3. Supprimer un membre\n0. Retour\n");   
    printf("\nTapez un numero : ");scanf ("%hd",&choix);

    switch(choix) {
        case 0://Retour au menu principal
            initialisation();
            menu_choix(catalogue, utilisateurs);    
        case 1://Fonction d'ajout un membre
            ajout_membre(utilisateurs,membre);
            break;
        case 2:
            // modifier_membre()
            break;
        case 3://Fonction supprimer un membre
            int membreID;
            printf("Saissisez l'ID du membre : ");scanf("%d",&membreID);
            supprimer_membre(utilisateurs,membreID);
            break;
        default:
            menu_gestion_membre(catalogue, utilisateurs);
    }

}

//=============================================================================
// Toutes les fonctions permettant de gérer les membres
//=============================================================================

//Fonction qui permet de récuperer le nombre de ligne dans le fichier catalogue afin d'attriber un ID
int id_membre(FILE *utilisateurs){
    //Ouverture du fichier en mode "lecture" avec "r" 
    utilisateurs = fopen("membres.txt", "r");

    //Compter le nombre de lignes dans le fichier
    int nb_ligne = 0;
    char espace;
    while ((espace = fgetc(utilisateurs)) != EOF) {
        if (espace == '\n') {
            nb_ligne++;
        }
    }

    //Vérifier si le fichier est vide, on attribue le premier ID en 0
    if (nb_ligne == 0) {
        nb_ligne = 0;
    }

    //Fermer le fichier
    fclose(utilisateurs);
    return nb_ligne;
}

//Fonction qui permet la création d'un membre avec son id, nom, prenom, annee de naissance
void ajout_membre(FILE *utilisateurs, Membre addmembre){
    char prenom[50];
    char nom[50];
    Date annee_naissance;

    // Attribuer l'ID d'un membre
    addmembre.id = id_membre(utilisateurs);

    // Ajout d'un prenom au membre
    printf("\nEntrez votre Prenom : ") ; scanf("%50s", prenom);
    for (int i = 0; i<50; i++){
        addmembre.prenom[i] = prenom[i];
    }

    // Ajout d'un nom au membre
    printf("\nEntrez votre Nom : ") ; scanf("%50s", nom);
    for (int i = 0; i<50; i++){
        addmembre.nom[i] = nom[i];
    }

    // Ajout d'une année de naissance du membre
    printf("\nEntrez la date de naissance (jj mm aaaa) : ") ; scanf("%d %d %d", &annee_naissance.jour, &annee_naissance.mois, &annee_naissance.année);
    for (int i = 0; i<50; i++){
        addmembre.annee_naissance = annee_naissance;
    }

    //Ajout du livre dans le fichier catalogue.txt et attribuer l'id du livre en se basant sur sa position dans le catalogue
    if (utilisateurs == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(0);
    }
    char separateur = ';';
    fprintf(utilisateurs,"%d%c%s%c%s%c%02d-%02d-%02d%c\n",addmembre.id,separateur,addmembre.prenom,separateur,addmembre.nom,separateur,addmembre.annee_naissance.jour, addmembre.annee_naissance.mois, addmembre.annee_naissance.année,'#');
    fclose(utilisateurs);
}


// Fonction permettant de supprimer un membre du catalogue en créeant un fichier temporaire permettant de mettre à jour le catalogue
void supprimer_membre(FILE *utilisateurs, int membreID){
    utilisateurs = fopen("membres.txt", "r");

    // Creation d'un fichier temporaire pour les membres non supprimés
    FILE* membre_temp = fopen("membre_temp.txt", "w");
    if (membre_temp == NULL) {
        printf("Problème lors de la création du fichier.\n");
        fclose(utilisateurs);
        exit(0);
    }

    char ligne[200];
    int id;
    int membreSupprime = 0; // indice de suppression du membre

    while (fgets(ligne, sizeof(ligne), utilisateurs) != NULL) {
        sscanf(ligne, "%d", &id);

        //Si l'ID correspond on n'ecrit pas dans le nouveau fichier membres.txt
        if (id != membreID) {
            fprintf(membre_temp, "%s", ligne);
        } else {
            membreSupprime = 1;
        }
    }

    //Fermeture des fichiers
    fclose(utilisateurs);
    fclose(membre_temp);

    //Supprime l'ancien fichier membres
    remove("membres.txt");

    //Renomemr le fichier temporaire en membres.txt
    rename("membre_temp.txt", "membres.txt");

    //Affichage dans le terminal d'un message succès/erreur
    if (membreSupprime) {
        printf("Membres supprimé avec succès.\n");
    } 
    else {
        printf("Aucun membre trouvé avec l'ID spécifié.\n");
    }
}

//=============================================================================
// Toutes les fonctions permettant de gérer les livres
//=============================================================================

//Fonction qui permet de récuperer le nombre de ligne dans le fichier catalogue afin d'attriber un ID
int id_livre(FILE *catalogue){
    //Ouverture du fichier en mode "lecture" avec "r" 
    catalogue = fopen("catalogue.txt", "r");

    //Compter le nombre de lignes dans le fichier
    int nb_ligne = 0;
    char espace;
    while ((espace = fgetc(catalogue)) != EOF) {
        if (espace == '\n') {
            nb_ligne++;
        }
    }

    //Vérifier si le fichier est vide, on attribue le premier ID en 0
    if (nb_ligne == 0) {
        nb_ligne = 0;
    }

    //Fermer le fichier
    fclose(catalogue);
    return nb_ligne;
}

//Fonction qui permet la création d'un livre avec son id, titre, l'auteur, sa categorie et son statut
void ajout_livre(FILE *catalogue, Livre addLivre){
    char titre[200];
    char auteur[200];
    unsigned short int categorie;

    //Attribuer l'ID du livre
    addLivre.id = id_livre(catalogue);

    //Ajout du titre du livre
    printf("\nEntrez un titre : ");scanf("%*s %49[^\n]",titre);
    for (int i = 0; i<200; i++ ) {
        addLivre.titre[i] = titre[i];
    }

    //Ajout du nom de l'auteur
    printf("\nEntrez le nom de l'auteur : ");scanf("%*s %49[^\n]",auteur);
    for (int i = 0; i<200; i++ ) {
        addLivre.auteur[i] = auteur[i];
    }
    
    //Ajout de la catégorie
    printf("\nSélectionnez la catégorie : ");
    scanf("%hd",&categorie);
    while (categorie < 1 || categorie > 6) {
        printf("Entrez un nombre existant.\n");   
        scanf("%hd",&categorie);        
    }
    addLivre.categorie = categorie;

    //Definir le statut du livre : Disponible automatiquement lors de l'ajout
    addLivre.statut = 1;

    //Ajout du livre dans le fichier catalogue.txt et attribuer l'id du livre en se basant sur sa position dans le catalogue
    if (catalogue == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(0);
    }
    char separateur = ';';
    fprintf(catalogue,"%d%c%s%c%s%c%hd%c%d%c\n",addLivre.id,separateur,addLivre.titre,separateur,addLivre.auteur,separateur,addLivre.categorie,separateur,addLivre.statut,'#');
    fclose(catalogue);

}

//Fonction permettant de supprimer un livre du catalogue en créeant un fichier temporaire permettant de mettre à jour le catalogue
void supprimer_livre(FILE *catalogue, int livreID) {
    //Ouverture du fichier en mode lecture et modification
    catalogue = fopen("catalogue.txt", "r+");

    //Création d'un fichier temporaire pour stocker les livres non supprimés
    FILE* catalogue_temp = fopen("catalogue_temp.txt", "w");
    if (catalogue_temp == NULL) {
        printf("Problème lors de la création du fichier.\n");
        fclose(catalogue);
        exit(0);
    }

    char ligne[200];
    int id;
    int livreSupprime = 0; // indice de suppression du livre

    while (fgets(ligne, sizeof(ligne), catalogue) != NULL) {
        // Récupération de l'ID du livre
        sscanf(ligne, "%d", &id);

        //Si l'ID correspond a livreID, on n'ecrit pas dans le nouveau fichier catalogue
        if (id != livreID) {
            fprintf(catalogue_temp, "%s", ligne);
        } else {
            livreSupprime = 1;
        }
    }

    // Fermeture des fichiers
    fclose(catalogue);
    fclose(catalogue_temp);

    //Supprime l'ancien catalogue
    remove("catalogue.txt");

    //Renomemr le fichier temporaire en catalogue.txt
    rename("catalogue_temp.txt", "catalogue.txt");

    //Affichage dans le terminal d'un message succès/erreur
    if (livreSupprime) {
        printf("Livre supprimé avec succès.\n");
    } 
    else {
        printf("Aucun livre trouvé avec l'ID spécifié.\n");
    }
}

//=============================================================================
// Toutes les fonctions recherche
//=============================================================================

//Fonction qui permet d'effectuer un affichage de tous les livres correspondant à une catégorie
void rechercheCategorie() {
    FILE *fichier = fopen("catalogue.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int choixColonne;
    printf("1. Linux\n2. Langages de programmation\n3. Hacking\n4. Certifications\n5. Réseau\n\nEntrez la catégorie de recherche : ");
    scanf("%d", &choixColonne);

    char ligne[MAX_LINE_LENGTH];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Séparation des colonnes avec le délimiteur ';'
        char *token;
        char *colonne[MAX_COLUMNS];
        int numColonnes = 0;

        //On separe la chaine de caractere "ligne" avec le separateur ";"
        token = strtok(ligne, ";");
        while (token != NULL && numColonnes < MAX_COLUMNS) {
            colonne[numColonnes] = token;
            numColonnes++;
            token = strtok(NULL, ";");
        }

        // Vérification de la quatrième colonne et affichage de la ligne correspondante
        if (numColonnes >= 4 && atoi(colonne[3]) == choixColonne) {
            printf("\nLigne correspondante : %s\n", ligne);
            for (int i = 0; i < numColonnes; i++) {
                printf("Colonne %d : %s\n", i+1, colonne[i]);
            }
            printf("\n");
        }
    }

    fclose(fichier);
}

//Fonction qui permet d'effectuer un affichage de tous les livres correspondant à un auteur
void rechercherAuteur() {
    FILE *fichier = fopen("catalogue.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char auteurRecherche[50];
    printf("Entrez le nom de l'auteur : ");
    scanf("%*s %99[^\n]", auteurRecherche);  // Lire toute la ligne incluant les espaces

    char ligne[MAX_LINE_LENGTH];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Séparation des colonnes avec le délimiteur ';'
        char *token;
        char *colonne[MAX_COLUMNS];
        int numColonnes = 0;

        //On separe la chaine de caractere "ligne" avec le separateur ";"
        token = strtok(ligne, ";");
        while (token != NULL && numColonnes < MAX_COLUMNS) {
            colonne[numColonnes] = token;
            numColonnes++;
            token = strtok(NULL, ";");
        }

        // Vérification de la troisième colonne (auteur) et affichage de la ligne correspondante
        if (numColonnes >= 3 && strstr(colonne[2], auteurRecherche) != NULL) {
            printf("Ligne correspondante : %s\n", ligne);

            // Affichage des colonnes individuelles
            for (int i = 0; i < numColonnes; i++) {
                printf("Colonne %d : %s\n", i+1, colonne[i]);
            }
            printf("\n");
        }
    }

    fclose(fichier);
}

//Fonction qui permet d'effectuer un affichage de tous les livres correspondant au titre d'un livre
void rechercherTitre() {
    FILE *fichier = fopen("catalogue.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char titreRecherche[100];
    printf("Entrez le titre : ");
    scanf("%*s %99[^\n]", titreRecherche);  // Lire toute la ligne incluant les espaces

    char ligne[MAX_LINE_LENGTH];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Séparation des colonnes avec le délimiteur ';'
        char *token;
        char *colonne[MAX_COLUMNS];
        int numColonnes = 0;

        //On separe la chaine de caractere "ligne" avec le separateur ";"
        token = strtok(ligne, ";");
        while (token != NULL && numColonnes < MAX_COLUMNS) {
            colonne[numColonnes] = token;
            numColonnes++;
            token = strtok(NULL, ";");
        }

        // Vérification de la deuxième colonne (titre) et affichage de la ligne correspondante
        if (numColonnes >= 2 && strstr(colonne[1], titreRecherche) != NULL) {
            printf("Ligne correspondante : %s\n", ligne);

            // Affichage des colonnes individuelles
            for (int i = 0; i < numColonnes; i++) {
                printf("Colonne %d : %s\n", i+1, colonne[i]);
            }
            printf("\n");
        }
    }

    fclose(fichier);
}