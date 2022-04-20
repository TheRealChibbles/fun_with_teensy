#include <stdint.h>


void main(void) {


  /* uint32_t c = 0; */
  /* while(1) { */
  /*   if(c % 100000 == 0) { */
  /*     *GPIOc_PCOR = 0x20; */
  /*   } */
  /*   if((c+5000) % 100000 == 0) { */
  /*     *GPIOc_PSOR = 0x20; */
  /*   } */
  /*   c++; */
  /* } */
  while(1) {};
}

/*
  Offene Fragen:

  1. Wie muss der NVIC bespielt werden?
  2. Merkt sich der Prozessor wo er unterbrochen wurde, wenn ja wo und wie?
  3. Wie kann man die Clock f�r das TIP modul konfigurieren?
  4. Wann ist ein interrupt abgeschlossen?
     1. Muss man das selber mache? Oder passiert das automatisch?
     2. Wo ist der �bergang vom Resethandler zur Main?
        Wo ist es sinnvoll die Main aufzurufen?
 */
