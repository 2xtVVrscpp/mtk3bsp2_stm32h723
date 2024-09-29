################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.c 

OBJS += \
./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.o 

C_DEPS += \
./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.d 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/%.o mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/%.su mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/%.cyclo: ../mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/%.c mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -D_STM32CUBE_NUCLEO_H723_ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/config" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/include" -I"/home/masayukigondo/Documents/workspace/sample/mtk3bsp2_stm32h723/mtk3_bsp2/mtkernel/kernel/knlinc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtk3_bsp2-2f-sysdepend-2f-stm32_cube-2f-device-2f-hal_adc

clean-mtk3_bsp2-2f-sysdepend-2f-stm32_cube-2f-device-2f-hal_adc:
	-$(RM) ./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.cyclo ./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.d ./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.o ./mtk3_bsp2/sysdepend/stm32_cube/device/hal_adc/hal_adc.su

.PHONY: clean-mtk3_bsp2-2f-sysdepend-2f-stm32_cube-2f-device-2f-hal_adc

