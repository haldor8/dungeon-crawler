#ifndef H_TESTS
#define H_TESTS
#include "creation_salles.h"
/**
 * \brief
 *
 * \param
 */
int lettresAdjacentes(pos_salle **salle, char lettre, int pos_lon, int pos_larg);

/**
 * \brief
 *
 * \param
 */
char quelle_lettre(int code_lettre, pos_salle **salle, int cpt_lon, int cpt_larg, int *champion_place);

/**
 * \brief vérifie si la salle peut être insérée en x,y et si elle ne peut l'être, la fonction modifie
 * la position (soit l'incrémentation de la boucle) pour que la fonction qui l'appelle n'ait pas à
 * calculer inutilement en boucle si la salle peut être placée
 *
 * \param salle : la salle qu'on souhaite placer
 * \param donjon : le donjon entier
 * \param pos_lon : pointeur sur la longueur initiale à tester
 * \param pos_larg : pointeur sur la largeur initiale à tester
 */
int est_libre(pos_salle **salle, pos_salle **donjon, int *pos_lon, int *pos_larg);
#endif