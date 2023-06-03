/*---  Header Information ---------------------------------------------------------------------- */
// Autor: Jassan, Joel
// Date:
//
// Header: Hardware Abstration Layer declaration
/*---------------------------------------------------------------------------------------------- */



#ifndef BSP_H
#define BSP_H

/*---  Includes  ------------------------------------------------------------------------------- */

#include "digital.h"

/*---  Macros  --------------------------------------------------------------------------------- */

/*---  Definitions  ---------------------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

typedef struct board_s {
    digital_output_t buzzer;
    digital_input_t set_time;
    digital_input_t set_alarm;
    digital_input_t decrement;
    digital_input_t increment;
    digital_input_t accept;
    digital_input_t cancel;
} const * const board_t;

/*---  Public Function Declaration  ------------------------------------------------------------ */

board_t BoardCreate(void);

/*---  End of File  ---------------------------------------------------------------------------- */
#endif
