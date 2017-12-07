#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

int main(int argc, char** argv) {
	auto console = spdlog::stdout_logger_st("console");
	console->info("Application started, version: " + boost::lexical_cast<std::string>(version()) + ".");

	console->info("Application finished successfully.");
	return 0;
}