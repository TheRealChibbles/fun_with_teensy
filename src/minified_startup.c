#include <stdint.h>
#include "register.h"

extern unsigned long _initial_stack;
void reset_isr(void);
void nmi_isr(void);
void hard_fault_isr(void);
void timer_isr(void);
void not_used_isr(void);
void service_isr(void);
void pendable_service_isr(void);
void system_tick_isr(void);

// siehe Sektion 3.3.2.3 in der Chipdokumentation
#define NVIC_NUM_INTERRUPTS 32
__attribute__ ((section(".vectors"), used))
void (* const _VectorsTable[NVIC_NUM_INTERRUPTS+16])(void) =
  {(void (*)(void))((unsigned long)&_initial_stack),
   reset_isr,
   nmi_isr,
   hard_fault_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   service_isr,
   not_used_isr,
   not_used_isr,
   pendable_service_isr,
   system_tick_isr,
   // chip specific interrupts
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   timer_isr, // hier! Warum nochmal hier?
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr,
   not_used_isr};

void nmi_isr(void)		__attribute__ ((weak, alias("not_used_isr")));
void hard_fault_isr(void)       __attribute__ ((weak, alias("not_used_isr")));
void service_isr(void)          __attribute__ ((weak, alias("not_used_isr")));
void pendable_service_isr(void) __attribute__ ((weak, alias("not_used_isr")));
void system_tick_isr(void)      __attribute__ ((weak, alias("not_used_isr")));

// Die nächsten paar Symbole werden im Linker Script definiert
//   und beziehen sich auf konkrete Zellen im resultiernden Image
extern uint32_t _text_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;

// init function
extern void morser(void);

__attribute__ ((section(".startup"),optimize("-Os")))
  void reset_isr(void) {
  *SIM_COPC = 0x00000000; // disable the watchdog

  // Data Sektion aus dem Flash in den RAM kopieren
  uint32_t* data_flash = &_text_end;
  uint32_t* data_ram = &_data_start;
  while(data_ram < &_data_end) *data_ram++ = *data_flash++;

  // BSS Sektion mit Nullen fuellen
  uint32_t* bss_addr = &_bss_start;
  while(bss_addr < &_bss_end) *bss_addr++ = 0;
  // enable clocks to GPIO Block C; nned to happen before enabeling the Port
  *SIM_SCGC5 = 0x00000800;

  *GPIOc_PDDR = 0x20;
  *PORTc_PCR5 = 0x100; // still works with this bit sequence. The crucial part seems the 001 sequence for the multiplexer

  // TODO: Hint-hint: there is an interrupt enable register in the NVIC regs

  *NVIC_SETENA = 0x00400000;
  // Periodic Interrupt Timer (PIT) clocking enable
  *SIM_SCGC6 = 0x00800000;

  // turn on the PIT module (TODO: Wrong! Read the doc)
  *PIT_MCR = 0x00000000;

  // setting timer load value so that it triggers every 5s, provided that the bus clock
  // has 48MHz => 5s * 48_000_000Hz = 240_000_000
  *PIT_LDVAL0 = 240000000;

  // enabebling the 0th timer and also enabeling the corresponding interrupt
  *PIT_TCTRL0 = 0x00000003;

  // TODO, hier kommt der eigentliche Startup code hin
  morser();

}

static uint8_t is_on = 0;

void timer_isr(void) {
  if(is_on == 0) {
    *GPIOc_PSOR = 0x20;
    is_on = 1;
  } else {
    *GPIOc_PCOR = 0x20;
    is_on = 0;
  }
  // Interrupt clearen
  *PIT_TFLG0 = 0x00000001;
}

void not_used_isr(void) {
  while(1) {};
}

// Flash Security Setting. On Teensy 3.2, you can lock the MK20 chip to prevent
// anyone from reading your code.  You CAN still reprogram your Teensy while
// security is set, but the bootloader will be unable to respond to auto-reboot
// requests from Arduino. Pressing the program button will cause a full chip
// erase to gain access, because the bootloader chip is locked out.  Normally,
// erase occurs when uploading begins, so if you press the Program button
// accidentally, simply power cycling will run your program again.  When
// security is locked, any Program button press causes immediate full erase.
// Special care must be used with the Program button, because it must be made
// accessible to initiate reprogramming, but it must not be accidentally
// pressed when Teensy Loader is not being used to reprogram.  To set lock the
// security change this to 0xDC.  Teensy 3.0 and 3.1 do not support security lock.
#define FSEC 0xDE

// Flash Options
 #define FOPT 0xF9
// #define FOPT 0xE8

// siehe Sektion 27.3.1 in der Chipdokumentation
__attribute__ ((section(".flashconfig"), used))
const uint8_t flashconfigbytes[16] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, FSEC, FOPT, 0xFF, 0xFF
};
