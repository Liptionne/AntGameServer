# Serveur Fourmis CPP

[WIP]


Le projet nécessite Boost pour fonctionner (version 1.80) : https://www.boost.org/users/download/

Il faut ajouter boost en librairie externe.

Pour faire fonctionner le serveur, necessite de lancer le .exe 
Un paramétrage approfondi dans le fichier option.json permet de paramétrer les options du serveur.

Pour utiliser le client, il suffit de créer un client en spécifiant l'adresse et le port du serveur.
Puis de faire .join(difficulté) le client quand vous voulez vous connecter à une partie en choisissant la difficulté.
Enfin, faire un client.move(direction) à chaque déplacement de la fourmi, le programme enverra le mouvement au serveur.
Le programme se charge de mettre à jour le labyrinthe à chaque reception des données.