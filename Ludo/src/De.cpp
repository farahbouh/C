#include "De.h"
#include <cstdlib>   //pour rand()
#include <cassert>
#include <iostream>
using namespace std;


De::De(): val(1) // initialisation par liste plus propre
{ }

De::~De()
{
    val = 0;
}

void De::LancerDe()
{
    val = rand()%6+1;
    assert( val >=1 && val <=6); //verifie que la val est compris entre 1 et 6
}

int De::GetVal() const
{
    return val;
}

void De:: testRegression(){
    cout <<"Debut de test de regression de la classe De " <<endl;

    //test du const
    De d1;
    assert(d1.GetVal()== 1);

    //test du lance de dé
    d1.LancerDe();
    int valeur= d1.GetVal();
    assert(valeur >=1 && valeur <=6);

    //effectuer plusieurs lance pour verifier la validite
    for(int i= 0; i<25; i++){
        d1.LancerDe();
        valeur= d1.GetVal();
        assert(valeur >=1 && valeur <=6);
    }

    cout <<"Tous les test de regression de la classe De ont reussi" <<endl;

}






