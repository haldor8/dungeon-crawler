#include "creation_salles.h"
#include "tests.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int longueur_min_salle = 5;
int longueur_max_salle = 20;

int largeur_min_salle = 5;
int largeur_max_salle = 20;

void pause()
{
    char d;
    printf("Appuyez sur entree pour continuer.");
    // Deux scanf à cause du dernier \n
    scanf("%c", &d);
    scanf("%c", &d);
}

pos_salle **initSalle(int longueur, int largeur, char *type_salle)
{
    if (longueur < 5 || largeur < 5)
    {
        printf("La longueur et la largeur de la salle doivent être supérieures à 6.\n");
        return NULL;
    }

    // Allouer de l'espace pour le tableau bidimensionnel
    pos_salle **salle = (pos_salle **)malloc(longueur * sizeof(pos_salle *));
    for (int i = 0; i < longueur; i++)
    {
        salle[i] = (pos_salle *)malloc(largeur * sizeof(pos_salle));
    }

    // Remplir le tableau avec les caractères
    for (int i = 0; i < longueur; i++)
    {
        for (int j = 0; j < largeur; j++)
        {
            if (i == 0 || i == longueur - 1 || j == 0 || j == largeur - 1)
            {
                // Si nous sommes sur le bord du salle, stocker #
                (salle[i][j]).icone = '#';
            }
            else
            {
                // Sinon, stocker un espace
                (salle[i][j]).icone = ' ';
            }
            /*La taille insérée dans la structure équivaut à la taille restante à passer pour simplifier
            les boucles pour vérifier si l'espace est libre ou non
            */
            salle[i][j].longueur = longueur - i;
            salle[i][j].largeur = largeur - j;
            salle[i][j].type = type_salle;
        }
    }
    return salle;
}

pos_salle **remplirSalle(int seed)
{
    // Initialise la salle selon des dimensions aléatoires entre 3 et 10
    pos_salle **salle;
    int champion_place = 0; // Booléen pour savoir si LE champion a été placé
    int longueur , largeur;

    printf("Entrez la longueur de la salle : ");
    scanf("%d", &longueur);
    printf("Entrez la largeur de la salle : ");
    scanf("%d", &largeur);

    salle = initSalle(longueur, largeur, "salle");

    // Remplit aléatoirement la salle
    for (int cpt_lon = 1; cpt_lon < salle[0][0].longueur - 1; cpt_lon++)
    {
        for (int cpt_larg = 1; cpt_larg < salle[0][0].largeur - 1; cpt_larg++) // on initialise à 1 et les dimensions max -1 pour rester dans le cadre et ne pas dépasser
        {
            int code_lettre = 0 + (rand() % 50); // Génère un nombre entre 0 et 50
            if (code_lettre < 5)                 // Si le nombre est au-delà de 5 on ne change pas le caractère
            {
                salle[cpt_lon][cpt_larg].icone = quelle_lettre(code_lettre, salle, cpt_lon, cpt_larg, &champion_place);
            }
        }
    }
    return salle;
}

void libererMemoire(pos_salle **salle, int longueur)
{
    // On libère chaque ligne
    for (int i = 0; i < longueur; i++)
    {
        free(salle[i]);
    }
    // Puis on finit par le tableau contenant toutes les lignes
    free(salle);
}

void libererMemoireTableau(pos_salle ***salles, int longueur, int nombre_de_salles)
{
    // On libère la mémoire de chaque salle contenu dans le tableau
    for (int i = 0; i < nombre_de_salles; i++)
    {
        libererMemoire(salles[i], longueur);
    }
    // Puis on libère le tableau contenant les salles
    free(salles);
}

void insererSalle(pos_salle **donjon, pos_salle **salle, int pos_larg, int pos_lon)
{
    for (int cpt_lon = 0; cpt_lon < salle[0][0].longueur; cpt_lon++)
    {
        for (int cpt_larg = 0; cpt_larg < salle[0][0].largeur; cpt_larg++)
        {
            donjon[pos_lon + cpt_lon][pos_larg + cpt_larg] = salle[cpt_lon][cpt_larg];
        }
    }
}

