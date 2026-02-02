#include "AffichageSDL.h"
#include <iostream>

using namespace std;

int main()
{
    srand(time(NULL));
    AffichageSDL sj;
    
    Jeu J;
    sj.SdlBoucle(J);

    return 0;
}