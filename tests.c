#include "tests.h"
#include <stdio.h>

int lettresAdjacentes(pos_salle **salle, char lettre, int pos_lon, int pos_larg)
{
    if (salle[pos_lon - 1][pos_larg].icone == lettre || salle[pos_lon][pos_larg - 1].icone == lettre || salle[pos_lon + 1][pos_larg].icone == lettre || salle[pos_lon][pos_larg + 1].icone == lettre)
    {
        return 1;
    }
    return 0;
}

void permuterLettres(pos_salle **donjon, char lettre_a_changer, char nv_lettre, int pos_lon, int pos_larg)
{
    if (donjon[pos_lon - 1][pos_larg].icone == lettre_a_changer)
    {
        donjon[pos_lon - 1][pos_larg].icone = nv_lettre;
    }
    if (donjon[pos_lon][pos_larg - 1].icone == lettre_a_changer)
    {
        donjon[pos_lon][pos_larg - 1].icone = nv_lettre;
    }
    if (donjon[pos_lon + 1][pos_larg].icone == lettre_a_changer)
    {
        donjon[pos_lon + 1][pos_larg].icone = nv_lettre;
    }
    if (donjon[pos_lon][pos_larg + 1].icone == lettre_a_changer)
    {
        donjon[pos_lon][pos_larg + 1].icone = nv_lettre;
    }
}

char quelle_lettre(int code_lettre, pos_salle **salle, int cpt_lon, int cpt_larg, int *champion_place)
{
    char lettres[5] = {'M', 'C', 'B', 'A', 'P'}; // Tableau de taille 5, contenant les possibilités
    if (code_lettre < 5)                         // 5 car c'est la taille du tableau contenant toutes les lettres
    {
        if (lettres[code_lettre] != 'B') // Si le monstre n'est pas le champion, on procède normalement
        {
            // Vérifie que le monstre qu'on tente de placer n'est pas à côté d'un piège
            if (lettres[code_lettre] == 'M' && lettresAdjacentes(salle, 'P', cpt_lon, cpt_larg) == 1)
            {
                return 'W';
            }
            if (lettres[code_lettre] == 'P')
            {
                permuterLettres(salle, lettres[code_lettre], 'W', cpt_lon, cpt_larg);
            }
            else
                return lettres[code_lettre];
        }
        else if (champion_place == 0) // Si le champion n'a pas été placé, on le place et préviens qu'il l'a été, sinon on passe
        {
            *champion_place++;
            return lettres[code_lettre];
        }
        return ' ';
    }
}

char quelle_lettre_man(int code_lettre, pos_salle **salle, int cpt_lon, int cpt_larg, int *champion_place)
{
    char lettres[5] = {'M', 'C', 'B', 'A', 'P'}; // Tableau de taille 5, contenant les possibilités
    if (code_lettre < 5)                         // 5 car c'est la taille du tableau contenant toutes les lettres
    {
        if (lettres[code_lettre] != 'B') // Si le monstre n'est pas le champion, on procède normalement
        {
            // Vérifie que le monstre qu'on tente de placer n'est pas à côté d'un piège
            if (lettres[code_lettre] == 'M' && lettresAdjacentes(salle, 'P', cpt_lon, cpt_larg) == 1)
            {
                return 'W';
            }
            if (lettres[code_lettre] == 'P')
            {
                permuterLettres(salle, lettres[code_lettre], 'W', cpt_lon, cpt_larg);
            }
            else
                return lettres[code_lettre];
        }
        else if (champion_place == 0) // Si le champion n'a pas été placé, on le place et préviens qu'il l'a été, sinon on passe
        {
            *champion_place++;
            return lettres[code_lettre];
        }
        return ' ';
    }
}
int est_libre(pos_salle **salle, pos_salle **donjon, int *pos_larg, int *pos_lon)
{
    // printf("Salle + pos %d + %d, total : %d, Longueur donjon %d\n", salle[0][0].largeur, *pos_larg, salle[0][0].largeur + *pos_larg, donjon[0][0].largeur - 2);
    //   -2 car on exclut les bords sinon il peut y avoir des faux-positifs
    if (salle[0][0].largeur + *pos_larg <= donjon[0][0].largeur || salle[0][0].longueur + *pos_lon <= donjon[0][0].longueur)
    {
        for (int cpt_lon = 1; cpt_lon < salle[0][0].longueur; cpt_lon++)
        {
            for (int cpt_larg = 1; cpt_larg < salle[0][0].largeur; cpt_larg++)
            {
                if ((donjon[*pos_lon + cpt_lon][*pos_larg + cpt_larg]).icone == '#')
                {
                    // Change pos_larg par la valeur (soit la position) +1 pour décaler la boucle, et ne pas tester stupidement
                    *pos_larg = donjon[*pos_lon + cpt_lon][*pos_larg + cpt_larg].largeur + *pos_larg + cpt_larg + 1;
                    // Renvoie 1 pour signaler que l'emplacement n'est pas libre
                    return 1;
                }
            }
        }
        return 0;
    }
    return 1;
}

int remplir_salle_manuellement()
{
    int choix;
    printf("Souhaitez-vous remplir la salle manuellement ?\n 1)Oui\n Autre)Non");
    scanf("%d", &choix);
    if (choix == 1)
    {
        return 1;
    }
    return 0;
}