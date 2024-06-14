// Dynamic Function Pointer Array Allocation - Basic Event Controller
// EventController library based on event.h 2024, Irq handle functions.
// Created : 08-01-2024 : BerkN
// Updates available at https://github.com/BerkN/EventController

#ifndef EVENT_H_
#define EVENT_H_

#include <stdlib.h>
#include <stdint.h>

#define EVENT_INIT_CAPACITY         2
#define EVENT_MAX_CAPACITY          8

typedef enum{
	EVENT_CLOSE = 0,
	EVENT_READY = 1,
	EVENT_ERROR = 2
}eventState_e;

typedef void (*event_t)(void);

typedef struct eventHandle_s{
    event_t* arr;
    uint8_t  arr_size;
    uint8_t  arr_capacity;
    eventState_e state;
}eventHandle_t;

void eventInit(eventHandle_t* handle);
void eventCall(eventHandle_t* handle);
void eventAdd(eventHandle_t* handle, void (*event));
void eventRemove(eventHandle_t* handle);
void eventFree(eventHandle_t* handle);

#endif
