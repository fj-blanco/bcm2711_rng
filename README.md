# BCM2711 Hardware Random Number Generator

This repository provides a C implementation for accessing the hardware random number generator on the BCM2711 SoC used in Raspberry Pi 4 devices by directly mapping the memory-mapped I/O (MMIO) registers of the RNG into the user-space process using the /dev/mem device file. The code is based on [this post by bzt](https://forums.raspberrypi.com/viewtopic.php?t=196015), [rst answer](https://forums.raspberrypi.com/viewtopic.php?t=196015#p1741749) and the Raspberry Pi Linux driver: [iproc-rng200.c](https://github.com/raspberrypi/linux/blob/rpi-5.4.y/drivers/char/hw_random/iproc-rng200.c).

The code has been tested on a **Raspberry Pi 4 Model B 4 × Cortex-A72** running **DietPi v8.15 64-bit**.

## Building

To build the example application, run the following command:

```sh
make
```

## Usage
After building the project, run the main executable to see the bcm_rand32 function in action:

```sh
./main
```

You can also include the bcm2711_rng.h header in your own projects to utilize the bcm_rand32 function.