//---  Code Information ------------------------------------------------------------------------ */
// Autor: Jassan, Joel
// Date: may/2023
//
/*---------------------------------------------------------------------------------------------- */

#include "digital.h"
#include "chip.h"

/*---  Includes  ------------------------------------------------------------------------------- */

/*---  Macros and Definitions  ----------------------------------------------------------------- */

#ifndef OUTPUT_INSTANCES
    #define OUTPUT_INSTANCES 4
#endif

/*---  Private Data Declaration  --------------------------------------------------------------- */

struct digital_output_s{
    uint8_t port;
    uint8_t pin;
    bool allocated;
};

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------ */

/*---  Private Function Implementation  -------------------------------------------------------- */

digital_output_t DigitalOutputAllocate (void) {
    digital_output_t output = NULL;

    static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

    for(int index = 0; index < OUTPUT_INSTANCES; index++) {
        if (!instances[index].allocated) {
            instances[index].allocated = true;
            output = &instances[index];
            break;
        }
    }

    return output;
}


/*---  Public Function Implementation  --------------------------------------------------------- */

digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin){
    digital_output_t output = DigitalOutputAllocate();

    if (output) {
        output->port = port;
        output->pin = pin;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->port, output->pin, true);
    }

    return output;
}

void DigitalOutputActivate (digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, true);
}

void DigitalOutputDeactivate (digital_output_t output){
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->port, output->pin, false);
}

void DigitalOutputToggle (digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);
}