//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
	\file	UART.c
	\author	Alan Sanchez y Alberto Bautista
	\date	13/Abril/2016
	\brief	Archivo main de UART

    History:
        20160414_1930   :   
	
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "UART.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/*!
    \def
    \brief
*/


//------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------
/*!
    \enum
    \brief
*/


//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------
/*!
    \var	UART_gbRxData
    \brief	
*/
static volatile U08 UART_gbRxData;
//------------------------------------------------------------------------------
/*!
    \fn		vfnCfgUART0
    \param
    \return
    \brief  Configuracion de los puertos para UART
*/
void vfnCfgUART0(void) {

	//NVIC_ISER |= (1 << 12);
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	PORTA_PCR1 = PORT_PCR_MUX(ALTERNATIVE2);
	PORTA_PCR2 = PORT_PCR_MUX(ALTERNATIVE2);

	UART0_C2 &= ~(UART0_C2_TE_MASK);
	UART0_C2 &= ~(UART0_C2_RE_MASK);

	UART0_C1 = DEFAULT;
	UART0_C3 = DEFAULT;
	UART0_S2 = DEFAULT;

	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(MCGFLLCLK);
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(MCGIRCLK);

	UART0_BDH |= (~UART0_BDH_SBR_MASK) | BAUD_RATE >> 8;
	UART0_BDL |= (~UART0_BDL_SBR_MASK) | BAUD_RATE;

	UART0_C4 &= (~UART0_C4_OSR_MASK) | OVER_SAMPLING;

	UART0_C5 |= UART0_C5_BOTHEDGE_MASK;
	
	UART0_C2 |= UART0_C2_RE_MASK;// | UART0_C2_RIE_MASK;
}
/*!
    \fn		u08UART_RxBuffer
    \param
    \return UART_gbRxData
    \brief  Sirve para alamcenar el valor que se recibe por UART
*/
U08 u08UART_RxBuffer(void) {
	
	return UART_gbRxData;
}
/*!
    \fn		uart0_getchar
    \param
    \return UART0_D
    \brief  Sirve para recibir el valor que es mandado
*/
unsigned char uart0_getchar (void)
{
	if (UART0_S1 & UART_S1_RDRF_MASK) {
		
		return UART0_D;
	}
	return 121;
}
/*!
    \fn		vfnUART0_IRQHandler
    \param
    \return
    \brief  
*/
void vfnUART0_IRQHandler(void) {
	
	if (UART0_S1 & UART_S1_RDRF_MASK) {
		
		UART_gbRxData = UART0_D;
	}
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

