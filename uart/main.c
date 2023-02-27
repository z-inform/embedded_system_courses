#include "circ_buffer.h"
#include "stm32f746xx.h"
#include "inits.h"

uint32_t interrupt = 0;

extern circ_buffer read_buffer;

int main(void) {

    char prompt[] = "Tell a tale";

    nvic_init();
    usart_init();
    USART6->CR1 |= 1; //enable usart6

    while(1){
        if (circmp(prompt, &read_buffer) == 0) {
            dma_init();
            USART6->ICR |= 1 << 6;
            DMA2_Stream6->CR |= 1;
        }
    }
    return 0;
}

