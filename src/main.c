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

typedef enum {
	SIN_CONFIGURAR,
	MOSTRANDO_HORA,
	AJUSTANDO_MINUTOS_ACTUAL,
	AJUSTANDO_HORAS_ACTUAL,
	AJUSTANDO_MINUTOS_ALARMA,
	AJUSTANDO_HORAS_ALARMA,
} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void SisTick_Init(uint32_t time);

/* === Public variable definitions ============================================================= */

static board_t board;
static clock_t reloj;
static modo_t modo;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void SwitchMode(modo_t valor) {
	modo = valor;
	switch (modo) {
	case SIN_CONFIGURAR:
		DisplayFlashDigits(board->display, 0, 3, 200);
		break;
	case MOSTRANDO_HORA:
		DisplayFlashDigits(board->display, 0, 0, 0);
		break;
	case AJUSTANDO_MINUTOS_ACTUAL:
		DisplayFlashDigits(board->display, 2, 3, 200);
		break;
	case AJUSTANDO_HORAS_ACTUAL:
		DisplayFlashDigits(board->display, 0, 1, 200);
		break;
	case AJUSTANDO_MINUTOS_ALARMA:
		DisplayFlashDigits(board->display, 2, 3, 200);
		DisplayToggleDot(board->display, 0);
		DisplayToggleDot(board->display, 1);
		DisplayToggleDot(board->display, 2);
		DisplayToggleDot(board->display, 3);
		break;
	case AJUSTANDO_HORAS_ALARMA:
		DisplayFlashDigits(board->display, 0, 1, 200);
		DisplayToggleDot(board->display, 0);
		DisplayToggleDot(board->display, 1);
		DisplayToggleDot(board->display, 2);
		DisplayToggleDot(board->display, 3);
		break;
	default:
		break;
	}
}

int main(void) {
	uint8_t entrada[ALARM_SIZE];

	reloj = ClockCreate(REFRESH_TIME);
	board = BoardCreate();

	SisTick_Init(REFRESH_TIME);
	SwitchMode(SIN_CONFIGURAR);

	// -- Infinite loop
	while (true) {

		// -------------------------

		if (DigitalInputHasActivated(board->accept)) {
			if (modo == AJUSTANDO_MINUTOS_ACTUAL) {
				SwitchMode(AJUSTANDO_HORAS_ACTUAL);
			} else if (modo == AJUSTANDO_MINUTOS_ACTUAL) {
				ClockSetTime(reloj, entrada, sizeof(entrada));
				SwitchMode(MOSTRANDO_HORA);
			}
		}

		if (DigitalInputHasActivated(board->cancel)) {
			if (ClockSetTime(reloj, entrada, sizeof(entrada))) {
				SwitchMode(MOSTRANDO_HORA);
			} else {
				SwitchMode(SIN_CONFIGURAR);
			}
		}

		if (DigitalInputHasActivated(board->set_time)) {
			SwitchMode(AJUSTANDO_MINUTOS_ACTUAL);
			ClockGetTime(reloj, entrada, sizeof(entrada));
			DisplayWriteBCD(board->display, entrada, sizeof(entrada));
		}

		if (DigitalInputHasActivated(board->set_alarm)) {
		}

		if (DigitalInputHasActivated(board->decrement)) {
			if (modo == AJUSTANDO_MINUTOS_ACTUAL) {
				entrada[3] = entrada[3] - 1; // falta el carry
			} else if (modo == AJUSTANDO_HORAS_ACTUAL) {
				entrada[1] = entrada[1] - 1; // falta el carry
			}
			DisplayWriteBCD(board->display, entrada, sizeof(entrada));
		}

		if (DigitalInputHasActivated(board->increment)) {
			if (modo == AJUSTANDO_MINUTOS_ACTUAL) {
				entrada[3] = entrada[3] + 1; // falta el carry
			} else if (modo == AJUSTANDO_HORAS_ACTUAL) {
				entrada[1] = entrada[1] + 1; // falta el carry
			}
			DisplayWriteBCD(board->display, entrada, sizeof(entrada));
		}

		// Retardo de tiempo
		for (int index = 0; index < 100; index++) {
			for (int delay = 0; delay < 5000; delay++) {
				__asm("NOP");
			}
		}
	}
}

void SysTick_Handler(void) {
	static bool last_value = false;
	bool current_value;
	uint8_t hora[CLOCK_SIZE];

	DisplayRefresh(board->display);
	current_value = ClockRefresh(reloj, CLOCK_SIZE);

	if (current_value != last_value) {
		last_value = current_value;

		if (modo <= MOSTRANDO_HORA) {
			ClockGetTime(reloj, hora, CLOCK_SIZE);
			DisplayWriteBCD(board->display, hora, CLOCK_SIZE);

			if (current_value) {
				DisplayToggleDot(board->display, 1);
			}
		}
	}
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
