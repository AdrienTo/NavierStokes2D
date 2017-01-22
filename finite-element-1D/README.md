# Résolution numérique 1D d'équations elliptiques linéaires via les éléments finis 

## Contenu du dossier
- src:  les sources du programme, en C++
- include: les headers C++
- test: les fichiers nécessaires aux tests de bon fonctionnement
## Vérification des sources

Pour vérifier le bon fonctionnement des classes, lancer les commandes suivantes dans ce dossier:
```
make testR1
make testmeshes
cd test
./R1_test
./meshes_test
```
Aucun assert ne devrait être lancé et vous devriez avoir deux messages 'Test well performed'
## Classes et méthodes implémentées:
#simple_dim.c simple_dim.h

Implémentation d'une classe R1, point en une dimension (un réel). Elle n'est pas d'une grande utilité en pratique, mais est utile pour une généralisation en dimensions supérieures.

#meshes_seg.c meshes_seg.h

Implémentation d'une classe Seg et de ses méthodes, qui représente deux points de R1 et plus généralement un vertice de dim 1.

Implémentation des fonctions loadSeg et loadNodes qui permettent de charger des fichiers `.msh` et les stocker sous des vecteurs de pointeurs.


Implémentation d'une classe ** abstraite ** Mesh_1D. 
- Le constructeur permet de charger un fichier de maillage une dimension `.msh` et de le stocker, en conservant les informations sur sa géométrie, via trois vecteurs.
- La méthode linearForm doit être réécrite par la classe qui hérite de ces propriétés (Mesh_1D étant abstraite). Elle correspond à l'action de l'opérateur différentiel sur la base des fonctions choisies pour les éléments finis
- La méthode make_Rigidity_Matrix permet de construire la matrice de rigidité du problème lorsque linearForm est définie. La complexité inférieure à n*n et le résultat est stocké sous la forme de matrice creuse sous la forme CRS (Compressed Row Storage)
- La méthode get_Rigidity_Matrix permet de récupérer la matrice de rigidité stockée.

Implémentation de la classe Orthogonal_Mesh_1D. C'est un premier exemple de classe qui hérite de Mesh_1D. Elle sert pour des tests de bon fonctionnement.

Implémentation de la classe P1_Lapl_Mesh_1D. Cette classe correspond à la résolution par éléments finis de l'équation de la chaleur stationnaire (-Laplacien(u) = f ). Les éléments choisis sont les P1 de Laplace, la fonction linearForm est définie en conséquent.

