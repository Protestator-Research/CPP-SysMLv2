#pragma once

#include <chrono>
#include <time.h>
#include <string>
#include <sysmlv2/rest/sysmlv2rest_global.h>

namespace SysMLv2::REST {
	class SYSMLV2REST_EXPORT Utilities {
	public:
		static std::string toIso8601(std::chrono::time_point<std::chrono::system_clock> t)
		{
			time_t epochSeconds = std::chrono::system_clock::to_time_t(t);
			std::stringstream stream;
			struct tm buf;
#ifdef WIN32
			gmtime_s(&buf, &epochSeconds);
#else
			gmtime_r(&epochSeconds, &buf);
#endif
			stream << std::put_time(&buf, "%FT%T");
			auto truncated = std::chrono::system_clock::from_time_t(epochSeconds);
			auto USDelta = std::chrono::duration_cast<std::chrono::microseconds>(t - truncated).count();
			stream << "." << std::fixed << std::setw(6) << std::setfill('0') << USDelta;
			return stream.str();
		}

		static  std::chrono::time_point<std::chrono::system_clock> fromIso8601(std::string value)
		{
			std::istringstream in{ value };
			std::chrono::sys_time<std::chrono::milliseconds> tp;
			in >> std::chrono::parse("%FT%TZ", tp);
			if (in.fail())
			{
				in.clear();
				in.exceptions(std::ios::failbit);
				in.str(value);
				in >> std::chrono::parse("%FT%T%Ez", tp);
			}
			return tp;
		}
	private:
	};
}