#ifndef STRATEGIE_H
#define STRATEGIE_H

#include "base.h"
#include "os_manager.h"
#include "planet.h"
#include "spaceship.h"
#include <stdint.h>

void manage_spaceship_radar(int8_t ship_id, int8_t ship_id_reference, Spaceship_t* spaceships, Base_t* base);
void manage_spaceship_collector(int8_t ship_id, Spaceship_t* spaceships, Base_t* base, Planet_t* planet);
void manage_spaceship_attacker(int8_t ship_id, int8_t ship_ref_id, Spaceship_t* spaceships, Base_t* base);

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

#endif // __STRATEGIE_H__
