/*
 * main.h
 *
 *  Created on: 12 Sept 2026
 *      Author: glenk
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "stm32f407xx.h"
#include <stdint.h>

/*
 * configuration struct for an SPIx peripheral
 * */
typedef struct {
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPOL;
	uint8_t SPI_SSM;
} SPI_Config_t;

/*
 * @SPI_DeviceMode
 * */
#define SPI_DEVICE_MODE_MASTER	1
#define SPI_DEVICE_MODE_SLAVE 	0

/*
 * @SPI_BusConfig
 * */
#define SPI_BUS_CONFIG_FD 					1
#define SPI_BUS_CONFIG_HD 					2
#define SPI_BUS_CONFIG_SIMPLEX_RX_ONLY 		3

/*
 * @SPI_SclkSpeed
 * */
#define SPI_SCLK_SPEED_DIV2		0
#define SPI_SCLK_SPEED_DIV4     1
#define SPI_SCLK_SPEED_DIV8     2
#define SPI_SCLK_SPEED_DIV16    3
#define SPI_SCLK_SPEED_DIV32    4
#define SPI_SCLK_SPEED_DIV64    5
#define SPI_SCLK_SPEED_DIV128   6
#define SPI_SCLK_SPEED_DIV256   7

/*
 * @SPI_DFF
 * */
#define SPI_DFF_8BITS 	0
#define SPI_DFF_16BITS	1

/*
 * @SPI_CPOL
 * */
#define SPI_CPOL_HIGH 	1
#define SPI_CPOL_LOW 	0

/*
 * @SPI_CPHA
 * */
#define SPI_CPHA_HIGH 	1
#define SPI_CPHA_LOW 	0

/*
 * @SPI_SSM
 * */
#define SPI_SSM_EN 	1
#define SPI_SSM_DI 	0

/*
 * handle struct for an SPIx peripheral
 * */
typedef struct {
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
} SPI_Handle_t;


/*
 * Peripheral Clock setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_Receive(SPI_RegDef_t *pSPIx, uint8_t *RxBuffer);

/*
 * Peripheral Control
 * */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


#endif /* SPI_DRIVER_H_ */
