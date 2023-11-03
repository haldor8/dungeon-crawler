#include "creation_salles.h"
#include "tests.h"
#include "affichage.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int longueur_min_salle = 5;
int longueur_max_salle = 5;
int largeur_min_salle = 20;
int largeur_max_salle = 20;

pos_salle **initSalle(int longueur, int largeur, char *type_salle)
{
    if (longueur <= 2 || largeur <= 2)
    {
        printf("La longueur et la largeur de la salle doivent être supérieures à 2.\n");
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
    srand(seed);
    int longueur = longueur_min_salle + (rand() % longueur_max_salle);
    int largeur = largeur_min_salle + (rand() % largeur_max_salle);
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
    for (int i = 0; i < longueur; i++)
    {
        free(salle[i]);
    }
    free(salle);
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

                // afficherSalle(donjon);
                /*
                char d;
                printf("Appuyez sur entrer pour continuer.");
                // Deux scanf à cause du dernier \n
                scanf("%c", &d);
                scanf("%c", &d); //*/
            }
        }
    }
    return donjon;
}