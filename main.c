#include "Board_LED.h"
#include "stm32f407xx.h"

void delay() {
	for (uint32_t i = 0; i < 100000; i++);
}

int main(void) {
	
	//
	// Clock setup:
	//
	
	RCC_TypeDef *pRCC = RCC;
	
	// Enable HSE (high speed external clock):
	pRCC->CR |= (1 << 16); // Turn on HSE.
	while (!(pRCC->CR & (1 << 17))); // Wait until HSE is ready.
	pRCC->CFGR &= ~(0x3); // Clear HSE bits.
	pRCC->CFGR |= 0x1; // Set HSE as system clock.
	
	// Enable clocks for buses to be able to work with
	// periferals which are located on these buses:
	pRCC->APB2ENR |= (1 << 8); // Enable clock for APB2 bus.
	pRCC->AHB1ENR |= (1 << 0); // Enable clock for AHB1 bus.
	
	//
	// Write to periferals:
	//
	
	// Write to GPIOA PUPDR register:
	GPIO_TypeDef *pGPIO = GPIOA;
	pGPIO->PUPDR = 0x55;
	
	// Write to ADC1 CR1 register:
	ADC_TypeDef *pADC = ADC1;
	pADC->CR1 = 0x55;
	
	//
	// Led roulette:
	//
	
	LED_Initialize();
	
	while (1) {
		LED_On(0);
		delay();
		LED_Off(0);
		LED_On(1);
		delay();
		LED_Off(1);
		LED_On(2);
		delay();
		LED_Off(2);
		LED_On(3);
		delay();
		LED_Off(3);
	}
	
	return 0;
}
