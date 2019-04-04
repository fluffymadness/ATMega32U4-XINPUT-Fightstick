#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
	#include "LUFAConfig.h"
	#include <avr/pgmspace.h>
	#include <LUFA/LUFA/Drivers/USB/USB.h>
	/* Macros: */
		/** Endpoint address of the Joystick HID reporting IN endpoint. */
		#define JOYSTICK_EPADDR_IN        (ENDPOINT_DIR_IN | 1)

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif
