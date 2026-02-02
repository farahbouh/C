#include "Jeu.h"
#include <iostream>
#include <cassert>

using namespace std;

void Jeu:: InitialiserPlateau()
{

    //Inialisation du chemin principal
    for(int i=0; i<5; i++){
        chemin[i]={6, (13-i)};
    }
    for(int i=5; i<=10; i++)   
    {
        chemin[i]={(10-i), 8};
    }
    chemin[11]={0, 7};
    for(int i=12; i<18; i++)
    {
        chemin[i]={(i-12), 6};
    }
    for(int i=23; i>=18; i--){
        chemin[i]={6, (23-i)};
    }
    chemin[24]={7, 0};
    for(int i=25; i<31; i++){
        chemin[i]={8, (i-25)};
    }
    for(int i=31; i<37; i++){   //////10 11 12 13
        chemin[i]={(i-22), 6};
    }
    chemin[37]={14, 7};
    for(int i=38; i<44; i++){
        chemin[i]={(52-i), 8};
    }
    for(int i=44; i<50; i++){
        chemin[i]={8, (i-35)};
    }
    chemin[50]={7, 14};
    chemin[51]={6, 14};
    chemin[52]={6, 13};

    //Zone gagnante
    for(int i=0; i<6; i++){
        zone_Gagnante_R[i]={7, (13-i)};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_J[i]={7, (i+1)};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_V[i]={(i+1), 7};
    }
    for(int i=0; i<6; i++){
        zone_Gagnante_B[i]={(13-i), 7};
    }

    //le tab de coord des cases depart de chaque pion des chaque joueur
    LesCasesDepart[0]=chemin[0];
    LesCasesDepart[1]=chemin[13];
    LesCasesDepart[2]=chemin[26];
    LesCasesDepart[3]=chemin[39];
    //les case de depart de chaque joueur
    case_Depart_R=0;
    case_Depart_V=13;
    case_Depart_J=26;
    case_Depart_B=39;

    //Coordonnees de Poules pour chque joueur
    joueurs[0]->RemplirCoordonneePoule(1.75, 12.5);  //rouge
    joueurs[1]->RemplirCoordonneePoule(1.75, 3.5);  //vert
    joueurs[2]->RemplirCoordonneePoule(10.75, 3.5); //jaune
    joueurs[3]->RemplirCoordonneePoule(10.75, 12.5); //bleu

    coordo_poule[0] = make_pair(1.75, 12.5);
    coordo_poule[1] = make_pair(1.75, 3.5);
    coordo_poule[2] = make_pair(10.75, 3.5);
    coordo_poule[3] = make_pair(10.75, 12.5);
    
    joueurs[0]->RemplirCoordonneePoule(coordo_poule[0].first, coordo_poule[0].second);  //rouge
    joueurs[1]->RemplirCoordonneePoule(coordo_poule[1].first, coordo_poule[1].second);  //vert
    joueurs[2]->RemplirCoordonneePoule(coordo_poule[2].first, coordo_poule[2].second); //jaune
    joueurs[3]->RemplirCoordonneePoule(coordo_poule[3].first, coordo_poule[3].second); //bleu
}

Jeu::Jeu(): etat(ATTENTE_LANCER_DE), nb_Joueur(4), joueur_actuel(0)
{
    De de;
    //init de  classemnt qui doit etre vide
    classement.clear();

    //int nb_Joueur=4;
    /*Comme on a un vector de joeur on aura pas besoin d'allouer et desallouer dynmiquement
    car vector le gere automatiquemnt pour nous
    et aussi VECTOR nous permet d'ajouter(PUSH.BACK) ou de retirer des joueurs avec ces methodes
    sans se soucier de la taille du tab 
     */
    for (int i=0;i<nb_Joueur; i++)
    {
        joueurs.push_back(new Joueur(i,HUMAIN,0, 0, 0)); //ajoute a la fin du vector
      //gerer la couleur 
    }
    assert(joueurs.size()== static_cast<size_t>(nb_Joueur));

    InitialiserPlateau();
}

