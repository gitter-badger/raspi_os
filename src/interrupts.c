#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "peripherals/armtimer.h"
#include "base.h"
#include "drivers/gpio.h"
#include "interrupts.h"

static irq_controller_t* pIRQController = (irq_controller_t*) INTERRUPT_CONTROLLER_BASE;

irq_controller_t* GetIRQController (void) {
    return pIRQController;
}

void __attribute__((interrupt("ABORT"))) reset_vector (void) {
    printf ("Reset abort interrupt...\n");
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector (void) {
    while(1) {
        printf ("Stuck in UNDEF interrupt loop!\n");
        // TRAP!!!
    }
}

void __attribute__((interrupt("SWI"))) software_interrupt_vector (void) {
    printf ("Software interrupt...\n");
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector (void) {
    printf ("Prefetch abort interrupt...\n");
}

void __attribute__((interrupt("ABORT"))) data_abort_vector (void) {
    printf ("Data abort interrupt...\n");
}

void __attribute__((interrupt("IRQ"))) interrupt_vector (void) {
    static int lit = 0;
    
    // Clear the ARM Timer interrupt
    GetARMTimer ()->m_uIRQClear = 1;
    
    // Flip the LED
    if (lit) {
        GetGPIO ()->m_rGPSET1 = (1 << LED_GPIO_BIT);
        lit = 0;
    } else {
        GetGPIO ()->m_rGPCLR1 = (1 << LED_GPIO_BIT);
        lit = 1;    
    }
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector (void) {
    printf ("FIQ interrupt...\n");
}
