//---  Code Information ------------------------------------------------------------------------ */
// Autor: Jassan, Joel
// Date: may/2023
//
/*---------------------------------------------------------------------------------------------- */

#include "digital.h"
#include "chip.h"

/*---  Includes  ------------------------------------------------------------------------------- */

/*---  Macros and Definitions  ----------------------------------------------------------------- */

/*---  Private Data Declaration  --------------------------------------------------------------- */

struct digital_output_s{
    uint8_t port;
    uint8_t pin;
};

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------ */

/*---  Private Function Implementation  -------------------------------------------------------- */

/*---  Public Function Implementation  --------------------------------------------------------- */

digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin){
    static struct digital_output_s output;

    output.port = port;
    output.pin = pin;
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, output.port, output.pin, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output.port, output.pin, true);

    return &output;
}

void DigitalOutputActivate (digital_output_t output){

}

void DigitalOutputDeactivate (digital_output_t output){

}

void DigitalOutputToggle (digital_output_t output){
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->port, output->pin);
}