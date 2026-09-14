#include <stdint.h>
#include "stm32f407xx.h"
#include "spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi) {
	/*
	 * Responsible for turning on the hardware clock for a specific SPI peripheral
	 * */
	if (EnorDi == ENABLE) {
		if (pSPIx == SPI1) {
			SPI1_PCLK_EN();
		} else if (pSPIx == SPI2) {
			SPI2_PCLK_EN();
		} else if (pSPIx == SPI3) {
			SPI3_PCLK_EN();
		}
	} else {
		// TODO
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle) {
	/*
	 * Init settings for SPI peripheral
	 * */

	uint32_t tempReg = 0; // temporary register whose value will be copied to SPI_CR1

	// 1. Configure the device mode i.e Slave or Master
	tempReg |= pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. Configure the bus config
	if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD) {
		// BIDIMODE is cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
	} else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD) {
		// BIDIMODE is set
		tempReg |= (1 << SPI_CR1_BIDIMODE);
	} else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY) {
		// BIDIMODE is cleared & RX ONLY is set
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
		tempReg |= (1 << SPI_CR1_RX_ONLY);
	}

	// 3. Configure the serial clock speed SCLK
	tempReg |= pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. Configure the data frame format
	tempReg |= pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF;

	// 5. Configure CPOL
	tempReg |= pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA;

	// 6. Configure SPHA
	tempReg |= pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;

	// 7. Configure Software Slave Management
	tempReg |= pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempReg;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx) {
	// TODO
}

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len) {
	while (Len > 0) {
		// Polling TXE to check if set
		while (pSPIx->SR & (1 << 1)) {
			// check 8 bit or 16 bit DFF
			if (pSPIx->CR1 & (1 << 11)) {
				// if 16 bit, we load the DR with 2 bytes of data and decrement Len 2 times
				pSPIx->DR = *((uint16_t*) pTxBuffer);
				Len--;
				Len--;
				(uint16_t*) pTxBuffer++;
			} else {
				// handling 8 bit DFF
				pSPIx->DR = *pTxBuffer;
				Len--;
				pTxBuffer++; // incrementing the TX buffer by 1 byte to point to the next address
			}
		}
	}
}






