
#include <boost/function.hpp>
#include <boost/scope_exit.hpp>

enum cotask_state {

	TASK_STATE_RUNNING,    // 运行中，表示任务要被调度
	TASK_STATE_EXCUTING,   // 任务执行中，表示任务正在被执行，等待任务主动放弃时间片
	TASK_STATE_TIMEDSLEEP, // 任务在等待一个时间
	TASK_STATE_AWAITTING,  // 任务被停止调度，等待一个条件触发
};


struct cotask{
	boost::function<void()> coro;

	cotask_state state;

	bool run()
	{
		if (state == TASK_STATE_RUNNING)
		{
			BOOST_SCOPE_EXIT(state)
			{
				state = TASK_STATE_RUNNING;
			}BOOST_SCOPE_EXIT_END
			//BOOST_
			state = TASK_STATE_EXCUTING;

			coro();
			return true;
		}
		return false;
	}
};

namespace avOS{
void init();
void sched_run();
}

