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
    digital_output_t led_RGB_rojo;
    digital_output_t led_RGB_verde;
    digital_output_t led_RGB_azul;
    digital_output_t led_rojo;
    digital_output_t led_verde;
    digital_output_t led_amarillo;

    digital_input_t tec_1;
    digital_input_t tec_2;
    digital_input_t tec_3;
    digital_input_t tec_4;
} const * const board_t;

/*---  Public Function Declaration  ------------------------------------------------------------ */

board_t BoardCreate(void);

/*---  End of File  ---------------------------------------------------------------------------- */
#endif
