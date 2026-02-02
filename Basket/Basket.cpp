#include <Grapic.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace grapic;

/// *************************************************
// Constantes pour la configuration du jeu
const int DIMW = 550;            // Dimension de la fenêtre (carrée)
const float friction = 0.60;     // Coefficient de friction pour les rebonds
const float dt = 0.01;           // Pas de temps pour l'update
const float g = -9.81;           // Gravité
const float i = 1.0;             // Incrément de score
const float hauteur = 100;       // Hauteur d'un joueur
const float largeur = 50;        // Largeur d'un joueur
const float vitesse_joueur = 2;  // Vitesse de déplacement joueur
const float vitesse_robot = 0.5; // Vitesse du robot
const float hauteur_panier = 430; // Hauteur du panier
const float centre_fenetre = DIMW/2;
const float taille_joueur = 100; 
const float largeur_joueur = 50;
const float taille_cheveux = 10; // Correction orthographique
const float distance_B_J = 40;   // Distance maximale pour interaction balle-joueur

/// *************************************************
// Structure pour représenter un vecteur 2D ou nombre complexe
struct Complex {
    float x, y;
};

Complex make_complex(float x, float y) {
    Complex c;
    c.x = x; c.y = y;
    return c;
}

/// Crée un vecteur à partir d'un angle (degrés) et d'une magnitude
Complex make_complex_exp(float r, float theta_deg) {
    Complex c;
    c.x = r*cos(theta_deg);
    c.y = r*sin(theta_deg);
    return c;
}

/// Opérateurs pour Complex
Complex operator+(Complex a, Complex b) { return make_complex(a.x+b.x, a.y+b.y); }
Complex operator-(Complex a, Complex b) { return make_complex(a.x-b.x, a.y-b.y); }
Complex operator*(float lambda, Complex b) { return make_complex(lambda*b.x, lambda*b.y); }
Complex operator/(Complex b, float d) { return make_complex(b.x/d, b.y/d); }
Complex operator*(Complex a, Complex b) { return make_complex(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x); }

/// Scale autour d'un point centre
Complex scale(Complex p, float cx, float cy, float lambda) {
    Complex centre = make_complex(cx, cy);
    return (lambda*(p-centre))+centre;
}

/// Convertit degrés en radians
float rad_trad(float deg) {
    return ( M_PI*deg/180.f );
}

/// Rotation autour d'un centre
Complex rotate(Complex p, float cx, float cy, float theta_deg) {
    Complex rot = make_complex_exp(1, rad_trad(theta_deg));
    Complex centre = make_complex(cx, cy);
    return (p-centre)*rot + centre;
}

/// **********************************************************************************
// Structures principales du jeu
struct Balle {
    Complex position, vitesse, force;
    float angle;
    float masse;
};

struct Panier {
    Complex position; // Position du panier (haut du poteau)
};

struct Joueur {
    Complex position;
    float score;      // Score actuel du joueur
};

struct World {
    int win;          // Variable pour contrôler le comptage des points
    float dt;
    Balle B;          // La balle
    Panier PA, PB;    // Deux paniers (gauche et droite)
    Joueur a, b;      // Joueurs
};

/// **********************************************************************************
// Initialisation des objets
void initballe(Balle &B) {
    B.position = make_complex(centre_fenetre,5); // Balle au centre du sol
    B.vitesse = make_complex(10,10);
    B.force = make_complex(0,0);
    B.masse = 1.0;
}

void initpanier(Panier &PA) { PA.position = make_complex(0, hauteur_panier); }
void initpanier2(Panier &PB) { PB.position = make_complex(DIMW, hauteur_panier); }

void initjoueura(Joueur &a) { a.position = make_complex(centre_fenetre+50 , 50); a.score = 0; }
void initjoueurb(Joueur &b) { b.position = make_complex(centre_fenetre-50 , 50); b.score = 0; }

/// **********************************************************************************
// Dessin des objets
void drawballe(Balle &B) {
    color(255,137,0);
    circleFill(B.position.x, B.position.y, 20); // Dessine la balle
}

void drawpanier1(Panier PA) {
    color(255,255,255);
    rectangleFill(PA.position.x, PA.position.y, 60,445); // Panier gauche
    color(12,12,0);
    rectangleFill(0, 0, 15, 500); // Poteau gauche
}

void drawpanier2(Panier PB) {
    color(12,12,0);
    rectangleFill(PB.position.x, PB.position.y, DIMW-60,445); // Panier droit
    color(215,255,255);
    rectangleFill(DIMW,0,DIMW-15,500); // Poteau droit
}

void drawJoueura(Joueur &a) {
    color(0,255,255); 
    rectangleFill(a.position.x,0,a.position.x+largeur_joueur,taille_joueur); // Corps joueur
    color(0,0,0);
    rectangleFill(a.position.x+largeur_joueur,taille_joueur,a.position.x-largeur_joueur+largeur_joueur,taille_joueur+20); // Tête
    color(240,235,210);
    rectangleFill(a.position.x+largeur_joueur,taille_joueur,a.position.x-largeur_joueur+largeur_joueur,taille_joueur+15); // Cheveux
}

void drawJoueurb(Joueur &b) {
    color(255,0,0); 
    rectangleFill(b.position.x,0,b.position.x+largeur_joueur,taille_joueur);
    color(0,0,0);
    rectangleFill(b.position.x+largeur_joueur,taille_joueur,b.position.x-largeur_joueur+largeur_joueur,taille_joueur+20);
    color(240,235,210);
    rectangleFill(b.position.x+largeur_joueur,taille_joueur,b.position.x-largeur_joueur+largeur_joueur,taille_joueur+15);
}

