# Jeu de Basket - Simulation en C++

**Version 1.1** – Farah Avril 2023  
**Dernière mise à jour :** 06/05/2023

Ce programme permet de jouer au basket en C++ en utilisant la librairie **Grapic**.  
Il est basé sur le TP Particule et simule la physique pour déterminer la trajectoire de la balle selon la vitesse initiale, l’angle de lancement et la position de départ.

---

## Contrôles

- **Joueur 1 :**
  - Déplacement gauche : `KeyLeft`
  - Déplacement droite : `KeyRight`
  - Tir : `KeyDown`

- **Joueur 2 :**
  - Déplacement gauche : `c`
  - Déplacement droite : `b`
  - Tir : `v`

- **Réinitialisation de la balle :** barre `Espace`

- **Souris :** pour la sélection du menu

---

## Historique des versions

- **07/04/2023** : Vérification du fonctionnement du TP Particule et TP Spring + création du README  
- **14/04/2023** : Débogage de Grapic + création des structures  
- **21/04/2023** : Affichage graphique  
- **28/04/2023** : Début des fonctions d’initialisation  
- **04/05/2023** : Possibilité pour que le joueur tire à droite et à gauche selon la proximité de la balle  
- **05/05/2023** : Ajout des collisions sur la tête des joueurs, couleurs et derniers réglages  

---

## Description des modes de jeu

### Monde 1 : 1 Joueur
- Initialisation pour un seul joueur
- Le joueur 1 utilise les touches `KeyLeft`, `KeyRight` et `KeyDown`
- **Objectif :** 5 points pour gagner

### Monde 2 : 2 Joueurs
- Initialisation pour deux joueurs
- **Joueur 1** : `KeyLeft`, `KeyRight`, `KeyDown`  
- **Joueur 2** : `c`, `b`, `v`
- **Objectif :** 5 points pour gagner

### Monde 3 : 1 Joueur + Robot
- Initialisation pour un joueur et un robot
- **Joueur 1** : `KeyLeft`, `KeyRight`, `KeyDown`  
- **Joueur 2 (robot)** : paramètres définis dans le programme
- **Objectif :** 5 points pour gagner

---

## Remerciements

- À mon père, qui m’a donné l’idée de ce projet  
- À Cherazade, qui m’a aidé à déboguer le code  
- À Madame Desserée, qui m’a enseigné le C++

---

## Contact

Si vous avez des questions ou des commentaires, n’hésitez pas à m’envoyer un mail.

**Bonne simulation de lancer de basket !**