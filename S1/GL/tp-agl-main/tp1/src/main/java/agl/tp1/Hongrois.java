package agl.tp1;

import java.util.List;
/**
* Interface de l'algorithme hongrois utilisé pour réaliser le couplage maximal de
poids min↪→
*/
public interface Hongrois {
  /**
  * Permet de positionner la taille (hauteur) de la matrice
  * @param hauteur la hauteur de la matrice avec hauteur>0
  */
  public void setHauteur(int hauteur);
  /**
  * Permet de positionner la taille (largeur) de la matrice
  * @param largeur la largeur de la matrice avec largeur>0
  */
  public void setLargeur(int largeur);
  /**
  * Permet de positionner les valeurs de la matrice
  * @param adjListe la liste d'adjacence définie par (i, j, v)
  * (i, j, v) : la case (i, j) prend la valeur v
  * avec 1<=i<=hauteur ; 1<=j<=largeur ; v>=0
  */
  public void setAdjacenceList(List<List<Integer>> adjListe);
  /**
  * Calcule et retourne les affectations
  * @param phaseNumber : 1 pour une affectation partielle, 2 pour une
  affectation globale↪→
  * @return une liste de couples (i, j) qui correspondent aux affectations
  calculées↪→
  */
  public List<List<Integer>> affectation(int phaseNumber);
}