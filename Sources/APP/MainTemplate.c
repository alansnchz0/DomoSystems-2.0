//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
	\file	MainTemplate.c
	\author	Alan Sanchez y Alberto Bautista
	\date	13/Abril/2016
	\brief	Archivo main

    History:
        20160414_1930   :

*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "derivative.h"
#include "RainSensor.h"
#include "PWM.h"
#include "UART.h"
#include "GPIO.h"
#include "Types.h"
//------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------
/*!
    \def	AUTO
    \brief	Poner el mode de la aplicacion en Automatico
*/
#define AUTO 1

/*!
    \def	MANUAL
    \brief	Poner el mode de la aplicacion en Manual
*/
#define MANUAL 0
//------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------
/*!
    \enum	eBTSTATES
    \brief	Enumeracion para la maquina de estados de la aplicacion
*/
typedef enum {
	eSTATE0 = 0,
	eSTATE1,
	eSTATE2,
	eRESET
}eBTSTATES;
//------------------------------------------------------------------------------
// Local Functions prototypes
//------------------------------------------------------------------------------
void vfnBTState0 (void);
void vfnBTState1 (void);
void vfnBTState2 (void);
void vfnBTStateReset (void);
void vfnRSState0 (void);
void vfnRSState1 (void);
void vfnRSState2 (void);
void vfnRSStateReset (void);
//------------------------------------------------------------------------------
// Variables
//------------------------------------------------------------------------------
/*!
    \var	u08BTStateValue
    \brief	Variable para almacenar el estado actual de la maquina de estados del Bluetooth
*/
eBTSTATES u08BTStateValue = eSTATE0;
/*!
    \var	u08BTStateValue
    \brief	Variable para almacenar el estado actual de la maquina de estados del Sensor de Lluvia
*/
eBTSTATES u08RSStateValue = eSTATE0;
/*!
    \var	u08UART_D
    \brief	Variable para almacenar lo que se recibe de UART
*/
U08 u08UART_D;
/*!
    \var	u08AutoMode
    \brief	Variable inicializar el modo en Automatico
*/
U08 u08AutoMode = AUTO;
/*!
    \var	vfnBTMachineState
    \brief	Arreglo de Apuntadores a funciones de la maquina de estados del Bluetooth
*/
void(*vfnBTMachineState[])(void) = { vfnBTState0, vfnBTState1, vfnBTState2, vfnBTStateReset };
/*!
    \var	vfnRSMachineState
    \brief	Arreglo de Apuntadores a funciones de la maquina de estados del Sensor de Lluvia
*/
void(*vfnRSMachineState[])(void) = { vfnRSState0, vfnRSState1, vfnRSState2, vfnRSStateReset };
/*!
    \var	u08PortSelected
    \brief	Guarda el valor del puerto seleccionado
*/
static volatile U08 u08PortSelected;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Main Function
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main( void ) {

	vfnCfgPorts();
	vfnCfgLedPorts();
	vfnCfgUART0();
	cfgPWM();
	vfnCfgRainSensorPorts();

    for(;;) {
		if (u08RSStateValue <= eRESET)
			(*vfnRSMachineState[u08RSStateValue])();
		if (u08BTStateValue <= eRESET)
			(*vfnBTMachineState[u08BTStateValue])();
    }
    return 0;
}
//------------------------------------------------------------------------------
//********** Bluetooth **********//
/*!
    \fn		vfnBTState0
    \param
    \return
    \brief	Estado 0 de la maquina de estados donde se recibe el caracter y se manda al siguiente estado dependiendo la condicion
*/
void vfnBTState0 (void) {

	u08UART_D = uart0_getchar();
	if((u08UART_D == 'E' || u08UART_D == 'e')) {

		u08PortSelected = 4;
		vfnToggleRedLed();
		u08BTStateValue = eSTATE1;
	}else if(u08UART_D == 'o' || u08UART_D == 'O') {

		vfnTPM0ChannelValue(4500);
		//TPM0_C0V = 4500;
	}else if(u08UART_D == 'c' || u08UART_D == 'C') {

		vfnTPM0ChannelValue(2000);
		//TPM0_C0V = 2000;
	}else if(u08UART_D == 'm' || u08UART_D == 'M') {

		u08AutoMode = MANUAL;
	}else if(u08UART_D == 'a' || u08UART_D == 'A') {

		u08AutoMode = AUTO;
	}else {
		// do nothing
	}
}
/*!
    \fn		vfnBTState1
    \param
    \return
    \brief	Estado 1 de la maquina de estados donde se recibe el caracter y se manda al siguiente estado dependiendo la condicion
*/
void vfnBTState1 (void) {

	u08UART_D = uart0_getchar();
	if(u08UART_D == '1' || u08UART_D == '0' || u08UART_D == '2') {

		vfnTooglePinX(u08UART_D - 48, u08PortSelected);
		//vfnTogglePinE(u08UART_D - 48);
		u08BTStateValue = eRESET;
	}else if(u08UART_D == 'o' || u08UART_D == 'O') {

		vfnTPM0ChannelValue(4500);
		//TPM0_C0V = 4500;
	}else if(u08UART_D == 'c' || u08UART_D == 'C') {

		vfnTPM0ChannelValue(2000);
		//TPM0_C0V = 2000;
	}else if(u08UART_D == 'm' || u08UART_D == 'M') {

		u08AutoMode = MANUAL;
	}else if(u08UART_D == 'a' || u08UART_D == 'A') {

		u08AutoMode = AUTO;
	}else {
		// do nothing
	}
}
/*!
    \fn		vfnBTState2
    \param
    \return
    \brief
*/
void vfnBTState2 (void) {

}
/*!
    \fn		vfnBTStateReset
    \param
    \return
    \brief	Estado de la maquina de estados donde se hace el reset y manda al primer estado
*/
void vfnBTStateReset (void) {
	u08BTStateValue = eSTATE0;
}
//********** RAIN SENSOR **********//
/*!
    \fn		vfnRSState0
    \param
    \return
    \brief	Estado 0 de la maquina de estados donde se manda al siguiente estado dependiendo la condicion
*/
void vfnRSState0 (void) {

	if(u08AutoMode == AUTO) {

		u08RSStateValue = eSTATE1;
	} else if (u08AutoMode == MANUAL) {

		u08RSStateValue = eSTATE2;
	} else {
		// do nothing
	}
}
/*!
    \fn		vfnRSState1
    \param
    \return
    \brief	Estado 1 de la maquina de estados donde se cambia el valor del TPM0_COV para el movimiento del Servomotor
*/
void vfnRSState1 (void) {

	if(vfnIsRaining()) {

		vfnTPM0ChannelValue(2000);
		//TPM0_C0V = 2000;
	} else {

		vfnTPM0ChannelValue(4500);
		//TPM0_C0V = 4500;
	}
	u08RSStateValue = eRESET;

}
/*!
    \fn		vfnRSState2
    \param
    \return
    \brief	Estado 2 de la maquina de estados donde se checa si el sensor de lluvia detecta lluvia y cambia el TPM0_COV para el movimiento del Servomotor
*/
void vfnRSState2 (void) {

	if(vfnIsRaining()) {

		vfnTPM0ChannelValue(4500);
		//TPM0_C0V = 4500;
	} else {
		// do nothing
	}
	u08RSStateValue = eRESET;
}
/*!
    \fn		vfnRSStateReset
    \param
    \return
    \brief	Estado de la maquina de estados donde se hace el reset y manda al primer estado
*/
void vfnRSStateReset (void) {

	u08RSStateValue = eSTATE0;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
