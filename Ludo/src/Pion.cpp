#include "Pion.h"
#include <iostream>
#include <cassert>
using namespace std; 


Pion::Pion(int idf)
{
    assert(idf >= 0 && idf < 4); // l'id valide : 0, 1, 2, 3
    i=0;    //dans la poule
    id = idf;
    est_sorti = false;
    est_arrive = false;
    x =0;
    y =0;
    tour = 0;
    
}

Pion::Pion()
{
    i=0;    //dans la poule
    id = -1;
    est_sorti = false;
    est_arrive = false;
    tour = 0;
}
//destructeur a voir car il ne sert a rien sans sdl
Pion::~Pion()
{
    i=0;    //remet dans la poule
    est_sorti = false;
    est_arrive = false; 
    ResetTour();   
}

int Pion::GetTour() const
{
    return tour;
}

void Pion::IncrementeTour()
{
    tour++;
}

void Pion::ResetTour()
{
    tour=0;
}

unsigned int Pion::GetI() const
{
    return i;
}

int Pion::GetId() const
{
    return id;
}

bool Pion::GetEstSorti() const
{
    return est_sorti;
}

bool Pion::GetEstArrive() const 
{
    return est_arrive;
}

void Pion::SetEstArrive()
{
    est_arrive = true;
}

void Pion::SetI(const int nb)   //verification du bon pion dans plateau
{
    cout<<"Ancien I: "<<i<<endl;
    assert(nb >0); // on attend 1 increment positif
    i+=nb;
    cout<<"Nouveau I: "<<i<<endl;
    //cout<<"Le pion se deplace et se trouve en "<<i<<endl;
}

void Pion::ChangerI(const int nb)
{
    assert( nb >=0 && nb<= 58); // position valides , max logique du parcours
    i=nb;
}

void Pion::SortirDeLaBase(const float newx, const float newy){
    assert(! est_sorti);  //eviter de sortir 2 fois
    est_sorti=true; //Le pion est maintenant en jeu
    i=0;  //supposons que la position de depart soit 1
    x= newx;
    y=newy;
    cout<<"Pion "<<id <<" sorti de la base"<<endl;
}

void Pion::RetournerBase(){
    est_sorti=false;
    i=0;
    
    cout<<"Pion "<<id <<"dans la base"<<endl;
}

void Pion::CoordonneesPionPoule(const float cx,const float cy)
{
    assert(cx >= 0 && cx < 600);
    assert(cy >= 0 && cy < 600);
    x= cx;
    y= cy;
}


float Pion::GetXPion () const
{
	return x;
}

float Pion::GetYPion () const
{
	return y;
}

void Pion::SetX (const float cx)
{
    assert(cx >= 0 && cx < 700);
    x=cx;
}

void Pion::SetY (const float cy)
{
    assert(cy >= 0 && cy < 700);
    y=cy;
}


void Pion:: testRegression(){
    cout <<"Debut de tests de regression de la classe  PION "<<endl;

    //test de const pion avec ID
    Pion p1(1);
    assert(p1.GetId()== 1);
    assert(p1.GetI()== 0);
    assert(!p1.GetEstSorti());
    assert(!p1.GetEstArrive());

    // Test des coordonnées de base
    p1.CoordonneesPionPoule(100.0f, 200.0f);
    assert(p1.GetXPion() == 100.0f);
    assert(p1.GetYPion() == 200.0f);

    // Test des setters X/Y
    p1.SetX(300.0f);
    p1.SetY(400.0f);
    assert(p1.GetXPion() == 300.0f);
    assert(p1.GetYPion() == 400.0f);

    // Test de sortie de la base
    p1.SortirDeLaBase(50.0f, 60.0f);
    assert(p1.GetEstSorti());
    assert(p1.GetI() == 0);
    assert(p1.GetXPion() == 50.0f);
    assert(p1.GetYPion() == 60.0f);

    // Test de déplacement
    p1.SetI(3);  // avance de 3
    assert(p1.GetI() == 3);
    p1.ChangerI(10);  // position absolue
    assert(p1.GetI() == 10);

    // Test retour à la base
    p1.RetournerBase();
    assert(!p1.GetEstSorti());
    assert(p1.GetI() == 0);

    // Test du constructeur par défaut
    Pion p2;
    assert(p2.GetId() == -1);
    assert(p2.GetI() == 0);
    assert(!p2.GetEstSorti());
    assert(!p2.GetEstArrive());

    cout << "Tous les tests de régression de la classe Pion ont réussi" << endl;
}

