# Rendu OPENGL 
### Auteur : Maëva LAUZIER

## Déplacement caméra 

La caméra se déplace avec ZQSD et la souris pour l'angle de vue. 

## Scene 

La scène est composée exclusivement de cube qui sont de deux textures différentes. Les cubes ont une vitesse de rotation et une 
scale tous différentes.

## Ressources utilisées 

Ce projet est fait à l'aide des tutoriels de learnopengl.com. 
Une librairie additionnelle a été installer : SDL2. Cette librairie est utilisée pour charger les textures
(c'est un chard d'assaut pour aller acheter le pain, mais c'est suite à des erreurs pour installer des librairies 
que je me suis retrouvée avec celle-ci qui fonctionnait et que j'ai gardé pour ne pas perdre plus de temps.) 

## Installation

Si l'executable ne fonctionne pas : 
- installer l'éditeur qtcreator
- installer msys2 (https://wiki.qt.io/MSYS2#Initial_Setup_of_MSYS2)
- installer SDL2 via pacman (pacman -Ss sdl)

=> toutes les textures et shader doivent être dans le dossier release crée par qt
=> par defaut qt crée ces dossiers ( release, debug) en dehors du projet
=> mettre donc les dossier en dehors du projet