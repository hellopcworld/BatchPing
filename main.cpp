#include <map>
#include <set>
#include <future>
#include <hash_map>
#include <stdlib.h>
#include <chrono>
#include <sys/types.h>
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <bitset>
//#include "util/inv_redis.h"
//#include "AdListSortThread.h"

#include <boost/exception/all.hpp>
#include <boost/exception/get_error_info.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/foreach.hpp>

#include "masspinger/PingManager.h"

using namespace std;
using namespace boost;


#define URCU_INLINE_SMALL_FUNCTIONS     1


boost::mutex io_mutex;
boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

typedef boost::posix_time::ptime PTIME_T;
#define GET_NOWTICK             boost::posix_time::microsec_clock::universal_time()
typedef int32_t pt_t;

using namespace pinger;

void ShowResult(const std::vector<PingResult>& ret)
{
	BOOST_FOREACH(auto& it, ret)
	{
		cout<<"result: ip:"<<it.ip<<", state:"<< it.pingState <<endl;
	}
}


int main(int argc, char* argv[])
{
	vector<string> iplist;
	iplist.push_back("8.8.8.8");
	iplist.push_back("10.12.19.4");
	iplist.push_back("8.8.8.98");
	iplist.push_back("9.9.9.9");

	{
		PingManager pm;
		pm.BatchPing(iplist, ShowResult);

	}
	sleep(10);
	cout << "End" << endl;
	return 0;
}


