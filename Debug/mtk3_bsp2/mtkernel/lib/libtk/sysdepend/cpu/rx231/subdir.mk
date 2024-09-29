################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.c \
../mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.c \
../mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.c 

OBJS += \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.o \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.o \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.o 

C_DEPS += \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.d \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.d \
./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.d 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/%.o mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/%.su mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/%.cyclo: ../mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/%.c mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -D_STM32CUBE_NUCLEO_H723_ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/config" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/include" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/mtkernel/kernel/knlinc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-rx231

clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-rx231:
	-$(RM) ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.cyclo ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.d ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.o ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/int_rx231.su ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.cyclo ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.d ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.o ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ipr_rx231.su ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.cyclo ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.d ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.o ./mtk3_bsp2/mtkernel/lib/libtk/sysdepend/cpu/rx231/ptimer_rx231.su

.PHONY: clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtk-2f-sysdepend-2f-cpu-2f-rx231

