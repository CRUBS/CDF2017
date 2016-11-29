################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/interrupt/interrupt_handlers.c 

C_DEPS += \
./src/interrupt/interrupt_handlers.d 

OBJS += \
./src/interrupt/interrupt_handlers.o 


# Each subdirectory must supply rules for building sources it contributes
src/interrupt/interrupt_handlers.o: ../src/interrupt/interrupt_handlers.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/interrupt/interrupt_handlers.d" -MT"src/interrupt/interrupt_handlers.o" -MT"src/interrupt/interrupt_handlers.d" @"src/interrupt/interrupt_handlers.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/interrupt/interrupt_handlers.d" -MT"src/interrupt/interrupt_handlers.o" -MT"src/interrupt/interrupt_handlers.d" -x c   -nostdinc -I"C:\PROGRA~2\GCCFOR~1.201\rx-elf\rx-elf/rx-elf/optlibinc" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\asservissement" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\uart" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\interrupt" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\pwm" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\encoder" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -g2 -g -mlittle-endian-data -mcpu=rx200 -nofpu "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/interrupt/interrupt_handlers.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c  -Wa,-adlhn="$(basename $(notdir $<)).lst" -nostdinc -I"C:\PROGRA~2\GCCFOR~1.201\rx-elf\rx-elf/rx-elf/optlibinc" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\asservissement" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\uart" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\interrupt" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\pwm" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src\encoder" -I"C:\Users\Mickael Leconte\Documents\GitHub\CDF2017\rx210\src" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -g2 -g -mlittle-endian-data -mcpu=rx200 -nofpu -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

