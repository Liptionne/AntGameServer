# Serveur Fourmis CPP

**[WIP]**


Le projet n�cessite **Boost** pour fonctionner (version 1.80) : https://www.boost.org/users/download/

La version C++ utilis�e est C++17.

Il faut ajouter boost en librairie externe.

### Fonctionnement du serveur

Pour faire fonctionner le serveur, necessite de lancer le .exe 
Un param�trage approfondi dans le fichier option.json permet de param�trer les options du serveur.



### Fonctionnement du client
1. Cr�er un client en sp�cifiant l'adresse et le serveur � qui se connecter
2. Appeller `Client.join(difficulty)` pour initier la connexion et demander � rejoindre une partie.
3. Appeller `Client.move(direction)` pour chaque d�placement du joueur. **C'est bien au client de v�rifier que le d�placement est possible !**