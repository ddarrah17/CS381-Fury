################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Aspect.cpp \
../src/Command.cpp \
../src/Engine.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp \
../src/FlyingEntity381.cpp \
../src/GameMgr.cpp \
../src/GfxMgr.cpp \
../src/InputMgr.cpp \
../src/Mgr.cpp \
../src/Physics2D.cpp \
../src/Physics3D.cpp \
../src/SoundMgr.cpp \
../src/UiMgr.cpp \
../src/UnitAI.cpp \
../src/Utils.cpp \
../src/main.cpp 

OBJS += \
./src/Aspect.o \
./src/Command.o \
./src/Engine.o \
./src/Entity381.o \
./src/EntityMgr.o \
./src/FlyingEntity381.o \
./src/GameMgr.o \
./src/GfxMgr.o \
./src/InputMgr.o \
./src/Mgr.o \
./src/Physics2D.o \
./src/Physics3D.o \
./src/SoundMgr.o \
./src/UiMgr.o \
./src/UnitAI.o \
./src/Utils.o \
./src/main.o 

CPP_DEPS += \
./src/Aspect.d \
./src/Command.d \
./src/Engine.d \
./src/Entity381.d \
./src/EntityMgr.d \
./src/FlyingEntity381.d \
./src/GameMgr.d \
./src/GfxMgr.d \
./src/InputMgr.d \
./src/Mgr.d \
./src/Physics2D.d \
./src/Physics3D.d \
./src/SoundMgr.d \
./src/UiMgr.d \
./src/UnitAI.d \
./src/Utils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/OGRE -I/usr/include/audio -I/usr/include/AL -I"/home/josephstine/workspace/Fury/inc" -I/usr/local/include/OGRE/Overlay -I/usr/include/ois -O0 -g3 -Wall -c -fmessage-length=0  -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


