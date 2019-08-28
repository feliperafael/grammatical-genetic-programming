#include "Configures.h"

Configures* conf;


/* Null, because instance will be initialized on demand. */
Configures* Configures::instance = 0;

Configures* Configures::getInstance() {
    if (instance == 0) {
        instance = new Configures();
    }

    return instance;
}

Configures::Configures() {
}
