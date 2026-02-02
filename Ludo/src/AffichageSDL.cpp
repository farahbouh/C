#include "AffichageSDL.h"
#include <iostream>
#include <string>


using namespace std;

AffichageSDL::AffichageSDL(): m_window(nullptr), m_renderer(nullptr), m_font(nullptr), m_font_g(nullptr)
{

    cout<<"SDL: init"<<endl;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout<<"Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    //Initialisation de SDL_ttf pour l'affichage texte -> besoin pour les joueurs
    //si initialisation echoue -> quite
    cout<<"SDL_ttf: init"<<endl;
    if(TTF_Init()!=0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    m_font = TTF_OpenFont("data/American_Captain.ttf", 24); // 24 = taille de police
    m_font_g = TTF_OpenFont("data/American_Captain.ttf", 46); // 46 = taille de police
    if (!m_font) {
        std::cout << "Erreur chargement police : " << TTF_GetError() << std::endl;
        exit(1);
    }


    //Initialisation de SDL_image pour charger image (PNG, JPG)
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    cout<<"SDL_image: init"<<endl;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        cout<<"SDL_m_image could not initialize! SDL_m_image Error: "<<IMG_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }


    //taille fenêtre
    int dimx, dimy;
    dimx = dimy = 600;     //Largeur, Hauteur

    m_window = SDL_CreateWindow("LUDO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN);
    //SDL_SetWindowResizable(m_window, SDL_FALSE);
    if(m_window == NULL)
    {
        cout<<"Erreur lors de la creation de la fenetre: "<<SDL_GetError()<<endl;
        SDL_Quit();
        exit(1);
    }

    /*index= -1 : laise SDL choisir automatiquement le meilleur GPU
    SDL_RENDERER_ACCELERATED : accceleration materielle 
    */
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    assert( m_renderer);

    //Image plateau
    m_plateau.loadFromFile("data/plateau.png", m_renderer);

    for(int i=0; i<4; i++)
    {
        m_pion_rouge[i].loadFromFile("data/pion/rond_rouge.png", m_renderer);
        m_pion_vert[i].loadFromFile("data/pion/rond_vert.png", m_renderer);
        m_pion_jaune[i].loadFromFile("data/pion/rond_jaune.png", m_renderer);
        m_pion_bleu[i].loadFromFile("data/pion/rond_bleu.png", m_renderer);
    }
   

    //de
    m_faces_de[0].loadFromFile("data/de/de_1.png", m_renderer);
    for(int i=2; i<=6; i++)
    {
        string nom_fichier = "data/de/de_"+to_string(i)+".png";
        m_faces_de[i-1].loadFromFile(nom_fichier.c_str(), m_renderer);
    }


    m_encadrer.loadFromFile("data/encadrer.png", m_renderer);
    m_menu.loadFromFile("data/menu.png", m_renderer);

    m_1.loadFromFile("data/1.png", m_renderer);
    m_1_sombre.loadFromFile("data/1_sombre.png", m_renderer);

    m_2.loadFromFile("data/2.png", m_renderer);
    m_2_sombre.loadFromFile("data/2_sombre.png", m_renderer);

    m_3.loadFromFile("data/3.png", m_renderer);
    m_3_sombre.loadFromFile("data/3_sombre.png", m_renderer);

    m_4.loadFromFile("data/4.png", m_renderer);
    m_4_sombre.loadFromFile("data/4_sombre.png", m_renderer);
    
    m_start.loadFromFile("data/start.png", m_renderer);
    m_start_sombre.loadFromFile("data/start_sombre.png", m_renderer);

    m_end.loadFromFile("data/end.png", m_renderer);

    bouton1 = {60, 350, 100, 100};
    bouton2 = {185, 350, 100, 100};
    bouton3 = {310, 350, 100, 100};
    bouton4 = {435, 350, 100, 100};
    bouton_start = {200 ,475, 200, 75};


}

//libere la meoire allouee
AffichageSDL::~AffichageSDL(){
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    //Mix_FreeChunk(de_son);
    de_son = nullptr;


}


void AffichageSDL::AfficherTexte(SDL_Renderer* renderer, TTF_Font* font, const std::string& texte, int x, int y)
{
    SDL_Color couleur = {0, 0, 0}; // noir
    SDL_Surface* surface = TTF_RenderText_Blended(font, texte.c_str(), couleur);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}



void AffichageSDL:: SdlAff(bool end_game, bool menu, bool cliquer, bool cliquer_start, bool de_lancer, Jeu &Jeu){

    SDL_SetRenderDrawColor(m_renderer, 130, 140, 255, 255);
    SDL_RenderClear(m_renderer);



    //Affichage du plateau 
    int dimx, dimy; 
    SDL_GetWindowSize(m_window, &dimx, &dimy);
    if(menu)
    {
        m_menu.draw(m_renderer, 0, 0, dimx, dimy);
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
    
    
        // Si la souris est sur le bouton 1
         if (mouseX >= bouton1.x && mouseX <= bouton1.x + bouton1.w &&
            mouseY >= bouton1.y && mouseY <= bouton1.y + bouton1.h) {
            m_1_sombre.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
        } else {
            if(cliquer && Jeu.GetNbJoueurReel()==1)
            {
                m_1_sombre.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
            }else{
                m_1.draw(m_renderer, bouton1.x, bouton1.y, bouton1.w, bouton1.h);
            }
            
        }
        //2
        if (mouseX >= bouton2.x && mouseX <= bouton2.x + bouton2.w &&
            mouseY >= bouton2.y && mouseY <= bouton2.y + bouton2.h) {
            m_2_sombre.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
        } else {
            if(cliquer && Jeu.GetNbJoueurReel()==2)
            {
                m_2_sombre.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
            }else{
                m_2.draw(m_renderer, bouton2.x, bouton2.y, bouton2.w, bouton2.h);
            }
            
        }
        //3
        if (mouseX >= bouton3.x && mouseX <= bouton3.x + bouton3.w &&
            mouseY >= bouton3.y && mouseY <= bouton3.y + bouton3.h) {
            m_3_sombre.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
        } else {//pour gagner l image sombre
            if(cliquer && Jeu.GetNbJoueurReel()==3)
            {
                m_3_sombre.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
            }else{
                m_3.draw(m_renderer, bouton3.x, bouton3.y, bouton3.w, bouton3.h);
            }
            
        }
        //4
        if (mouseX >= bouton4.x && mouseX <= bouton4.x + bouton4.w &&
            mouseY >= bouton4.y && mouseY <= bouton4.y + bouton4.h) {
            m_4_sombre.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
        } else {
            if(cliquer && Jeu.GetNbJoueurReel()==4)
            {
                m_4_sombre.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
            }else{
                m_4.draw(m_renderer, bouton4.x, bouton4.y, bouton4.w, bouton4.h);
            }
            
        }



        //bouton start
        if (mouseX >= bouton_start.x && mouseX <= bouton_start.x + bouton_start.w &&
            mouseY >= bouton_start.y && mouseY <= bouton_start.y + bouton_start.h) {
            m_start_sombre.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
        } else {
            if(cliquer_start)
            {
                m_start_sombre.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
            }else{
                m_start.draw(m_renderer, bouton_start.x, bouton_start.y, bouton_start.w, bouton_start.h);
            }
            
        }

    }else{

        m_plateau.draw(m_renderer, 0, 0, dimx, dimy); //à haut en gauche
        
        if(Jeu.GetJoueurActuel()==0)
        {
            m_encadrer.draw(m_renderer, 12, 370, 219, 218);
        }
        if(Jeu.GetJoueurActuel()==1)
        {
            m_encadrer.draw(m_renderer, 12, 11, 219, 218);
        }
        if(Jeu.GetJoueurActuel()==2)
        {
            m_encadrer.draw(m_renderer, 370, 11, 220, 218);
        }
        if(Jeu.GetJoueurActuel()==3)
        {
            m_encadrer.draw(m_renderer, 370, 370, 220, 218);
        }
    
        for (int i=0; i<4; i++)
        {
            //cout<<"Pion "<<i<<" X: "<<Jeu.GetJoueur(0)->GetPion(i).GetXPion()<<" Y: "<<Jeu.GetJoueur(0)->GetPion(i).GetYPion()<<endl;
    
            m_pion_rouge[i].draw(m_renderer, Jeu.GetJoueur(0)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(0)->GetPion(i).GetYPion()*40, 30, 30);
            m_pion_vert[i].draw(m_renderer, Jeu.GetJoueur(1)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(1)->GetPion(i).GetYPion()*40, 30, 30);
            m_pion_jaune[i].draw(m_renderer, Jeu.GetJoueur(2)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(2)->GetPion(i).GetYPion()*40, 30, 30);
            m_pion_bleu[i].draw(m_renderer, Jeu.GetJoueur(3)->GetPion(i).GetXPion()*40, Jeu.GetJoueur(3)->GetPion(i).GetYPion()*40, 30, 30);
    
        }
    
        //texte
        pair<int, int> positions [4]= {
            {80, 570},   // rouge
            {80, 210},    // vert
            {435, 210},   // jaune
            {435, 570}   // bleu
        };

        for (int i = 0; i < 4; i++) 
        {
            string label;
            if (i < Jeu.GetNbJoueur())
                Jeu.GetJoueur(i)->SetLabel("Joueur " + to_string(i + 1));
            else
                Jeu.GetJoueur(i)->SetLabel("Computer " + to_string(i - Jeu.GetNbJoueur() + 1));
    
            AfficherTexte(m_renderer, m_font, Jeu.GetJoueur(i)->GetLabel(), positions[i].first, positions[i].second);
        }
    
        //affichage du dé si pas tirer
        m_faces_de[Jeu.GetDe().GetVal()-1].draw(m_renderer, dimx/2-35, dimy/2-37);
        //si tirer (pour l'instant sans prendre en compte le joueur pour test)
        if(de_lancer)
        {
            for(int i=0; i<6; i++)
            {
                m_faces_de[i].draw(m_renderer, dimx/2-35, dimy/2-37);
                SDL_RenderPresent(m_renderer);
                SDL_Delay(50);      //petite pause
            }
            
            cout<<Jeu.GetDe().GetVal()<<endl;
            m_faces_de[Jeu.GetDe().GetVal()-1].draw(m_renderer, dimx/2-35, dimy/2-37);
            de_lancer = false;
        }

    }

    if(end_game)
    {
        m_end.draw(m_renderer, 0, 0, dimx, dimy);
        //AfficherTexte(m_renderer, m_font_g, "test", 175, 250);
        int nb_classe = Jeu.GetClassementSize();
        for(int i=0; i<nb_classe; i++)
        {
            int gagnant = Jeu.GetClassement(i);
            string id_label = Jeu.GetJoueurGagnant(gagnant)->GetLabel();
            AfficherTexte(m_renderer, m_font, id_label, 175,250 - (i*50) );
        }
    }

    /*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {       //44100 frequence en Hz, format par defaut, stereo, 2042 taille buffer audio, plus petit = plus rapide 
        cout << "Erreur Mix_OpenAudio : " << Mix_GetError() << std::endl;
    }

    
    ///son
    de_son = Mix_LoadWAV("data/son/de_son.wav");
    if (!de_son) {
        cout << "Erreur de chargement du son : " << Mix_GetError() <<endl;
    }

    Mix_VolumeChunk(de_son, MIX_MAX_VOLUME);*/


}


void AffichageSDL::AnimerDeplacement(Jeu &Jeu, int id_joueur, int id_pion, int i_depart, int i_arrivee) {
    for (int i = i_depart + 1; i <= i_arrivee; i++) {
        float x, y;

        if (i <= 52) {
            // On est encore sur le chemin classique
            int case_depart = Jeu.IdVersCase(*Jeu.GetJoueur(id_joueur));
            int index_chemin = (i + case_depart) % 52;
            x = Jeu.GetChemin(index_chemin).first;
            y = Jeu.GetChemin(index_chemin).second;
        } else {
            // On est dans la zone gagnante du joueur
            int index_gagnant = i - 53;
            const pair<int, int>* tab_zone = Jeu.IdversTableauGagnant(id_joueur);
            x = tab_zone[index_gagnant].first;
            y = tab_zone[index_gagnant].second;
        }

        Jeu.GetJoueur(id_joueur)->SetXpion(id_pion, x);
        Jeu.GetJoueur(id_joueur)->SetYpion(id_pion, y);

        SdlAff(false,false, false, false, false, Jeu);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(200);
    }
}

void AffichageSDL::SdlBoucle(Jeu &Jeu)
{
    SDL_Event events;
    bool menu=true;
    bool quit = false;
    bool de_lancer_aff = false;
    bool de_lancer_aff_ia = false;
    bool cliquer = false;
    bool cliquer_start = false;
    bool end_game = false;

    int dimx, dimy; 
    SDL_GetWindowSize(m_window, &dimx, &dimy);

    cout<<"Le pion 0 de J0 a pour i= "<<Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI()<<endl;

    while (!quit)
    {
        

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
                quit = true;

            if(menu && events.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = events.button.x;
                int y = events.button.y;

                if (x >= bouton_start.x && x <= bouton_start.x + bouton_start.w && y >= bouton_start.y && y <= bouton_start.y + bouton_start.h) 
                {
                    cout << "Jeu commence"<<endl;
                    cliquer_start = true;
                    menu = false;
                }

                if (x >= bouton1.x && x <= bouton1.x + bouton1.w && y >= bouton1.y && y <= bouton1.y + bouton1.h) 
                {
                    Jeu.SetNbJoueurReel(1);
                    Jeu.ConfigurerNbJoueurs(1); // cas 1 seul humain
                    std::cout << "1 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton2.x && x <= bouton2.x + bouton2.w && y >= bouton2.y && y <= bouton2.y + bouton2.h) 
                {
                    Jeu.SetNbJoueurReel(2);
                    Jeu.ConfigurerNbJoueurs(2); // cas 2 humains
                    std::cout << "2 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton3.x && x <= bouton3.x + bouton3.w && y >= bouton3.y && y <= bouton3.y + bouton3.h) 
                {
                    Jeu.SetNbJoueurReel(3);
                    Jeu.ConfigurerNbJoueurs(3); // cas 3 humains
                    std::cout << "3 joueur sélectionné\n";
                    cliquer = true;
                }
                else if (x >= bouton4.x && x <= bouton4.x + bouton4.w && y >= bouton4.y && y <= bouton4.y + bouton4.h) 
                {
                    Jeu.SetNbJoueurReel(4);
                    Jeu.ConfigurerNbJoueurs(4); // cas 4 humains
                    std::cout << "4 joueur sélectionné\n";
                    cliquer = true;
                }
            }
            
            if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                case SDL_SCANCODE_0:
                    end_game=true;
                    break;

                case SDL_SCANCODE_SPACE:
                    if (Jeu.GetEtat()==ATTENTE_LANCER_DE)
                    {
                        Jeu.Gerer_Jeu(0);   //changer?
                        //Mix_PlayChannel(-1, de_son, 0);     //-1 canal, 0 pour jouer une fois
                        de_lancer_aff = true;
                        /*if (Mix_PlayChannel(-1, de_son, 0) == -1) {
                            std::cout << "Erreur de lecture du son : " << Mix_GetError() << std::endl;
                        }*/
                        
                    }
                    break;

                case SDL_SCANCODE_RETURN:
                    if (Jeu.GetEtat() == ATTENTE_ACTION)
                    {
                        Jeu.SetEtat(ATTENTE_SORTIE_PION);
                        Jeu.Gerer_Jeu(0);   //changer?
                    }
                    break;

                case SDL_SCANCODE_1:         //pion avec id=0         
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(0);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 0, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                        Jeu.VerifierCollision(Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(0), *Jeu.GetJoueur(Jeu.GetJoueurActuel()));
                    }
                    break;

                case SDL_SCANCODE_2:        //pion avzec id=1           
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(1).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(1);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(1).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 1, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_3:        //pion avec id=2              
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(2).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(2);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(2).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 2, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_4:        //pion avec id=3              
                    if(Jeu.GetEtat() == ATTENTE_ACTION)
                    {//a remplacer 0 par GetJoueur(joueur_actuel)
                        int i_depart = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(3).GetI();

                        Jeu.SetEtat(ATTENTE_DEPLACEMENT);
                        Jeu.Gerer_Jeu(3);

                        int i_arrivee = Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(3).GetI();
                        AnimerDeplacement(Jeu, Jeu.GetJoueurActuel(), 3, i_depart, i_arrivee);  //premier 0 est le joueur a remplacer
                    }
                    break;

                case SDL_SCANCODE_N: 
                    Jeu.SetEtat(FIN_TOUR);
                    Jeu.Gerer_Jeu(0);

                    break;

                default:
                    //etat = ATTENTE_LANCER_DE;
                    break;
                }
                }
        }

        while (Jeu.IAdoitJouer()) {
            int id_ia = Jeu.GetJoueurActuel();
            int i_depart[4];
            for (int p = 0; p < 4; p++)
            {
                i_depart[p] = Jeu.GetJoueur(id_ia)->GetPion(p).GetI();
            }

            SdlAff(false, menu, cliquer, cliquer_start, false, Jeu);
            SDL_RenderPresent(m_renderer);
                
        
            // 1. === Détection et animation du dé ===
            if (Jeu.GetEtat() == ATTENTE_LANCER_DE) {
                
                de_lancer_aff_ia = true;

                Jeu.GererTourIA(); // juste lancer le dé
                SdlAff(false, menu, cliquer, cliquer_start, de_lancer_aff_ia, Jeu); // animation du dé
                SDL_RenderPresent(m_renderer);
                SDL_Delay(1000);
                de_lancer_aff = false;
            }
        
            // 2. === Sortie pion si besoin ===
            if (Jeu.GetEtat() == ATTENTE_SORTIE_PION) {
                Jeu.GererTourIA(); // juste sortir le pion
               // SDL_Delay(300);
            }
        
            // 3. === Déplacement du pion ===
            if (Jeu.GetEtat() == ATTENTE_ACTION) {
                Jeu.GererTourIA(); // déplacement du pion
                //SDL_Delay(300);
        
                int i_apres = -1;
                for (int p = 0; p < 4; p++) {
                    i_apres = Jeu.GetJoueur(id_ia)->GetPion(p).GetI();
                    if (i_apres != i_depart[p]) {
                        AnimerDeplacement(Jeu, id_ia, p, i_depart[p], i_apres);
                        Jeu.VerifierCollision(Jeu.GetJoueur(Jeu.GetJoueurActuel())->GetPion(p), *Jeu.GetJoueur(Jeu.GetJoueurActuel()));
                        break;
                    }

                }
                
            }
        
            // 4. === Fin du tour ===
            if (Jeu.GetEtat() == FIN_TOUR) {
                Jeu.GererTourIA(); // passe au prochain joueur
                SDL_Delay(200);
            }
            //de_lancer_aff = true;
            // Affichage global
            SdlAff(false, menu, cliquer, cliquer_start, false, Jeu);
            de_lancer_aff_ia = false;
            SDL_RenderPresent(m_renderer);
        }
        

        /*if(Jeu.IAdoitJouer()){
            ia_joue= false;
        }*/
        //Mix_CloseAudio(); 

        // Affichage

        SdlAff(end_game, menu, cliquer, cliquer_start, de_lancer_aff, Jeu);
        de_lancer_aff =false;
        SDL_RenderPresent(m_renderer);
    }
}