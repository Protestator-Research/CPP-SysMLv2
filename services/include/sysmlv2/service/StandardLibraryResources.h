//
// The standard library as it is embedded in the library (sysmlv2resources: the textual notation, sysmlv2xmiresources: the XMI files of the
// pilot implementation). Meant for programs that build their own SysMLv2::Files::Workspace and want the standard library without reading
// files from disk.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <sysmlv2/Workspace.h>
#include <sysmlv2/service/sysmlv2service_global.h>

namespace SysMLv2::API
{
	/// One file of the embedded standard library.
	struct StandardLibraryFile
	{
		/// The path of the file inside the resources, for example "sysml.library/KerML/Semantic/Base.kerml" (text) or
		/// "sysml.library.xmi/Kernel Libraries/Kernel Semantic Library/Base.kermlx" (XMI). Unique within the list; the XMI files name each
		/// other by hrefs relative to this name, so pass it to Workspace::addText() as the source name.
		std::string name;
		/// The content of the file. Points into the data that is embedded in the library: valid for the lifetime of the process.
		std::string_view content;
		/// SourceLanguage::KerML or SourceLanguage::SysML for the text, SourceLanguage::Xmi for the XMI files.
		SysMLv2::Files::SourceLanguage language = SysMLv2::Files::SourceLanguage::SysML;
	};

	/// The XMI files of the standard library (all packages, in the order of the library), for Workspace::addText(content, name, language).
	/// Files that are not embedded are left out.
	SYSMLV2SERVICE_EXPORT std::vector<StandardLibraryFile> standardLibraryXmi();

	/// The text files of the standard library (all packages, in the order of the library).
	SYSMLV2SERVICE_EXPORT std::vector<StandardLibraryFile> standardLibraryText();
}
