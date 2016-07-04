#ifndef PROTO_H
#define PROTO_H
#include "stm32f4xx.h"

typedef struct 
{
		uint16_t velocity;
		uint16_t RPM;
		uint32_t motoHours;
		uint16_t fuelLevel;
		uint16_t oilPressure;
		uint16_t coolantTemperature;
		uint16_t pictoState;
} stProtocolData;

void Proto_Init(void);

#endif