pos_salle **remplirDonjon(pos_salle **donjon, pos_salle ***salles, int nombres_salles)
{
    for (int cpt_lon = 1; cpt_lon < donjon[0][0].longueur - 1; cpt_lon++)
    {
        int seed_salle = (int)time(NULL);
        srand(seed_salle);
        int quelle_salle = (rand() % nombres_salles);
        for (int cpt_larg = 1; cpt_larg < donjon[0][0].largeur - 1; cpt_larg++)
        {
            int seed_placer = (int)time(NULL);
            srand(seed_placer + cpt_lon + cpt_larg);
            int placer = (rand() % 20);

            if (placer >= 0 && placer <= 10)
            {
                // printf("cpt larg début : %d\n", cpt_larg);
                if (est_libre(salles[quelle_salle], donjon, &cpt_larg, &cpt_lon) == 0)
                {
                    insererSalle(donjon, salles[quelle_salle], cpt_larg, cpt_lon);
                }
                else if (est_libre(salles[quelle_salle], donjon, &cpt_larg, &cpt_lon) == 1)
                {
                    cpt_lon += salles[quelle_salle][0][0].longueur;
                    break;
                }
            }
        }
    }
    return donjon;
}

pos_salle **remplirSalle_man()
{
    // Initialise la salle selon des dimensions aléatoires entre 3 et 10
    pos_salle **salle;
    int longueur, largeur, continuer = 1, ligne = 1, colonne = 1;
    char la_lettre;

    printf("Entrez la longueur de la salle : ");
    scanf("%d", &longueur);
    printf("Entrez la largeur de la salle : ");
    scanf("%d", &largeur);

    salle = initSalle(longueur, largeur, "salle");
    
    // Remplit manuellement la salle
    while (continuer == 1){
        afficherSalle(salle);

        printf("Entrez la ligne : ");
        scanf("%d", &ligne);
        printf("Entrez la colonne :");
        scanf("%d", &colonne);

        printf("Quelle lettre souhaitez-vous mettre ? (choix : M C B A P W, autre = arreter)\n");
        scanf("%c", &la_lettre);
        scanf("%c", &la_lettre);

        if(dans_les_dimensions(ligne, 1, longueur) == 1 && dans_les_dimensions(colonne, 1, largeur) == 1){
            if(est_lettre_valide(la_lettre, "MCBAPW", 6) == 1){
                salle[ligne][colonne].icone = placement_lettre(salle, la_lettre, ligne, colonne);
            }
            else{
                continuer = 0;
            }    
        }
        else{
            printf("Position incorrecte, veuillez reessayer.\n");
        }
    }
    return salle;
}


pos_salle **remplirDonjon_man(pos_salle **donjon, pos_salle ***salles, int nombres_salles)
{
    int continuer = 1;
    int ligne, colonne, quelle_salle;
    while (continuer == 1)
    {
        afficherSalle(donjon);

        printf("Quelle salle ? (utilisez un nombre entre 0 inclus et %d exclu.\nUne valeur incorrecte affichera toutes les salles)\nPour quitter, entrez %d\n", nombres_salles, nombres_salles);
        scanf("%d", &quelle_salle);

        if (quelle_salle >= 0 && quelle_salle < nombres_salles)
        {
            afficherSalle(salles[quelle_salle]);
            printf("Ou souhaitez-vous placer cette salle ?\n");
            printf("Colonne : ");
            scanf("%d", &colonne);
            printf("Ligne : ");
            scanf("%d", &ligne);

            if (dans_les_dimensions(ligne, 1, donjon[0][0].longueur) == 1 && dans_les_dimensions(colonne, 1, donjon[0][0].largeur) == 1)
            {
                if (est_libre(salles[quelle_salle], donjon, &colonne, &ligne) == 0)
                {
                    insererSalle(donjon, salles[quelle_salle], colonne, ligne);
                }
                else
                {
                    printf("Position invalide. Continuer ?\n 1)Oui\n Autre)Non");
                    scanf("%d", &continuer);
                }
            }
            else{
                printf("Position invalide. Veuillez reessayer\n");
            }
        }else if(quelle_salle == nombres_salles){
            return donjon;
        }
        else
        {
            for(int i = 0; i < nombres_salles ; i++){
                printf("Salle numero %d : \n", i);
                afficherSalle(salles[i]);
            }
            pause();
        }
    }
    return donjon;
}

char placement_lettre(pos_salle **salle, char lettre, int pos_lon, int pos_larg)
{
    switch (lettre){
        case 'M':
            if(lettresAdjacentes(salle, 'P', pos_lon, pos_larg) == 1){
                return 'W';
            }
            return 'M';
        case 'P':
            permuterLettres(salle, 'M', 'W', pos_lon, pos_larg);
            return 'P';
        default :
            return lettre;
    }
}