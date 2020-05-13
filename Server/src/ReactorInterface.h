#ifndef __REACTORINTERFACE_H__
#define __REACTORINTERFACE_H__

#include <memory>
#include <map>
#include <list>

#include "EventHandlerPtr.h"

namespace reactor
{

    class ReactorInterface
    {
    public:
        void operator()();

        void RegisterEventHandler(int fd, const EventHandlerPtr& handler);

        /*void getEventHandlerFor(int fd, std::list<EventHandlerPtr>& handlers) const*/

        /* virtual bool unregisterEventHandler(const EventHandlerPtr& iHandler); */

    protected:
        virtual void run() = 0;

    private:
        std::map<int, std::list<EventHandlerPtr>> m_events;
    };

} // namespace reactor
#endif /* __REACTORINTERFACE_H__ */
