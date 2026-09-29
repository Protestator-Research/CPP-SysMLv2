//
// Created by herzo on 24.09.2026.
//

#include <sysmlv2/service/implementation/InstanceManager.h>

#include <kerml/root/elements/Element.h>
#include <kerml/root/namespaces/NamespaceImport.h>
#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/namespaces/OwningMembership.h>
#include <kerml/root/namespaces/Import.h>
#include <sysmlv2/Parser.h>

#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <unordered_set>
#include <cmrc/cmrc.hpp>

#include "kerml/ErrorTypes.h"

CMRC_DECLARE(Library);

namespace SysMLv2::API
{

	void InstanceManager::parseModel(std::string model)
	{
		InstanceModel = model;
		rebuildModel();
	}

	void InstanceManager::appendNonStandardLibrary(std::string model)
	{
		NonStandardLibraries.push_back(model);
	}

	std::vector<std::shared_ptr<SysMLv2::Files::ParserError>> InstanceManager::getParserErrors() const
	{
		return ParserErrors;
	}

	std::vector<std::shared_ptr<KerML::Entities::Element>> InstanceManager::getElements() const
	{
		return Elements;
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
			if (elem->declaredName() == name)
				returnValue.emplace_back(elem);
		}

		return returnValue;
	}

	std::shared_ptr<KerML::Entities::Element> InstanceManager::findElementWithQualifiedName(const std::string& name) const
	{
		auto it = std::find_if(Elements.begin(), Elements.end(), [&name](const std::shared_ptr<KerML::Entities::Element>& elem)
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
				return (elem->getId() == uuid);
			});

		if (it != Elements.end())
			return *it;

		return nullptr;
	}

	void InstanceManager::rebuildModel()
	{
		Elements.clear();
		ParserErrors.clear();
		LogicalErrors.clear();
		const auto modelResults = SysMLv2::Files::Parser::parseSysMLv2(InstanceModel);
		Elements.insert(Elements.end(), modelResults.first.begin(), modelResults.first.end());
		ParserErrors.insert(ParserErrors.end(), modelResults.second.begin(), modelResults.second.end());
		importStandardLibraries();
		parseNonStandardLibraries();
		resolveNamespaceImports();
		analyzeRootNamespaces();
	}

	void InstanceManager::importStandardLibraries() {
		std::vector<std::shared_ptr<KerML::Entities::Element>> elementsToAppend;
		for (const auto& element : Elements) {
			if (element->getType() == "NamespaceImport") {
				const auto& import = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(element);
				if (import->importedNamespace() != nullptr)
				{
					if (!import->importedNamespace()->declaredName().has_value())
					{
						LogicalErrors.push_back("Namespace Import with no name is not allowed!");
						continue;
					}
					auto it = std::ranges::find(StandardLibraries, import->importedNamespace()->declaredName());

					if (it != StandardLibraries.end()) {
						auto fs = cmrc::Library::get_filesystem();
						std::size_t index = std::distance(StandardLibraries.begin(), it);
						auto data = fs.open(StandardLibrariesPaths[index]);
						std::string content(data.begin(), data.end());
						const auto parserResults = SysMLv2::Files::Parser::parseSysMLv2(content);
						elementsToAppend.insert(elementsToAppend.end(), parserResults.first.begin(), parserResults.first.end());
					}
				}
				else
				{
					LogicalErrors.push_back("Error: No Namespace created for import");
				}
			}
		}
		Elements.insert(Elements.end(), elementsToAppend.begin(), elementsToAppend.end());
	}

	void InstanceManager::parseNonStandardLibraries()
	{
		for (const auto& model : NonStandardLibraries)
		{
			const auto modelResults = SysMLv2::Files::Parser::parseSysMLv2(model);
			Elements.insert(Elements.end(), modelResults.first.begin(), modelResults.first.end());
			ParserErrors.insert(ParserErrors.end(), modelResults.second.begin(), modelResults.second.end());
		}
	}

	void InstanceManager::resolveNamespaceImports()
	{
		for (const auto& elem : Elements)
		{
			if (elem->getType() == "NamespaceImport")
			{
				const auto& import = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(elem);
				if (import->importedNamespace() != nullptr) {
					if (!import->importedNamespace()->declaredName().has_value())
					{
						//std::cout << "Error: NamespaceImport of Namespace without name." << std::endl;
						LogicalErrors.push_back("Error: NamespaceImport of Namespace without name.");
						continue;
					}
					const auto& elementsWithNames = findAllElementsWithDeclaredName(import->importedNamespace()->declaredName().value());
					
					bool namespaceChanged = false;
					boost::uuids::uuid oldNamespaceImportUUID;

					for (const auto& elementOfFinding :elementsWithNames)
					{
						if (elementOfFinding->getType() != "Namespace")
						{
							//std::cout << "Error: NamespaceImport should result in an namespace that is Imported. Please use the Membership Import!" << std::endl;
							LogicalErrors.push_back("Error: NamespaceImport should result in an namespace that is Imported. Please use the Membership Import!");
							continue;
						}
						if (!elementOfFinding->ownedElements().empty())
						{
							oldNamespaceImportUUID = import->importedNamespace()->getId();
							import->setImportedNamespace(std::dynamic_pointer_cast<KerML::Entities::Namespace>(elementOfFinding));
							namespaceChanged = true;
						}
					}

					if (namespaceChanged) {
						auto it = std::find_if(Elements.begin(), Elements.end(), [oldNamespaceImportUUID](const std::shared_ptr<KerML::Entities::Element>& elem)
							{
								return (elem->getId() == oldNamespaceImportUUID);
							});
						if (it != Elements.end())
						{
							Elements.erase(it);
						}else
						{
							//std::cout << "Internal Error: Element that is replaced not found in Element list." << std::endl;
							LogicalErrors.push_back("Internal Error: Element that is replaced not found in Element list.");
						}
					}
				}
				else {
					//std::cout << "Error: Namespace Import Without valid Namespace causes errors in model." << std::endl;
					LogicalErrors.push_back("Error: Namespace Import Without valid Namespace causes errors in model.");
				}
			}
		}
	}

	void InstanceManager::analyzeRootNamespaces()
	{
		RootNamespace = std::make_shared<KerML::Entities::Namespace>("");

		std::vector<std::shared_ptr<KerML::Entities::Element>> rootCandidates;
		for (const auto& elem : Elements)
		{
			if (elem == nullptr || elem == RootNamespace) {
				continue;
			}

			if (elem->owner() == nullptr) {
				rootCandidates.push_back(elem);
			}
		}

		for (const auto& elem : rootCandidates)
		{
			attachToRootNamespace(elem);
		}

		updateQualifiedNamesRecursively(RootNamespace, "");
	}

	void InstanceManager::attachToRootNamespace(const std::shared_ptr<KerML::Entities::Element>& elem)
	{
		if (!elem) return;

		if (auto importElem = std::dynamic_pointer_cast<KerML::Entities::Import>(elem))
		{
			importElem->setOwner(RootNamespace);
			importElem->setImportOwningNamespace(RootNamespace);
			RootNamespace->appendOwnedImport(importElem);
			RootNamespace->appendOwnedElement(importElem);
			return;
		}

		auto membership = std::make_shared<KerML::Entities::OwningMembership>();
		membership->setVisibility(KerML::Entities::PUBLIC);

		if (elem->declaredName().has_value()) {
			membership->setMemberName(elem->declaredName().value());
			membership->setDeclaredName(elem->declaredName().value());
		}
		if (elem->declaredShortName().has_value()) {
			membership->setMemberShortName(elem->declaredShortName().value());
			membership->setDeclaredShortName(elem->declaredShortName().value());
		}

		membership->setMemberElement(elem);
		membership->setMembershipOwningNamespace(RootNamespace);
		membership->setOwner(RootNamespace);

		elem->setOwner(RootNamespace);
		elem->setOwningRelationship(membership);

		RootNamespace->appendOwnedMember(elem);
		RootNamespace->appendMember(elem);
		RootNamespace->appendOwnedMembership(membership);
		RootNamespace->appendMembership(membership);
		RootNamespace->appendOwnedElement(elem);
		RootNamespace->appendOwnedElement(membership);

		Elements.push_back(membership);
	}

	void InstanceManager::updateQualifiedNamesRecursively(
		const std::shared_ptr<KerML::Entities::Element>& elem, 
		const std::string& parentQualifiedName)
	{
		if (!elem) return;

		std::unordered_set<const KerML::Entities::Element*> visited;

		auto recurse = [&](auto self, const std::shared_ptr<KerML::Entities::Element>& currentElem, const std::string& currentParentQName) -> void {
			if (!currentElem) return;
			if (visited.contains(currentElem.get())) return;
			visited.insert(currentElem.get());

			std::string currentName;
			if (currentElem->declaredName().has_value() && !currentElem->declaredName()->empty()) {
				currentName = currentElem->declaredName().value();
			} else if (currentElem->declaredShortName().has_value() && !currentElem->declaredShortName()->empty()) {
				currentName = currentElem->declaredShortName().value();
			}

			std::string nextQName = currentParentQName;
			bool isRelationship = (std::dynamic_pointer_cast<KerML::Entities::Relationship>(currentElem) != nullptr);

			if (!currentName.empty() && !isRelationship) {
				nextQName = currentParentQName.empty() ? currentName : (currentParentQName + "::" + currentName);
				currentElem->setQualifiedName(nextQName);
			}

			for (const auto& child : currentElem->ownedElements())
			{
				if (child) {
					self(self, child, nextQName);
				}
			}
		};

		recurse(recurse, elem, parentQualifiedName);
	}
}
