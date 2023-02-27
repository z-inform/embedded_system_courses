#include "inits.h"
#include "stm32f746xx.h"
#include "borodino.h"

void dma_init() {
    //enable DMA2 clocking
    RCC->AHB1ENR |= 1 << 22;

    DMA2_Stream6->CR &= 0;
    while (DMA2_Stream6->CR & 1) {};

    //set periph address
    DMA2_Stream6->PAR = 0x40011400 + 0x28;
    //set memory address
    DMA2_Stream6->M0AR = (uint32_t) borodino;
    //set memory size
    DMA2_Stream6->NDTR = sizeof(borodino);

    //select ch6 USART6_TX
    DMA2_Stream6->CR |= 5 << 25;
    //set high priority
    DMA2_Stream6->CR |= 0b10 << 16;
    //set memory increment mode
    DMA2_Stream6->CR |= 1 << 10;
    //select memory-periph transfer
    DMA2_Stream6->CR |= 1 << 6;

    DMA2->HIFCR = 0xffffffff;

}

void usart_init() { //usart active in 152000 8N1

    // enable GPIOC clocking
    RCC->AHB1ENR |= 1 << 2;

    // put usart6 pins in AF mode
    GPIOC->MODER |= 0b1010 << 12;
    GPIOC->AFR[0] |= 0b1000 << 24;
    GPIOC->AFR[0] |= 0b1000 << 28;

    //enable usart 6 clocking
    RCC->APB2ENR |= 1 << 5;

    //enable rx interrupt
    USART6->CR1 |= 1 << 5;
    //enable receiver and transmitter
    USART6->CR1 |= 0b11 << 2;
    //enable DMA for transmitter
    USART6->CR3 |= 1 << 7;
    //set 115200 baud rate
    USART6->BRR = 139;
}

void nvic_init() {
     NVIC->ISER[(((uint32_t)71) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)71) & 0x1FUL));
}
