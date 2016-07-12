#ifndef PROTO_H
#define PROTO_H
#include "stm32f4xx.h"

#pragma pack(1) 
typedef struct 
{
		uint16_t velocity;
		uint16_t RPM;
		uint32_t motoHours;
		uint16_t fuelLevel;
		uint16_t oilPressure;
		uint16_t coolantTemperature;
		uint32_t pictoState;
} stProtocolData;
#pragma pack() 
void Proto_Init(void);

#endif
