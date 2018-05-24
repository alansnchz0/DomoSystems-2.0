//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*!
	\file	GPIO.c
	\author	Alan Sanchez y Alberto Bautista
	\date	13/Abril/2016
	\brief	Archivo main de GPIO

    History:
        20160414_1930   :   
	
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
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
    \var	MASKSIM
    \brief	Arreglo para activar el reloj de los puertos
*/

const unsigned int MASKSIM[] = {SIM_SCGC5_PORTA_MASK,SIM_SCGC5_PORTB_MASK,SIM_SCGC5_PORTC_MASK,SIM_SCGC5_PORTD_MASK,SIM_SCGC5_PORTE_MASK};
/*!
    \var	MASKBASE
    \brief Arreglo para establecer modo de los puertos
*/

const PORT_MemMapPtr MASKBASE[] = {PORTA_BASE_PTR,PORTB_BASE_PTR,PORTC_BASE_PTR,PORTD_BASE_PTR,PORTE_BASE_PTR};

/*!
    \var	MASKDIR
    \brief Arreglo para seleccionar el puerto donde se van a enviar datos
*/


const GPIO_MemMapPtr MASKDIR[] = {PTA_BASE_PTR,PTB_BASE_PTR,PTC_BASE_PTR,PTD_BASE_PTR,PTE_BASE_PTR};
//------------------------------------------------------------------------------
/*!
    \fn		vfnCfgPorts
    \param	u08pinToToggle
    \return
    \brief  Sirve para configurar el reloj de los puertos
*/
void vfnCfgPorts(void) {
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /* This bit controls the clock gate to the Port A module. */
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /* This bit controls the clock gate to the Port B module. */
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; /* This bit controls the clock gate to the Port C module. */
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; /* This bit controls the clock gate to the Port E module. */
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /* This bit controls the clock gate to the Port D module. */
}
/*!
    \fn		vfnTogglePin
    \param	u08pinToToggle
    \return
    \brief  Sirve para hacer un Toggle a un pin del Puerto B
*/
void vfnTogglePin(U08 u08pinToToggle) {
	
	GPIOB_PDOR ^= GPIO_PDOR_PDO(1 << u08pinToToggle);
}
/*!
    \fn		vfnTogglePinE
    \param	u08pinToToggle
    \return
    \brief  Sirve para hacer un Toggle a un pin del Puerto B
*/
void vfnTogglePinE(U08 u08pinToToggle) {
	
	GPIO_PDOR_REG(PTE_BASE_PTR) ^= GPIO_PDOR_PDO(1 << u08pinToToggle);
}

/*!
    \fn		vfnTooglePinX
    \param	u08pinToToggle u08Base
    \return
    \brief  Sirve para un toggle del puerto y pin que se le enviaron
*/
void vfnTooglePinX(U08 u08pinToToggle, U08 u08Base) {
	
	GPIO_PDOR_REG(MASKDIR[u08Base]) ^= GPIO_PDOR_PDO(1 << u08pinToToggle);
}
/*!
    \fn		vfnCfgRainSensorGPIO
    \param	
    \return
    \brief  Configurar el puerto B0 para el sensor de lluvia
*/
void vfnCfgRainSensorGPIO(void) {
	
	PORTB_PCR0 = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
}
/*!
    \fn		u08CheckBit
    \param	u08Bit
    \return
    \brief  Checar el estado de el pin que recibe del Puerto B
*/
U08 u08CheckBit(U08 u08Bit) {
	
	return ( GPIOB_PDIR & GPIO_PDIR_PDI(1 << u08Bit) );
}

/*!
    \fn		vfnPortPCR
    \param	u08Base u08Alternative u08Pin
    \return
    \brief  Sirve para seleccionar modo de un pin mandado del puerto mandado
*/
void vfnPortPCR (U08 u08Base, U08 u08Alternative, U08 u08Pin){
	
	PORT_PCR_REG(MASKBASE[u08Base], u08Pin) = PORT_PCR_MUX(u08Alternative);
}

/*!
    \fn		vfnCfgLedPorts
    \param	
    \return
    \brief  Sirve para la configurar los pines como salida (Leds)
*/
void vfnCfgLedPorts(void) {
	
	PORTB_PCR18 = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	PORTB_PCR19 = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	PORTD_PCR1  = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	PORTE_PCR0  = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	PORTE_PCR1  = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	PORTE_PCR2  = PORT_PCR_MUX(ALTERNATIVE1); /* Pin Mux Control - Alternative 1 (GPIO). */
	
	GPIOB_PDDR |= GPIO_PDDR_PDD(1 << 18); /* Pin is configured as general-purpose output */
	GPIOB_PDDR |= GPIO_PDDR_PDD(1 << 19); /* Pin is configured as general-purpose output */
	GPIOD_PDDR |= GPIO_PDDR_PDD(1 << 1);  /* Pin is configured as general-purpose output */
	GPIOE_PDDR |= GPIO_PDDR_PDD(1 << 0);  /* Pin is configured as general-purpose output */
	GPIOE_PDDR |= GPIO_PDDR_PDD(1 << 1);  /* Pin is configured as general-purpose output */
	GPIOE_PDDR |= GPIO_PDDR_PDD(1 << 2);  /* Pin is configured as general-purpose output */
	
	GPIOB_PDOR |= GPIO_PDOR_PDO(1 << 18); /* Pin is set with 1 - LED OFF */
	GPIOB_PDOR |= GPIO_PDOR_PDO(1 << 19); /* Pin is set with 1 - LED OFF */
	GPIOD_PDOR |= GPIO_PDOR_PDO(1 << 1);  /* Pin is set with 1 - LED OFF */
	GPIOE_PDOR |= GPIO_PDOR_PDO(1 << 0);  /* Pin is set with 1 - LED OFF */
	GPIOE_PDOR |= GPIO_PDOR_PDO(1 << 1);  /* Pin is set with 1 - LED OFF */
	GPIOE_PDOR |= GPIO_PDOR_PDO(1 << 2);  /* Pin is set with 1 - LED OFF */
}
/*!
    \fn		vfnTurnOnRedLed
    \param
    \return
    \brief  Sirve para prender el Led rojo del pin 18
*/
void vfnTurnOnRedLed(void) {
	
	GPIOB_PDOR &= ~(GPIO_PDOR_PDO(1 << 18));
}
/*!
    \fn		vfnToggleRedLed
    \param
    \return
    \brief  Sirve para hacer un Toogle el Led rojo del pin 18
*/
void vfnToggleRedLed(void) {
	
	GPIOB_PDOR ^= GPIO_PDOR_PDO(1 << 18);
}
/*!
    \fn		vfnToggleGreenLed
    \param
    \return
    \brief  Sirve para hacer un Toogle el Led verde del pin 19
*/
void vfnToggleGreenLed(void) {
	
	GPIOB_PDOR ^= GPIO_PDOR_PDO(1 << 19);
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

