/*
 *
 * Copyright jun/2022, Joel Jassan <joeljassan@hotmail.com>
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

/** \brief Simple brief of a ".c" template*/

/* ---  Headers files inclusions   ------------------------------------------------------------- */

#include "pantalla.h"
#include <string.h>

/* ---  Macros definitions  -------------------------------------------------------------------- */

#ifndef DISPLAY_MAX_DIGITS
#define DISPLAY_MAX_DIGITS 8
#endif

/*---  Private Data Declaration  --------------------------------------------------------------- */

struct display_s {
	uint8_t digits;
	uint8_t active_digit;
	int8_t flashing_digits;
	uint16_t flashing_count;  // cuenta de la frecuencia de parpadeo
	uint16_t flashing_factor; // frecuencia de parpadeo
	uint8_t memory[DISPLAY_MAX_DIGITS];
	struct display_driver_s driver[1];
};

/*---  Private Variable Declaration ------------------------------------------------------------ */

static const uint8_t IMAGES[] = {

	SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,			   //! < 0
	SEGMENT_B | SEGMENT_C,															   //! < 1
	SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,						   //! < 2
	SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,						   //! < 3
	SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,									   //! < 4
	SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,						   //! < 5
	SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,			   //! < 6
	SEGMENT_A | SEGMENT_B | SEGMENT_C,												   //! < 7
	SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, //! < 8
	SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,			   //! < 9
};

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

// Funcion para asignar un descriptor para crear una nueva pantalla de 7 segmentos
static display_t DisplayAllocate(void);

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

display_t DisplayAllocate(void) {
	static struct display_s instances[1] = {0};

	return &instances[0];
}

/*---  Public Function Implementation  --------------------------------------------------------- */

display_t DisplayCreate(uint8_t digits, display_driver_t driver) {
	display_t display = DisplayAllocate();

	if (display) {
		display->digits = digits;
		display->active_digit = digits - 1;
		display->flashing_digits = 0;
		display->flashing_count = 0;
		display->flashing_factor = 0;
		memcpy(display->driver, driver, sizeof(display->driver));
		memset(display->memory, 0, sizeof(display->memory));
		display->driver->ScreenTurnOff();
	}

	return display;
};

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size) {
	memset(display->memory, 0, sizeof(display->memory));

	for (int index = 0; index < size; index++) {
		if (index >= display->digits)
			break;
		display->memory[index] = IMAGES[number[index]];
	}
}

void DisplayRefresh(display_t display) {
	uint8_t segments;

	display->driver->ScreenTurnOff();
	display->active_digit = (display->active_digit + 1) % display->digits;

	segments = display->memory[display->active_digit];
	if (display->flashing_factor) {
		if (display->active_digit == 0)
			display->flashing_count = (display->flashing_count + 1) % display->flashing_factor;

		if ((display->active_digit & display->flashing_digits) == 1) // no funciona
			if (display->flashing_count > display->flashing_factor / 2)
				segments = 0;
	}

	display->driver->SegmentsTurnOn(segments);
	display->driver->DigitTurnOn(display->active_digit);
}

void DisplayFlashDigits(display_t display, int8_t flashing_digits, uint8_t size,
						uint16_t frequency) {
	display->flashing_factor = frequency;
	display->flashing_digits = 1 << 3; // no funciona
}

/*---  End of File  ---------------------------------------------------------------------------- */