#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>

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

    closedir(dir);
    return event_path_output; 
}

struct libevdev *initController() {
    struct libevdev *dev = NULL;
    int fd = open(eventPath(), O_RDONLY);
    int rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
        fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
        exit(1);
    }
    return dev;
}

int buttonIsPressed(int BUTTON, struct libevdev *controller,struct input_event ev) {
    return libevdev_event_is_code(&ev, EV_KEY, BUTTON) && libevdev_get_event_value(controller, EV_KEY, BUTTON);
}

int buttonIsReleased(int BUTTON, struct libevdev *controller,struct input_event ev) {
    return libevdev_event_is_code(&ev, EV_KEY, BUTTON) && !libevdev_get_event_value(controller, EV_KEY, BUTTON);
}

int buttonIsBeingPressed(int BUTTON, struct libevdev *controller,struct input_event ev,int *state) {
    int code = libevdev_event_is_code(&ev, EV_KEY, BUTTON);
    int value = libevdev_get_event_value(controller, EV_KEY, BUTTON);
    if (code && value)
        *state = 1;
    else if (code && !value)
        *state = 0;
    return *state;
}

int triggerValue(int TRIGGER, struct libevdev *controller,struct input_event ev,int *state) {
    int code = libevdev_event_is_code(&ev, EV_ABS, TRIGGER);
    int value = libevdev_get_event_value(controller, EV_ABS, TRIGGER);
    if (code && value > 0)
        *state = value;
    else if (code && value == 0)
        *state = 0;
    return *state;
}

int axisValue(int AXIS, struct libevdev *controller,struct input_event ev,int *state) {
    int code = libevdev_event_is_code(&ev, EV_ABS, AXIS);
    int value = libevdev_get_event_value(controller, EV_ABS, AXIS);
    if (code && (value <= (MID_AXIS - DEADZONE) || value >= (MID_AXIS + DEADZONE)))
        *state = value;
    else if (code && (value > (MID_AXIS - DEADZONE) && value < (MID_AXIS + DEADZONE)))
        *state = MID_AXIS;
    return *state;
}