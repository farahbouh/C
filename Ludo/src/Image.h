#ifndef IMAGE_H
#define IMAGE_H
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <filesystem>
#include <SDL2/SDL_ttf.h>       //gerer polices de texte
#include <SDL2/SDL_image.h>




/**======== CLASS IMAGE ======== */
/**
 * @class Image 
 * @brief pour gerer une image avec SDL2
 */

class Image{
private:
    SDL_Surface *m_surface; ///<charger et manipuler des images
    SDL_Texture *m_texture; ///<affichage de l'image sur l'ecran
    bool m_hasChanged;  ///< si imae a change
    
public:
    Image();
    ~Image();
    /**
     * @brief charge une image depuis un fichier et la convertit en 
     *         une texture utilsable par la SDL
     * @param filename le fichier
     * @param m_renderer le renderer
     */
    void loadFromFile(const char *filename, SDL_Renderer *m_renderer);  

    /**
     * @brief
     * @param m_renderer le renderer
     */
    void loadFromCurrentSurface(SDL_Renderer *m_renderer);

    /**
     * @brief
     */
    void draw(SDL_Renderer *m_renderer, int x, int y, int w = -1, int h = -1);

    /**
     * @brief
     */
    SDL_Texture *getTexture() const;

    /**
     * @brief
     */
    void setSurface(SDL_Surface *surf);

 };


 #endif