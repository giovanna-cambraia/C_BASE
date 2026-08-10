#include <stdio.h>

int main()
{
    int ammo = 110;
    int ammoPerWave = 20;
    int hordeWaveCount = 0;

    do
    {
        if (ammo >= ammoPerWave)
        {
            printf("Horde incoming!\n");
            ammo = ammo - ammoPerWave;
            printf("Horde cleared out. Ammo remaining: %d\n", ammo);
            hordeWaveCount++;
        }
        else
        {
            printf("Out of ammo! Run away.\n");
            break;
        }

    } while (ammo != 0);

    printf("St. John handled %d waves before zeroing out.", hordeWaveCount);

    return 0;
}

// ? Gamey-like code! You have 100 bullets and face waves of zombies. Each wave costs a random-ish (or fixed, to start) number of bullets to clear. Loop through waves, 
// ? subtracting ammo each time, and stop — printing "Out of ammo!" — the moment you can't afford the next wave.