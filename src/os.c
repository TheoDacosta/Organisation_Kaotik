#include "os_manager.h"

void os_delayMs(uint32_t delay)
{
    uint32_t start_time = get_current_timeMs();
    while ((get_current_timeMs() - start_time) < delay)
        ;
}
