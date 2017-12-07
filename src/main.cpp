#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

struct xray 
{
	xray()
	{
		std::cout << __FUNCTION__ << " [" << __FILE__ << ":" << __LINE__ << "]" << std::endl;
	}
	xray(const xray&)
	{
		std::cout << __FUNCTION__ << std::endl;
	}
	~xray()
	{
		std::cout << __FUNCTION__ << std::endl;
	}
};

struct closure 
{
	int m_offset;
	closure(const int &offset = 0) : m_offset(offset)
	{

	}
	int operator()(int a, int b)
	{
		return m_offset + a + b;
	}
};

auto min(int a, float b) -> decltype(a + b)
{
	if(a < b)
		return a;
	else
		return b;
}

int main(int argc, const char** argv) 
{
	auto console = spdlog::stdout_logger_st("console");
	auto wellcome = std::string("Application started, \"") + argv[0] + "\" version: " + boost::lexical_cast<std::string>(version());
	console->info(wellcome);

	auto r = min(2, 1.1);
	std::cout << "max: " << r << " type: " << typeid(r).name() << "\n";

	std::cout << "xray\n";
	xray x;

	std::cout << "closure\n";
	closure l(100);
	std::cout << l(1,2) << std::endl;

	console->info("Application finished successfully.");
	return 0;
}

