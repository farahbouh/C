#ifndef COLOR_H
#define COLOR_H

/**
 * @struct Color
 * @brief Couleur de chaque joueur
 */
struct Color{
    unsigned char r, v,b; ///< composante rouge vert bleu de la couleur 

    /**
     * @brief constructeur par defaut de la classe Color
     */
    Color();

    /**
     * @brief destructeur de la classe Color
     */
    ~Color();

    /**
     * @brief constructeur/changer  par initialisation de la classe
     * @param nr la couleur rouge
     * @param nv la couleur verte
     * @param nb la couleur bleue
     */
    void setColor(unsigned char nr, unsigned char nv, unsigned char nb); 

    /**
     * @brief methode pour recuperer la couleur
     */
    const Color& getColor();

    /**
     * @brief methode pour recuperer la comosante rouge de la couleur
     * @return unsigned char
     */
    unsigned char getR() const;

    /**
     * @brief methode pour recuperer la comosante rouge de la couleur
     * @return unsigned char
     */
    unsigned char getV() const;

    /**
     * @brief methode pour recuperer la comosante rouge de la couleur
     * @return unsigned char
     */
    unsigned char getB() const;
    
    


};



#endif