#include <map>
#include <list>
#include <algorithm>
#include <iterator>
#include <mutex>

#include "EventHandlerPtr.h"
#include "ReactorInterface.h"

namespace reactor
{
    std::mutex g_event_mutex;

    void ReactorInterface::operator()()
    {
        while(true)
        {
            this->run();
        }
    }

    void ReactorInterface::RegisterEventHandler(int fd, const EventHandlerPtr& handler)
    {
        std::lock_guard<std::mutex> guard(g_event_mutex);
        auto search = m_events.find(fd);
        if (search == m_events.end())
        {
            std::list<EventHandlerPtr> handler_list{handler};
            m_events[fd] = handler_list;
        }
        else
        {
            search->second.push_back(handler);
        }
    }

} // namespace reactor
