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

//! Estructura que almacena los descriptores de la bsp
typedef struct board_s {
    digital_output_t led_RGB_rojo;  //!< Denotado R
    digital_output_t led_RGB_verde; //!< Denotado G
    digital_output_t led_RGB_azul;  //!< Denotado B
    digital_output_t led_amarillo;  //!< Denotado LED 1 en placa
    digital_output_t led_rojo;      //!< Denotado LED 2 en placa
    digital_output_t led_verde;     //!< Denotado LED 3 en placa

    digital_input_t tec_1;          //!< Denotado TEC 1 en placa
    digital_input_t tec_2;          //!< Denotado TEC 2 en placa
    digital_input_t tec_3;          //!< Denotado TEC 3 en placa
    digital_input_t tec_4;          //!< Denotado TEC 4 en placa
} const * const board_t;

/*---  Public Function Declaration  ------------------------------------------------------------ */

board_t BoardCreate(void);

/*---  End of File  ---------------------------------------------------------------------------- */
#endif
