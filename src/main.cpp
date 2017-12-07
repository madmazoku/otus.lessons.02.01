#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

auto add(int a, int b) -> int
{
	return a + b;
}

int main(int argc, char** argv) {
	auto console = spdlog::stdout_logger_st("console");
	console->info("Application started, version: " + boost::lexical_cast<std::string>(version()) + ".");

	auto r = add(1, 2);
	std::cout << "add: " << r << "\n";

	console->info("Application finished successfully.");
	return 0;
}