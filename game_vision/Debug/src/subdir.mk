################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BinaryImage.cpp \
../src/ConvertToBinaryImage.cpp \
../src/FeatureExtraction.cpp \
../src/ImageText.cpp \
../src/OCR.cpp \
../src/RecordProcessedImage.cpp \
../src/RegionOfInterest.cpp \
../src/SendDataToPython.cpp \
../src/SeperateObjects.cpp \
../src/main.cpp 

OBJS += \
./src/BinaryImage.o \
./src/ConvertToBinaryImage.o \
./src/FeatureExtraction.o \
./src/ImageText.o \
./src/OCR.o \
./src/RecordProcessedImage.o \
./src/RegionOfInterest.o \
./src/SendDataToPython.o \
./src/SeperateObjects.o \
./src/main.o 

CPP_DEPS += \
./src/BinaryImage.d \
./src/ConvertToBinaryImage.d \
./src/FeatureExtraction.d \
./src/ImageText.d \
./src/OCR.d \
./src/RecordProcessedImage.d \
./src/RegionOfInterest.d \
./src/SendDataToPython.d \
./src/SeperateObjects.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -fopenmp -std=c++0x -I/usr/include/python2.7 -I/usr/include/boost/ -O1 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


