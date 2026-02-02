#ifndef AFFICHAGESDL_H
#define AFFICHAGESDL_H

#include <stdlib.h>
#include <filesystem>


#include <SDL2/SDL.h>           //affichage graphique   
//#include <SDL2/SDL_image.h>     //charger des images
#include <SDL2/SDL_ttf.h>  
#include <SDL2/SDL_mixer.h>

#include "Jeu.h"
#include "Image.h"
#include "De.h"
#include "Joueur.h"

/**
 * @class AffichageSDL
 * @brief gere l'affichage sdl du jeu 
 */
class AffichageSDL
{
private:
    SDL_Window *m_window;  ///<Fenetre de la SDL
    SDL_Renderer *m_renderer; ///< Moteur du rendu graphique
    TTF_Font *m_font; ///< Police de texte
    TTF_Font *m_font_g;   ///Police classement

    Image m_plateau; ///< image du plateau
    Image m_faces_de[6]; ///<image du dé
    Image m_de_inter[5]; ///<image intermediaire du dé
    Image m_pion_rouge[4]; ///< image pion Rouge
    Image m_pion_vert[4];   ///<Image pion Vert
    Image m_pion_jaune[4];   ///<Image pion Jaune
    Image m_pion_bleu[4];   ///<Image pion Bleu
    Image m_encadrer;
    Image m_menu;
    Image m_1;
    Image m_1_sombre;
    Image m_2;
    Image m_2_sombre;
    Image m_3;
    Image m_3_sombre;
    Image m_4;
    Image m_4_sombre;

    Image m_start;
    Image m_start_sombre;

    Image m_end;

    Image Mix_StartTrack;

    SDL_Rect bouton1;
    SDL_Rect bouton2;
    SDL_Rect bouton3;
    SDL_Rect bouton4;
    SDL_Rect bouton_start;

    Mix_Chunk* de_son;
    

    /**
     * @brief fonction qui gere l'affichage
     * @param menu menu du jeu
     * @param cliquer si on a cliquer sur un bouton
     * @param cliquer_start si on a cliquer sur start
     * @param de_lancer si le dé a ete lancer
     * @param Jeu jeu
     * @param end_game si jeu est fini
     */
    void SdlAff(bool end_game, bool menu, bool cliquer, bool cliquer_star, bool de_lancer, Jeu &Jeu);


public:
    /**
     * @brief Initialise SDL et charge les ressources(Constructeur)
     */
    AffichageSDL(); 
    /**
     * @brief (Destructeur) libere de la memoire allouee
     */
    ~AffichageSDL();

    /**
     * @brief Boucle principale qui gere les evenements du jeu
     */
    void SdlBoucle(Jeu &J);
    /**
    * @brief animation pour voir les pions se deplacer 1 par 1
    * @param Jeu jeu
    * @param joueur_actuel joueur a qui on effectue animation
    * @param id_pion pion a deplacer
    * @param i_depart ancienne position
    * @param i_arrivee nouvelle position
    */
    void AnimerDeplacement (Jeu &Jeu, int joueur_actuel,int id_pion, int i_depart, int i_arrivee);

    /**
     * @brief donne nom pour chq joueur
     * @param renderer renderer
     * @param font police
     * @param texte texte a ecrire
     * @param x coordonnee
     * @param y coordonnee
     */
    void AfficherTexte(SDL_Renderer* renderer, TTF_Font* font, const string& texte, int x, int y); 
};


#endif

