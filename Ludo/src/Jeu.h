#ifndef JEU_H
#define JEU_H
#include <algorithm>
#include <vector>
#include "Joueur.h"
#include "De.h"


using namespace std;

/**
* @class Jeu
* @brief Définit le jeu et le fait marcher 
*/
enum EtatJeu {      /// les etat du jeu
    ATTENTE_LANCER_DE,
    ATTENTE_ACTION,
    ATTENTE_SORTIE_PION,
    ATTENTE_DEPLACEMENT,
    FIN_TOUR
};

class Jeu
{
    private:
        EtatJeu etat;       ///<l'etat du jeu actuel
        int nb_Joueur;      ///<nb de joueur 
        int nb_Joueur_reel;
        int joueur_actuel; ///< le joueur actuel qui joue
        vector<Joueur*> joueurs; ///<Tableau dyna de joueur
        vector<Joueur*> joueurs_gagnants;   ///<tableau dynamique des joueurs gagnants
        vector<int> classement; ///<tab dyna qui gere le classement des joueurs 
        //vector<Joueur> * joueurs;      ///<creer tableau de nb Joueur présent
        De de;              ///le de du jeu 
        pair<int, int> chemin[53]; ///< le chemin commun de tous les piosn 
        pair<int, int> zone_Gagnante_R[6]; ///< la partie gagnante du jRouge
        pair<int, int> zone_Gagnante_V[6]; ///< la partie gagnante du jVert
        pair<int, int> zone_Gagnante_J[6]; ///< la partie gagnante du jJaune
        pair<int, int> zone_Gagnante_B[6]; ///< la partie gagnante du jBleu
        pair<int, int> LesCasesDepart[4]; ///< le tab des cases de depart de chaque joueur dans le chemin
        int case_Depart_R; ///<la case de departRouge
        int case_Depart_V; ///<la case de departVert
        int case_Depart_J; ///<la case de departJaune
        int case_Depart_B; ///<la case de departBleu

        pair<float,float> coordo_poule[4];




    public:
        /**
         * @ initialise les elements du plateau
         */
        void InitialiserPlateau();
    
        /**
        * @brief Constructeur
        */
        Jeu();

        /**
        * @brief Autre constructeur qui prends en paramètre le nombre de joueur
        * @param nb_j nombre de joueur
        */
        Jeu(int nb_j);

        /**
        * @brief Destructeur
         */
        ~Jeu();

        /**
        * @brief retourne l'etat actuel du jeu
        * @return EtatJeu
        */
        EtatJeu GetEtat() const;

        /**
        * @brief modifie l'etat
        * @param etat_jeu l etat du jeu
        */
        void SetEtat(EtatJeu etat_jeu);

        /**
        * @brief Remplie le nombre de joueur
        * @param nb nbr de jo
        */
        void SetNbJoueur(int nb);

        /**
         * @brief Retourne nbr joueurs actuel
         * @return int
         */
        int GetNbJoueur() const;

                /**
        * @brief Remplie le nombre de joueur reel
        * @param nb nbr de joueur
        */
       void SetNbJoueurReel(int nb);

       /**
        * @brief Retourne nbr joueurs actuel reel
        */
       int GetNbJoueurReel() const;


        /**
        * @brief retourne les coordonée de la poule d'un joueur
        * @param i index du joueur
        * @return pair<int, int>
         */
        pair<int, int> GetCoordoPoule(int i) const;

        /**
        * @brief remplie coordonnee de la poule d'un joueur
        * @param cx coordo x
        * @param cy coordo y
        */
        void SetCoordoPoule(int i, float cx, float cy);  //peut etre elle sert a rien 
        
        /**
         * @brief retoune les coordonnees d'indice i
         * @param i l'indice
         * @return pair<int, int>
         */
        pair<int,int> GetChemin(int i);


        /**
        * @brief  Retourne le joueur actuel
        * @return int
        */
       int GetJoueurActuel() const ;

        /**
        * @brief Modifie le joueurs actuel
        * @param i indice du joueur 
        */
       void SetJoueurActuel(int i);


