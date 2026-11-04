//
// Created by herzo on 24.09.2026.
//

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>
#include <sysmlv2/service/sysmlv2service_global.h>

namespace KerML
{
	namespace Entities
	{
		class Namespace;
		class Element;
	}
}

namespace SysMLv2
{
	namespace Files
	{
		class ParserError;
		class Workspace;
	}
}

namespace SysMLv2::API
{
	/// The form in which the standard library is loaded from the embedded resources.
	enum class StandardLibraryFormat
	{
		Text, ///< the textual notation (sysmlv2resources), parsed
		Xmi   ///< the XMI serialization of the pilot implementation (sysmlv2xmiresources), read
	};

	/**
	 * @class InstanceManager
	 * @brief Holds one instance model (SysML v2 text) together with the user libraries it depends on and the parts of the
	 * standard library it needs, parsed and resolved as one SysMLv2::Files::Workspace.
	 *
	 * The instance model, the non-standard libraries and the needed standard library files are separate sources of one
	 * workspace: every source has its own root namespace, and the names and imports of all of them are resolved against each
	 * other by Workspace::resolve() (scoped resolution, imports, visibility, aliases, short names).
	 *
	 * Standard library files are loaded from the embedded resources (sysmlv2resources, or sysmlv2xmiresources for the XMI format) on
	 * demand:
	 *  - the library packages that the instance model and the non-standard libraries name (`import ScalarValues::*;`,
	 *    `Base::Anything`, ...): every reference that starts with the name of a standard library package loads that package's file;
	 *    this is repeated for the loaded files, so the imports of the library files are followed too (the XMI files name each other by
	 *    hrefs: the files of the hrefs that no loaded file can resolve are loaded);
	 *  - the library packages that the implicit specializations of the model elements refer to (a `part` specializes
	 *    `Parts::parts`, ...), chosen by the metaclasses that occur in the model, and `Base`.
	 * A package that the model or a non-standard library defines itself is not loaded from the standard library.
	 */
	class SYSMLV2SERVICE_EXPORT InstanceManager
	{
	public:
		InstanceManager();
		virtual ~InstanceManager();
		InstanceManager(const InstanceManager&) = delete;
		InstanceManager& operator=(const InstanceManager&) = delete;

		/**
		 * Keeps the standard library between the models (default: off). With the mode off every parseModel and every
		 * appendNonStandardLibrary builds a fresh workspace and loads the standard library again.
		 *
		 * With the mode on the workspace stays: parseModel replaces only the sources of the model and of the non-standard libraries
		 * (their elements may be the targets of references of the old model), and appendNonStandardLibrary adds the library as a new
		 * source. The standard library files that were loaded stay loaded, resolved, and are not parsed again; new ones are added when
		 * the model needs them. The sources of the user have a higher level than those of the standard library, so a reference of the
		 * library never resolves to an element of the model. Libraries of earlier models therefore remain loaded in this mode. If a
		 * model or library defines a root package with the name of a standard library package that is loaded, the workspace is built
		 * anew. One difference to the default mode remains: the references of the standard library files never bind to the model, so a model
		 * package with the name of a standard library package (for example `package ScalarValues`) is not used by the library files that
		 * name it, which the default mode (all sources on one level) allows.
		 *
		 * Changing the mode takes effect with the next parseModel (which builds the workspace for the mode).
		 */
		void setReuseStandardLibrary(bool reuse);
		bool reuseStandardLibrary() const;

		/**
		 * The format the standard library is loaded in (default: Xmi, which loads about twice as fast; the qualified names of all elements and the references that stay unresolved are the same as with Text, see the InstanceManagerFormats tests). Takes effect with the next parseModel; a workspace that was
		 * built with another format is built anew then. With Xmi, a model or library that defines a root package with the name of a
		 * standard library package (`package Base`) is processed with the text for as long as it does (the workspace is built anew when
		 * that changes, also in the mode that keeps the standard library): the library files then bind to the package of the model by
		 * name, as in the text format, which the id based XMI files cannot do.
		 */
		void setStandardLibraryFormat(StandardLibraryFormat format);
		StandardLibraryFormat standardLibraryFormat() const;

		/**
		 * Sets the instance model and rebuilds everything (a fresh workspace: nothing of an earlier model is kept, the
		 * non-standard libraries that were appended so far are parsed again with the new model). In the mode that keeps the standard
		 * library (setReuseStandardLibrary()) only the sources of the model and of the libraries are replaced.
		 * @param model SysML v2 text.
		 */
		void parseModel(std::string model);

		/**
		 * Adds a user library (SysML v2 text) that the instance model may import. It is kept for all later parseModel calls.
		 * If a model was already parsed the model is rebuilt so that it sees the library (in the mode that keeps the standard library
		 * the library is added to the workspace); otherwise the library is used by the next parseModel.
		 */
		void appendNonStandardLibrary(std::string model);

		/**
		 * Syntax errors of the instance model, the non-standard libraries and (should there be any) the standard library
		 * files that were loaded. References that cannot be resolved are not errors, see getUnresolvedReferences().
		 * (The reference stays valid until the next parseModel or appendNonStandardLibrary call, like the other getters that return one.)
		 */
		const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& getParserErrors() const;