Jeu::Jeu(int nb_j):etat(ATTENTE_LANCER_DE), nb_Joueur(nb_j), joueur_actuel(0)
{
    //init de  classemnt qui doit etre vide
    classement.clear();
    for (int i=0;i<nb_j; i++)
    {
        joueurs.push_back(new Joueur(i,HUMAIN, 0, 0, 0));      //gerer la couleur 
    }
    assert(joueurs.size()== static_cast<size_t>(nb_Joueur));

    InitialiserPlateau();
}

Jeu::~Jeu()
{
    for (Joueur * joueur: joueurs)
    {
        delete joueur;
    }
    joueurs.clear();
    joueurs_gagnants.clear();
    classement.clear();

} //Plus besoin de delete[] car 'vector' gere la mem automatiquement, pour chq joueur du vector on delete



void Jeu::AffichageLimiteTerrain_SDL(int x, int y, char t[4])
{
for (int i = 0; i < y; i++)  
	{
		for (int j = 0; j < x; j++) 
		{
			if (i == 0 || i == y - 1)   
				std::cout << "-";
			else if (j == 0 || j == x - 1) 
				std::cout << "|";
			else if (j<=2 && i<=2)
				std::cout<<t[1];
			else if (i >= y - 3 && j >= x - 3)
				std::cout<<t[2];
			else if (i<=2 && j>=27)
				std::cout<<t[3];
			else if (j<=2 && i>=12)
				std::cout<<t[0];
            else if (
                ((i == 5 || i == 9) && (j <= 10 || j >= 20)) ||  
                ((j == 10 || j == 20) && (i <= 5 || i >= 9)) ||  
                ((i == 1 || i == y - 2) && j >= 10 && j <= 20) ||  
                ((j == 1 || j == x - 1 || j == x - 2) && i >= 5 && i <= 9))
				std::cout<<"*";
			else 
				std::cout << ".";  
		}	std::cout <<std::endl; 
	}
}

void Jeu::Demarer_Jeu(char tab[4])
{
    
    int taille_x, taille_y;         //taille plateau
    taille_x = 30;    //affichage a part 
    taille_y = 15;

    AffichageLimiteTerrain_SDL(taille_x, taille_y, tab);


    cout<<"Le jeu commence avec: "<< nb_Joueur<< "joueurs" <<endl;

    //Affichage des joueurs et leur couleurs
    for( const auto joueur: joueurs){
        assert(joueur != nullptr);
        cout<<"Player: "<<joueur->getId()<< " -Color: ( "
        <<(int)joueur->getCouleur().getR()<<", " 
        <<(int)joueur->getCouleur().getV()<<", " 
        <<(int)joueur->getCouleur().getB()<<" )"<<endl;

    }

    bool continu= true;
    do{
        /*for(int i=0; i<nb_Joueur; i++){
            Gerer_Tour(*joueurs[i]);  //on passe par reference
        }*/

        if(joueurs_gagnants.size()==(static_cast<long unsigned int>(nb_Joueur)-1))
        {
            continu=false;
        }
    }while(continu);


}



Joueur* Jeu::GetJoueur(unsigned int id) const
{
    assert(id< joueurs.size());
    return joueurs[id];
}

Joueur* Jeu::GetJoueurGagnant(int id) const
{
    assert(id<0);
    return joueurs_gagnants[id];
}

int Jeu:: GetClassementSize() const {
    return classement.size();
}


De& Jeu::GetDe()
{
    return de;
}


void Jeu::Gerer_Tour(Joueur & j, bool & sortir_pion, bool & lancer_de)
{
    //pair<int,int> cordoDepart = LesCasesDepart[j.getId()];

    //if(de.GetVal()==6 && (j.GetNbpionArrives()<4|| (sortir_pion)) )
    if (sortir_pion)// && de.GetVal()==6)
    {
        cout<<"sortir_pion"<<endl;
        j.SortirPionBase(make_pair(10,10));
    }else{
        //deplacement
        //collision
    }
    sortir_pion=false;
    lancer_de = false; 
}


EtatJeu Jeu::GetEtat() const
{
    return etat;
}

void Jeu::SetEtat(EtatJeu etat_jeu)
{
    etat = etat_jeu;
}

void Jeu::SetNbJoueur(int nb)
{
    nb_Joueur = nb;
}

int Jeu::GetNbJoueur() const
{
    return nb_Joueur;
}

void Jeu::SetNbJoueurReel(int nb)
{
    nb_Joueur_reel = nb;
}

