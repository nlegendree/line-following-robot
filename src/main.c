#include "controller.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open(eventPath(), O_RDONLY);
    //...

    return 0;
}