
#include <vector>
#include "avos.hpp"

static cotask * current;
static std::vector<cotask> cotask_list;


// 初始化avOS
void avOS::init()
{
	// TODO
}

// the main loop，这里，主要进行各种协程的调度，并且要做到实时。
// 对不同的任务，一定要按照一定的优先级进行完美调度
void avOS::sched_run()
{
	while (true)
	{
		for (auto it = cotask_list.begin(); it != cotask_list.end(); it ++)
		{
			current = & (*it);
			// 返回 true 意思是当前的 task 有任务并且执行了
			if ( it->run() )
				break;
		}
	}
}