int Jeu::GetNbJoueurReel() const
{
    return nb_Joueur_reel;
}

pair<int, int> Jeu::GetCoordoPoule(int i) const
{
    return coordo_poule[i];
}

void Jeu::SetCoordoPoule(int i, float cx, float cy)
{
    coordo_poule[i] = make_pair(cx, cy);
}

pair<int,int> Jeu::GetChemin(int i)
{
    assert(i >=0 && i <53);
    return chemin[i];
}

int Jeu::GetJoueurActuel() const
{
    return joueur_actuel;
}

void Jeu::SetJoueurActuel(int i)
{
    assert(i >=0 && i< nb_Joueur);
    joueur_actuel = i;
}

int  Jeu:: IdVersCase(Joueur &j) const
{
    switch(j.getId()){
        case 0: return case_Depart_R;
        case 1: return case_Depart_V;
        case 2: return case_Depart_J;
        case 3: return case_Depart_B;
        default:
            cout <<"Valeur inattendu "<<endl;
            return -1;
    }
}

const pair<int, int>* Jeu::IdversTableauGagnant(int id_joueur) const
{
    switch (id_joueur){
        case 0: return zone_Gagnante_R;
        case 1: return zone_Gagnante_V;
        case 2: return zone_Gagnante_J;
        case 3: return zone_Gagnante_B;
        default: 
            cout<<"Id du joueur inexistant"<<endl;
            return nullptr;
    }
}

int Jeu::GetClassement(int id) const
{
    return classement[id];
}

//FONCTIONS VERIFIERCOLLISIONS
void Jeu::VerifierCollision(Pion &pion_deplace, Joueur &joueur_actuel)
{
    //remplacer ici par le tableau depart
	//int tab_case_special[4]={0,13,26,39}; // case special ou on ne peux pas supprimer de pion on a aussi les cases en couleurs  
	//cout<<"--------------collision"<<endl;
	int case_joueur_actuel = (IdVersCase(joueur_actuel) + pion_deplace.GetI()) % 52;

	//cout << "Case actuelle du joueur " << joueur_actuel.getId() << " : " << case_joueur_actuel<<" a fait tant de pas "<< (static_cast<int>(pion_deplace.GetI()))<< endl;
	for(size_t i=0; i<joueurs.size(); i++) // boucle pour parcourir les joueurs
	{ 
		Joueur& autre_joueur = *joueurs[i]; // recuperation des joueurs
		//cout<<"Checkons avec le joueur :"<<autre_joueur.getId()<<endl;
		if (joueur_actuel.getId()!=autre_joueur.getId()) // on ne doit pas comparer avec lui meme
		{	
			for (int j = 0; j < 4; j++) // boucle pour parcourir les pions
			{
				Pion& pion_autre_joueur = autre_joueur.GetPion(j); // on recupere un pion
                if(pion_autre_joueur.GetTour()==1)
                {
                    continue;       // si le pion a deja fait un tour CAD il est dans la zone gagnant safe
                }
				int case_autre_joueur = (IdVersCase(autre_joueur) + (pion_autre_joueur.GetI())) % 52; // permet de transformer le nombre de pas en position dans le jeu
				//cout << "  Pion " << j << " de l’adversaire est en case " << case_autre_joueur << endl;
				
				for (int c=0; c<4; c++) // parcours les cases speciales ///a enlever
				{
					if ((case_autre_joueur!=IdVersCase(*joueurs[0])) && 
                        (case_autre_joueur!=IdVersCase(*joueurs[1])) &&
                        (case_autre_joueur!=IdVersCase(*joueurs[2])) &&
                        (case_autre_joueur!=IdVersCase(*joueurs[3])) )//|| (pion_autre_joueur.GetI()< 52)) // interdit de manger dans la case 52 -> zone propre
					{
						if (case_autre_joueur == case_joueur_actuel) // si meme endroit alors on fait retourner à la base
						{
							//cout << ">>> COLLISION détectée ! Le pion adverse retourne à la base." << endl;
							pion_autre_joueur.RetournerBase();
                            autre_joueur.RentrerPionBase(j, coordo_poule[i]);
							return;
						}
					}	
					else
					{
						//cout<<"case special donc rien"<<endl;
					}
				}
			}
		}
	}
}

