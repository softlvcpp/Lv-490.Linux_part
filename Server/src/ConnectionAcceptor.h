#ifndef __CONNECTIONACCEPTOR_H__
#define __CONNECTIONACCEPTOR_H__

#include <string>
#include <memory>

#include "ReactorInterface.h"

class ConnectionAcceptor
{
public:
    ConnectionAcceptor(const std::string& address,
                       const std::string& port,
                       const std::shared_ptr<reactor::ReactorInterface>& trafficManager):
                       m_address(address),
                       m_port(port),
                       m_traffic_manager(trafficManager) {};

    void operator()();
private:
    std::string m_address;
    std::string m_port;
    std::shared_ptr<reactor::ReactorInterface> m_traffic_manager;
};
#endif /* __CONNECTIONACCEPTOR_H__ */
