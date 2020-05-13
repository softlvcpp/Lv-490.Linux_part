#include "EventHandler.h"

namespace reactor
{

    void EventHandler::operator()(int fd, EventType event_type)
    {
        handle(fd, event_type);
    }

} // namespace reactor
