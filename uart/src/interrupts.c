#include "interrupts.h"
#include "stm32f746xx.h"
#include "circ_buffer.h"

extern circ_buffer read_buffer;

void USART6_IRQHandler() {
    if (USART6->ISR & (1 << 5)) {
        circ_write(USART6->RDR, &read_buffer);
    }
}
