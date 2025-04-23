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

## Scripts et automatisations

### Script de pre-commit

cf [.pre-commit-config.yaml](.pre-commit-config.yaml)

Lorsque l'on commit, nous vérifions des règles classiques d'espaces à la fin d'une ligne, ligne vide à la fin d'un fichier et l'ajout de fichiers volumineux. Ajouté à ceci un linter et formatteur pour le language C, prédominant dans ce projet.\
Ces vérifications sont gérées par l'appel de hooks déjà fait par la merveilleuse communauté des développeurs (leur travail est super).
La difficulté est arrivée pour installer platformio sur nos machines et gérer les liens afin de pouvoir exécuter en ligne de commande les commandes de compilation et de test du projet.

Pour éviter cette étape d'édition de lien fastidieuse à toute l'équipe, on a écrit un script pour mettre en place ces liens (après que tous les membres aient installé platformio). cf [link_platformio.sh](./scripts/link_platformio.sh).\
Le `exit 0` est là pour éviter une erreur lors du pre-commit une fois que l'édition de lien a déjà été faite une première fois. Il faut donc être vigilant lors du premier commit réalisé pour ne pas manquer les erreurs possibles de ce script.

### Lancer le jeu en local

...@Movic16

### Debug sur l'environnement native

Le besoin de debogger sur l'environnement native s'est fait sentir lorsqu'on a décidé d'exécuter notre programme sur cet environnement pour la compétition.
ça s'est fait assez rapidement, Visual Studio Code propose des configuration de debug pour le C. Il fallait configurer comme il faut pour appeler notre exécutable `/.pio/build/native/program` et lui renseigner les arguments dont on a besoin. Pour être sûr d'avoir la dernière version compilée, on peut choisir de build avec platformio avant l'exécution du programme. \
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

## Abstraction de l'OS

Nous avions besoin de pouvoir lancer le programme à la fois sur la carte (stm32f4Discovery) et sur notre ordinateur (native). Ce besoin est né lorsque nous avons pris la décision de lancer nos tests unitaires sur nos machines plutôt que sur la carte.

Afin de permettre la flexibilité de changer l'environnement sur lequel notre programme est exécuté, nous avons dû séparer les méthodes spécifiques à l'OS de la carte et l'OS de nos ordinateurs.

... et @TheoDacosta

Bien sûr ! Voici une reformulation améliorée et enrichie de ton texte, avec une meilleure fluidité et des transitions plus naturelles :

---

Dans un premier temps, nous avons défini un ensemble de méthodes communes aux deux environnements visés. Ces commandes fondamentales permettent notamment :

- d’initialiser le système d’exploitation,
- de lancer le système (démarrage du noyau),
- de créer un délai (delay),
- de créer un mutex,
- d’acquérir et de libérer ce mutex,
- de réinitialiser la mesure du temps,
- de créer un thread,
- de récupérer l’heure courante.

L’ensemble de ces prototypes a été déclaré dans un fichier commun, servant de base pour l’implémentation multi-environnement. Pour aller plus loin, nous avons ensuite créé un second fichier, nommé "os_manager_cmsisV2.c", spécifiquement dédié à l’implémentation de l’OS sur la carte cible.

Ce fichier s’appuie sur la bibliothèque CMSIS‑RTOS v2, ce qui nous a permis de réutiliser  de nombreux blocs fonctionnels , tels que :

- l’initialisation et le démarrage de l’OS,
- la création de threads et de mutex,
- la gestion des attributs spécifiques aux threads et aux mutex.

Cette approche modulaire facilite non seulement la maintenance du code, mais aussi son adaptation à différents environnements matériels. Nous aborderons d’ailleurs plus en détail, dans la suite du rapport, la question cruciale de la taille de la pile (stack). En effet, nous avons observé que celle-ci doit impérativement être comprise entre 1024 et 2048 octets : en dehors de cette plage, le système d’exploitation ne démarre pas correctement, ce qui souligne l’importance d’un paramétrage précis.

Au cours des premières phases du projet, nous avons également été confrontés à un dysfonctionnement lors de la gestion des threads : lorsque nous augmentions leur nombre, seul le dernier thread  était  exécuté. Après consultation de la documentation, nous avons compris qu’il était indispensable d’appeler la fonction osThreadYield() à la fin de la fonction release_mutex(). Cette instruction permet de rendre la main au noyau, assurant ainsi une véritable planification multitâche et une meilleure répartition de l’exécution entre les différents threads.

Par ailleurs, afin de limiter les risques de bugs liés à l’utilisation des bibliothèques standard, nous avons fait le choix de concevoir nos propres fonctions bas niveau. Celles-ci ont été regroupées dans le fichier "hardware.c". Ce dernier centralise l’ensemble des routines essentielles à la gestion matérielle, notamment :

- l’initialisation des horloges,
- la configuration des entrées/sorties,
- la gestion des délais et des interruptions,
- la récupération et l’écriture d’informations sur la liaison série,
- l’initialisation de la graine du générateur pseudo-aléatoire (PRNG),
- la conversion d’un entier en chaîne de caractères.

Cette organisation rigoureuse du code assure une meilleure robustesse et une plus grande maîtrise du fonctionnement global du système, tout en facilitant les évolutions futures du projet.



## Nos Erreurs

Au cours de ce projet, nous avons fait face à plusieurs défis majeurs, particulièrement lors du lancement de l'OS sur la carte. Ces obstacles étaient principalement dus à deux facteurs :

- Notre manque de  connaissance
- Une mauvaise gestion

Avec du recul, nous aurions dû suivre les conseils de notre enseignant concernant la réalisation de tests réguliers.

Cette négligence nous a coûté cher : à quelques jours de la compétition, notre système ne fonctionnait que partiellement.

Cette situation critique nous a forcés à revoir entièrement certains parites  dans l'urgence.

Une refonte complète était nécessaire pour atteindre les niveaux de stabilité et de performance requis pour la compétition. Cette expérience nous a enseigné l'importance cruciale des tests réguliers dans le développement de systèmes embarqués.


## Notions apprises

...
