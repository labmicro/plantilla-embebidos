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

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

board_t BoardCreate(void) {
    Chip_SCU_PinMuxSet(LED_R_PORT, LED_R_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_R_FUNC);
    board.led_RGB_rojo = DigitalOutputCreate(LED_R_GPIO,LED_R_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(LED_G_PORT, LED_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_G_FUNC);
    board.led_RGB_verde = DigitalOutputCreate(LED_G_GPIO,LED_G_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(LED_B_PORT, LED_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_B_FUNC);
    board.led_RGB_azul = DigitalOutputCreate(LED_B_GPIO,LED_B_BIT, inverted_logic);

    /******************/
    Chip_SCU_PinMuxSet(LED_1_PORT, LED_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_1_FUNC);
    board.led_rojo = DigitalOutputCreate(LED_1_GPIO,LED_1_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(LED_2_PORT, LED_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_2_FUNC);
    board.led_amarillo = DigitalOutputCreate(LED_2_GPIO,LED_2_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(LED_3_PORT, LED_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_3_FUNC);
    board.led_verde = DigitalOutputCreate(LED_3_GPIO, LED_3_BIT, inverted_logic);

    /******************/
    Chip_SCU_PinMuxSet(TEC_1_PORT, TEC_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_1_FUNC);
    board.tec_1 = DigitalInputCreate(TEC_1_GPIO, TEC_1_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(TEC_2_PORT, TEC_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_2_FUNC);
    board.tec_2 = DigitalInputCreate(TEC_2_GPIO, TEC_2_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(TEC_3_PORT, TEC_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_3_FUNC);
    board.tec_3 = DigitalInputCreate(TEC_3_GPIO, TEC_3_BIT, inverted_logic);

    Chip_SCU_PinMuxSet(TEC_4_PORT, TEC_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_4_FUNC);
    board.tec_4 = DigitalInputCreate(TEC_4_GPIO, TEC_4_BIT, inverted_logic);

    return &board;
}

/*---  Public Function Implementation  --------------------------------------------------------- */

/*---  End of File  ---------------------------------------------------------------------------- */