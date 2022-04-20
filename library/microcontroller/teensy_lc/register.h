#include <stdint.h>
#ifndef REGISTER_H
#define REGISTER_H "register.h"

  uint32_t * const SIM_COPC = (uint32_t *)0x40048100;


  uint32_t * const NVIC_SETENA = (uint32_t *)0xE000E100;


  uint32_t * const GPIOc_PSOR = (uint32_t *)0x400FF084; //Port set output register
  uint32_t * const GPIOc_PCOR = (uint32_t *)0x400FF088; //Port set output register
  uint32_t * const GPIOc_PDDR = (uint32_t *)0x400FF094; // port data direction register 
  uint32_t * const PORTc_PCR5 = (uint32_t *)0x4004B014; // portc pin control register (register for the led)

	// System Clock Gating Control Register 5
  uint32_t * const SIM_SCGC5 = (uint32_t *)0x40048038;

	// // System Clock Gatin Control Register 6
  uint32_t * const SIM_SCGC6 = (uint32_t *)0x4004803C;
	// // Periodic Interrupt Timer Module Control REgister
 
  uint32_t * const PIT_MCR = (uint32_t *)0x40037000;
	// // Periodic intervall timer Load value #0
  uint32_t * const PIT_LDVAL0 = (uint32_t *)0x40037100;
	// //periodic intervall timer timer controll register #0
  uint32_t * const PIT_TCTRL0 = (uint32_t *)0x40037108;
	// //periodic interupt timer timer flag register #0
  uint32_t * const PIT_TFLG0 = (uint32_t *)0x4003710C;


#endif
