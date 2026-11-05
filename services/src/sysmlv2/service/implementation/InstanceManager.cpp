//
// Created by herzo on 24.09.2026.
//

#include <kerml/root/elements/NameEscaping.h>
#include <sysmlv2/service/implementation/InstanceManager.h>
#include "../StandardLibraryTable.h"

#include <kerml/core/features/Feature.h>
#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <sysmlv2/ParserError.h>
#include <sysmlv2/Workspace.h>

#include <boost/uuid/uuid.hpp>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(Library);
CMRC_DECLARE(LibraryXmi);

namespace SysMLv2::API
{
	namespace
	{

		/// The levels of the sources in the mode that keeps the workspace (see Workspace::setSourceLevel()): a reference of the standard
		/// library never resolves to an element of the model.
		constexpr int StandardLevel = 0;
		constexpr int UserLevel = 1;


		using Detail::StandardLibraryEntry;

		const StandardLibraryEntry* findStandardLibrary(const std::string& packageName)
		{
			const auto it = std::find_if(std::begin(Detail::StandardLibraryTable), std::end(Detail::StandardLibraryTable),
				[&packageName](const StandardLibraryEntry& file) { return packageName == file.Name; });
			return it == std::end(Detail::StandardLibraryTable) ? nullptr : &*it;
		}

		/// The library package a metaclass name (`PartUsage`) makes necessary: the packages that the implicit specializations of
		/// the elements of that metaclass refer to (`Parts::parts`, ...). A metaclass name that contains Text needs Package.
		/// The table over-approximates (the imports of the library files add the rest); it only has to name the packages that a
		/// model does not have to import to get implicit specializations.
		struct ImplicitLibraryPackage
		{
			const char* Text;
			const char* Package;
		};

		constexpr ImplicitLibraryPackage ImplicitLibraryPackages[] = {
			// SysML
			{"Concern", "Requirements"}, {"Requirement", "Requirements"}, {"Satisfy", "Requirements"},
			{"View", "Views"}, {"Rendering", "Views"},
			{"Constraint", "Constraints"},
			{"UseCase", "UseCases"}, {"AnalysisCase", "AnalysisCases"}, {"VerificationCase", "VerificationCases"}, {"Case", "Cases"},
			{"Calculation", "Calculations"},
			{"State", "States"},
			{"Flow", "Flows"},
			{"Action", "Actions"}, {"Transition", "Actions"}, {"Node", "Actions"}, {"Loop", "Actions"},
			{"Interface", "Interfaces"}, {"Allocation", "Allocations"},
			{"Connection", "Connections"}, {"Connector", "Connections"},
			{"Port", "Ports"}, {"Part", "Parts"}, {"Item", "Items"}, {"Metadata", "Metadata"},
			{"Enumeration", "Attributes"}, {"Attribute", "Attributes"},
			{"Occurrence", "Occurrences"}, {"Succession", "Occurrences"},
			// KerML
			{"Metaclass", "Metaobjects"}, {"Structure", "Objects"}, {"Interaction", "Transfers"}, {"Association", "Links"},
			{"Binding", "Links"}, {"Connector", "Links"}, {"Class", "Occurrences"}, {"Predicate", "Performances"},
			{"Function", "Performances"}, {"Behavior", "Performances"}, {"Step", "Performances"}, {"Expression", "Performances"},
			{"Invariant", "Performances"}
		};

		/// The name a reference starts with: `ScalarValues::Real` -> `ScalarValues`, `'Some Name'.x` -> `Some Name`.
		std::string firstSegment(const std::string& name)
		{
			std::string segment;
			bool quoted = false;
			for (const char c : name)
			{
				if (c == '\'')
				{
					quoted = !quoted;
					continue;
				}
				if (!quoted && (c == ':' || c == '.'))
					break;
				segment.push_back(c);
			}
			return segment;
		}

		/// The library package of a library file (`Kernel Libraries/Base.kermlx` -> `Base`): the file is named like the package.
		std::string packageOfFile(const std::string& file)
		{
			const auto slash = file.find_last_of("/\\");
			const auto start = slash == std::string::npos ? 0 : slash + 1;
			const auto dot = file.find('.', start);
			return file.substr(start, dot == std::string::npos ? std::string::npos : dot - start);
		}

