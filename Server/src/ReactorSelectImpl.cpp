#include <vector>
#include <iostream>

#include "select.h"

#include "ReactorSelectImpl.h"

namespace reactor
{

    void ReactorSelectImpl::run()
    {
        std::vector<int> read_fds;
        std::vector<int> write_fds;
        std::vector<int> except_fds;

        int aResult = sys::select(read_fds, write_fds, except_fds, m_timeout);

        switch(aResult)
        {
            case -1:
                //log "Error in select"
                break;
            case 0:
                //log "Timeout in select"
                break;
            default:
                for (auto aFd : read_fds)
                {
                    //TODO read
                }
                for (auto aFd : write_fds)
                {
                    //TODO write
                }
                break;
        }
    }

} // namespace reactor
