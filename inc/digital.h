/*---  Header Information ---------------------------------------------------------------------- */
// Autor: Jassan, Joel
// Date: 
//
/*---------------------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>

#ifndef DIGITAL_H
#define DIGITAL_H


/*---  Includes  ------------------------------------------------------------------------------- */

/*---  Macros  --------------------------------------------------------------------------------- */
typedef struct digital_output_s * digital_output_t; 

/*---  Definitions  ---------------------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);

void DigitalOutputActivate (digital_output_t output);

void DigitalOutputDeactivate (digital_output_t output);

void DigitalOutputToggle (digital_output_t output);


/*---  End of File  ---------------------------------------------------------------------------- */
#endif
