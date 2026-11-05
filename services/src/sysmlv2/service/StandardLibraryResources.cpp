//
// The embedded standard library as a list of files, see StandardLibraryResources.h.
//

#include <sysmlv2/service/StandardLibraryResources.h>

#include "StandardLibraryTable.h"

#include <iterator>
#include <string_view>
#include <system_error>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(Library);
CMRC_DECLARE(LibraryXmi);

namespace SysMLv2::API
{
	namespace
	{
		template <class Filesystem>
		std::vector<StandardLibraryFile> files(const Filesystem& fs, bool xmi)
		{
			std::vector<StandardLibraryFile> result;
			result.reserve(std::size(Detail::StandardLibraryTable));
			for (const auto& entry : Detail::StandardLibraryTable)
			{
				const std::string_view path(xmi ? entry.XmiPath : entry.Path);
				try
				{
					// (the data of cmrc is static: the view stays valid)
					const auto data = fs.open(std::string(path));
					const SysMLv2::Files::SourceLanguage language = xmi ? SysMLv2::Files::SourceLanguage::Xmi
						: path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML;
					result.push_back({std::string(path), std::string_view(data.begin(), data.size()), language});
				}
				catch (const std::system_error&)
				{
					// the resource is not embedded
				}
			}
			return result;
		}
	}

	std::vector<StandardLibraryFile> standardLibraryXmi()
	{
		return files(cmrc::LibraryXmi::get_filesystem(), true);
	}

	std::vector<StandardLibraryFile> standardLibraryText()
	{
		return files(cmrc::Library::get_filesystem(), false);
	}
}
