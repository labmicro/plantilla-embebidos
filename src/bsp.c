/*---  Code Information ------------------------------------------------------------------------ */
// Autor: Jassan, Joel
// Date: 
//
// Project: Hardware Abstraction Layer Creation
/*---------------------------------------------------------------------------------------------- */



/*---  Includes  ------------------------------------------------------------------------------- */
#include "chip.h"
#include "bsp.h"
#include "ciaa.h"

/*---  Macros and Definitions  ----------------------------------------------------------------- */


// Control de logica invertida.
// Creo que deberia ir dentro de "digital".
#ifndef inverted_logic
    #define inverted_logic 0
#endif

static struct board_s board = {0};

/*---  Private Data Declaration  --------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

//!Funcion de configuracion del buzzer
void BuzzerInit(void);

//!Funcion de configuracion de las teclas
void KeysInit(void);



/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

void BuzzerInit(void){
    Chip_SCU_PinMuxSet(LED_B_PORT, LED_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_B_FUNC);
    board.buzzer = DigitalOutputCreate(LED_B_GPIO,LED_B_BIT, inverted_logic);
}

void KeysInit(void){
    Chip_SCU_PinMuxSet(TEC_1_PORT, TEC_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_1_FUNC);
    board.accept = DigitalInputCreate(TEC_1_GPIO, TEC_1_BIT, true);

    Chip_SCU_PinMuxSet(TEC_2_PORT, TEC_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_2_FUNC);
    board.cancel = DigitalInputCreate(TEC_2_GPIO, TEC_2_BIT, true);

    Chip_SCU_PinMuxSet(TEC_3_PORT, TEC_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_3_FUNC);
    board.set_time = DigitalInputCreate(TEC_3_GPIO, TEC_3_BIT, true);

    Chip_SCU_PinMuxSet(TEC_4_PORT, TEC_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_4_FUNC);
    board.set_alarm = DigitalInputCreate(TEC_4_GPIO, TEC_4_BIT, true);
}

/*---  Public Function Implementation  --------------------------------------------------------- */

/*---  End of File  ---------------------------------------------------------------------------- */