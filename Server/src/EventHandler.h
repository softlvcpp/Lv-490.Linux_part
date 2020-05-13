#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "EventType.h"

namespace reactor
{

    class EventHandler
    {
    public:
        void operator()(int fd, EventType event_type);

    protected:
        virtual void handle(int fd, EventType event_type) = 0;
    };

} // namespace reactor

#endif /* __EVENTHANDLER_H__ */
