# Résolution numérique 2D d'équations elliptiques linéaires via les éléments finis 

## Contenu du dossier
- src:  les sources du programme, en C++
- include: les headers C++
- test: les fichiers nécessaires aux tests de bon fonctionnement

## Vérification des sources

Pour vérifier le bon fonctionnement des classes, lancer les commandes suivantes dans ce dossier:
```
source test.sh
```
Aucun assert ne devrait être lancé et vous devriez avoir deux messages `Test well performed`

## Classes et méthodes implémentées:

### double_dim.c doublee_dim.h

Implémentation d'une classe R2, point en deux dimensions (deux réel). Une classe de matrice de taille 2 a été implémentée, mais n'est pas utilisée

### meshes_tri.c meshes_tri.h

Implémentation d'une classe Tri et de ses méthodes, qui représente un triangle de R2 et plus généralement un vertice de dim 2.

Implémentation des fonctions loadTri et loadNodes qui permettent de charger des fichiers `.msh` et les stocker sous des vecteurs de pointeurs.


Implémentation d'une classe __abstraite__ Mesh_2D. 
- Le constructeur permet de charger un fichier de maillage une dimension `.msh` et de le stocker, en conservant les informations sur sa géométrie, via trois vecteurs.
- La méthode bilinearFormForm doit être réécrite par la classe qui hérite de ces propriétés (Mesh_2D étant abstraite). Elle correspond à l'action de l'opérateur différentiel sur la base des fonctions choisies pour les éléments finis (typiquement, l'opérateur diff est le laplacien).
- La méthode linearForm doit être réécrite par la classe qui hérite de ces propriétés (Mesh_2D étant abstraite). Elle correspond à l'intégrale du produit de la fonction du membre de droite contre les fonctions de bases choisies.
- La méthode make_Stiffness_Matrix permet de construire la matrice de rigidité du problème lorsque linearForm est définie. La complexité inférieure à n*n et le résultat est stocké sous la forme de matrice creuse sous la forme CRS (Compressed Row Storage)
- La méthode get_Stiffness_Matrix permet de récupérer la matrice de rigidité stockée.
- La méthode make_Constant_Vector permet de construire le vecteur constant du problème, selon la fonction  (i.e b pour le problème Ax = b). La complexité inférieure à n*n et le résultat est stocké sous la forme de matrice creuse sous la forme CRS (Compressed Row Storage)

Implémentation de la classe Orthogonal_Mesh_2D. C'est un premier exemple de classe qui hérite de Mesh_1D. Elle sert pour des tests de bon fonctionnement.

Implémentation de la classe P2_Lapl_Mesh_2D. Cette classe correspond à la résolution par éléments finis de l'équation de la chaleur stationnaire (-Laplacien(u) = f ). Les éléments choisis sont les P1 de Laplace, la fonction linearForm est définie en conséquent.

