#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/lexical_cast.hpp>

#include "../bin/version.h"

auto min(int a, float b) -> decltype(a + b)
{
	if(a < b)
		return a;
	else
		return b;
}

int main(int argc, const char** argv) {
	auto console = spdlog::stdout_logger_st("console");
	auto wellcome = std::string("Application started, \"") + argv[0] + "\" version: " + boost::lexical_cast<std::string>(version());
	console->info(wellcome);

	auto r = min(2, 1.1);
	std::cout << "max: " << r << " type: " << typeid(r).name() << "\n";

	console->info("Application finished successfully.");
	return 0;
}