bool Jeu:: IAdoitJouer() const{
    assert(joueur_actuel >=0 && joueur_actuel <static_cast<int>(joueurs.size()));
    return GetJoueur(joueur_actuel)->GetType() == IA ;
}


void Jeu:: ConfigurerNbJoueurs(int nb_humains){
    nb_Joueur= 4;

    for(int i=0; i< 4; i++){
        if(i<nb_humains){
            joueurs[i]->SetType(HUMAIN);

        }else{
            joueurs[i]->SetType(IA);
        }
    }
}

void Jeu:: GererTourIA(){
    Joueur* joueur_ia= GetJoueur(joueur_actuel);
    int i_gagnant = 0;
    const pair<int, int> * tab_zone_g;

    switch (etat){

        case ATTENTE_LANCER_DE:
            de.LancerDe();
            cout<<"Joueur actuel IA : "<<joueur_actuel<<endl;
            cout << "Dé lancé, valeur = " << de.GetVal() << endl;
            if( de.GetVal()==6 && !joueur_ia->TousPionsSortis()){
                etat=ATTENTE_SORTIE_PION;

            }else{
                etat=ATTENTE_ACTION;
            }
            break;

        case ATTENTE_SORTIE_PION:
            assert(GetJoueurActuel() >= 0 && GetJoueurActuel() < static_cast<int>(joueurs.size()));
            //sortir le premier pion non sorti dans  le sens 1, 4 des pions
            for(int i=0; i< 4; i++){
                if(!joueur_ia->GetPion(i).GetEstSorti()){
                    cout << "Sortie de pion" << endl;
                    joueur_ia->SortirPionBase(LesCasesDepart[joueur_actuel]);
                    etat = FIN_TOUR;
                    break;
                }
            }
            break;



        case ATTENTE_ACTION:
            //Avancer le premier pion sorti
            for(int i=0; i<4; i++){
                if(joueur_ia->GetPion(i).GetEstSorti()&& !joueur_ia->GetPion(i).GetEstArrive()){
                    joueur_ia ->DeplacerUnPion(i, de.GetVal());
                    tab_zone_g = IdversTableauGagnant(joueur_ia->getId());
                    i_gagnant = (joueur_ia->GetPion(i).GetI() - 53);
    
                    if(joueur_ia->GetPion(i).GetI()>=58)
                    {
                        joueur_ia->GetPion(i).ChangerI(58);  //met a jour le i
                        joueur_ia->GetPion(i).SetEstArrive();
                        cout<<"i= "<<joueur_ia->GetPion(i).GetI()<<endl;
                        joueur_ia->SetXpion(i, tab_zone_g[5].first);   //a voir si pas 58
                        joueur_ia->SetYpion(i, tab_zone_g[5].second);     
                    }else{
                        if(joueur_ia->GetPion(i).GetI()>52 && joueur_ia->GetPion(i).GetI()<58)
                        {
                            joueur_ia->SetXpion(i, tab_zone_g[i_gagnant].first);
                            joueur_ia->SetYpion(i, tab_zone_g[i_gagnant].second);

                        }

                    }
                    break;
                }
            }
            etat= FIN_TOUR;
            break;
            
        case FIN_TOUR:
            //passer au joueur suivant
            joueur_actuel = (joueur_actuel + 1)% 4;
            etat= ATTENTE_LANCER_DE;
            break;
    }
    /*if(GetJoueur(joueur_actuel)->GetType() == IA){
        //faire dans la SDL un Delay pour l'effet visuel
        GererTourIA(); //l'IA suivante joue automatiquement
    }*/
}




