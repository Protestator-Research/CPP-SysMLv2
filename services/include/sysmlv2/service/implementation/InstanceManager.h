//
// Created by herzo on 24.09.2026.
//

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include <list>
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
	/**
	 * @class InstanceManager
	 * @brief Holds one instance model (SysML v2 text) together with the user libraries it depends on and the parts of the
	 * standard library it needs, parsed and resolved as one SysMLv2::Files::Workspace.
	 *
	 * The instance model, the non-standard libraries and the needed standard library files are separate sources of one
	 * workspace: every source has its own root namespace, and the names and imports of all of them are resolved against each
	 * other by Workspace::resolve() (scoped resolution, imports, visibility, aliases, short names).
	 *
	 * Standard library files are loaded from the embedded resources (sysmlv2resources) on demand:
	 *  - the library packages that the instance model and the non-standard libraries name (`import ScalarValues::*;`,
	 *    `Base::Anything`, ...): every reference that cannot be resolved and starts with the name of a standard library package
	 *    loads that package's file; this is repeated for the loaded files, so the imports of the library files are followed too;
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
		 * Sets the instance model and rebuilds everything (a fresh workspace: nothing of an earlier model is kept, the
		 * non-standard libraries that were appended so far are parsed again with the new model).
		 * @param model SysML v2 text.
		 */
		void parseModel(std::string model);

		/**
		 * Adds a user library (SysML v2 text) that the instance model may import. It is kept for all later parseModel calls.
		 * If a model was already parsed the model is rebuilt so that it sees the library; otherwise the library is used by the
		 * next parseModel.
		 */
		void appendNonStandardLibrary(std::string model);

		/**
		 * Syntax errors of the instance model, the non-standard libraries and (should there be any) the standard library
		 * files that were loaded. References that cannot be resolved are not errors, see getUnresolvedReferences().
		 */
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> getParserErrors() const;

		/**
		 * The names in the instance model and in the non-standard libraries that could not be resolved, as ParserErrors of
		 * type WARNING (with source name, line and column). Unresolved references inside the standard library are not listed.
		 */
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> getUnresolvedReferences() const;

		/**
		 * The elements of all sources: instance model, non-standard libraries and the loaded standard library files (in that
		 * order). The root namespaces are not elements of a source and not included; the memberships are.
		 */
		std::vector<std::shared_ptr<KerML::Entities::Element>> getElements() const;

		/// The elements of the instance model and of the non-standard libraries only (see getElements()).
		std::vector<std::shared_ptr<KerML::Entities::Element>> getModelElements() const;

		/**
		 * The root namespace of the instance model: it owns the top-level elements of the model through their memberships.
		 * @return the namespace; null before the first parseModel call.
		 */
		std::shared_ptr<KerML::Entities::Namespace> getRootNamespace() const;

		/// All elements (see getElements()) whose declared name is @p name.
		std::list<std::shared_ptr<KerML::Entities::Element>> findAllElementsWithDeclaredName(std::string name);

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
		void rebuildModel();
		void loadStandardLibraries(size_t userSources);
		bool loadStandardLibrary(const std::string& packageName);

		std::unique_ptr<SysMLv2::Files::Workspace> Model;
		std::size_t UserSourceCount = 0;
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> ParserErrors;
		std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> UnresolvedReferences;
		std::vector<std::shared_ptr<KerML::Entities::Element>> Elements;
		std::shared_ptr<KerML::Entities::Namespace> RootNamespace = nullptr;
		std::vector<std::string> LoadedStandardLibraries;

		bool ModelParsed = false;
		std::string InstanceModel;
		std::vector<std::string> NonStandardLibraries;
	};
}
