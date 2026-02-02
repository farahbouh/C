#include "Image.h"
#include <iostream>
using namespace std;

Image::Image():m_surface(nullptr), m_texture(nullptr),
 m_hasChanged(false)    //constructeur, tout a 0
{
}


Image::~Image()     //destructeur
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}


void Image::loadFromFile(const char *filename, SDL_Renderer *m_renderer)
{
    m_surface = IMG_Load(filename); //charge image en tant que sdl_surface
    if (m_surface == nullptr)   //si l'image n'a pas ete trouver, on va remonter 3 fois dans les dossiers
    {
        string nfn = string(filename);
        int n = 0;
        while ((m_surface == nullptr) && (n < 3))
        {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr)   //si apres les 3 tentatives, l'image n'a toujours pas ete trouver, affiche erreur et quitte
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Répertoire courant : " << currentPath << std::endl;
        cout << "Error: cannot load " << filename << endl;
        exit(1);
    }

    SDL_Surface *surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface, SDL_PIXELFORMAT_ARGB8888, 0);//converti au format ARGB8888->chq pixel consomme 32bits en memoire et a 4 composante -> opacité, R,V,B 
    SDL_FreeSurface(m_surface);     //liberation de la memoire occupé par m_surface
    m_surface = surfaceCorrectPixelFormat;      //met correctformat dans m_surface

    m_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceCorrectPixelFormat);    //converti SDL_surface en SDL_texture
    if (m_texture == nullptr)
    {
        cout << "Error: problem to create the texture of " << filename << endl;
        exit(1);
    }
}

void Image::draw(SDL_Renderer *m_renderer, int x, int y, int w, int h)
{
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w < 0) ? m_surface->w : w;   //si w<0 prends +w
    r.h = (h < 0) ? m_surface->h : h;   //si   

    if (m_hasChanged)
    {
        ok = SDL_UpdateTexture(m_texture, nullptr, m_surface->pixels, m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(m_renderer, m_texture, nullptr, &r);
    assert(ok == 0);
}

SDL_Texture *Image::getTexture() const { return m_texture; }

void Image::setSurface(SDL_Surface *surf) { m_surface = surf; }

