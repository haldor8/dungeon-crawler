#ifndef H_TESTS
#define H_TESTS
#include "creation_salles.h"
/**
 * \brief vérifie qu'aucune lettre adjacente (dans le tableau) ne soit égale à celle passée en paramètre
 *
 * \param salle : la salle où se situe les lettres
 * 
 * \category : char
 * \param lettre : la lettre à vérifier
 * 
 * \param pos_long : la ligne où se situe la position qu'on souhaite tester
 * \param pos_larg : la colonne où se situe la position qu'on souhaite tester
 */
int lettresAdjacentes(pos_salle **salle, char lettre, int pos_lon, int pos_larg);

/**
 * \brief change toutes les lettres autour d'une position par une autre lettre si elles sont égales à celle passée en paramètre
 *
 * \param donjon : la salle ou le donjon où se situe les lettres
 * 
 * \param lettre_a_changer : la lettre qui doit être changée
 * \param nv_lettre : la nouvelle lettre qui doit remplacer l'ancienne
 * 
 * \param pos_long : la ligne où se situe la position qu'on souhaite tester
 * \param pos_larg : la colonne où se situe la position qu'on souhaite tester
 */
void permuterLettres (pos_salle** donjon, char lettre_a_changer,  char nv_lettre, int pos_lon, int pos_larg);

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

/**
 * \brief vérifie si une lettre est valide
 *
 * \param lettre : char : la lettre qu'on souhaite tester
 * \param liste_lettres : char* : les possibilités de lettres
 * \param nb_lettres : int : la taille de la liste de lettres
 */
int est_lettre_valide(char lettre, char* liste_lettres, int nb_lettres);

/**
 * \brief vérifie si un nombre est entre 2 valeurs
 *
 * \param nombre : int : le nombre à tester
 * \param minimum : int : la valeur minimale incluse
 * \param taille_max : int : la valeur maximale exclue
 */
int dans_les_dimensions(int nombre, int minimum, int taille_max);
#endif