# Serveur Fourmis CPP

**[WIP]**


Le projet nécessite **Boost** pour fonctionner (version 1.80) : https://www.boost.org/users/download/

La version C++ utilisée est C++17.

Il faut ajouter boost en librairie externe.

Une documentation doxygen est disponible dans le dossier "doc"

### Fonctionnement du serveur

Pour faire fonctionner le serveur, necessite de lancer le .exe 
Un paramétrage approfondi dans le fichier option.json permet de paramétrer les options du serveur.



### Fonctionnement du client
1. Créer un client en spécifiant l'adresse et le serveur à qui se connecter
2. Appeller `Client.join(difficulty)` pour initier la connexion et demander à rejoindre une partie.
3. Appeller `Client.move(direction)` pour chaque déplacement du joueur. **C'est bien au client de vérifier que le déplacement est possible !**