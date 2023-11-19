// Librairies "personnelles"
#include "affichage.h"
#include "creation_salles.h"
// Librairies standard
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


pos_salle ***menu_remplir_salles(int seed, pos_salle ***salles, int nombre_de_salles)
{
        int cpt = 0;
        int est_salle_man;
        pos_salle **salle_temp;

        printf("Souhaitez-vous remplir les salles\n 1) Manuellement\n Autre) Aleatoirement ");
        scanf("%d", &est_salle_man);

        while (cpt < nombre_de_salles)
        {
            if(est_salle_man == 1){
                salle_temp = remplirSalle_man();
            }
            else{
                salle_temp = remplirSalle(seed);
            }

            int conserve = 0;
            afficherSalle(salle_temp);
            printf("Souhaitez-vous conserver cette salle ?\n 1)Oui\n Autre : non");
            scanf("%d", &conserve);

            if (conserve == 1)
            {
                salles[cpt] = salle_temp;
                cpt++;
            }
        }
    return salles;
}


int main()
{
    int seed = (int)time(NULL);
    int longueur, largeur;
    int est_donjon_man, nombre_de_salles;

   // Demander à l'utilisateur la longueur et la largeur du donjon
    printf("Entrez la longueur du donjon : ");
    scanf("%d", &longueur);
    printf("Entrez la largeur du donjon : ");
    scanf("%d", &largeur);
    printf("Entrez le nombre de salles : ");
    scanf("%d", &nombre_de_salles); 

    // On génère un donjon en spécifiant que c'est un donjon pour se retrouver plus facilement dans les tests
    pos_salle **donjon = initSalle(longueur, largeur, "donjon");
    // On génère un tableaux de salles pour faire différentes salles
    pos_salle ***salles = (pos_salle ***)malloc((nombre_de_salles) * sizeof(pos_salle **));
    

    printf("Souhaitez-vous remplir le donjon\n 1) Manuellement\n Autre) Automatiquement ");
    scanf("%d", &est_donjon_man);

    if (est_donjon_man == 1)
    {   
        salles = menu_remplir_salles(seed, salles, nombre_de_salles);
        donjon = remplirDonjon_man(donjon, salles, nombre_de_salles);
    }
    else if (est_donjon_man == 2)
    {
        salles = menu_remplir_salles(seed, salles, nombre_de_salles);
        donjon = remplirDonjon(donjon, salles, nombre_de_salles);
    }
    else
    {
        printf("Nombre invalide, recommencez");
        printf("Souhaitez-vous remplir le donjon\n 1 : manuellement\n 2) automatiquement");
        scanf("%d", &est_donjon_man);
    }
    


    //  Afficher le donjon
    afficherSalle(donjon);

    // On met le programme en pause pour éviter qu'il se ferme tout seul
    pause();

    // Libérer la mémoire allouée pour le donjon
    libererMemoire(donjon, longueur);
    // On libère la mémoire allouée à la liste de tableaux contenant les salles
    libererMemoireTableau(salles, longueur, nombre_de_salles);

    return 0;
}