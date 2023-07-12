#ifndef GESTION_H 
#define GESTION_H

//=============================================================================
// énumérations
//=============================================================================

//Enumération concernant les catégories des livres
typedef enum {
    Linux = 1,
    Languages_de_programmation,
    Hacking,
    Certifications,
    Réseau,
}Categorie;

//Enumération concernant le statut des livres
typedef enum {
    DISPONIBLE = 1,
    EMPRUNTE,
    RESERVE
}Statut;

//=============================================================================
// structures
//=============================================================================

//Type de données concernant la date
typedef struct {
    int jour;
    int mois;
    int année;
}Date;

//Type de données représentant les informations pour un livre
typedef struct {
    int id;
    char titre[200];
    char auteur[200];
    Categorie categorie;
    Statut statut;
}Livre;


//Type de données représentant les informations des membres de la bibliothèque
typedef struct {
    int id;
    char prenom[20];
    char nom[20];
    Date annee_naissance;
    int livre_emprunte;
}Membre;

//=============================================================================
// prototypes
//=============================================================================

/*Initialisation du programme*/
void initialisation();
void menu_choix(FILE *catalogue, FILE *utilisateurs);

/*Recherche d'un livre*/
void menu_recherche(FILE *catalogue, FILE *utilisateurs);
void rechercheCategorie(); //Recherche d'un livre par categorie
void rechercherTitre(); //Recherche d'un livre par titre
void rechercherAuteur(); //Recherche d'un livre par auteur


/*Ajout, suppression et modification de livres dans un catalogue*/
void menu_gestion_livre(FILE *catalogue, FILE *utilisateur); //Menu concernant la gestion du livre
void ajout_livre(FILE *catalogue,Livre livre); //Ajout du livre dans le fichier catalogue.txt
int id_livre(FILE *catalogue); //Récuperer le nombre de ligne du fichier pour attribuer l'ID du livre
void supprimer_livre(FILE *catalogue, int livreID); //Permet de supprimer un livre du catalogue
void modifier_livre(FILE *catalogue, Livre livre);

/*Ajout, suppression et modification de membres*/
void menu_gestion_membre(FILE *catalogue, FILE *utilisateurs); //Menu concernant la gestion du livre
void ajout_membre(FILE *catalogue, Membre membre); //Ajout du livre dans le fichier catalogue.txt
int id_membre(FILE *catalogue); //Récuperer le nombre de ligne du fichier pour attribuer l'ID du livre
void supprimer_membre(FILE *catalogue, int membreID); //Permet de supprimer un livre du catalogue
void modifier_membre(FILE *catalogue, Membre membre);

#endif