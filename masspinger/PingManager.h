//
// Created by xinduan on 15-12-24.
// PingManager 简单实现  不考虑线程安全！
//

#ifndef SPLITSTR_PINGMANAGER_H
#define SPLITSTR_PINGMANAGER_H

#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "Pinger.h"

using std::vector;
using std::string;

namespace pinger {
class PingManager
{
public:
    void BatchPing(const vector<string>& hosts, Callback_T retFunc) {
        m_workThread.reset(
                new boost::thread(boost::bind(&PingManager::StartPingServer, this, hosts, retFunc)) );
    }

private:
    void StartPingServer(const vector<string>& hosts, Callback_T retFunc)
    {
        boost::asio::io_service io_service;
        boost::shared_ptr<Pinger> ping_receiver(new Pinger(io_service, hosts, retFunc));
        io_service.run();
    }

private:
    //boost::thread_group m_workerThreads;
    boost::shared_ptr<boost::thread> m_workThread;
};

}
#endif //SPLITSTR_PINGMANAGER_H
