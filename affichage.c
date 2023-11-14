#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"

void afficherSalle(pos_salle **donjon)
{
    // Afficher le donjon en parcourant le tableau
    for (int i = 0; i < donjon[0][0].longueur; i++)
    {
        for (int j = 0; j < donjon[0][0].largeur; j++)
        {
            printf("%c", donjon[i][j].icone);
        }
        printf("\n");
    }
}