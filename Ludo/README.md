# Ludo - Jeu de Société

## Description

Le projet **LUDIFAI** est une implémentation du jeu de société Ludo connu aussi sous le nom des 4 petits cheveaux
en utilisant le C++ et la bibliothèque SDL. Le but du jeu est de déplacer tous ses pions de la case de départ à la case d'arrivée en 1er, en fonction des résultats des dés. En effet, on peut sortir un pion que si on tire un 6. 

Ce jeu propose une interface graphique avec des pions colorés, un plateau interactif, et la possibilité de jouer à plusieurs, seule et avec une IA.

### Règles du jeu

1. **Lancer de dé** : À chaque tour, le joueur lance un dé pour déterminer combien de cases il peut déplacer ses pions. Il ne peut pas tirer le dé si il a deja gagné

2. **Sortir un pion** : Un joueur peut sortir un pion de sa zone de départ uniquement s’il tire un 6. Sinon il saute son tour

3. **Avancer les pions** : Les pions se déplacent selon le résultat du dé. Le joueur peut choisir quel pion déplacer tant qu'il est sortie de sa zone de depart.

4. **Gagner** : Le joueur qui parvient à déplacer ses 4 pions de la case de départ à la case d’arrivée en premier gagne la partie.


## Fonctionnalités

- **Dé**: utilisé pour lancer un chiffre aléatoire (souvent entre 1 et 6) qui détermine combien de cases un joueur peut déplacer ses pions. Si un 6 est tiré le joueur peut choisir de soit sortir un pion soit deplace un pion sorti.

- **Pion** : Représente une pièce du joueur qui se déplace sur le plateau selon les résultats des dés.

- **Joueur** : contrôle des pions d'une couleur spécifique et cherche à les amener à la zone de sécurité.

- **Jeu** : Gère le déroulement de la partie, les tours de jeu et la condition de fin.

- **Color** : Détermine la couleur des pions et des cases du joueur.

- **Image** : Affiche les éléments graphiques du jeu (pions, dés, plateau) à l'écran.

- **AffichageSDL** : Gère l'affichage visuel du jeu en utilisant la bibliothèque SDL.

## Prérequis
- **C++** 
- **SDL2** pour l'affichage graphique.

## Installation

### Étape 1 : Cloner le repository
Clonez ce repository sur votre machine locale en utilisant la commande suivante :

```bash
git clone https://forge.univ-lyon1.fr/p2103816/LUDIFAI.git
```

### Étape 2 : Lancer le jeu

```bash
cd LUDIFAI
cd p2409132_p2103816_p2208997
make // pour exécuter
./bin/mainsdl //pour afficher la SDL
```