################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OCR.cpp \
../src/SendDataToPython.cpp \
../src/SeperateObjects.cpp \
../src/convertToBinaryImage.cpp \
../src/featureextraction.cpp \
../src/main.cpp \
../src/recordProcessedImage.cpp 

OBJS += \
./src/OCR.o \
./src/SendDataToPython.o \
./src/SeperateObjects.o \
./src/convertToBinaryImage.o \
./src/featureextraction.o \
./src/main.o \
./src/recordProcessedImage.o 

CPP_DEPS += \
./src/OCR.d \
./src/SendDataToPython.d \
./src/SeperateObjects.d \
./src/convertToBinaryImage.d \
./src/featureextraction.d \
./src/main.d \
./src/recordProcessedImage.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/include/python2.7 -I/usr/include/boost/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


