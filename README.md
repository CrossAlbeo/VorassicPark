# Vorassic Park

Développement d’un programme en C permettant d’arbitrer une partie de Vorassic Park entre deux à quatre joueurs.

Pour rappel, le but est d’engranger le plus de points ou de capturer un territoire plus grand que ses adversaires en capturant les cases d’un espace commun. 

Programme compatible et optimisé pour un environnement Windows.

## Fonctionnalités

- Exécution dans le terminal
- Création de la grille (de 5 à 26 colonnes/lignes)
- Saisie des coups au clavier
- 2 modes : serpent et pieuvre
- Générateurs de valeurs : distance entre les joueurs ou aléatoire
- Affichage "graphique" des scores

Bonus :

- Multijoueur (jusqu’à 4 joueurs)
- Arrêt intelligent d’une partie
- Mode conquête : le gagnant ne sera plus celui qui aura capturé le plus de cases mais celui qui capture le plus de case ET le plus grand territoire (en proportion, 35% pour le score des cases contre 65% pour le territoire capturé)
- Ajout de murs

## API

```c
void setColors()
```
Définie la configuration pour les couleurs.

```c
void init()
```
Configuration de base de la grille, ajout de murs (#), de valeurs aléatoires...

```c
void configCPlayer()
```
Paramétrage du nombre de joueurs.

```c
int checkMove()
```
Renvoie 1 si le joueur peut encore jouer, ou 0 dans le cas contraire.

```c
int playOrNext()
```
Renvoie 1 si le joueur peut jouer à cette case, ou 0 dans le cas contraire.

```c
void draw()
```
Dessine la grille dans le terminal.

```c
int maxScore()
```
Renvoie l’indice du premier joueur avec le plus grand score. En mode strict (troisième paramètre à 1), renvoie l’indice du joueur avec le plus grand score à condition qu’il soit le seul à avoir ce score, sinon -1.

Permet d’arrêter le jeu quand il ne reste plus qu’un joueur et que ce joueur à le score le plus élevé de la partie. 

## Bibliothèque

- Conio