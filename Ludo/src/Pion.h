#ifndef PION_H
#define PION_H

/**
* @class Pion
* @brief Un pion d'un joueur qui se deplace le long d'un chemin
*/

class Pion{
    private: 
        unsigned int i;    ///<position du pion dans le chemin
        int id;             ///<identifiant 
        int tour;           ///<nbr de tour
        bool est_sorti;     ///<si pion est sorti de la poule
        bool est_arrive;    ///<si pion est arrive a case d'arrivée
        float x; ///< la coordonnee x du pion
        float y;  ///< la coordonnee y du pion

    public: 
        Pion();
        /**
        * @brief Constructeur qui initialise un pion dans la poule
        */
        Pion(int idf);

        /**
        * @brief Destructeur qui vide un pion 
        */
        ~Pion();

        /**
         * @brief Retourne le nbr de tour
         * @return int
         */
        int GetTour() const;

        /**
         * @brief Incremente le nombre de tour
         */
        void IncrementeTour();

        /**
         * @brief Remet a 0 le nbr de tour
         */
        void ResetTour();
        
        /**
        * @brief Retourne position du pion 
        * @return unsigned int 
        */        
        unsigned int GetI() const;

        /**
        * @brief Retourne identifiant du pion
        * @return int
        */
        int GetId() const;

        /**
        * @brief Retourne si le pion est sorti de sa poule ou non  
        * @return true si le pion est sorti de la poule
        * @return false le cas echeant      
        */
        bool GetEstSorti() const;

        /**
         * @brief Met a true est arrivé
         */
        void SetEstArrive();

        /**
        * @brief Retourne si le pion est arrivé a la case d'arrivée ou non 
        * @return true si est_arrive est vrai
        * @return false le cas echeant           
        */
        bool GetEstArrive() const;

        /**
        * @brief Deplace le pion en fonction du nombre du dé lancé
        * @param nb nombre de place à incrémenter a la position du pion 
        */
        void SetI(const int nb);

        /**
         * @brief change la position du pion
         * @param nb le nombre de cases que doit changer le i 
         */
        void ChangerI(const int nb);

        /**
         * @brief elle sort le pion donc change les coordonnees dun pion
         * @param newx le new position du x
         * @param newy le new position y
         */
        void SortirDeLaBase(const float newx, const float newy); 

        /**
         * @brief retourne le pion dans la poule en changeant le i et ses coordonnées
         */
        void RetournerBase(); // retourner à la base

        /**
		* @brief remplir coordonnée des pions dans la poule 
		* @param x coordonnée x du pion
		* @param y coordonée y du pion 
		*/
		void CoordonneesPionPoule(const float x, const float y);

		/**
		* @brief Retourne les coordonnées x d'un pion
        * @return float
		 */
		float GetXPion ()const;	
		
		/**
         * @brief Retourne les coordonnées y d'un pion
         * @return float
		 */
		 float GetYPion ()const;

        /**
		* @brief modifie les coordonnées x d'un pion
        * @param cx x a modifider
		 */
		void SetX (float cx);	
		
        /**
		* @brief modifie les coordonnées x d'un pion
        * @param cy x a modifider
		 */
        void SetY (float cy);

        /**
         * @brief fait les tests de toutes les fonctions de la classe
         */
        void  testRegression();
};

#endif