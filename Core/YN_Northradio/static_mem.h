#ifndef STATIC_MEM_H_
#define STATIC_MEM_H_

/**
 * @brief Allocate variables and stack for a task using static memory.
 *
 * @param NAME A name used as base name for the variables that are created
 * @param STACK_DEPTH The stack depth in nr of StackType_t entries.
 */
#define STATIC_MEM_TASK_ALLOC(NAME,STACK_DEPTH,PRIORITY) \
static const int    NAME##_stackDepth = (STACK_DEPTH);\
static StackType_t  NAME##_stackBuffer[(STACK_DEPTH)];\
static StaticTask_t NAME##_taskBuffer;\
static UBaseType_t 	NAME##_priority = PRIORITY;

/**
 * @brief Create a task using static memory
 *
 * The task is created under the assumption that STATIC_MEM_TASK_ALLOC() has been
 * used to define the required variables and buffers.
 *
 * @param NAME A name used as base name for the variables, same name that was used in STATIC_MEM_TASK_ALLOC()
 * @param FUNCTION The function that implements the task
 * @param TASK_NAME A descriptive name for the task
 * @param PARAMETERS Passed on as argument to the function implementing the task
 * @param PRIORITY The task priority
 */
#define STATIC_MEM_TASK_CREATE(NAME, FUNCTION, PARAMETERS) \
xTaskCreateStatic((FUNCTION), #NAME, NAME##_stackDepth, (PARAMETERS), (NAME##_priority), NAME ##_stackBuffer, & NAME##_taskBuffer)


/**
 * @brief Creates a number of variables required for a queue using static memory.
 *
 * All variables created by this macreo are named using the NAME parameter as a base.
 *
 * Example:
 * STATIC_MEM_QUEUE_ALLOC(myQueue, 5, sizeof(int));
 *
 * @param NAME - the name of the queue handle (xQueueHandle). The name is also used as
 * base name for the other variables that are required.
 * @param LENGTH - the length of the queue (in items)
 * @param ITEM_SIZE - the size of the items in the queue
 */
#define STATIC_MEM_QUEUE_ALLOC(NAME, LENGTH, ITEM_SIZE)\
static const int NAME ## 	 _length = (LENGTH); \
static const int NAME ## 	 _itemSize = (ITEM_SIZE); \
static uint8_t NAME ## 	     _storage[(LENGTH) * (ITEM_SIZE)]; \
static StaticQueue_t NAME ## _queue;

/**
 * @brief Creates a queue using static memory
 *
 * The queue is created under the assumption that variables have been created
 * using the STATIC_MEM_QUEUE_ALLOC() macro
 *
 * @param NAME - the name of the queue handle
 */
#define STATIC_MEM_QUEUE_CREATE(NAME) \
xQueueCreateStatic(NAME ## _length, NAME ## _itemSize, NAME ## _storage, &NAME ## _queue)


#endif /* STATIC_MEM_H_ */
