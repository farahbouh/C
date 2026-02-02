#include <iostream>
#include "Joueur.h"   //a enlever pour jeu
#include "Pion.h"
#include "De.h"   //a enlever pour jeu
#include "Color.h"
#include "Jeu.h"
#include "AffichageSDL.h"

using namespace std;

int main() {
    //  Test de la classe Color
    cout << "==== TEST COLOR ====" << endl;
    Color c;
    c.setColor(255, 0, 0); // Rouge
    cout << "Couleur définie : R=" << (int)c.getColor().r 
         << ", V=" << (int)c.getColor().v 
         << ", B=" << (int)c.getColor().b << endl;

    // Test de la classe De (lancer de dé)
    cout << "\n==== TEST DE ====" << endl;
    De de;
    for (int i = 0; i < 5; i++) {
        cout << "Lancer " << i+1 << " : " << de.GetVal() << endl;
    }

    //  Test de la classe Pion
    cout << "\n==== TEST PION ====" << endl;
    Pion pion1(1);
    cout << "Pion créé avec ID " << pion1.GetId() 
         << ", Position : " << (int)pion1.GetI() << endl;

    pion1.SetI(6); // Déplacement de 6 cases
    cout << "Après déplacement : Position = " << (int)pion1.GetI() << endl;

    // Test de la classe Joueur
    cout << "\n==== TEST JOUEUR ====" << endl;
    Joueur joueur1(1, HUMAIN,0, 255, 0); // Joueur vert
    cout << "Joueur " << joueur1.getId() 
         << " a la couleur R=" << (int)joueur1.getCouleur().getR() 
         << ", V=" << (int)joueur1.getCouleur().getV ()
         << ", B=" << (int)joueur1.getCouleur().getB() << endl;

     //Test de l'affichage sdl jeu 
     Jeu j;
    char t[4];
     bool valide;
     cout<<"depart jeu"<<endl;
     cout<<"Choisissez vos pions: *, +, ^, °"<<endl;

     for(int i=0; i<4; i++)
     {
          do{
               valide = true;
               cout<<"Utilisateur "<<i+1<<": ";
               cin>>t[i];
               cout<<endl;

               for (int j=0; j<i; j++)
               {
                    if(t[j]==t[i])
                    {
                         cout<<"Pion deja prit recommencez"<<endl;
                         valide = false;
                         break;
                    }
               }               
          }while(!valide);

     }


     //AffichageSDL sj;

     //sj.SdlBoucle();

    return 0;
}
