// create by Asim Ihsan
// modify by xinduan

#ifndef PINGER_H
#define PINGER_H

#include <string>
#include <set>
#include <tr1/unordered_map>
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/exception/all.hpp>


#include "icmp_header.hpp"
#include "ipv4_header.hpp"
#include "Host.h"


namespace pinger {
namespace posix_time = boost::posix_time;

struct PingResult
{
    int32_t pingState;
    std::string ip;
    PingResult():pingState(0){}
    PingResult(int32_t state, const std::string& tip)
            :pingState(state),ip(tip){}
};

typedef boost::function<void (const std::vector<PingResult>&)> Callback_T;
typedef std::tr1::unordered_map<std::string, boost::shared_ptr<Host> > MapSpt_T;

    enum PingState
    {
        PING_OK     = 1,
        PING_FAIL   = 2,
    };

class Pinger {
public:
    Pinger(boost::asio::io_service &io_service,
           const std::vector<std::string> &hosts,
           Callback_T retFunc);

    ~Pinger();

private:
    MapSpt_T hosts_lookup;
    icmp::socket socket;
    boost::asio::streambuf reply_buffer;
    shared_ptr_deadline_timer m_setRetTimer;


    void start_receive();

    void handle_receive(std::size_t length);

    void start_send(boost::shared_ptr<Host> host);

    unsigned short get_identifier();

    void set_host_responsive(boost::shared_ptr<Host> host);

    void set_host_unresponsive(boost::shared_ptr<Host> host, const boost::system::error_code &error);

    bool is_network_unreachable;

    void SendHostState(Callback_T retFunc);

}; // class Pinger

}//end namespace pinger
#endif // PINGER_HPP