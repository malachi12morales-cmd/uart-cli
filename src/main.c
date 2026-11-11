#include "stm32f4xx.h"

#define LED_PIN 5U

static void delay(volatile uint32_t n)
{
    while (n--) {
        __NOP();
    }
}

int main(void)
{
    /* Enable the GPIOA clock, then read it back so the enable takes effect */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)RCC->AHB1ENR;

    /* PA5 as general-purpose output (MODER bits = 01) */
    GPIOA->MODER &= ~(3U << (LED_PIN * 2U));
    GPIOA->MODER |=  (1U << (LED_PIN * 2U));

    for (;;) {
        GPIOA->ODR ^= (1U << LED_PIN);
        delay(500000);
    }
}