		/**
		 * The names in the instance model and in the non-standard libraries that could not be resolved, as ParserErrors of
		 * type WARNING (with source name, line and column). Unresolved references inside the standard library are not listed.
		 */
		const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& getUnresolvedReferences() const;

		/**
		 * The elements of all sources in the order of the sources: instance model, non-standard libraries and the loaded standard
		 * library files (in the mode that keeps the standard library, a library that is appended later follows the standard library
		 * files that are loaded at that time). The root namespaces are not elements of a source and not included; the memberships are.
		 */
		const std::vector<std::shared_ptr<KerML::Entities::Element>>& getElements() const;

		/// The elements of the instance model and of the non-standard libraries only (see getElements()).
		std::vector<std::shared_ptr<KerML::Entities::Element>> getModelElements() const;

		/**
		 * The root namespace of the instance model: it owns the top-level elements of the model through their memberships.
		 * @return the namespace; null before the first parseModel call.
		 */
		std::shared_ptr<KerML::Entities::Namespace> getRootNamespace() const;

		/// All elements (see getElements()) whose declared name is @p name.
		std::list<std::shared_ptr<KerML::Entities::Element>> findAllElementsWithDeclaredName(const std::string& name) const;

		/**
		 * The element with the qualified name @p name (`VehiclePackage::Car`), searched in the instance model, the libraries and
		 * the standard library. The qualifiedName() of every element of every source is set from the chain of its owning
		 * namespaces (unnamed elements have none and do not contribute a segment).
		 * @return the element, or null.
		 */
		std::shared_ptr<KerML::Entities::Element> findElementWithQualifiedName(const std::string& name) const;

		/// The element (of all sources) with the given id, or null.
		std::shared_ptr<KerML::Entities::Element> findElementWithId(const boost::uuids::uuid& uuid) const;

	private:
		/// Builds a new workspace with all sources.
		void rebuildModel();
		/// Keeps the workspace: replaces the sources of the model and of the non-standard libraries.
		void updateModel();
		/// Keeps the workspace: adds the last non-standard library as a source.
		void addNonStandardLibrary();
		/// The format the standard library is loaded in for the user sources @p sources: the configured one, except that the XMI files
		/// (which refer to each other by id) cannot see a package of the model that has the name of a standard library package, which the
		/// text does: such a model is processed with the text (Finding: same result as the text format).
		StandardLibraryFormat formatFor(const std::vector<std::size_t>& sources) const;
		/// Whether a root package of the given sources has the name of a standard library package that is loaded.
		bool definesLoadedStandardPackage(const std::vector<std::size_t>& sources) const;
		/// Loads what the user sources named by @p changed need (they are new or were replaced).
		/// @return the index of the first source that was added for the standard library.
		std::size_t loadStandardLibraries(const std::vector<std::size_t>& changed);
		bool loadStandardLibrary(const std::string& packageName);
		/// Loads the library packages that the references of the given sources name, and of the library files that this loads.
		void preloadStandardLibraries(std::vector<std::size_t> pending);
		/// Takes errors, warnings and elements from the workspace and sets the qualified names of the sources that are new or were replaced.
		void publishModel(const std::vector<std::size_t>& changed, std::size_t firstLibrary);
		void buildIndices();

		std::unique_ptr<SysMLv2::Files::Workspace> Model;
		/// The sources of the user in the workspace: the instance model first, then the non-standard libraries.
		std::vector<std::size_t> UserSources;
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> ParserErrors;
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> UnresolvedReferences;
		std::vector<std::shared_ptr<KerML::Entities::Element>> Elements;
		/// Lookup tables over Elements (built with every change of the model).
		std::unordered_map<boost::uuids::uuid, std::shared_ptr<KerML::Entities::Element>, boost::hash<boost::uuids::uuid>> ElementsById;
		/// By declared name; the elements of a name are in the order of Elements.
		std::unordered_map<std::string, std::vector<std::shared_ptr<KerML::Entities::Element>>> ElementsByDeclaredName;
		/// By qualified name; the first element of Elements wins.
		std::unordered_map<std::string, std::shared_ptr<KerML::Entities::Element>> ElementsByQualifiedName;
		std::shared_ptr<KerML::Entities::Namespace> RootNamespace = nullptr;
		/// The standard library packages that were loaded into the workspace.
		std::unordered_set<std::string> LoadedStandardLibraries;
		/// The names of the root packages that the model and the non-standard libraries define.
		std::unordered_set<std::string> UserPackages;

		bool ModelParsed = false;
		std::string InstanceModel;
		std::vector<std::string> NonStandardLibraries;

		bool ReuseStandardLibrary = false;
		StandardLibraryFormat LibraryFormat = StandardLibraryFormat::Xmi;
		/// The format the workspace was built with: LibraryFormat, or the text for a model that defines a package of the standard library.
		StandardLibraryFormat ActiveFormat = StandardLibraryFormat::Xmi;
		/// Whether the workspace was built for the current mode and format, so that it can be kept.
		bool WorkspaceReusable = false;
	};
}
