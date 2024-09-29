################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.c 

OBJS += \
./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.o 

C_DEPS += \
./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.d 


# Each subdirectory must supply rules for building sources it contributes
mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/%.o mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/%.su mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/%.cyclo: ../mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/%.c mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -D_STM32CUBE_NUCLEO_H723_ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_stm32h723/mtk3_bsp2" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_stm32h723/mtk3_bsp2/config" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_stm32h723/mtk3_bsp2/include" -I"D:/dev/mtkernel/dev_mtk3bsp2_20000B1/mtk3bsp2_stm32h723/mtk3_bsp2/mtkernel/kernel/knlinc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtm-2f-sysdepend-2f-iote_m367

clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtm-2f-sysdepend-2f-iote_m367:
	-$(RM) ./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.cyclo ./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.d ./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.o ./mtk3_bsp2/mtkernel/lib/libtm/sysdepend/iote_m367/tm_com.su

.PHONY: clean-mtk3_bsp2-2f-mtkernel-2f-lib-2f-libtm-2f-sysdepend-2f-iote_m367

