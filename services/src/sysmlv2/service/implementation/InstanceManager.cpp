//
// Created by herzo on 24.09.2026.
//

#include <sysmlv2/service/implementation/InstanceManager.h>

#include <kerml/root/elements/Element.h>
#include <kerml/root/namespaces/NamespaceImport.h>
#include <kerml/root/namespaces/Namespace.h>
#include <sysmlv2/Parser.h>

#include <boost/uuid/uuid.hpp>
#include <iostream>
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
		const auto modelResults = SysMLv2::Files::Parser::parseSysMLv2(InstanceModel);
		Elements.insert(Elements.end(), modelResults.first.begin(), modelResults.first.end());
		ParserErrors.insert(ParserErrors.end(), modelResults.second.begin(), modelResults.second.end());
		importStandardLibraries();
		parseNonStandardLibraries();
	}

	void InstanceManager::importStandardLibraries() {
		std::vector<std::shared_ptr<KerML::Entities::Element>> elementsToAppend;
		for (const auto& element : Elements) {
			if (element->getType() == "NamespaceImport") {
				const auto& import = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(element);
				if (import->importedNamespace() != nullptr)
				{
					std::cout << "Imported Namespace: " << import->importedNamespace()->declaredName().value_or("error in getting namespace name") << std::endl;
					auto it = std::ranges::find(StandardLibraries, import->importedNamespace()->declaredName());

					if (it != StandardLibraries.end()) {
						std::cout << "Use Standard Libary Namespaces: " << *it << '\n';
						auto fs = cmrc::Library::get_filesystem();
						std::size_t index = std::distance(StandardLibraries.begin(), it);
						auto data = fs.open(StandardLibrariesPaths[index]);
						std::string content(data.begin(), data.end());
						const auto parserResults = SysMLv2::Files::Parser::parseSysMLv2(content);
						elementsToAppend.insert(elementsToAppend.end(), parserResults.first.begin(), parserResults.first.end());
						//ParserErrors.insert(ParserErrors.end(), parserResults.second.begin(), parserResults.second.end());
					}
				}
				else
				{
					std::cout << "No Namespace created for import" << std::endl;
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
						std::cout << "Error: NamespaceImport of Namespace without name." << std::endl;
						return;
					}
					const auto& elementsWithNames = findAllElementsWithDeclaredName(import->importedNamespace()->declaredName().value());
					
					bool namespaceChanged = false;
					boost::uuids::uuid oldNamespaceImportUUID;

					for (const auto elementOfFinding :elementsWithNames)
					{
						if (elementOfFinding->getType() != "Namespace")
						{
							std::cout << "Error: NamespaceImport should result in an namespace that is Imported. Please use the Membership Import!" << std::endl;
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
							std::cout << "Internal Error: Element that is replaced not found in Element list." << std::endl;
						}
					}
				}
				else
					std::cout << "Error: Namespace Import Without valid Namespace causes errors in model." << std::endl;
			}
		}
	}

	void InstanceManager::analyzeRootNamespaces()
	{
		RootNamespace = std::make_shared<KerML::Entities::Namespace>("root");
		for (const auto& elem : Elements)
		{
			if (elem->owner()==nullptr)
			{
				RootNamespace->appendOwnedMember(elem);
				elem->setOwner(RootNamespace);
			}
		}
	}
}
