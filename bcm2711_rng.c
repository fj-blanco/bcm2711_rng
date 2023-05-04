#include "bcm2711_rng.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// For BCM2711
#define BCM2711_PERIPHERAL_BASE 0xFE000000
#define BCM2711_RNG_BASE (BCM2711_PERIPHERAL_BASE + 0x00104000)

// Change this to the appropriate base address for your system
#define RNG_BASE_ADDRESS BCM2711_RNG_BASE

static volatile uint32_t *rng_base = NULL;

void *map_rng_registers(void)
{
    int mem_fd;
    void *mapped_rng_base;

    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        perror("Cannot open /dev/mem");
        return NULL;
    }

    mapped_rng_base = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, RNG_BASE_ADDRESS);

    close(mem_fd);

    if (mapped_rng_base == MAP_FAILED)
    {
        perror("mmap failed");
        return NULL;
    }

    return mapped_rng_base;
}

void bcm2711_rng_enable(void)
{
    if (!rng_base)
    {
        fprintf(stderr, "RNG base address not initialized\n");
        exit(1);
    }
    rng_base[0x00 >> 2] |= 0x00000001;
}

uint32_t bcm2711_rng_read(void)
{
    if (!rng_base)
    {
        fprintf(stderr, "RNG base address not initialized\n");
        exit(1);
    }

    // Wait until there's random data available
    do {} while ((rng_base[0x24 >> 2] & (0xFF << 24)) == 0);

    return rng_base[0x20 >> 2];
}

void init_bcm_rand(void)
{
    rng_base = (uint32_t *)map_rng_registers();
    if (!rng_base)
    {
        fprintf(stderr, "Failed to map RNG registers\n");
        exit(1);
    }
    bcm2711_rng_enable();
}

uint32_t bcm_rand32(void)
{
    if (!rng_base)
    {
        fprintf(stderr, "RNG not initialized\n");
        exit(1);
    }
    return bcm2711_rng_read();
}