		/// Whether @p file ends with .sysmlx, .kermlx or .xmi (any case).
		bool hasXmiExtension(const std::string& file)
		{
			std::string lower(file);
			std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
			const std::string_view view(lower);
			return view.ends_with(".sysmlx") || view.ends_with(".kermlx") || view.ends_with(".xmi");
		}

		/// The library package that a reference that no loaded source could resolve names. The XMI files refer to each other by hrefs
		/// ("<path of the file>#<id>"): the file of an href is a library file, which is named like its package (`Base.kermlx`). The other
		/// references are names.
		std::string packageOfReference(const std::string& name)
		{
			// A name is an href only if it does not start with a quote (`'a#b'::x` is a name) and the part before the # is a file of the
			// XMI formats: otherwise it is a name, which starts with its first segment.
			const auto hash = name.rfind('#');
			if (hash == std::string::npos || name.front() == '\'' || !hasXmiExtension(name.substr(0, hash)))
				return firstSegment(name);
			return packageOfFile(name.substr(0, hash));
		}

		/// The elements @p element owns: its owned elements, the owned members of a namespace and the owned related elements of a
		/// relationship (a membership does not list its member among its owned elements).
		std::vector<std::shared_ptr<KerML::Entities::Element>> ownedChildren(const std::shared_ptr<KerML::Entities::Element>& element)
		{
			std::vector<std::shared_ptr<KerML::Entities::Element>> children = element->ownedElements();
			if (const auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element))
			{
				const auto members = ns->ownedMember();
				children.insert(children.end(), members.begin(), members.end());
			}
			if (const auto relationship = std::dynamic_pointer_cast<KerML::Entities::Relationship>(element))
			{
				const auto related = relationship->ownedRelatedElement();
				children.insert(children.end(), related.begin(), related.end());
			}
			return children;
		}

		/// The name an element has for the qualified names: its declared name, else its declared short name, else (a feature) the declared name of the
		/// feature it redefines first, found along the naming features. Empty if there is none.
		std::string nameOf(const std::shared_ptr<KerML::Entities::Element>& element)
		{
			if (element->declaredName().has_value() && !element->declaredName()->empty())
				return element->declaredName().value();
			if (element->declaredShortName().has_value() && !element->declaredShortName()->empty())
				return element->declaredShortName().value();
			auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(element);
			std::unordered_set<const KerML::Entities::Feature*> visited;
			while (feature && visited.insert(feature.get()).second)
			{
				const auto naming = feature->namingFeature();
				if (!naming.has_value() || !naming.value())
					break;
				const auto& named = naming.value();
				if (named->declaredName().has_value() && !named->declaredName()->empty())
					return named->declaredName().value();
				if (named->declaredShortName().has_value())
					break;
				feature = named;
			}
			return std::string();
		}

