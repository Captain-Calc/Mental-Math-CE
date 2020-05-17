// convpng v7.2
#include <stdint.h>
#include "MentalMI.h"

#include <fileioc.h>
<<<<<<< HEAD
uint8_t *MentalMI[16] = {
=======
uint8_t *MentalMI[17] = {
>>>>>>> 71192d1... Release version 2.0.0
 (uint8_t*)0,
 (uint8_t*)258,
 (uint8_t*)516,
 (uint8_t*)774,
 (uint8_t*)1032,
 (uint8_t*)1290,
 (uint8_t*)1548,
 (uint8_t*)1806,
 (uint8_t*)2064,
 (uint8_t*)2322,
 (uint8_t*)2580,
 (uint8_t*)2838,
 (uint8_t*)3096,
 (uint8_t*)3354,
 (uint8_t*)3612,
 (uint8_t*)3870,
<<<<<<< HEAD
=======
 (uint8_t*)4128,
>>>>>>> 71192d1... Release version 2.0.0
};

bool MentalMI_init(void) {
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("MentalMI", "r");
    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)MentalMI[0];
    for (i = 0; i < MentalMI_num; i++) {
        MentalMI[i] += data;
    }

    ti_CloseAll();

    return (bool)appvar;
}
