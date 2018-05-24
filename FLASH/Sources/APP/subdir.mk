################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/APP/MainTemplate.c" \
"../Sources/APP/sa_mtb.c" \

C_SRCS += \
../Sources/APP/MainTemplate.c \
../Sources/APP/sa_mtb.c \

OBJS += \
./Sources/APP/MainTemplate.o \
./Sources/APP/sa_mtb.o \

C_DEPS += \
./Sources/APP/MainTemplate.d \
./Sources/APP/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/APP/MainTemplate.o" \
"./Sources/APP/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/APP/MainTemplate.d" \
"./Sources/APP/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/APP/MainTemplate.o \
./Sources/APP/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/APP/MainTemplate.o: ../Sources/APP/MainTemplate.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/APP/MainTemplate.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/APP/MainTemplate.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/APP/sa_mtb.o: ../Sources/APP/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/APP/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/APP/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


