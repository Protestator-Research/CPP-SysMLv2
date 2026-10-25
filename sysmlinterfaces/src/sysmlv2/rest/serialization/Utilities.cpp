#include <sysmlv2/rest/serialization/Utilities.h>
#include <cctype>
#include <iomanip>
#include <sstream>
std::string SysMLv2::REST::Utilities::toIso8601(std::chrono::time_point<std::chrono::system_clock> t)
{
	// floor (not to_time_t) so that times before 1970 get a non-negative fraction.
	const auto flooredSeconds = std::chrono::floor<std::chrono::seconds>(t);
	time_t epochSeconds = std::chrono::system_clock::to_time_t(
		std::chrono::time_point_cast<std::chrono::system_clock::duration>(flooredSeconds));
	std::stringstream stream;
	struct tm buf;
#ifdef WIN32
	gmtime_s(&buf, &epochSeconds);
#else
	gmtime_r(&epochSeconds, &buf);
#endif
	stream << std::put_time(&buf, "%FT%T");
	auto USDelta = std::chrono::duration_cast<std::chrono::microseconds>(t - flooredSeconds).count();
	stream << "." << std::fixed << std::setw(6) << std::setfill('0') << USDelta;
	// The timestamps of the API are UTC (SysML v2 API, 7.1.2), so the zone designator is always written.
	stream << "Z";
	return stream.str();
}

std::chrono::time_point<std::chrono::system_clock> SysMLv2::REST::Utilities::fromIso8601(std::string value)
{
#if (defined(WIN32) && (_MSC_VER > 1931) || defined(__GNUC__) && (__GNUC__ > 13)) && !defined(__APPLE__)
	// Full clock precision, so fractional seconds (milli-, micro- or nanoseconds) are accepted.
	std::chrono::sys_time<std::chrono::system_clock::duration> tp;
	for (const char* format : { "%FT%TZ", "%FT%T%Ez", "%FT%T" })
	{
		std::istringstream in{ value };
		in >> std::chrono::parse(format, tp);
		if (!in.fail())
			return tp;
	}
	throw std::ios_base::failure("Utilities::fromIso8601: invalid timestamp '" + value + "'");
#else
	// Fallback without std::chrono::parse: YYYY-MM-DDTHH:MM:SS[.fraction][Z|+HH:MM|-HH:MM]
	std::tm tm = {};
	std::istringstream ss(value);
	ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
	if (ss.fail())
		throw std::ios_base::failure("Utilities::fromIso8601: invalid timestamp '" + value + "'");
#ifdef WIN32
	auto tp = std::chrono::system_clock::from_time_t(_mkgmtime(&tm));
#else
	auto tp = std::chrono::system_clock::from_time_t(timegm(&tm));
#endif
	if (ss.peek() == '.')
	{
		ss.get();
		std::chrono::nanoseconds fraction{ 0 };
		long long scale = 100000000;
		while (std::isdigit(ss.peek()))
		{
			fraction += std::chrono::nanoseconds((ss.get() - '0') * scale);
			scale /= 10;
		}
		tp += std::chrono::duration_cast<std::chrono::system_clock::duration>(fraction);
	}
	const int sign = ss.peek();
	if (sign == '+' || sign == '-')
	{
		ss.get();
		int hours = 0, minutes = 0;
		char colon;
		ss >> hours >> colon >> minutes;
		const auto offset = std::chrono::hours(hours) + std::chrono::minutes(minutes);
		tp += (sign == '+') ? -offset : offset;
	}
	return tp;
#endif
}
