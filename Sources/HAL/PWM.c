//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
	\file	PWM.c
	\author	Alan Sanchez y Alberto Bautista
	\date	13/Abril/2016
	\brief	Archivo main de PWM

    History:
        20160414_1930   :   
	
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "pwm.h"
#include "GPIO.h"

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
    \var	
    \brief	
*/

//------------------------------------------------------------------------------
/*!
    \fn		cfgPWM
    \param
    \return
    \brief  Configuracion del PWM -con los reloj y el modo en que va funcionar
*/
void cfgPWM(void) {
	vfnPortPCR(3,4,0);
	
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK; /* TPM0 Clock Gate Control - Enabled */
	
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(MCGFLLCLK); /* TPM clock source select - MCGFLLCLK clock or MCGPLLCLK/2 */
	SIM_SOPT2 &= ~(SIM_SOPT2_PLLFLLSEL_MASK); /* Selects the MCGPLLCLK or MCGFLLCLK clock for various peripheral clocking options - MCGFLLCLK clock */
	
	TPM0_CNT = 0; /* Clear counter register */
	
	TPM0_MOD = 52816; /* Set signal period to 20 ms */
	
	TPM0_SC = 0x0B;
	//TPM0_SC |= TPM_SC_CMOD(0x01); /* Clock Mode Selection - LPTPM counter increments on every LPTPM counter clock */
	//TPM0_SC |= TPM_SC_PS(0x03); /* Prescale Factor Selection - Divide by 8 */
	
	TPM0_C0SC = 0x28;
	//TPM0_C0SC |= TPM_CnSC_MSB_MASK; /* Channel Mode Select */
	//TPM0_C0SC |= TPM_CnSC_ELSB_MASK; /* Edge or Level Select */
}
/*!
    \fn		vfnTPM0ChannelValue
    \param	u32Value
    \return
    \brief  Funcion que cambia el valor del canal del PWM
*/
void vfnTPM0ChannelValue(U32 u32Value) {
	
	TPM0_C0V = u32Value;
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

