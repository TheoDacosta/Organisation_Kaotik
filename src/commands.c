#include "commands.h"
#include "hardware.h"
#include "os_manager.h"
#include "trajectory.h"

Mutex_t serial_mutex;

void build_command(char* dest, char* command, int args[], int nb_args)
{
    while (*command != '\0') {
        *dest = *command;
        dest++;
        command++;
    }
    for (int i = 0; i < nb_args; i++) {
        *dest = ' ';
        dest++;
        itoa(args[i], dest, 10);
        while (*dest != '\0') {
            dest++;
        }
    }
    *dest = '\n';
    dest++;
    *dest = '\0';
}

/**
 * @brief Crée une commande de déplacement.
 *
 * @param ship_id Identifiant du vaisseau.
 * @param angle Angle de déplacement.
 * @param speed Vitesse de déplacement.
 * @param buffer Chaine de caractère representant la commande.
 */
void create_move_command(int8_t ship_id, uint16_t angle, uint16_t speed, char* buffer)
{
    char* command = "MOVE";
    int args[] = { ship_id, angle, speed };
    build_command(buffer, command, args, 3);
}

/**
 * @brief Crée une commande de tir.
 *
 * @param ship_id Identifiant du vaisseau.
 * @param angle Angle de tir.
 * @param buffer Chaine de caractère representant la commande.
 */
void create_fire_command(int8_t ship_id, uint16_t angle, char* buffer)
{
    char* command = "FIRE";
    int args[] = { ship_id, angle };
    build_command(buffer, command, args, 2);
}

/**
 * @brief Creer une commande de radar.
 *
 * @param ship_id Identifiant du vaisseau.
 * @param buffer Chaine de caractère representant la commande.
 */
void create_radar_command(int8_t ship_id, char* buffer)
{
    char* command = "RADAR";
    int args[] = { ship_id };
    build_command(buffer, command, args, 1);
}

/**
 * @brief Envoie une commande de déplacement.
 *
 * @param ship_id Identifiant du vaisseau.
 * @param angle Angle de déplacement.
 * @param speed Vitesse de déplacement.
 */
void send_move_command(int8_t ship_id, uint16_t angle, uint16_t speed)
{
    char buffer[100];
    create_move_command(ship_id, angle, speed, buffer);
    if (buffer[0] != '\0') {
        get_mutex(serial_mutex);
        puts(buffer);
        gets(buffer);
        release_mutex(serial_mutex);
    }
}

/**
 * @brief Envoie une commande de tir.
 *
 * @param ship_id Identifiant du vaisseau.
 * @param angle Angle de tir.
 * @param buffer Chaine de caractère representant la commande.
 */
void send_fire_command(int8_t ship_id, uint16_t angle)
{
    char buffer[100];
    create_fire_command(ship_id, angle, buffer);
    if (buffer[0] != '\0') {
        get_mutex(serial_mutex);
        puts(buffer);
        gets(buffer);
        release_mutex(serial_mutex);
    }
}

/**
 * @brief Creer une commande de radar.
 *
 * @param ship_id Identifiant du vaisseau.
 */
void send_radar_command(int8_t ship_id, char* response)
{
    char buffer[100];
    create_radar_command(ship_id, buffer);
    if (buffer[0] != '\0') {
        get_mutex(serial_mutex);
        puts(buffer);
        gets(response);
        release_mutex(serial_mutex);
    }
}

/**
 * @brief Verifie si l'angle est valide.
 *
 * @param angle Angle à vérifier.
 * @return 1 si l'angle est valide, 0 sinon.
 */
uint8_t is_valid_angle(uint16_t angle)
{
    return angle <= MAX_ANGLE;
}

/**
 * @brief Verifie si l'identifiant du vaisseau est valide.
 *
 * @param ship_id Identifiant du vaisseau à vérifier.
 * @return 1 si l'identifiant est valide, 0 sinon.
 */
uint8_t is_valid_id_spaceship(int8_t ship_id)
{
    return ship_id > 0 && ship_id <= MAX_SHIP_ID;
}

/**
 * @brief Verifie si la vitesse est valide.
 *
 * @param speed Vitesse à vérifier.
 * @param ship_id Identifiant du vaisseau.
 * @return 1 si la vitesse est valide, 0 sinon.
 */
uint8_t is_valid_speed(uint16_t speed, uint8_t ship_id)
{
    if (ship_id <= 5) {
        return speed <= MAX_ATTACKERS_SPEED;
    } else if (ship_id <= 7) {
        return speed <= MAX_EXPLORERS_SPEED;
    } else {
        return speed <= MAX_COLLECTORS_SPEED;
    }
}