void Jeu::Gerer_Jeu(int id_pion_deplacer)
{
    assert(joueur_actuel >=0 && joueur_actuel < static_cast<int>(joueurs.size()));
    //for (int i=0; i<nb_joueur; i++) //pour faire un tour a tester
    int i_depart=0;  //pour cout
    int case_depart = 0;  //ok
    int i_reel=0;   //ok
    int index_chemin = 0;    //ok
    int i_gagnant = 0;
    const pair<int, int> * tab_zone_g;
    int tentatives =0; //pour joueur prochain

    switch (etat)
    {
        case ATTENTE_ACTION:
            break;

        case ATTENTE_LANCER_DE:
            de.LancerDe();
            cout<<"Joueur actuel: "<<joueur_actuel<<endl;
            cout<< "Dé lancé, valeur = " << de.GetVal() << endl;
            etat = ATTENTE_ACTION;
            break;

        case ATTENTE_SORTIE_PION:
            assert(GetJoueurActuel() >= 0 && GetJoueurActuel() < static_cast<int>(joueurs.size()));

            if(de.GetVal()==6 && joueurs[GetJoueurActuel()]->GetNbpionArrives()<4)
            {
                cout << "Sortie de pion" << endl;
                cout << "le x et y de chemin[1]: ("<<chemin[0].first <<" ;" << chemin[0].second <<" )"<<endl;
                GetJoueur(joueur_actuel)->SortirPionBase(LesCasesDepart[joueur_actuel]);
                etat = FIN_TOUR;
                             
            }
            break;  
            
        case ATTENTE_DEPLACEMENT:
            //rajouter condition si pion est sorti
            i_depart = joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI();
            cout<<"I depart: "<<i_depart<<endl;
            case_depart = IdVersCase(*joueurs[joueur_actuel]);

            
            if(joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetEstSorti() && !joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetEstArrive())
            {
                cout<<"tour= "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetTour()<<endl;
                if(joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<=52  && joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetTour() == 0)   //a changer normalement c est l'indice de leur ancienne position dans le chemin
                {
                    joueurs[joueur_actuel]->DeplacerUnPion(id_pion_deplacer, de.GetVal());  //met a jour le i
                    cout<<"i apres deplacement: "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<<endl;
                    int i_reel = joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI();
                    int index_chemin = (i_reel + case_depart) % 52;
                    
                    //INCREMENTATION DU TOUR 
                    if(joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()>52)
                    {
                        //si on rentre dans zone g depuis l'exterieur->transition
                        joueurs[joueur_actuel]->GetPion(id_pion_deplacer).IncrementeTour();
                        tab_zone_g = IdversTableauGagnant(joueur_actuel);
                        i_gagnant = (joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI() - 53);

                        joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, tab_zone_g[i_gagnant].first);
                        joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, tab_zone_g[i_gagnant].second);
                        
                    }else{
                        assert(index_chemin >=0 && index_chemin < 53);
                        cout << "i pion = " << i_reel << endl;
                        cout << "i chemin = " << index_chemin << endl;
                        //COORDONNEE 
                        joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, chemin[index_chemin].first);
                        joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, chemin[index_chemin].second);  
    
                    }
                    

                }else{      //cas ou l'on est dans la zone
                        joueurs[joueur_actuel]->DeplacerUnPion(id_pion_deplacer, de.GetVal());  //met a jour le i
                        cout<<"i apres deplacement: "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<<endl;
                        int i_reel = joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI();
                        int index_chemin = (i_reel + case_depart) % 52;


                        
                        assert(index_chemin >=0 && index_chemin < 53);
                        cout << "i pion = " << i_reel << endl;
                        cout << "i chemin = " << index_chemin << endl;

                        tab_zone_g = IdversTableauGagnant(joueur_actuel);
                        i_gagnant = (joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI() - 53);
                        
                        if(joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()>=58)
                        {
                            joueurs[joueur_actuel]->GetPion(id_pion_deplacer).ChangerI(58);  //met a jour le i
                            joueurs[joueur_actuel]->GetPion(id_pion_deplacer).SetEstArrive();
                            cout<<"i= "<<joueurs[joueur_actuel]->GetPion(id_pion_deplacer).GetI()<<endl;
                            joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, tab_zone_g[5].first);   //a voir si pas 58
                            joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, tab_zone_g[5].second);     
                        }else{
                            joueurs[joueur_actuel]->SetXpion(id_pion_deplacer, tab_zone_g[i_gagnant].first);
                            joueurs[joueur_actuel]->SetYpion(id_pion_deplacer, tab_zone_g[i_gagnant].second);

                        }
                }  
            }

            etat = FIN_TOUR;
            break;

        case FIN_TOUR:
            //verifie si le joueur actuel a gangne et l'add dans le classement
            if(joueurs[joueur_actuel]->GetNbpionArrives() == 4){
                if(find(classement.begin(), classement.end(), joueur_actuel) == classement.end()){
                    classement.push_back(joueur_actuel);
                    joueurs_gagnants.push_back(GetJoueur(joueur_actuel));
                    cout<< "Joueur " << joueur_actuel <<" a terminé . YOUPI"<<endl;
                }
            }
            //passer au joeur suivant qui n'a pas fini
            do{
                joueur_actuel = (joueur_actuel + 1)%nb_Joueur;
                tentatives ++;
            }while(joueurs[joueur_actuel]->GetNbpionArrives() == 4 && tentatives <= nb_Joueur);

            if(tentatives > nb_Joueur){
                cout <<"Tous les joueurs ont fini la partie et le classement est :" << endl;
                for(size_t i=0; i< classement.size() ; i++){
                    cout <<"Joueur "<< i << "E"<<endl; 
                }
            }
            cout << "Nouveau joueur : " << joueur_actuel << endl;
            etat = ATTENTE_LANCER_DE;
            break;
    
        
        default:     
            joueur_actuel = (joueur_actuel + 1)%nb_Joueur;
            break;
    }
    //cas de l'IA
    if(GetJoueur(joueur_actuel)->GetType() == IA){
        //faire dans la SDL un Delay pour l'effet visuel
        GererTourIA(); //l'IA joue
    }
}





