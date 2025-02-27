#ifndef STRATEGY_H
#define STRATEGY_H

#include "base.h"
#include "os_manager.h"
#include "planet.h"
#include "spaceship.h"
#include <stdint.h>
void manage_spaceship_radar(Spaceship_t* space, Spaceship_t* space_ref, Base_t* base, char* command);
void manage_spaceship_collector(Spaceship_t* space, Spaceship_t* space_ref, Base_t* base, char* command);
void manage_spaceship_attacker(Spaceship_t* space, Spaceship_t* space_ref, Spaceship_t* space_ships, Base_t* base, char* command);

// Le je dois faire quoi exactement ?
// Je dois créer des commandes de déplacement, de tir et
// de radar pour les vaisseaux.
// comment je vais mis prendre ?
// première conditions dire ssi le vaiseau est broke il retourne à la base
// dans le cas ou il est pas cassé on vas tchek son id en gros on sai que
// les attauqants 1 à 3 sont assimilé au collecteur  - > lui dire de suivre le ship id 7
// les attaquants 4 et 5 sont assimilé au 2 - > lui dire de suivre le ship id 8
// les explorateurs 1 et 2 ont  ne sais pas encore
// On dois gérer la cas  es tirs ! Dans le cas
// Il est dans une certaine IDBOX donc porté de tir il vas simplement s'orienter vers le vaisseau enemie et tirer

// En terme de commade il me faut quoi
// -> il me faut les différentes commandes de déplacement
// -> il me faut les différentes commandes de tir
// la commande est en vie

#endif // __STRATEGY_H__
