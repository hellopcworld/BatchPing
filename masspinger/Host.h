// add by xinduan

#ifndef HOST_H
#define HOST_H

#include <iostream>
#include <boost/asio.hpp>


using std::cout;
using std::endl;

using boost::asio::ip::icmp;

typedef boost::shared_ptr<boost::asio::deadline_timer> shared_ptr_deadline_timer;
typedef boost::weak_ptr<boost::asio::deadline_timer> weak_ptr_deadline_timer;

namespace pinger{

class Host
{
public:
    Host(boost::asio::io_service& io_service, const std::string& host);

    inline const std::string& get_host_ip_address() { return Host::host_ip_address; }
    inline const std::string& get_hostname() { return Host::hostname; }
    inline bool get_is_hostname_available() { return Host::is_hostname_available; }

    inline unsigned short get_sequence_number() { return Host::sequence_number; }
    inline void increment_sequence_number() { Host::sequence_number++; }

    inline const boost::posix_time::ptime& get_time_sent() { return Host::time_sent; }
    inline void set_time_sent(const boost::posix_time::ptime& time_sent) { Host::time_sent = time_sent; }

    inline const icmp::endpoint& get_destination() { return Host::destination; }

    //inline weak_ptr_deadline_timer get_send_timer() { return weak_ptr_deadline_timer(Host::send_timer); }
    inline weak_ptr_deadline_timer get_unresponsive_timer() { return weak_ptr_deadline_timer(Host::unresponsive_timer); }

    void set_responsive();
    void set_unresponsive(const boost::system::error_code& error);

    inline int32_t get_alive()const {return m_IsAlive;}

private:
    //log4cxx::LoggerPtr logger;
    //shared_ptr_deadline_timer send_timer;
    shared_ptr_deadline_timer unresponsive_timer;    
    unsigned short sequence_number;
    boost::posix_time::ptime time_sent;        
    icmp::endpoint destination;
    bool is_responsive;

    std::string host_ip_address;
    std::string hostname;
    bool is_hostname_available;
    int32_t m_IsAlive;
}; // class Host

}
#endif // HOST_HPP
