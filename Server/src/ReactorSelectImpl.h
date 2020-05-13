#ifndef __REACTORSELECTIMPL_H__
#define __REACTORSELECTIMPL_H__

#include "ReactorInterface.h"

namespace reactor
{

    class ReactorSelectImpl : public ReactorInterface
    {
    public:
        void set_timeout(int timeout){m_timeout = timeout;}
    protected:
        virtual void run() override;

    private:
        int m_timeout;
    };

} // namespace reactor
#endif /* __REACTORSELECTIMPL_H__ */
