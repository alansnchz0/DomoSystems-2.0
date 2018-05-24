################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/HAL/GPIO.c" \
"../Sources/HAL/PWM.c" \
"../Sources/HAL/UART.c" \

C_SRCS += \
../Sources/HAL/GPIO.c \
../Sources/HAL/PWM.c \
../Sources/HAL/UART.c \

OBJS += \
./Sources/HAL/GPIO.o \
./Sources/HAL/PWM.o \
./Sources/HAL/UART.o \

C_DEPS += \
./Sources/HAL/GPIO.d \
./Sources/HAL/PWM.d \
./Sources/HAL/UART.d \

OBJS_QUOTED += \
"./Sources/HAL/GPIO.o" \
"./Sources/HAL/PWM.o" \
"./Sources/HAL/UART.o" \

C_DEPS_QUOTED += \
"./Sources/HAL/GPIO.d" \
"./Sources/HAL/PWM.d" \
"./Sources/HAL/UART.d" \

OBJS_OS_FORMAT += \
./Sources/HAL/GPIO.o \
./Sources/HAL/PWM.o \
./Sources/HAL/UART.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/HAL/GPIO.o: ../Sources/HAL/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/HAL/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/HAL/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/HAL/PWM.o: ../Sources/HAL/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/HAL/PWM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/HAL/PWM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/HAL/UART.o: ../Sources/HAL/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/HAL/UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/HAL/UART.o"
	@echo 'Finished building: $<'
	@echo ' '