/// **********************************************************************************
// Physique et collisions
void computegravityforce(World& w) { w.B.force = make_complex(0, g*w.B.masse); }
void addforce(Balle &b, Complex f) { b.force = b.force + f; }

float distance(Complex PA, Complex PB) {
    return sqrt(pow(PA.x-PB.x,2) + pow(PA.y-PB.y,2));
}

/// Collisions de la balle avec sol, murs et têtes des joueurs
void collision(World &w) {
    // Sol et plafond
    if (w.B.position.y <= 0) { w.B.position.y = -w.B.position.y; w.B.vitesse.y = -w.B.vitesse.y; w.B.vitesse = friction*w.B.vitesse; }
    if (w.B.position.y >= DIMW) { w.B.position.y = DIMW-(w.B.position.y-DIMW); w.B.vitesse.y = -w.B.vitesse.y; w.B.vitesse = friction*w.B.vitesse; }
    // Murs gauche/droite
    if (w.B.position.x <= 0) { w.B.position.x = -w.B.position.x; w.B.vitesse.x = -w.B.vitesse.x; w.B.vitesse = friction*w.B.vitesse; }
    if (w.B.position.x >= DIMW) { w.B.position.x = DIMW-(w.B.position.x-DIMW); w.B.vitesse.x = -w.B.vitesse.x; w.B.vitesse = friction*w.B.vitesse; }
    // Collision tête joueur A
    if ((w.B.position.x >= w.a.position.x) && (w.B.position.x <= w.a.position.x+largeur_joueur) &&
        (w.B.position.y <= taille_joueur+15) && (w.B.position.y >= taille_joueur+taille_cheveux)) {
        w.B.vitesse.y += 50; w.B.vitesse.x -= 5; w.B.vitesse = friction*w.B.vitesse;
    }
    // Collision tête joueur B
    if ((w.B.position.x >= w.b.position.x) && (w.B.position.x <= w.b.position.x+largeur_joueur) &&
        (w.B.position.y <= taille_joueur+15) && (w.B.position.y >= taille_joueur+taille_cheveux)) {
        w.B.vitesse.y += 50; w.B.vitesse.x += 5; w.B.vitesse = friction*w.B.vitesse;
    }
}

/// **********************************************************************************
// Fonctions pour mettre à jour la balle et les joueurs
void updateballe(World &w) {
    Complex f = make_complex(0,g*w.B.masse);
    addforce(w.B,f);
    w.B.vitesse = w.B.vitesse + dt*((1.0/w.B.masse)*w.B.force);
    w.B.position = w.B.position + dt * w.B.vitesse;
    collision(w);
    if (isKeyPressed(' ')) { // Réinitialiser la balle en cas de bug
        w.B.position = make_complex(DIMW/2, DIMW/2);
    }
}

void updatejoueurb(World &w) {
    const float d = 0.1f;
    if (w.b.position.y > 3) w.b.position.y -= d;
    if (isKeyPressed('c') && w.b.position.x > 0) w.b.position.x -= d + vitesse_joueur;
    if (isKeyPressed('b') && w.b.position.x+largeur_joueur <= DIMW) w.b.position.x += d + vitesse_joueur;
    if (isKeyPressed('v') && distance(w.B.position,w.b.position)<=distance_B_J) {
        if (w.B.position.x < w.b.position.x+10) w.B.vitesse = w.B.vitesse + make_complex(-largeur,hauteur);
        if (w.B.position.x > w.b.position.x+10) w.B.vitesse = w.B.vitesse + make_complex(largeur,hauteur);
    }
}

void updaterobot(World &w) {
    const float d = 0.1f;
    if (w.b.position.y > 3) w.b.position.y -= d;
    if (w.B.position.x < w.b.position.x+largeur_joueur && w.b.position.x > 0) w.b.position.x -= d + vitesse_robot;
    if (w.B.position.x > w.b.position.x && w.b.position.x < DIMW) w.b.position.x += d + vitesse_robot;
    if (distance(w.B.position,w.b.position) <= distance_B_J) {
        if (w.B.position.x < w.b.position.x+10) w.B.vitesse = w.B.vitesse + make_complex(-largeur,hauteur);
        if (w.B.position.x > w.b.position.x+10) w.B.vitesse = w.B.vitesse + make_complex(largeur,hauteur);
    }
}

int main(int , char**) {
    bool stop=false;
    winInit("Projet", DIMW, DIMW);
    backgroundColor(0,137,255);

    Menu menu;
    menu_add(menu, "1 Joueur");
    menu_add(menu, "2 Joueurs");
    menu_add(menu, "VS robots");
    menu_add(menu, "Regles");

    World w1,w2,w3;
    initballe(w1.B); initballe(w2.B); initballe(w3.B);

    while(!stop) {
        setKeyRepeatMode(true);
        winClear();
        int selection = menu_select(menu);
        switch(selection) {
            case 0: break; // Ajoute drawworld1 et updateworld1 ici
            case 1: break; // Drawworld2 etc.
            case 2: break; // Drawworld3 etc.
            case 3: fontSize(22); print(0,DIMW-25,"Voir README"); break;
        }
        menu_draw(menu, 0, 0, 200, 30);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}