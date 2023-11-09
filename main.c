// Librairies "personnelles"
#include "creation_salles.h"
#include "affichage.h"
// Librairies standard
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void pause(){
    char d;
    printf("Appuyez sur entrer pour fermer la fenêtre.");
    // Deux scanf à cause du dernier \n
    scanf("%c", &d);
    scanf("%c", &d);
}

int main()
{
    int longueur, largeur, nombre_de_salles;

    int seed = (int)time(NULL);
    // Demander à l'utilisateur la longueur et la largeur du salle
    printf("Entrez la longueur du salle : ");
    scanf("%d", &longueur);
    printf("Entrez la largeur du salle : ");
    scanf("%d", &largeur);
    printf("Entrez le nombres de salles : ");
    scanf("%d", &nombre_de_salles);

    // On génère un donjon en spécifiant que c'est un donjon pour se retrouver plus facilement dans les tests
    pos_salle **donjon = initSalle(longueur, largeur, "donjon");

    // On génère un tableaux de salles pour faire différentes salles
    pos_salle ***salles = (pos_salle ***)malloc(nombre_de_salles * sizeof(pos_salle **));
    for (int i = 0; i < nombre_de_salles; i++)
    {
        salles[i] = remplirSalle(seed);
    }
    
    donjon = remplirDonjon(donjon, salles, nombre_de_salles);

    //  Afficher la salle
    afficherSalle(donjon);

    //On met le programme en pause pour éviter qu'il se ferme tout seul
    pause();

    // Libérer la mémoire allouée
    libererMemoire(donjon, longueur);
    libererMemoireTableau(salles, longueur, nombre_de_salles);

    return 0;
}