		/// Sets the qualified name of every named, non-relationship element below @p root from the chain of the owning
		/// namespaces. An unnamed element gets none and adds no segment to the names of what it owns.
		void assignQualifiedNames(const std::shared_ptr<KerML::Entities::Element>& root)
		{
			if (!root)
				return;

			std::unordered_set<const KerML::Entities::Element*> visited;
			const auto visit = [&visited](auto self, const std::shared_ptr<KerML::Entities::Element>& element, const std::string& parent) -> void
			{
				if (!element || !visited.insert(element.get()).second)
					return;

				// The name as the notation writes it: declared names are stored without quotes, a feature without a declared name or short name
				// (`:>> p`) is known by the name of the feature it redefines. (Not Element::effectiveName(): its fallback to the qualified name
				// that an earlier run assigned would give the names of elements with a short name only a second time.)
				std::string name;
				if (const auto own = nameOf(element); !own.empty())
					name = KerML::Names::escapeName(own);

				std::string qualifiedName = parent;
				if (!name.empty() && std::dynamic_pointer_cast<KerML::Entities::Relationship>(element) == nullptr)
				{
					qualifiedName = parent.empty() ? name : parent + "::" + name;
					element->setQualifiedName(qualifiedName);
				}

				for (const auto& child : ownedChildren(element))
					self(self, child, qualifiedName);
			};

			// The root namespace itself has no name: its members start the qualified names.
			for (const auto& child : ownedChildren(root))
				visit(visit, child, "");
		}
	}

	InstanceManager::InstanceManager() = default;

	InstanceManager::~InstanceManager() = default;

	void InstanceManager::setReuseStandardLibrary(bool reuse)
	{
		ReuseStandardLibrary = reuse;
		WorkspaceReusable = false; // the workspace of the next parse is built for the mode
	}

	bool InstanceManager::reuseStandardLibrary() const
	{
		return ReuseStandardLibrary;
	}

	void InstanceManager::setStandardLibraryFormat(StandardLibraryFormat format)
	{
		LibraryFormat = format;
		WorkspaceReusable = false; // a workspace with the library in the other format is not kept
	}

	StandardLibraryFormat InstanceManager::standardLibraryFormat() const
	{
		return LibraryFormat;
	}

	void InstanceManager::parseModel(std::string model)
	{
		InstanceModel = std::move(model);
		ModelParsed = true;
		if (ReuseStandardLibrary && WorkspaceReusable && Model)
			updateModel();
		else
			rebuildModel();
	}

	void InstanceManager::appendNonStandardLibrary(std::string model)
	{
		NonStandardLibraries.push_back(std::move(model));
		if (!ModelParsed)
			return;
		if (ReuseStandardLibrary && WorkspaceReusable && Model)
			addNonStandardLibrary();
		else
			rebuildModel();
	}

	const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& InstanceManager::getParserErrors() const
	{
		return ParserErrors;
	}

	const std::vector<std::shared_ptr<SysMLv2::Files::ParserError>>& InstanceManager::getUnresolvedReferences() const
	{
		return UnresolvedReferences;
	}

	const std::vector<std::shared_ptr<KerML::Entities::Element>>& InstanceManager::getElements() const
	{
		return Elements;
	}

	std::vector<std::shared_ptr<KerML::Entities::Element>> InstanceManager::getModelElements() const
	{
		std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
		if (!Model)
			return elements;

		for (const std::size_t source : UserSources)
		{
			const auto& sourceElements = Model->elements(source);
			elements.insert(elements.end(), sourceElements.begin(), sourceElements.end());
		}
		return elements;
	}

	std::shared_ptr<KerML::Entities::Namespace> InstanceManager::getRootNamespace() const
	{
		return RootNamespace;
	}

	std::list<std::shared_ptr<KerML::Entities::Element>> InstanceManager::findAllElementsWithDeclaredName(const std::string& name) const
	{
		const auto it = ElementsByDeclaredName.find(name);
		if (it == ElementsByDeclaredName.end())
			return {};
		return std::list<std::shared_ptr<KerML::Entities::Element>>(it->second.begin(), it->second.end());
	}

	std::shared_ptr<KerML::Entities::Element> InstanceManager::findElementWithQualifiedName(const std::string& name) const
	{
		if (!Model || name.empty())
			return nullptr;

		// Scoped lookup from the implicit global namespace (the root packages of all sources): handles aliases and quoted names.
		const auto found = Model->find(name);
		if (found && !SysMLv2::Files::isUnresolved(found))
			return found;

		// Elements that are not reachable by name from the global namespace (top-level elements that are no packages, ...).
		const auto it = ElementsByQualifiedName.find(name);
		return it == ElementsByQualifiedName.end() ? nullptr : it->second;
	}

	std::shared_ptr<KerML::Entities::Element> InstanceManager::findElementWithId(const boost::uuids::uuid& uuid) const
	{
		const auto it = ElementsById.find(uuid);
		return it == ElementsById.end() ? nullptr : it->second;
	}

	void InstanceManager::buildIndices()
	{
		ElementsById.clear();
		ElementsByDeclaredName.clear();
		ElementsByQualifiedName.clear();
		ElementsById.reserve(Elements.size());
		for (const auto& elem : Elements)
		{
			if (!elem)
				continue;
			ElementsById.emplace(elem->getId(), elem); // (the first element of an id wins, like the linear search before)
			if (elem->declaredName().has_value())
				ElementsByDeclaredName[elem->declaredName().value()].push_back(elem);
			if (elem->qualifiedName().has_value())
				ElementsByQualifiedName.emplace(elem->qualifiedName().value(), elem);
		}
	}

	void InstanceManager::rebuildModel()
	{
		Elements.clear();
		ParserErrors.clear();
		UnresolvedReferences.clear();
		LoadedStandardLibraries.clear();
		UserSources.clear();
		RootNamespace = nullptr;
		Model = std::make_unique<SysMLv2::Files::Workspace>();

		// The instance model is the first source, the non-standard libraries follow, the standard library files come last. (In the mode that
		// keeps the workspace the user sources have a level above the standard library.)
		const int userLevel = ReuseStandardLibrary ? UserLevel : StandardLevel;
		UserSources.push_back(Model->addText(InstanceModel, "InstanceModel", SysMLv2::Files::SourceLanguage::SysML, userLevel));
		for (std::size_t index = 0; index < NonStandardLibraries.size(); ++index)
			UserSources.push_back(Model->addText(NonStandardLibraries[index], "NonStandardLibrary" + std::to_string(index + 1),
				SysMLv2::Files::SourceLanguage::SysML, userLevel));
		ActiveFormat = formatFor(UserSources);

		const std::size_t firstLibrary = loadStandardLibraries(UserSources);
		publishModel(UserSources, firstLibrary);
		WorkspaceReusable = ReuseStandardLibrary;
	}

	void InstanceManager::updateModel()
	{
		// The model and the non-standard libraries are parsed again: the targets of their references may be elements of the old model. The
		// standard library files stay as they are, resolved.
		Model->replaceSource(UserSources.front(), InstanceModel, SysMLv2::Files::SourceLanguage::SysML);
		for (std::size_t index = 0; index < NonStandardLibraries.size(); ++index)
			Model->replaceSource(UserSources[index + 1], NonStandardLibraries[index], SysMLv2::Files::SourceLanguage::SysML);

		// (the XMI files cannot refer to a package of the model by name: a model that defines a package with the name of a standard library
		// package is processed with the text, and the workspace that has the library in the other format is built anew)
		if (definesLoadedStandardPackage(UserSources) || formatFor(UserSources) != ActiveFormat)
		{
			rebuildModel();
			return;
		}
		const std::size_t firstLibrary = loadStandardLibraries(UserSources);
		publishModel(UserSources, firstLibrary);
	}

	void InstanceManager::addNonStandardLibrary()
	{
		const std::size_t source = Model->addText(NonStandardLibraries.back(), "NonStandardLibrary" + std::to_string(NonStandardLibraries.size()),
			SysMLv2::Files::SourceLanguage::SysML, UserLevel);
		UserSources.push_back(source);

		const std::vector<std::size_t> added{source};
		if (definesLoadedStandardPackage(added) || formatFor(UserSources) != ActiveFormat)
		{
			rebuildModel();
			return;
		}
		const std::size_t firstLibrary = loadStandardLibraries(added);
		publishModel(added, firstLibrary);
	}

	StandardLibraryFormat InstanceManager::formatFor(const std::vector<std::size_t>& sources) const
	{
		if (LibraryFormat != StandardLibraryFormat::Xmi)
			return LibraryFormat;
		for (const std::size_t source : sources)
		{
			for (const auto& package : Model->rootPackages(source))
			{
				if (package->declaredName().has_value() && findStandardLibrary(package->declaredName().value()) != nullptr)
					return StandardLibraryFormat::Text;
			}
		}
		return StandardLibraryFormat::Xmi;
	}

	bool InstanceManager::definesLoadedStandardPackage(const std::vector<std::size_t>& sources) const
	{
		for (const std::size_t source : sources)
		{
			for (const auto& package : Model->rootPackages(source))
			{
				if (package->declaredName().has_value() && LoadedStandardLibraries.count(package->declaredName().value()) != 0)
					return true;
			}
		}
		return false;
	}

	void InstanceManager::publishModel(const std::vector<std::size_t>& changed, std::size_t firstLibrary)
	{
		ParserErrors = Model->errors();
		UnresolvedReferences.clear();
		for (const std::size_t source : UserSources)
		{
			const auto warnings = Model->unresolvedAsWarnings(source);
			UnresolvedReferences.insert(UnresolvedReferences.end(), warnings.begin(), warnings.end());
		}
		Elements = Model->elements();

		// The sources that are new or were replaced; the other ones keep the qualified names they have.
		for (const std::size_t source : changed)
			assignQualifiedNames(Model->rootNamespace(source));
		for (std::size_t source = firstLibrary; source < Model->sourceCount(); ++source)
			assignQualifiedNames(Model->rootNamespace(source));
		buildIndices();

		RootNamespace = Model->rootNamespace(UserSources.front());
		if (RootNamespace == nullptr)
			RootNamespace = std::make_shared<KerML::Entities::Namespace>(""); // empty model: an empty root namespace
	}

	std::size_t InstanceManager::loadStandardLibraries(const std::vector<std::size_t>& changed)
	{
		// Packages that the model or a non-standard library defines itself are not taken from the standard library.
		UserPackages.clear();
		for (const std::size_t source : UserSources)
		{
			for (const auto& package : Model->rootPackages(source))
			{
				if (package->declaredName().has_value())
					UserPackages.insert(package->declaredName().value());
			}
		}

		// The standard library files are added from here on.
		const std::size_t firstLibrary = Model->sourceCount();

		// Base is the implicit general of every feature and type.
		loadStandardLibrary("Base");

		// The packages of the implicit specializations, by the metaclasses that occur in the model.
		std::unordered_set<std::string> wanted;
		for (const std::size_t source : changed)
		{
			std::unordered_set<std::string> metaclasses;
			for (const auto& element : Model->elements(source))
			{
				if (element)
					metaclasses.insert(element->getType());
			}
			for (const auto& metaclass : metaclasses)
			{
				for (const auto& entry : ImplicitLibraryPackages)
				{
					if (metaclass.find(entry.Text) != std::string::npos)
						wanted.insert(entry.Package);
				}
			}
		}
		for (const auto& entry : ImplicitLibraryPackages)
		{
			if (wanted.count(entry.Package) != 0)
				loadStandardLibrary(entry.Package);
		}

		// The packages that the sources name: every reference (imports included) that starts with the name of a standard library package
		// loads it; this goes on for the files that are loaded. That is what resolving would find missing, without a round of resolving for
		// every level of imports.
		std::vector<std::size_t> pending = changed;
		for (std::size_t source = firstLibrary; source < Model->sourceCount(); ++source)
			pending.push_back(source);
		preloadStandardLibraries(std::move(pending));

		// The packages that the loaded sources name and that were not found above: every unresolved reference that starts with the name of
		// a standard library package loads it (a safety net, normally one resolve). The files loaded in one round can name further packages,
		// so resolve and look again.
		for (;;)
		{
			Model->resolve();
			bool loaded = false;
			for (const auto& reference : Model->unresolvedReferences())
			{
				if (loadStandardLibrary(packageOfReference(reference.name)))
					loaded = true;
			}
			if (!loaded)
				break;
		}
		return firstLibrary;
	}

	void InstanceManager::preloadStandardLibraries(std::vector<std::size_t> pending)
	{
		while (!pending.empty())
		{
			const std::size_t source = pending.back();
			pending.pop_back();
			for (const auto& name : Model->referenceNames(source))
			{
				if (loadStandardLibrary(firstSegment(name)))
					pending.push_back(Model->sourceCount() - 1); // the file just added
			}
			// An XMI file names the files it needs by its hrefs, not by names.
			for (const auto& file : Model->referencedFiles(source))
			{
				if (loadStandardLibrary(packageOfFile(file)))
					pending.push_back(Model->sourceCount() - 1);
			}
		}
	}

	bool InstanceManager::loadStandardLibrary(const std::string& packageName)
	{
		if (LoadedStandardLibraries.count(packageName) != 0 || UserPackages.count(packageName) != 0)
			return false;

		const StandardLibraryEntry* file = findStandardLibrary(packageName);
		if (file == nullptr)
			return false;

		LoadedStandardLibraries.insert(packageName);
		try
		{
			if (ActiveFormat == StandardLibraryFormat::Xmi)
			{
				const auto fs = cmrc::LibraryXmi::get_filesystem();
				const auto data = fs.open(file->XmiPath);
				Model->addText(std::string(data.begin(), data.end()), std::string(file->XmiPath), SysMLv2::Files::SourceLanguage::Xmi, StandardLevel);
			}
			else
			{
				const auto fs = cmrc::Library::get_filesystem();
				const auto data = fs.open(file->Path);
				const std::string_view path(file->Path);
				Model->addText(std::string(data.begin(), data.end()), std::string(path),
					path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML, StandardLevel);
			}
		}
		catch (const std::system_error&)
		{
			return false; // the resource is not embedded: the reference stays unresolved
		}
		return true;
	}
}
