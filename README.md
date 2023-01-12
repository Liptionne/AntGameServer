# Serveur Fourmis CPP


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

# Ant-Game-Server
This repository represents a project done during my studies in Polytech Tours.

# What's the project ?

This project was a exposition project. The idea was to create a game, where players would be ants, and these ants would be in a maze, searching for food for their colony.
The whole idea is to show how ants can show their colony their path to retreive food sources.

How ants can communicate with each others ? By dropping some pheromons ! In nature, pheromons are little chemical molecules dropped by ants.
In our game, ants drop pheromons while they carry food on their back. In this way, it's easy to find food sources !

For this, the project was splitted in 3 teams : 
- The maze library : the team has to create a library that can create random mazes
- The client : this team should create an UI game, with a client moving in the maze
- The server (me) : I should build a server managing games, the players movements, the maze generation, etc

# What are the specifications of the project ?

The specifications : 
- The server should be asynchronous, in the way that a player no moving should see other players movement
- The server must call the library to create maze, and send this maze to all new players
- Be capable to replay a game
- Deal with starting and ending a game
- Manage multiple players and multiple games
- Can be run on different OS.
- Create the client method to be implemented in the player code

# Where are we today ?
Today I have a functionnal server, that can manage multiple games, multiple clients, start and end games.
But there is still work to do ! 

# TODO

 - Add a replay mode
 - add score to players
 - change ending and starting of games
 - add units tests and performance tests
 - add fog of war

