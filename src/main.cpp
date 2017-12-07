#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

auto max(int a, float b) -> decltype(a + b)
{
	if(a < b)
		return a;
	else
		return b;
}

int main(int argc, char** argv) {
	auto console = spdlog::stdout_logger_st("console");
	console->info("Application started, version: " + boost::lexical_cast<std::string>(version()) + ".");

	auto r = max(2, 1.1);
	std::cout << "add: " << r << "\n";

	console->info("Application finished successfully.");
	return 0;
}

