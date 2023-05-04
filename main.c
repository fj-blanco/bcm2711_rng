#include <stdio.h>
#include "bcm2711_rng.h"

int main(void)
{
    init_bcm_rand();
    for (int i = 0; i < 10; i++)
    {
        printf("Random number: %u\n", bcm_rand32());
    }
    return 0;
}