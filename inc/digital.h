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
typedef struct digital_input_s * digital_input_t; 

/*---  Definitions  ---------------------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

// Soporte de Salidas
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);

void DigitalOutputActivate (digital_output_t output);

void DigitalOutputDeactivate (digital_output_t output);

void DigitalOutputToggle (digital_output_t output);


// Soporte de Entradas
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin);

bool DigitalInputRead(digital_input_t input);


/*---  End of File  ---------------------------------------------------------------------------- */
#endif
