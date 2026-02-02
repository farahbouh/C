#include <iostream>
#include "Joueur.h"
#include <cassert>

using namespace std;

	Joueur::Joueur(): id(1), nbpionarrives(0), a_gagner(false), type(HUMAIN)
	{
		for(unsigned int i=0; i<4; i++){
			tab[i]=Pion(i); //cree 4 pions avec un identifiant unique
		}

	}



Joueur::Joueur(unsigned int ident, TypeJoueur t, unsigned char r, unsigned char v, unsigned char b)
:id(ident), nbpionarrives(0), a_gagner(false), type(t)
{
	couleur.setColor(r,v,b); //correctement initialise
	for (unsigned int i=0; i<4; i++){
		//tab[i] = new Pion(i);  
		tab[i] = Pion(i);
	}
}

Joueur::~Joueur()
{
	/*for (unsigned int i = 0; i < 4; i++) 
	{
		couleur.setColor(r,v,b); //correctement initialise
		for (unsigned int i=0; i<4; i++){
			tab[i] = Pion(i);  
		}
	}
	return pions_en_jeu;*/
	id=4; //vu qu on peut pas mettre -1 
	nbpionarrives = 0;
	a_gagner = false;
	couleur.setColor(0,0,0); //noir
	//peut pas vider un tableau statique
}

string Joueur::GetLabel() const
{
	return label;
}

void Joueur::SetLabel(string lab)
{
	label = lab;
}

TypeJoueur Joueur:: GetType() const{
	return type;
}

void Joueur::SetType(TypeJoueur t){
	type =t;
}

bool Joueur:: TousPionsSortis(){
	for(int i=0; i<4; i++){
		if(!tab[i].GetEstSorti()){
			return false;
		}
	}
	return true;
}
unsigned int Joueur::getId() const
{
	return id;
} 

bool Joueur::Joueur_Gagnant()
{
	if(GetNbpionArrives()==4)
	{
		a_gagner=true;
	}else{
		a_gagner=false;
	}
	return a_gagner;
}

int Joueur::GetNbpionArrives() const
{
	return nbpionarrives;
}

void Joueur::IncrementerNbPionArrive()
{
	nbpionarrives++;
}

Color Joueur:: getCouleur() const {return couleur ;}

Pion& Joueur::GetPion(int indice)
{
	assert(indice >=0 && indice <=3);
	return tab[indice];
}

void Joueur::GetPionsEnJeu(Pion pions_en_jeu[4]) const
{
	int index=0;
	for(int i=0; i<4; i++){
		if(!tab[i].GetEstArrive() && tab[i].GetEstSorti())
		{
			pions_en_jeu[index]=tab[i];
			index++;
		}
	}
}


float Joueur::GetYPion(int id_pion) const

{
	assert( id_pion >=0 && id_pion < 4);
	return tab[id_pion].GetYPion();
}

float Joueur::GetXPion(int id_pion) const
{
	assert( id_pion >=0 && id_pion < 4);
	return tab[id_pion].GetXPion();
}


void Joueur::RemplirCoordonneePoule(float cx, float cy)
{
	tab[0].CoordonneesPionPoule(cx, cy);
	tab[1].CoordonneesPionPoule(cx+1.75, cy);
	tab[2].CoordonneesPionPoule(cx, cy-1.75);
	tab[3].CoordonneesPionPoule(cx+1.75, cy-1.75);
}

void Joueur::RentrerPionBase(int id_pion, pair<float, float> coordo_pion)
{
	if(id_pion==0)
	{
		tab[0].CoordonneesPionPoule(coordo_pion.first, coordo_pion.second);
	}
	if(id_pion==1)
	{
		tab[1].CoordonneesPionPoule(coordo_pion.first+1.75, coordo_pion.second);
	}
	if(id_pion==2)
	{
		tab[2].CoordonneesPionPoule(coordo_pion.first, coordo_pion.second-1.75);
	}
	if(id_pion==3)
	{
		tab[3].CoordonneesPionPoule(coordo_pion.first+1.75, coordo_pion.second-1.75);
	}
}

void Joueur::SortirPionBase(pair<int,int> CoordSortiBase)
{
	assert(CoordSortiBase.first >= 0);
	assert(CoordSortiBase.second >= 0);

	int id_pion_a_sortir=-1; //gerer cas tout le pions sont sorti

	for (int i = 0; i <= 3; i++) 
	{
    	if (!tab[i].GetEstSorti())
		{
        	id_pion_a_sortir = i;
        	break;
    	}
	}
	
	if(id_pion_a_sortir!=-1)
	{
		//sort pion en mettant a jour les coordonées	
		tab[id_pion_a_sortir].SortirDeLaBase(CoordSortiBase.first, CoordSortiBase.second);
	}
}


void Joueur::DeplacerUnPion(int id_p, int val_de)
{
	assert(id_p >= 0 && id_p < 4);
	tab[id_p].SetI(val_de);
    cout<<"le pion "<<id_p<< "avance de " <<val_de <<"cases." <<endl;

}

void Joueur::SetXpion(int id_p, float cx)
{
	assert(id_p >= 0 && id_p < 4);
	tab[id_p].SetX(cx);
}

void Joueur::SetYpion(int id_p, float cy)
{
	assert(id_p >= 0 && id_p < 4);
	tab[id_p].SetY(cy);
}

void Joueur:: testRegression(){
	cout << "Début des test de regression de la classe Joueur "<<endl;

	Joueur j1( 0,HUMAIN, 55, 0, 0); //joueur rouge
	assert(j1.getId() == 0);
    assert(j1.getCouleur().r == 255);
    assert(j1.getCouleur().v == 0);
    assert(j1.getCouleur().b == 0);
	assert(j1.GetType()== HUMAIN);

	for(int i=0; i< 4; i++){
		assert(j1.GetPion(i).GetId()== i);
		assert(j1.GetPion(i).GetI()== 0);
	}

	j1.RemplirCoordonneePoule(100.0f, 100.0f);
	assert(j1.GetPion(0).GetXPion()== 100.0f);
	assert(j1.GetPion(1).GetYPion()== 101.75f);

	j1.SortirPionBase({50, 60});
	int compteur_pion_sortis= 0;
	for(int i=0; i< 4; i++){
		if(j1.GetPion(i).GetEstSorti()) compteur_pion_sortis++;
	}
	assert(compteur_pion_sortis == 1);

	j1.DeplacerUnPion(0, 5);
	assert(j1.GetPion(0).GetI()== 5);

	assert(j1.GetNbpionArrives()== 0);
	j1.IncrementerNbPionArrive();
    j1.IncrementerNbPionArrive();
    j1.IncrementerNbPionArrive();
    j1.IncrementerNbPionArrive();
    assert(j1.GetNbpionArrives() == 4);
    assert(j1.Joueur_Gagnant());

	Pion en_jeu[4];
	j1.GetPionsEnJeu(en_jeu); //devrait contenir au moin 1p s'il est pas arrive et sorti

	cout <<"Tous les test de regression de la classe Joueur sont reussi "<<endl;
}