/*
 * main.h
 *
 *  Created on: 12 Sept 2026
 *      Author: glenk
 */

#ifndef STM32F407XX_H_
#define STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

#define RCC_BASEADDR 0x40023800

#define SPI1_BASEADDR 0x40013000
#define SPI2_BASEADDR 0x40003800
#define SPI3_BASEADDR 0x40003C00

/*
 * Peripheral register definitions structs
 * */

typedef struct
{
  __vo uint32_t CR;            /*!< TODO,     										Address offset: 0x00 */
  __vo uint32_t CFGR;          /*!< TODO,     										Address offset: 0x08 */
  __vo uint32_t CIR;           /*!< TODO,     										Address offset: 0x0C */
  __vo uint32_t PLLCFGR;       /*!< TODO,     										Address offset: 0x04 */
  __vo uint32_t AHB1RSTR;      /*!< TODO,     										Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /*!< TODO,     										Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /*!< TODO,     										Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                       */
  __vo uint32_t APB1RSTR;      /*!< TODO,     										Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /*!< TODO,     										Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                  */
  __vo uint32_t AHB1ENR;       /*!< TODO,     										Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /*!< TODO,     										Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /*!< TODO,     										Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                       */
  __vo uint32_t APB1ENR;       /*!< TODO,     										Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /*!< TODO,     										Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                  */
  __vo uint32_t AHB1LPENR;     /*!< TODO,     										Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /*!< TODO,     										Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /*!< TODO,     										Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                       */
  __vo uint32_t APB1LPENR;     /*!< TODO,     										Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /*!< RTODO,     										Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                  */
  __vo uint32_t BDCR;          /*!< TODO,     										Address offset: 0x70 */
  __vo uint32_t CSR;           /*!< TODO,     										Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                  */
  __vo uint32_t SSCGR;         /*!< TODO,     										Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /*!< TODO,     										Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /*!< TODO,     										Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /*!< TODO,     										Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /*!< TODO,     										Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /*!< TODO,     										Address offset: 0x94 */
} RCC_RegDef_t;

typedef struct {
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;
} SPI_RegDef_t;


#define RCC  ((RCC_RegDef_t*) RCC_BASEADDR)

#define SPI1 ((SPI_RegDef_t*) SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t*) SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t*) SPI3_BASEADDR)

/*
 * Clock enable macros for SPI peripherals
 * */
#define SPI1_PCLK_EN() ((RCC->APB2ENR) |= (1 << 12))
#define SPI2_PCLK_EN() ((RCC->APB1ENR) |= (1 << 14))
#define SPI3_PCLK_EN() ((RCC->APB1ENR) |= (1 << 15))

/*
 * Bit position definitions for SPI_CR1
 */
#define SPI_CR1_CPHA		0
#define SPI_CR1_CPOL 		1
#define SPI_CR1_MSTR     	2
#define SPI_CR1_BR   		3
#define SPI_CR1_SPE     	6
#define SPI_CR1_LSBFIRST   	7
#define SPI_CR1_SSI     	8
#define SPI_CR1_SSM      	9
#define SPI_CR1_RX_ONLY     10
#define SPI_CR1_DFF     	11
#define SPI_CR1_CRCNEXT   	12
#define SPI_CR1_CRCEN   	13
#define SPI_CR1_BIDIOE     	14
#define SPI_CR1_BIDIMODE    15


/*
 * Generic macros
 * */
#define ENABLE 	1
#define DISABLE 0

#endif /* STM32F407XX_H_ */
