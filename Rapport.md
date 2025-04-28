# Rapport d'Organisation Kaotik

## Sommaire

* [Organisation du projet](#organisation-du-projet)
* [Scripts et automatisations](#scripts-et-automatisations)
* [Abstraction de l'OS](#abstraction-de-los)
* [Nos Erreurs](#nos-erreurs)
* [Notions apprises](#notions-apprises)

## Organisation du projet

Pour commencer le projet, nous ne sommes pas partis de rien. Une base de code nous était fourni, mais nous avions surtout déjà fait un projet l'an dernier sur ce même sujet. Nous avons donc surtout repris les fichiers servant à la configuration de platformio et aux github actions et actions de pre-commit déjà définies l'an dernier (Cela ne nous a pas empêché de les améliorer).

Au vue de nos difficultés l'an dernier pour gérer proprement les threads et les mutexes, nous avons décidés de ne pas reprendre le code écrit pour leur gestion et avons repris seulement les briques qui nous intéressaient.

## Script de pre-commit

cf [.pre-commit-config.yaml](.pre-commit-config.yaml)

Lorsque l'on commit, nous vérifions des règles classiques d'espaces à la fin d'une ligne, ligne vide à la fin d'un fichier et l'ajout de fichiers volumineux. Ajouté à ceci un linter et formatteur pour le language C, prédominant dans ce projet.\
Ces vérifications sont gérées par l'appel de hooks déjà fait par la merveilleuse communauté des développeurs (leur travail est super).
La difficulté est arrivée pour installer platformio sur nos machines et gérer les liens afin de pouvoir exécuter en ligne de commande les commandes de compilation et de test du projet.

Pour éviter cette étape d'édition de lien fastidieuse à toute l'équipe, on a écrit un script pour mettre en place ces liens (après que tous les membres aient installé platformio). cf [link_platformio.sh](./scripts/link_platformio.sh).\
Le `exit 0` est là pour éviter une erreur lors du pre-commit une fois que l'édition de lien a déjà été faite une première fois. Il faut donc être vigilant lors du premier commit réalisé pour ne pas manquer les erreurs possibles de ce script.

## Abstraction de l'OS

Nous avions besoin de pouvoir lancer le programme à la fois sur la carte (stm32f4Discovery) et sur notre ordinateur (native). Ce besoin est né lorsque nous avons pris la décision de lancer nos tests unitaires sur nos machines plutôt que sur la carte.

Afin de permettre la flexibilité de changer l'environnement sur lequel notre programme est exécuté, nous avons dû séparer les méthodes spécifiques à l'OS de la carte et l'OS de nos ordinateurs.

Dans un premier temps, nous avons défini la structure des méthodes qui seront implémentées de manière différentes suivant l'environnement utilisé. Ces commandes fondamentales permettent notamment :

* d’initialiser le système d’exploitation
* de lancer le système (démarrage du noyau)
* de créer un délai (delay)
* de créer un mutex
* d’acquérir et de libérer ce mutex
* de réinitialiser la mesure du temps
* de créer un thread
* de récupérer l’heure courante

Cette approche modulaire facilite non seulement la maintenance du code, mais aussi son adaptation à différents environnements matériels. Nous avons observé que les différences de paramétrages entre les différents environnements (carte et natif) étaient principalement liées à la gestion des threads et des mutex. En effet, la carte STM32F4 dispose de ressources matérielles limitées, ce qui nécessite une gestion plus rigoureuse des threads et des mutex pour éviter les conflits d'accès aux ressources partagées.

### OS de la carte

Le fichier pour l'OS de la carte est [os_manager_cmsisV2.c](./src/embedded/os_manager_cmsisV2.c)

Ce fichier s’appuie sur la bibliothèque CMSIS‑RTOS v2, ce qui nous a permis de réutiliser de nombreux blocs fonctionnels, tels que :

* l’initialisation et le démarrage de l’OS
* la création de threads et de mutex
* la gestion des attributs spécifiques aux threads et aux mutex

En plus de ces blocs fonctionnels, nous avons également dû implémenter certaines méthodes spécifiques de la bibliothèque standard C dont nous n'avions pas accès sur la carte. cf [hardware.c](./src/embedded/hardware.c) pour plus de détails.

### OS natif

Le fichier pour l'OS natif est [os_manager_native.c](./src/native/os_manager_native.c)

Ce fichier utilise la bibliothèque pthread, qui est une bibliothèque POSIX pour la gestion des threads. Cette bibliothèque est largement utilisée dans les systèmes d'exploitation de type Unix et Linux, ce qui en fait un choix idéal pour notre environnement de développement natif puisque nous étions tous sur Mac-OS ou Linux.

Nous avons également utilisé la bibliothèque `time.h` pour gérer les délais et la mesure du temps. Cette bibliothèque fournit des fonctions pour manipuler le temps et les dates, ce qui est essentiel pour notre projet.

### Gestion des threads

Au cours des premières phases du projet, nous avons été confrontés à un problème lors de la gestion des threads : les threads ne se rendaient pas la main successivement pour un mutex commun donné. Après consultation de la documentation, nous avons compris qu’il était indispensable d’appeler la méthode `osThreadYield()` à la fin de la méthode `release_mutex()` pour donner le mutex au prochain thread en attente. Sinon le thread venant de libérer le mutex le reprenait imédiatement. Ce qui gênait le bon fonctionnement de notre programme.

## Revirement de situation

Au vue de nos nombreux problèmes lorsque nous lancions le programme sur la carte. Nous avons décidé de lancer le programme sur l'environnement natif pour la compétition au lieu de le lancer sur la carte. Cette décision a demandé un travail supplémentaire pour adapter la communication serveur à l'environnement natif, mais elle nous a permis de nous concentrer sur la logique du jeu plutôt que sur les détails de nos soucis liés à l'exécution sur la carte.

Pour adapter cette communication, nous avons remplacé le fonctionnement du code fourni par notre enseignant servant à faire le lien entre le servuer et les messages envoyés par la caarte sur le port série. Nous avons donc déclaré la connection socket client en C dans le code natif remplaçant ce fonctionnement. cf `os_initialisation()` dans [os_manager_native.c](./src/native/os_manager_native.c) et les méthodes définies dans [socket.h](./src/native/socket.h) pour plus de détails.

La gestion des chaines de caractères est devenue bien plus importante lors de la mise en place de cette communication. Nous avons donc implémenté quelques méthodes pour les gérer de manière efficace. cf [string.c](./src/string.c) pour plus de détails. Ces méthodes ont été implémentées de manière à fonctionner aussi sur la carte, puisque non dépendantes de librairie spécifiques à l'environnement natif.

## Lancer le jeu en local

Plusieurs étapes sont nécessaires pour lancer le jeu en local :

1. Activer l'environnement virtuel Python
2. Définir un port pour le serveur
3. Récupérer le port de la carte STM32 pour la liaison série
4. Lancer le serveur de jeu
5. Lancer le viewer
6. Établir la communication série entre le serveur et le port série

Pour faciliter son lancement dans différents contextes (local, debug ou compétition), plusieurs scripts ont été mis en place.

Ces scripts automatisent :

* La gestion des connexions réseau et série
* Le démarrage des serveurs et du viewer
* La configuration dynamique des ports

### Fonctionnement en local

#### Environnement de la carte

En utilisant le script [start.sh](./scripts/start.sh), le lancement du jeu sur la carte STM32 se déroule en plusieurs étapes.

Prérequis : l'environnement virtuel Python est activé. (le script sera lancé depuis l'environnement virtuel Python)

Ensuite, un port TCP est généré dynamiquement grâce à la fonction random de Python. Le script récupère également le port physique sur lequel la carte STM32 est connectée.
Ce port est définit dans un fichier conf.properties ainsi que d'autres constantes spécifiques à l'environnement ou à la partie lancée.

```properties
serial=/dev/tty.usbserial-AD0K93ZF
address=192.168.43.152
port=50724
teamname=OrganisationKaotik
```

Lancez le serveur de jeu avec la commande `python -m space_collector.game.server -p $PORT --timeout 10`

Puis, la fenêtre du jeu s'ouvre avec : `python -m space_collector.viewer -p $PORT --small-window`

Une fois le serveur et l'interface graphique opérationnels, la communication série-TCP est établie à l'aide de la commande : `python -m space_collector.serial2tcp -p $PORT --serial $SERIAL --team-name "OrganisationKaotik"`

Cette communication est indispensable : elle permet de recevoir les données du jeu (comme l'état ou la position du vaisseau) et d’envoyer nos commandes (tir, déplacement, etc.).
Sans cette passerelle série vers TCP, aucune interaction avec le jeu n’est possible, ce qui entraînerait une défaite certaine.

#### Environnement natif

Suite à nos problèmes avec l'exécution du programme sur la carte, on a choisi d'exécuter le programme sur l'environnement natif.

On a donc défini un nouveau script [start_native.sh](./scripts/start_native.sh) qui permet de lancer le jeu en local sur l'environnement natif (sans la carte STM32) très similaire au script [start.sh](./scripts/start.sh).

#### Lancement pour la compétition

Pour la compétition nous n'hébergeons pas le serveur de jeu sur notre machine, mais sur un serveur distant. Le script [start_competition.sh](./scripts/start_competition.sh) permet de lancer le viewer et d'établir la communication série-TCP avec le serveur distant.

Ce script :

* Extrait dynamiquement l'ADDRESS, le PORT et le TEAMNAME depuis le fichier conf.properties
* Le script ouvre la fenêtre du jeu (space_collector.viewer) avec l'ADDRESS et le PORT indiqués.
* Après un court délai (sleep 3), il exécute le programme natif compilé en lui passant l'ADDRESS, le PORT et le TEAMNAME pour établir la communication via socket.

## Debug sur l'environnement native

Le besoin de debogger sur l'environnement native s'est fait sentir lorsqu'on a décidé d'exécuter notre programme sur cet environnement pour la compétition.
Ca s'est fait assez rapidement, Visual Studio Code propose des configuration de debug pour le C. Il fallait configurer comme il faut pour appeler notre exécutable `/.pio/build/native/program` et lui renseigner les arguments dont on a besoin. Pour être sûr d'avoir la dernière version compilée, on peut choisir de build avec platformio avant l'exécution du programme. \
Exemple :

```json
{
    "name": "(lldb) Debug native",
    "type": "cppdbg",
    "request": "launch",
    "program": "${workspaceFolder}/.pio/build/native/program",
    "args": [
        "localhost",
        "2000",
        "OrganisationKaotik"
    ],
    "stopAtEntry": false,
    "cwd": "${fileDirname}",
    "environment": [],
    "externalConsole": false,
    "MIMode": "lldb",
    "preLaunchTask": "PlatformIO: Build (native)"
}
```

 Nous avons donc adapté le script [start_native.sh](./scripts/start_native.sh) pour pouvoir renseigner ces paramètres par défaut simplement lors de l'appel du script en rajoutant des conditions afin de modifier le comportement lorsqu'on renseigne "debug" en paramètre de la commande.

## Nos Erreurs

Au cours de ce projet, nous avons fait face à plusieurs défis majeurs, particulièrement lors du lancement de l'OS sur la carte. Ces obstacles étaient principalement dus à deux facteurs :

* Notre manque de connaissance
* Une mauvaise gestion

Avec du recul, nous aurions dû suivre les conseils de notre enseignant concernant la réalisation de tests réguliers sur la carte.
Cette négligence nous a coûté cher : à quelques jours de la compétition, notre système ne fonctionnait que partiellement.
Malgré la mise en place de tests unitaires sur l'environnement natif, nous avons constaté que lorsque nous lançions le programme sur la carte tout ne fonctionnait pas comme prévu...
Nous avons donc dû nous concentrer sur la résolution de problèmes liés à l'OS, tels que la gestion des threads et des mutexes. Ces éléments étaient cruciaux pour le bon fonctionnement de notre système, mais leur complexité a entraîné des retards importants dans notre avancement.

## Notions apprises

Nous avons appris à gérer les threads et les mutexes de manière efficace.

En mettant en place des méthodes éprouvées de clean architecture et de séparation des préoccupations, nous avons pu créer un système plus modulaire et flexible. Cela nous a permis de nous adapter rapidement aux changements liés à nos erreurs.

Nous avons également pris conscience de l'importance de la gestion des ressources dans un environnement contraint, comme celui de la carte STM32F4. La nécessité de gérer les threads et les mutex de manière rigoureuse nous a permis d'acquérir une compréhension plus approfondie des systèmes embarqués et de leurs défis.
