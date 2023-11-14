// Librairies "personnelles"
#include "affichage.h"
#include "creation_salles.h"
// Librairies standard
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void pause()
{
    char d;
    printf("Appuyez sur entrer pour fermer la fenêtre.");
    // Deux scanf à cause du dernier \n
    scanf("%c", &d);
    scanf("%c", &d);
}

pos_salle **menu_donjon(pos_salle **donjon)
{
}

int main()
{
    int longueur, largeur, nombre_de_salles;
    int est_auto;
    int seed = (int)time(NULL);
    // Demander à l'utilisateur la longueur et la largeur du salle
    printf("Entrez la longueur du salle : ");
    scanf("%d", &longueur);
    printf("Entrez la largeur du salle : ");
    scanf("%d", &largeur);
    printf("Entrez le nombres de salles : ");
    scanf("%d", &nombre_de_salles);

    printf("Souhaitez-vous remplir le donjon\n 1 : manuellement\n 2) automatiquement");
    scanf("%d", &est_auto);

    // On génère un donjon en spécifiant que c'est un donjon pour se retrouver plus facilement dans les tests
    pos_salle **donjon = initSalle(longueur, largeur, "donjon");
    // On génère un tableaux de salles pour faire différentes salles
    pos_salle ***salles = (pos_salle ***)malloc(nombre_de_salles * sizeof(pos_salle **));

    if (est_auto == 2)
    {
        for (int i = 0; i < nombre_de_salles; i++)
        {
            salles[i] = remplirSalle(seed);
        }
        donjon = remplirDonjon(donjon, salles, nombre_de_salles);
    }
    else if (est_auto == 1)
    {
        int cpt = 0;
        int type_salle, combien_obj_speciaux, presence_monstres;
        pos_salle **salle_temp;
        while (cpt < nombre_de_salles)
        {
            printf("Quel type de salle cela doit être ?\n 1)Coffre\n 2)Boss\n 3)Autel\n 4)Salle piégée");
            scanf("%d", &type_salle);

            printf("Combien d'objets ou monstres spéciaux doit-il y avoir dans cette salle ?");
            scanf("%d", &combien_obj_speciaux);

            printf("Est-ce qu'il y a des monstres ?\n 1)Oui\n Autre)Non");
            scanf("%d", &presence_monstres);

            salle_temp = remplirSalle_man(seed, type_salle, combien_obj_speciaux, presence_monstres);
            int conserve;
            afficherSalle(salle_temp);
            printf("Souhaitez-vous conserver cette salle ?\n 1)Oui\n Autre : non");
            scanf("%d", &conserve);
            if (conserve == 1)
            {
                salles[cpt] = salle_temp;
                cpt++;
            }
        }
        donjon = remplirDonjon_man(donjon, salles, nombre_de_salles);
    }

    else
    {
        printf("Nombre invalide, recommencez");
        printf("Souhaitez-vous remplir le donjon\n 1 : manuellement\n 2) automatiquement");
        scanf("%d", &est_auto);
    }
    //  Afficher la salle
    afficherSalle(donjon);

    // On met le programme en pause pour éviter qu'il se ferme tout seul
    pause();
    // Libérer la mémoire allouée
    libererMemoire(donjon, longueur);
    libererMemoireTableau(salles, longueur, nombre_de_salles);

    return 0;
}