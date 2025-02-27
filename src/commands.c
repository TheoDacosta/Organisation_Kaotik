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
 * @brief Envoie une commande et récupère la réponse.
 *
 * @param command Commande à envoyer.
 * @param response Réponse à récupérer.
 */
void send_command(char* command, char* response)
{
    if (command[0] != '\0') {
        get_mutex(serial_mutex);
        puts(command);
        gets(response);
        release_mutex(serial_mutex);
    }
}
