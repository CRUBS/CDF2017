################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
..\src/decoder_quadra/decoder_quadra.c 

C_DEPS += \
./src/decoder_quadra/decoder_quadra.d 

OBJS += \
./src/decoder_quadra/decoder_quadra.o 


# Each subdirectory must supply rules for building sources it contributes
src/decoder_quadra/decoder_quadra.o: ../src/decoder_quadra/decoder_quadra.c
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@rx-elf-gcc -MM -MP -MF "src/decoder_quadra/decoder_quadra.d" -MT"src/decoder_quadra/decoder_quadra.o" -MT"src/decoder_quadra/decoder_quadra.d" @"src/decoder_quadra/decoder_quadra.depsub" "$<"
	@echo	rx-elf-gcc -MM -MP -MF "src/decoder_quadra/decoder_quadra.d" -MT"src/decoder_quadra/decoder_quadra.o" -MT"src/decoder_quadra/decoder_quadra.d" -x c   -nostdinc -I"C:\PROGRA~2\GCCFOR~1.201\rx-elf\rx-elf/rx-elf/optlibinc" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -g2 -g -mlittle-endian-data -mcpu=rx200 -nofpu "$<"
	@rx-elf-gcc -Wa,-adlhn="$(basename $(notdir $<)).lst" @"src/decoder_quadra/decoder_quadra.sub" -o "$(@:%.d=%.o)" "$<"
	@echo rx-elf-gcc -c -x c  -Wa,-adlhn="$(basename $(notdir $<)).lst" -nostdinc -I"C:\PROGRA~2\GCCFOR~1.201\rx-elf\rx-elf/rx-elf/optlibinc" -Wstack-usage=256 -D__RX_LITTLE_ENDIAN__=1 -g2 -g -mlittle-endian-data -mcpu=rx200 -nofpu -o "$(@:%.d=%.o)" "$<"
	@echo 'Finished scanning and building: $<'
	@echo.

