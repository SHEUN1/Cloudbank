################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SeperateObjects.cpp \
../src/transistor_vision.cpp \
../src/yingyang.cpp 

OBJS += \
./src/SeperateObjects.o \
./src/transistor_vision.o \
./src/yingyang.o 

CPP_DEPS += \
./src/SeperateObjects.d \
./src/transistor_vision.d \
./src/yingyang.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


