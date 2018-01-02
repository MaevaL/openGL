# Rendu OPENGL 
### Auteur : Ma�va LAUZIER

## D�placement cam�ra 

La cam�ra se d�place avec ZQSD et la souris pour l'angle de vue. 

## Scene 

La sc�ne est compos�e exclusivement de cube qui sont de deux textures diff�rentes. Les cubes ont une vitesse de rotation et une 
scale tous diff�rentes.

## Ressources utilis�es 

Ce projet est fait � l'aide des tutoriels de learnopengl.com. 
Une librairie additionnelle a �t� installer : SDL2. Cette librairie est utilis�e pour charger les textures
(c'est un chard d'assaut pour aller acheter le pain, mais c'est suite � des erreurs pour installer des librairies 
que je me suis retrouv�e avec celle-ci qui fonctionnait et que j'ai gard� pour ne pas perdre plus de temps.) 

## Installation

Si l'executable ne fonctionne pas : 
- installer l'�diteur qtcreator
- installer msys2 (https://wiki.qt.io/MSYS2#Initial_Setup_of_MSYS2)
- installer SDL2 via pacman (pacman -Ss sdl)

=> toutes les textures et shader doivent �tre dans le dossier release cr�e par qt
=> par defaut qt cr�e ces dossiers ( release, debug) en dehors du projet
=> mettre donc les dossier en dehors du projet