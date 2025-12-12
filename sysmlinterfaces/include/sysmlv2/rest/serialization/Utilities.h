#pragma once

#include <chrono>
#include <time.h>
#include <string>
#include <sysmlv2/interfaces/sysmlv2interfaces_global.h>

namespace SysMLv2::REST {
	class SYSMLV2INTERFACE_EXPORT Utilities {
	public:
		static std::string toIso8601(std::chrono::time_point<std::chrono::system_clock> t);

		static  std::chrono::time_point<std::chrono::system_clock> fromIso8601(std::string value);
	private:
	};
}