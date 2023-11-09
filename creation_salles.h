#ifndef H_AFFICHAGE
#define H_AFFICHAGE
// template
/**
 * \brief
 *
 * \param
 */

typedef struct
{
    char icone;
    int longueur;
    int largeur;
    char *type;
} pos_salle;

/**
 * \brief initialise une boîte avec juste des murs "#" et " " pour les espaces vides
 *
 * \param largeur : int : largeur du tableau (taille des sous-tableaux) --
 * \param longueur : int : longueur du tableau (nombre de sous-tableaux) |
 * \param type_salle : char* : type de salle à spécifier dans la structure
 */
pos_salle **initSalle(int largeur, int longueur, char *type_salle);

/**
 * \brief cette procédure libère chaque sous-tableau puis finis par libérer le dernier tableau qui contient les autres tableaux
 *
 * \param salle : pos_salle** : un pointeur de pointeur vers un pos_salle.
 * \param longueur : int : longueur du tableau principal.
 */
void libererMemoire(pos_salle **salle, int longueur);

/**
 * \brief cette procédure libère chaque sous-tableau puis finis par libérer le dernier tableau qui contient les autres tableaux
 *
 * \param salle : pos_salle*** : un pointeur vers un tableau bidimentionnel de type pos_salle.
 * \param longueur : int : longueur des sous-tableaux.
 * \param nombre_de_salles : int : le nombre de salles contenues dans le tableau principal
 */
void libererMemoireTableau(pos_salle ***salles, int longueur, int nombre_de_salles);

/**
 * \brief crée une salle (ajoute différents éléments, seuls les coffres peuvent s'additionner à d'autres éléments)
 *
 * \returns : un pos_salle (structure) avec des lettres insérées
 */
pos_salle **remplirSalle(int seed);

/**
 * \brief
 *
 * \param
 */
void insererSalle(pos_salle **donjon, pos_salle **salle, int pos_larg, int pos_lon);

/**
 * \brief
 *
 * \param
 */
pos_salle **remplirDonjon(pos_salle **donjon, pos_salle ***salles, int nombre_salles);
#endif