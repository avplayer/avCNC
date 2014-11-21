
/*
 *  interpreter 将 G 代码翻译为插补器能更容易的工作和识别的数据结构
 *
 */

#include <string>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/coroutine/all.hpp>

#include "gcode.hpp"


extern boost::coroutines::asymmetric_coroutine<gcode_ast>::push_type run_gcode;

// 处理 Gxx 命令
static void process_g_action(std::vector<std::string> tokens)
{
	auto action = tokens[0];
	// 快速定位
	if (action == "G00")
	{
		// 生成一个快速定位 AST 树然后 push 给 gcode 执行器协程

	}

}

static void process_gcode_line(std::vector<std::string> tokens)
{
	auto action = tokens[0];
	switch (action[0])
	{
		case 'g':
		case 'G':
			// 处理 G 命令
			return process_g_action(tokens);
	}
}

int main(int argc, char **argv)
{

	for(;;)
	{
		// 从标准输入读入
		std::string gcodeline;
		std::getline(std::cin, gcodeline);

		std::vector<std::string> tokens;
		boost::split(tokens, gcodeline, boost::is_any_of("\t \r"));
		if(tokens.empty())
			continue;
		if(tokens[0][0] == '%')
			continue;
		// 解析
		process_gcode_line(tokens);
	}


	return 0;
}
