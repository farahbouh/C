#include "Color.h"
#include <iostream>
using namespace std;
    
    Color::Color(): r(0), v(0), b(0){};

    Color::~Color(){}

    void Color::setColor(unsigned char nr, unsigned char nv, unsigned char nb){
        r=nr;
        v=nv;
        b=nb; 
    } 

    const Color& Color::getColor(){
        return *this; //Renvoie une reference sur l'objet courant
        
    }
    
    unsigned char Color::getR() const{ return r; }
    unsigned char Color::getV() const{ return v; }
    unsigned char Color::getB() const{ return b; }