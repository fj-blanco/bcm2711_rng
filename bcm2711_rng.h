#ifndef BCM2711_RNG_H
#define BCM2711_RNG_H

#include <stdint.h>

void init_bcm_rand(void);
uint32_t bcm_rand32(void);

#endif // BCM2711_RNG_H