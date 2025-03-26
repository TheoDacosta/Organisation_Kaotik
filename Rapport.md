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

... @LouisGresta

## Abstraction de l'OS

Nous avions besoin de pouvoir lancer le programme à la fois sur la carte (stm32f4Discovery) et sur notre ordinateur (native). Ce besoin est né lorsque nous avons pris la décision de lancer nos tests unitaires sur nos machines plutôt que sur la carte.

Afin de permettre la flexibilité de changer l'environnement sur lequel notre programme est exécuté, nous avons dû séparer les méthodes spécifiques à l'OS de la carte et l'OS de nos ordinateurs.

...@Debugsvg et @TheoDacosta

## Nos Erreurs

...

## Notions apprises

...
