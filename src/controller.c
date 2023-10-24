#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

char *eventPath() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/dev/input/");
    if (dir == NULL) {
        perror("Impossible d'ouvrir le répertoire /dev/input/");
        return NULL;
    }

    char event_path[267];
    char event_name[267];
    char *event_path_output = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "event") != NULL) {
            snprintf(event_path, sizeof(event_path), "/dev/input/%s", entry->d_name);

            // Ouverture du fichier d'événement pour lire son nom
            int fd = open(event_path, O_RDONLY);
            if (fd != -1) {
                //On récupère le nom associé au périphérique
                ioctl(fd, EVIOCGNAME(sizeof(event_name)), event_name);

                // Si la partie du nom correspond à la manette (on prend seulement l'évènement qui correspond aux touches)
                if (strstr(event_name, DEVICE_NAME) != NULL && !(strstr(event_name, "Touchpad") != NULL || strstr(event_name, "Sensors") != NULL)) {
                    event_path_output = strdup(event_path);
                    break;
                }

                close(fd);
            }
        }
    }

    if (event_path_output != NULL)
        printf("%s : %s\n",event_name,event_path_output);

    closedir(dir);
    return event_path_output; 
}