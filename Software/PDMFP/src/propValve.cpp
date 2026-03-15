#include "propValve.h"
#include <Arduino.h>

// Define prop valve pins here

void updatePropValves(float DC1, float DC2) {
    // unsure what this code looks like at the moment, so left here as placeholder.
    analogWrite(A0, DC1);
    analogWrite(A1, DC2);
    return;
}