void Jeu::TestRegression() {

    cout << " Début Test de Régression =====" << endl;
    Jeu jeu(4); // Création d'un jeu avec 4 joueurs

    // Vérifie que le nombre de joueurs est bien 4

    assert(jeu.GetJoueur(0) != nullptr);
    assert(jeu.GetJoueur(1) != nullptr);
    assert(jeu.GetJoueur(2) != nullptr);
    assert(jeu.GetJoueur(3) != nullptr);
    cout << "Joueurs bien initialisés ok" << endl;

    // Vérifie que tous les pions sont dans la base au début
    for(int i = 0; i < 4; ++i) {
        Joueur* j = jeu.GetJoueur(i);

        for(int p = 0; p < 4; ++p) {
            assert(j->GetPion(p).GetEstSorti() == false);
        }
    }
    cout << "Tous les pions commencent dans la base ok" << endl;
    
    // Vérifie les coordonnées d’une case du chemin
    pair<int,int> coord = jeu.GetChemin(0);
    assert(coord.first == 6 && coord.second == 13);
    cout << "Coordonnées du chemin[0] correctes ok" << endl;

    // Vérifie la validité du lancer de dé
    jeu.GetDe().LancerDe();
    int val = jeu.GetDe().GetVal();
    assert(val >= 1 && val <= 6);
    cout << " ok Lancer de dé donne une valeur correcte: " << val << endl;

    // Simulation de sortie de pion (si dé == 6)
    Joueur* j0 = jeu.GetJoueur(0);

  //jeu.GetDe().ChangerVal(6);  // Forcer la valeur du dé à 6 pour test
    do { 
        jeu.GetDe().LancerDe();

    } while (jeu.GetDe().GetVal()!=6);

    cout<<jeu.GetDe().GetVal()<<endl;
    j0->SortirPionBase({100.0f, 100.0f});
    jeu.SetEtat(ATTENTE_SORTIE_PION);
    jeu.Gerer_Jeu(0);
    assert(j0->GetPion(0).GetEstSorti());
    cout << "Sortie de pion fonctionne avec un 6" << endl;
    Joueur* j1 = jeu.GetJoueur(1); // joueur adverse

    // Le pion du joueur 1 est sorti et a avancé de 5 cases

    j1->SortirPionBase(jeu.GetChemin(0));
    j1->GetPion(0).ChangerI(5);  // Chemin[13 + 5] = case 18

    // On place le pion du joueur 0 pour qu’il arrive aussi sur cette case 18
    j0->GetPion(0).ChangerI(18);  // Chemin[0 + 18] = case 18

    // Vérification de la collision
    jeu.VerifierCollision(j0->GetPion(0), *j0);

    // Assert que le pion adverse a été renvoyé
    assert(!j1->GetPion(0).GetEstSorti());
    cout << "Collision détectée et pion retourné à la base ok" << endl;
    cout << "Tous les tests de régression ont reussi" << endl;

}





