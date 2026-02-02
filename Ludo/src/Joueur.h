#ifndef JOUEUR_H
#define JOUEUR_H
#include <vector>
#include <string>

#include "Pion.h"
#include "Color.h"


using namespace std;

/**
 * @class Joueur
 * @brief definit le Joueur et ses données 
 */

enum TypeJoueur{
	HUMAIN, 
	IA
};

class Joueur
{
	private:
    	unsigned int id; //< identifiant du joueur entre 0 et 3
    	int nbpionarrives; //< nb d pions arrives dansla partie gagante
    	Pion tab[4];  //< chaque joeur a 4 pions
    	Color couleur; //<  la couler du joeur et ses pions	
		bool a_gagner; //< pour veriier s'il a gagné
		TypeJoueur type; ///< le type du joueur
		string label;
    public:
		//Joueur(const Joueur& j) : 
		/**
		 * @brief le constructeur sans params
		 */
    	Joueur();

		/**
		 * @brief le constructeur avec params
		 * @param ident l'identifiant du joueur
		 * @param r le nouveau r de la couleur 
		 * @param v le nouveau v de la couleur
		 * @param b le nouveau b de la couleur
		 */
		Joueur(unsigned int ident, TypeJoueur t, unsigned char r, unsigned char v, unsigned char b);
		
		/**
		 * @brief le destructeur de la  classe
		 */
		~Joueur();

		/**
		 * @brief Retourne label du joueur
		 */
		string GetLabel() const;

		/**
		 * @brief ecrit label joueur
		 * @param lab label 
		 */
		void SetLabel (string lab);

		/**
		 * @brief methode qui retourne l'Id du joueur
		 * @return unsigned int
		 */
		unsigned int getId() const;

		/**
		 * @brief methode qui retourne la couleur du joueur
		 * @return Color
		 */
		Color getCouleur() const ;

		/**
		 * @brief retourne le nombre de pions arrives a destination
		 * @return int
		 */
    	int GetNbpionArrives() const;

		/**
		 * @brief met a jour le nb de piosn arrives
		 */
		void IncrementerNbPionArrive();

		/**
		 * @brief retourne le pion d'indice donnée
		 * @param indice l'indice du pion à renvoyer
		 * @return Pion&
		 */
		Pion& GetPion(int indice); 

		/**
		 * @brief recupere le tableau statique de pions qui sont en jeu
		 * @param pions_en_jeu[4] le tab de taille 4 des pions du joueur en jeu
		 */
		void GetPionsEnJeu(Pion pions_en_jeu[4]) const;
		
		/**
		 * @brief renvoie vrai si tous les pions du jours sonr arrives
		 * @return true si vrai
		 * @return false le cas echeant 
		 */
		bool Joueur_Gagnant();

		/**
		 * @brief renvoie la coord X du pion 
		 * @param id_pion l'indice du pion
		 * @return float
		 */
		float GetXPion(int id_pion) const;

		/**
		 * @brief renvoie la coord Y du pion 
		 * @param id_pion l'indice du pion
		 * @return float
		 */
		float GetYPion(int id_pion) const;

		/**
		 * @brief modifie la coord X du pion
		 * @param id_p l'indice du pion
		 * @param cx le new X du pion
		 */
		void SetXpion(int id_p, float cx);
		
		/**
		 * @brief modifie la coord Y du pion
		 * @param id_p l'indice du pion
		 * @param cy le new Y du pion
		 */
		void SetYpion(int id_p, float cy);

		void RentrerPionBase(int id_pion, pair<float, float> coordo_pion);
		
		/**
		 * @brief remplit le tab de coordonnées des piosn dans la poule
		 * @param cx la coord X du pion dans la poule
		 * @param cy la coord Y du pion dans la poule
		 */
		void RemplirCoordonneePoule(float cx, float cy);

		/**
		 * @brief sort le pion de la poule en le mettant aux coordonnes en params
		 * @param CoordSortiBase les coords x et y(en pair)
		 */
		void SortirPionBase(pair<int,int> CoordSortiBase);

		/**
		 * @brief deplace le pion en fnction de la valeur du dé
		 * @param id_pion l'indice du pion
		 * @param val_de la valeur du dé
		 */
		void DeplacerUnPion(int id_pion, int val_de);

		/**
		 * @brief retourne le type du joueur
		 * @return TypeJoueur
		 */
		TypeJoueur GetType() const;

		/**
		 * @brief change  le type du joueur
		 * @param t le type du joueur 
		 */
		void SetType(TypeJoueur t) ;

		/**
		 * @brief verifie que tous les pions spnt sortis
		 * @return true si vrai
		 * @return false si le cas echeant
		 */
		bool TousPionsSortis();

		/**
		 * @brief teste toutes les fonctions de la classe
		 */
		void  testRegression();
};

#endif
