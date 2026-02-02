#ifndef DE_H
#define DE_H

/**
* @class De
* @brief Un de qui retourne un chiffre lancé aléatoirement 
*/

class De{
    private: 
        int val;    ///valeur actuel du dé

    public:
        /**
        * @brief Constructeur qui initialise le de en lui attribuant une valeur
        */
        De();

        /**
        * @brief Desctructeur qui vide la valeur du dé
        */
        ~De();

        /**
        * @brief Retourne la valeur actuel du de
        * @return int
        */
        int GetVal() const;

        /**
        * @brief Lance le de
        */
       void LancerDe();

        /**
         * @brief fait les tests de toutes les fonctions de la classe
         */
        void  testRegression();

};

#endif