Pion& Jeu::ChoisirPionconsole(Joueur &joueur, int val_de) //ok
{

    int choix = -1;  // Initialisation Ã  une valeur invalide
    bool choixnonval = false;
    cout << "----------choisirpions" << endl;

    // Afficher les pions valides
    for (int i = 0; i < 4; i++)
    {
        Pion p = joueur.GetPion(i);
        if ((p.GetEstSorti() && (!p.GetEstArrive())) || (!p.GetEstSorti() && (val_de == 6))) {
            cout << "Pion " << i << " : valide";

        } else {
            cout << "Pion " << i << " : non valide";

        }
        cout <<" sortie ? "<< p.GetEstSorti()<<" arrivee ? "<<p.GetEstArrive()<<endl;
     }
    
     while (!choixnonval){   

        cout<<"ancien"<<choix<<endl;
        cout<<"choix (0-3) : "<<endl;
        cin>>choix;
        cout<<"nouveau"<<choix<<endl;
        
        if (choix<=3 && choix>=0){

            cout<<"bon choix"<<endl;
            Pion p = joueur.GetPion(choix);
            if ((p.GetEstSorti() && (!p.GetEstArrive())) || (!p.GetEstSorti() && (val_de == 6))){

                cout << "Pion " << choix << " : valide" << endl;
                return joueur.GetPion(choix);

            }
        }
    }

    joueur.GetPion(0).SortirDeLaBase(0,0);
    cout<<"? "<<joueur.GetPion(0).GetEstSorti();

    return joueur.GetPion(0);
}

bool Jeu::AGagner(Joueur& joueur)
{

    // Vérifier si tous les pions du joueur sont arrivés dans la zone gagnante
    for (int i = 0; i < 4; i++){

        Pion& pion = joueur.GetPion(i);
        if (!pion.GetEstArrive()) {
            return false; // Si un des pions n'est pas arrivé

        }
    }
    return true; // Tous les pions sont arrivés

}

void Jeu::Affichageconsole()
{
    cout << "Le jeu commence avec: " << nb_Joueur << " joueurs" << endl;
    
    // Boucle de jeu principale
    bool jeu_en_cours = true;
    while (jeu_en_cours){

        // Afficher l'état actuel du jeu
        cout << "--------------------------------Tour du joueur " << GetJoueurActuel() << endl;

        if (AGagner(*GetJoueur(GetJoueurActuel()))==false){

            // Lance le dee
            GetDe().LancerDe();
            int val_de = GetDe().GetVal();
            cout << "Dé lancé, valeur = " << val_de << endl;
            bool choisir= false; //possibilite de choisir un pion ? pour l'instant non
            
            for (int i = 0; i < 4; ++i){

                Pion& pion = GetJoueur(GetJoueurActuel())->GetPion(i); // recup i pion
                if ((pion.GetEstSorti() && (!pion.GetEstArrive())) || (!pion.GetEstSorti() && (val_de == 6))) // est ce que disp ?
                {
                    cout<<"jouable : "<<i<<endl;
                    choisir=true;

                }else{
                    cout<<"non jouable : "<<i<<endl;   

                }
            }
            if (choisir) // si dispo on accede au choix et aux collision + mise à jour de son indiceS
            {
                Pion& pionchoisi=ChoisirPionconsole(*GetJoueur(GetJoueurActuel()), val_de);
                cout<<"----------deplacerpion"<<endl;
                int avance = val_de;
                if (!pionchoisi.GetEstSorti()) 
                {
                    avance = 1; // il commence tout juste, donc 1 seule case et on le sort de la base
                    pionchoisi.SortirDeLaBase(0,0);

                }else{
                    pionchoisi.SetI(val_de); // sinon on avance de n du de

                }
                cout<<"le pion "<< pionchoisi.GetId()<< " avance de " <<avance <<"cases." <<endl;
                VerifierCollision(pionchoisi, *GetJoueur(GetJoueurActuel()));  // Vérifier s'il y a des collisions
            }
        }
        // Changer le joueur pour le tour suivant
        SetJoueurActuel((GetJoueurActuel() + 1) % 4);
    }
    cout << "Le jeu est terminé!" << endl;

}