        /**
        * @brief Demarer jeu place les pions et les joueurs pour le debut du jeu
        */
        void Demarer_Jeu(char tab[4]);
    

        /**
        * @brief affiche le jeu sous la console 
        * @param j jeu 
        * @param t_x taille x de la fenetre
        * @param t_y taille y de la fenetre
        */
        void AffichageLimiteTerrain_SDL (int t_x, int t_y, char tab[4]);



        /**
        * @brief verifie la collision entre les autres pions des autres joeur et le joueur
        * @param pion_deplace 1 ptr sur Pion qui est le pion du joueur a deplacer
        * @param jouur_actuel le joueur qui joue le tour
        */
        void VerifierCollision(Pion &pion_deplace, Joueur &joueur_actuel);

        /**
         * @brief renvoie le de du jeu
         * @return De&
         */
        De& GetDe();

        /**
         * @brief renvoie le joueur d'identifiant en param
         * @param id l'identifiant du joueur
         * @return Joueur *
         */
        Joueur * GetJoueur(unsigned int id) const;

        /**
         * @brief verifie si le pion du joueur est arrive
         * @param pion le pion du joueur
         * @param joueur le joueur
         */
        void VerifierArrivee(Pion pion, Joueur &joueur);

        /**
        * @brief gere les tours pour chaque joueur
        * @param j le joueur actuel 
		* @param sortir_pion si le joueur veut sortir un pion de la base
        * @param lancer_de 
        */
        void Gerer_Tour(Joueur & j, bool & sortir_pion, bool & lancer_de);

        /**
         * @brief donne la case depart du pion en fonction de son id
         * @param j le joueur
         * @return int
         */
        int IdVersCase(Joueur &j) const;

        /**
         * @brief gere le logique du tour de l'IA 
         */
        void GererTourIA();

        /**
         * @brief Gere le jeu pour chaque tour
         * @param id_pion_deplacer id du pion a deplacer
         */
        void Gerer_Jeu (int id_pion_deplacer);

        /**
          * @brief  verifie si c'est IA qui joue ou HUMAIN
          * @return true si c'est une IA
          * @return false le cas echeant
          */
        bool IAdoitJouer() const;

        /**
         * @brief Donne le tableau de la zone gagnante en fonction de l'id du joueur,
         *  la fonction est const donc on retourne un const
         * @return const pair<int, int>* 
         */
        const pair<int, int>* IdversTableauGagnant(int id_joueur) const;

        /**
         * @brief configure dynamiquement les types des joueurs
         * @param nb_humains le nb de joueurs humain pour la partie
         */
        void ConfigurerNbJoueurs(int nb_humains);
        
        /**
         * @brief permet de faire l'affichage sur la console
        */
       void Affichageconsole();

            /**
            *@brief Permet au joueur de choisir un pion à déplacer via la console. 
            *Cette fonction permet de choisir un pion disponible du joueur selon les règles du jeu.
            *@param joueur Référence vers le joueur qui doit jouer.
            *@param val_de La valeur du dé lancée au tour actuel.
            *@return Pion& Référence vers le pion choisi par le joueur.
            */
        Pion& ChoisirPionconsole(Joueur &joueur, int val_de);

        /**
            *@brief Vérifie si le joueur a gagné la partie.
            * Cette fonction verifie le joueur a gagné la partie.
            *@param joueur Référence vers le joueur a vérifiée.
            *@return true Si le joueur a rempli toutes les conditions de victoire.
            *@return false Sinon.
         */
        bool AGagner(Joueur& joueur);


        /**
         * @brief Retourne l'indice des joueurs gagnant
         * @param id indice tableau
         */
        Joueur* GetJoueurGagnant(int id) const;

        /**
         * @brief teste toutes les fonctions de la classe
         */
        void TestRegression();

        /**
         * @brief Retourne classment
         */
        int GetClassement(int id) const;

        /**
         * @brief retourne taille du tableau de classement
         */
        int GetClassementSize() const;

        
};

#endif

