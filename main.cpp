/**
 *
 * main.cpp  -  the main file for avCNC
 *
 */

/*
 * PLL 缓冲。PLL 缓存，根据电机的物理特性来决定输出速度。
 * 并且根据剩下的 PLL 缓冲的大小来决定是否进一步解析 G 代码。
 *
 */

#include <bitset>
#include <boost/circular_buffer.hpp>
#include <functional>
#include <boost/function.hpp>
#include <vector>
#include <boost/scope_exit.hpp>

#include "coroutine.hpp"
#include "avos.hpp"

// 用一个 N bits 长的数字表示每一个时钟周期 所有输出信号线的状态
// 每个轴需要 3 条信号，一条使能，一条方向，一条脉冲
// 3轴需要 9 条
typedef std::bitset<9> out_signal_pins_t;

struct avCNC_axis_pulse
{
	out_signal_pins_t step_dir;
	out_signal_pins_t step_pulse;
};

static struct avCNC_PLL
{
	//out_signal_pins_t
	boost::circular_buffer<out_signal_pins_t> all_outs;

}avCNC_PLL_buffer;

// 记录电机加速曲线的。
struct accel_table{

};

class avCNC_PLL_output : avCNC::coro::coroutine
{
public:
	avCNC_PLL_output() {}


	void operator()()
	{
		AVCNC_CORO_REENTER(this)
		{
			// 检查大小，小于设定值，就要申请调度插补器。

			if ( avCNC_PLL_buffer.all_outs.size() <  8000)
			{
				//  取消 buffer 满状态。
			}
			// 协程，正式开始输出 pinouts

			// 每隔 (1/15k) s 执行一次。



		}
	}

};


int main()
{
	// initialize

	avOS::init();

	// run the loop

	avOS::sched_run();
	return 0;
}