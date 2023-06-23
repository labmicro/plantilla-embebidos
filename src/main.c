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
#include "reloj.h"
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions * ==================================================================== */

#define REFRESH_TIME 1000

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void SisTick_Init(uint32_t time);

/* === Public variable definitions ============================================================= */

static board_t board;
static clock_t reloj;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

int main(void) {
	int reloj_activado = 0;

	uint8_t hora[CLOCK_SIZE];

	reloj = ClockCreate(REFRESH_TIME / 1000);
	board = BoardCreate();

	SisTick_Init(REFRESH_TIME);

	// -- Infinite loop
	while (true) {

		// -------------------------

		if (DigitalInputHasActivated(board->accept)) {
			reloj_activado = 1;
		}

		if (DigitalInputHasActivated(board->cancel)) {
			reloj_activado = 0;
		}

		if (DigitalInputHasActivated(board->set_time)) {
			// DisplayFlashDigits(board->display, 1, CLOCK_SIZE, 100);
		}

		if (DigitalInputHasActivated(board->set_alarm)) {
		}

		if (DigitalInputHasActivated(board->decrement)) {
		}

		if (DigitalInputHasActivated(board->increment)) {
		}
		DisplayFlashDigits(board->display, 0, CLOCK_SIZE, 100);
		// DisplayRefresh(board->display);

		// Retardo de tiempo
		for (int index = 0; index < 100; index++) {
			for (int delay = 0; delay < 300; delay++) {
				__asm("NOP");
			}
		}

		ClockGetTime(reloj, hora, CLOCK_SIZE);
		__asm volatile("cpsid i");
		DisplayWriteBCD(board->display, hora, CLOCK_SIZE);
		__asm volatile("cpsie i");
	}
}

void SysTick_Handler(void) {
	DisplayRefresh(board->display);
	ClockRefresh(reloj, CLOCK_SIZE);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
