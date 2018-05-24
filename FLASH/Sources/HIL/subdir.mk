################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/HIL/RainSensor.c" \

C_SRCS += \
../Sources/HIL/RainSensor.c \

OBJS += \
./Sources/HIL/RainSensor.o \

C_DEPS += \
./Sources/HIL/RainSensor.d \

OBJS_QUOTED += \
"./Sources/HIL/RainSensor.o" \

C_DEPS_QUOTED += \
"./Sources/HIL/RainSensor.d" \

OBJS_OS_FORMAT += \
./Sources/HIL/RainSensor.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/HIL/RainSensor.o: ../Sources/HIL/RainSensor.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/HIL/RainSensor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/HIL/RainSensor.o"
	@echo 'Finished building: $<'
	@echo ' '


