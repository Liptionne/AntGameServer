# Serveur Fourmis CPP

[WIP]


Le projet n�cessite Boost pour fonctionner (version 1.80) : https://www.boost.org/users/download/

Il faut ajouter boost en librairie externe.

Pour faire fonctionner le serveur, necessite de lancer le .exe 
Un param�trage approfondi dans le fichier option.json permet de param�trer les options du serveur.

Pour utiliser le client, il suffit de cr�er un client en sp�cifiant l'adresse et le port du serveur.
Puis de faire .join(difficult�) le client quand vous voulez vous connecter � une partie en choisissant la difficult�.
Enfin, faire un client.move(direction) � chaque d�placement de la fourmi, le programme enverra le mouvement au serveur.
Le programme se charge de mettre � jour le labyrinthe � chaque reception des donn�es.