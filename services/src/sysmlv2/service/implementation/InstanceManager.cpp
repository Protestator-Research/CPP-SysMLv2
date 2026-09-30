//
// Created by herzo on 24.09.2026.
//

#include <sysmlv2/service/implementation/InstanceManager.h>

#include <kerml/root/elements/Element.h>
#include <kerml/root/elements/Relationship.h>
#include <kerml/root/namespaces/Namespace.h>
#include <sysmlv2/ParserError.h>
#include <sysmlv2/Workspace.h>

#include <boost/uuid/uuid.hpp>
#include <algorithm>
#include <iterator>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(Library);

namespace SysMLv2::API
{
	namespace
	{
		/// The embedded standard library: the name of the (top-level) package and the path of its file in the resources
		/// (sysmlv2resources, namespace Library). The paths are those of resources/CMakeLists.txt.
		struct StandardLibraryFile
		{
			const char* Name;
			const char* Path;
		};

		constexpr StandardLibraryFile StandardLibrary[] = {
		// KerML/Semantic
		{"Base", "sysml.library/KerML/Semantic/Base.kerml"},
		{"Clocks", "sysml.library/KerML/Semantic/Clocks.kerml"},
		{"ControlPerformances", "sysml.library/KerML/Semantic/ControlPerformances.kerml"},
		{"FeatureReferencingPerformances", "sysml.library/KerML/Semantic/FeatureReferencingPerformances.kerml"},
		{"KerML", "sysml.library/KerML/Semantic/KerML.kerml"},
		{"Links", "sysml.library/KerML/Semantic/Links.kerml"},
		{"Metaobjects", "sysml.library/KerML/Semantic/Metaobjects.kerml"},
		{"Objects", "sysml.library/KerML/Semantic/Objects.kerml"},
		{"Observation", "sysml.library/KerML/Semantic/Observation.kerml"},
		{"Occurrences", "sysml.library/KerML/Semantic/Occurrences.kerml"},
		{"Performances", "sysml.library/KerML/Semantic/Performances.kerml"},
		{"SpatialFrames", "sysml.library/KerML/Semantic/SpatialFrames.kerml"},
		{"StatePerformances", "sysml.library/KerML/Semantic/StatePerformances.kerml"},
		{"Transfers", "sysml.library/KerML/Semantic/Transfers.kerml"},
		{"TransitionPerformances", "sysml.library/KerML/Semantic/TransitionPerformances.kerml"},
		{"Triggers", "sysml.library/KerML/Semantic/Triggers.kerml"},
		// KerML/DataTypes
		{"Collections", "sysml.library/KerML/DataTypes/Collections.kerml"},
		{"ScalarValues", "sysml.library/KerML/DataTypes/ScalarValues.kerml"},
		{"VectorValues", "sysml.library/KerML/DataTypes/VectorValues.kerml"},
		// KerML/Function
		{"BaseFunctions", "sysml.library/KerML/Function/BaseFunctions.kerml"},
		{"BooleanFunctions", "sysml.library/KerML/Function/BooleanFunctions.kerml"},
		{"CollectionFunctions", "sysml.library/KerML/Function/CollectionFunctions.kerml"},
		{"ComplexFunctions", "sysml.library/KerML/Function/ComplexFunctions.kerml"},
		{"ControlFunctions", "sysml.library/KerML/Function/ControlFunctions.kerml"},
		{"DataFunctions", "sysml.library/KerML/Function/DataFunctions.kerml"},
		{"IntegerFunctions", "sysml.library/KerML/Function/IntegerFunctions.kerml"},
		{"NaturalFunctions", "sysml.library/KerML/Function/NaturalFunctions.kerml"},
		{"NumericalFunctions", "sysml.library/KerML/Function/NumericalFunctions.kerml"},
		{"OccurrenceFunctions", "sysml.library/KerML/Function/OccurrenceFunctions.kerml"},
		{"RationalFunctions", "sysml.library/KerML/Function/RationalFunctions.kerml"},
		{"RealFunctions", "sysml.library/KerML/Function/RealFunctions.kerml"},
		{"ScalarFunctions", "sysml.library/KerML/Function/ScalarFunctions.kerml"},
		{"SequenceFunctions", "sysml.library/KerML/Function/SequenceFunctions.kerml"},
		{"StringFunctions", "sysml.library/KerML/Function/StringFunctions.kerml"},
		{"TrigFunctions", "sysml.library/KerML/Function/TrigFunctions.kerml"},
		{"VectorFunctions", "sysml.library/KerML/Function/VectorFunctions.kerml"},
		// DomainLibraries/Analysis
		{"AnalysisTooling", "sysml.library/DomainLibraries/Analysis/AnalysisTooling.sysml"},
		{"SampledFunctions", "sysml.library/DomainLibraries/Analysis/SampledFunctions.sysml"},
		{"StateSpaceRepresentation", "sysml.library/DomainLibraries/Analysis/StateSpaceRepresentation.sysml"},
		{"TradeStudies", "sysml.library/DomainLibraries/Analysis/TradeStudies.sysml"},
		// DomainLibraries/CauseAndEffect
		{"CausationConnections", "sysml.library/DomainLibraries/CauseAndEffect/CausationConnections.sysml"},
		{"CauseAndEffect", "sysml.library/DomainLibraries/CauseAndEffect/CauseAndEffect.sysml"},
		// DomainLibraries/Geometry
		{"ShapeItems", "sysml.library/DomainLibraries/Geometry/ShapeItems.sysml"},
		{"SpatialItems", "sysml.library/DomainLibraries/Geometry/SpatialItems.sysml"},
		// DomainLibraries/Metadata
		{"ImageMetadata", "sysml.library/DomainLibraries/Metadata/ImageMetadata.sysml"},
		{"ModelingMetadata", "sysml.library/DomainLibraries/Metadata/ModelingMetadata.sysml"},
		{"ParametersOfInterestMetadata", "sysml.library/DomainLibraries/Metadata/ParametersOfInterestMetadata.sysml"},
		{"RiskMetadata", "sysml.library/DomainLibraries/Metadata/RiskMetadata.sysml"},
		// DomainLibraries/QuantitiesAndUnits
		{"ISQ", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQ.sysml"},
		{"ISQAcoustics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAcoustics.sysml"},
		{"ISQAtomicNuclear", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQAtomicNuclear.sysml"},
		{"ISQBase", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQBase.sysml"},
		{"ISQCharacteristicNumbers", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCharacteristicNumbers.sysml"},
		{"ISQChemistryMolecular", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQChemistryMolecular.sysml"},
		{"ISQCondensedMatter", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQCondensedMatter.sysml"},
		{"ISQElectromagnetism", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQElectromagnetism.sysml"},
		{"ISQInformation", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQInformation.sysml"},
		{"ISQLight", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQLight.sysml"},
		{"ISQMechanics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQMechanics.sysml"},
		{"ISQSpaceTime", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQSpaceTime.sysml"},
		{"ISQThermodynamics", "sysml.library/DomainLibraries/QuantitiesAndUnits/ISQThermodynamics.sysml"},
		{"MeasurementRefCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementRefCalculations.sysml"},
		{"MeasurementReferences", "sysml.library/DomainLibraries/QuantitiesAndUnits/MeasurementReferences.sysml"},
		{"QuantityCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/QuantityCalculations.sysml"},
		{"Quantities", "sysml.library/DomainLibraries/QuantitiesAndUnits/Quantities.sysml"},
		{"SI", "sysml.library/DomainLibraries/QuantitiesAndUnits/SI.sysml"},
		{"SIPrefixes", "sysml.library/DomainLibraries/QuantitiesAndUnits/SIPrefixes.sysml"},
		{"TensorCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/TensorCalculations.sysml"},
		{"Time", "sysml.library/DomainLibraries/QuantitiesAndUnits/Time.sysml"},
		{"USCustomaryUnits", "sysml.library/DomainLibraries/QuantitiesAndUnits/USCustomaryUnits.sysml"},
		{"VectorCalculations", "sysml.library/DomainLibraries/QuantitiesAndUnits/VectorCalculations.sysml"},
		// DomainLibraries/RequirementDerivation
		{"DerivationConnections", "sysml.library/DomainLibraries/RequirementDerivation/DerivationConnections.sysml"},
		{"RequirementDerivation", "sysml.library/DomainLibraries/RequirementDerivation/RequirementDerivation.sysml"},
		// SystemsLibrary
		{"Actions", "sysml.library/SystemsLibrary/Actions.sysml"},
		{"Allocations", "sysml.library/SystemsLibrary/Allocations.sysml"},
		{"AnalysisCases", "sysml.library/SystemsLibrary/AnalysisCases.sysml"},
		{"Attributes", "sysml.library/SystemsLibrary/Attributes.sysml"},
		{"Calculations", "sysml.library/SystemsLibrary/Calculations.sysml"},
		{"Cases", "sysml.library/SystemsLibrary/Cases.sysml"},
		{"Connections", "sysml.library/SystemsLibrary/Connections.sysml"},
		{"Constraints", "sysml.library/SystemsLibrary/Constraints.sysml"},
		{"Flows", "sysml.library/SystemsLibrary/Flows.sysml"},
		{"Interfaces", "sysml.library/SystemsLibrary/Interfaces.sysml"},
		{"Items", "sysml.library/SystemsLibrary/Items.sysml"},
		{"Metadata", "sysml.library/SystemsLibrary/Metadata.sysml"},
		{"Parts", "sysml.library/SystemsLibrary/Parts.sysml"},
		{"Ports", "sysml.library/SystemsLibrary/Ports.sysml"},
		{"Requirements", "sysml.library/SystemsLibrary/Requirements.sysml"},
		{"StandardViewDefinitions", "sysml.library/SystemsLibrary/StandardViewDefinitions.sysml"},
		{"States", "sysml.library/SystemsLibrary/States.sysml"},
		{"SysML", "sysml.library/SystemsLibrary/SysML.sysml"},
		{"UseCases", "sysml.library/SystemsLibrary/UseCases.sysml"},
		{"VerificationCases", "sysml.library/SystemsLibrary/VerificationCases.sysml"},
		{"Views", "sysml.library/SystemsLibrary/Views.sysml"},
		};

		const StandardLibraryFile* findStandardLibrary(const std::string& packageName)
		{
			const auto it = std::find_if(std::begin(StandardLibrary), std::end(StandardLibrary),
				[&packageName](const StandardLibraryFile& file) { return packageName == file.Name; });
			return it == std::end(StandardLibrary) ? nullptr : &*it;
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

				std::string name;
				if (element->declaredName().has_value() && !element->declaredName()->empty())
					name = element->declaredName().value();
				else if (element->declaredShortName().has_value() && !element->declaredShortName()->empty())
					name = element->declaredShortName().value();

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

	void InstanceManager::parseModel(std::string model)
	{
		InstanceModel = std::move(model);
		ModelParsed = true;
		rebuildModel();
	}

	void InstanceManager::appendNonStandardLibrary(std::string model)
	{
		NonStandardLibraries.push_back(std::move(model));
		if (ModelParsed)
			rebuildModel();
	}

	std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> InstanceManager::getParserErrors() const
	{
		return ParserErrors;
	}

	std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> InstanceManager::getUnresolvedReferences() const
	{
		return UnresolvedReferences;
	}

	std::vector<std::shared_ptr<KerML::Entities::Element>> InstanceManager::getElements() const
	{
		return Elements;
	}

	std::vector<std::shared_ptr<KerML::Entities::Element>> InstanceManager::getModelElements() const
	{
		std::vector<std::shared_ptr<KerML::Entities::Element>> elements;
		if (!Model)
			return elements;

		for (std::size_t source = 0; source < UserSourceCount; ++source)
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

	std::list<std::shared_ptr<KerML::Entities::Element>> InstanceManager::findAllElementsWithDeclaredName(std::string name)
	{
		std::list<std::shared_ptr<KerML::Entities::Element>> returnValue;

		for (const auto& elem : Elements)
		{
			if (elem && elem->declaredName() == name)
				returnValue.emplace_back(elem);
		}

		return returnValue;
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
		const auto it = std::find_if(Elements.begin(), Elements.end(), [&name](const std::shared_ptr<KerML::Entities::Element>& elem)
			{
				return (elem && elem->qualifiedName().has_value() && elem->qualifiedName().value() == name);
			});

		if (it != Elements.end())
			return *it;

		return nullptr;
	}

	std::shared_ptr<KerML::Entities::Element> InstanceManager::findElementWithId(const boost::uuids::uuid& uuid) const
	{

		auto it = std::find_if(Elements.begin(), Elements.end(), [uuid](const std::shared_ptr<KerML::Entities::Element>& elem)
			{
				return (elem && elem->getId() == uuid);
			});

		if (it != Elements.end())
			return *it;

		return nullptr;
	}

	void InstanceManager::rebuildModel()
	{
		Elements.clear();
		ParserErrors.clear();
		UnresolvedReferences.clear();
		LoadedStandardLibraries.clear();
		RootNamespace = nullptr;
		Model = std::make_unique<SysMLv2::Files::Workspace>();

		// The instance model is source 0, the non-standard libraries follow, the standard library files come last.
		const std::size_t modelSource = Model->addText(InstanceModel, "InstanceModel", SysMLv2::Files::SourceLanguage::SysML);
		for (std::size_t index = 0; index < NonStandardLibraries.size(); ++index)
			Model->addText(NonStandardLibraries[index], "NonStandardLibrary" + std::to_string(index + 1), SysMLv2::Files::SourceLanguage::SysML);
		UserSourceCount = Model->sourceCount();

		loadStandardLibraries(UserSourceCount);
		Model->resolve();

		ParserErrors = Model->errors();
		for (std::size_t source = 0; source < UserSourceCount; ++source)
		{
			const auto warnings = Model->unresolvedAsWarnings(source);
			UnresolvedReferences.insert(UnresolvedReferences.end(), warnings.begin(), warnings.end());
		}
		Elements = Model->elements();

		for (std::size_t source = 0; source < Model->sourceCount(); ++source)
			assignQualifiedNames(Model->rootNamespace(source));

		RootNamespace = Model->rootNamespace(modelSource);
		if (RootNamespace == nullptr)
			RootNamespace = std::make_shared<KerML::Entities::Namespace>(""); // empty model: an empty root namespace
	}

	void InstanceManager::loadStandardLibraries(std::size_t userSources)
	{
		// Packages that the model or a non-standard library defines itself are not taken from the standard library.
		for (const auto& package : Model->rootPackages())
		{
			if (package->declaredName().has_value())
				LoadedStandardLibraries.push_back(package->declaredName().value());
		}

		// Base is the implicit general of every feature and type.
		loadStandardLibrary("Base");

		// The packages of the implicit specializations, by the metaclasses that occur in the model.
		std::unordered_set<std::string> wanted;
		for (std::size_t source = 0; source < userSources; ++source)
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

		// The packages that the loaded sources name: every unresolved reference that starts with the name of a standard library
		// package loads it. The files loaded in one round can name further packages, so resolve and look again.
		for (;;)
		{
			Model->resolve();
			bool loaded = false;
			for (const auto& reference : Model->unresolvedReferences())
			{
				if (loadStandardLibrary(firstSegment(reference.name)))
					loaded = true;
			}
			if (!loaded)
				break;
		}
	}

	bool InstanceManager::loadStandardLibrary(const std::string& packageName)
	{
		if (std::find(LoadedStandardLibraries.begin(), LoadedStandardLibraries.end(), packageName) != LoadedStandardLibraries.end())
			return false;

		const StandardLibraryFile* file = findStandardLibrary(packageName);
		if (file == nullptr)
			return false;

		LoadedStandardLibraries.push_back(packageName);
		try
		{
			const auto fs = cmrc::Library::get_filesystem();
			const auto data = fs.open(file->Path);
			const std::string_view path(file->Path);
			Model->addText(std::string(data.begin(), data.end()), std::string(path),
				path.ends_with(".kerml") ? SysMLv2::Files::SourceLanguage::KerML : SysMLv2::Files::SourceLanguage::SysML);
		}
		catch (const std::system_error&)
		{
			return false; // the resource is not embedded: the reference stays unresolved
		}
		return true;
	}
}
