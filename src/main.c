/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions * =============================================================== */

#include "bsp.h"
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions * ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

int main(void) {
  //SisTick_Init(1000);
  //SysTick_Config(1000);

  int reloj_activado = 0;
  int divisor = 0;

  uint8_t d0 = 0;
  uint8_t d1 = 0;
  uint8_t d2 = 0;
  uint8_t d3 = 0;
  board_t board = BoardCreate();
  

  // -- Infinite loop
  while (true){

    // testing de salida de loop
    divisor++;
    if (divisor == 10) {
      divisor = 0;
      DigitalOutputToggle(board->led_verde);

      if(d0 < 9) d0++;
      else {
        d0=0;
        if(d1 < 9) d1++;
        else {
          d1=0;
          if(d2 < 9) d2++;
          else {
            d2=0; 
            if(d3 < 9) d3++;
            else d3=0;
          }
        }
      }
    }
    // -------------------------

    if(DigitalInputHasActivated(board->accept)){
      reloj_activado = 1;
    }
    
    if(DigitalInputHasActivated(board->cancel)){
      reloj_activado = 0;
    }

    if (reloj_activado)
      DisplayWriteBCD(board->display, (uint8_t[]){d0,d1,d2,d3},4);
    else 
      DisplayWriteBCD(board->display, NULL, 0);


    if(DigitalInputHasActivated(board->set_time)){
      
    }
    if(DigitalInputHasActivated(board->set_alarm)){
      
    }
    if(DigitalInputHasActivated(board->decrement)){
      
    }

    //prueba de buzzer (enciende led)
    if (DigitalInputRead(board->increment)){
      DigitalOutputActivate(board->buzzer);
    } else {
      DigitalOutputDeactivate(board->buzzer);
    }


    if(DigitalInputHasActivated(board->increment)){
    
    }

    DisplayRefresh(board->display);


    //Retardo de tiempo
    for (int index = 0; index < 100; index++) {
      for (int delay = 0; delay < 300; delay++) {
        __asm("NOP");
      }
    }
  }

}
/*
void SysTick_Handler(void){
      DisplayRefresh(board->display);
}
*/

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
