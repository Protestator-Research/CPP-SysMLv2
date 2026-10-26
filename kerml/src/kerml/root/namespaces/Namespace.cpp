//
// Created by Moritz Herzog on 25.03.25.
//

#include <kerml/root/namespaces/Namespace.h>
#include <kerml/root/namespaces/Membership.h>
#include <kerml/root/namespaces/Import.h>

#include <vector>
#include <kerml/KerML.h>
#include <nlohmann/json.hpp>
#include "../../model/JsonSupport.h"

namespace KerML::Entities {

    Namespace::Namespace(boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {
        IsImported = false;
        _dType = "Namespace";
    }

    Namespace::Namespace(std::string namespaceName, bool isImported, boost::uuids::uuid elementID,
                         std::shared_ptr<Element> owner) : Element(elementID, owner) {
        setDeclaredName(namespaceName);
        IsImported = isImported;
        _dType = "Namespace";
    }

    Namespace::Namespace(std::string namespaceName, boost::uuids::uuid elementID, std::shared_ptr<Element> owner) : Element(elementID, owner) {
        IsImported = false;
        _dType = "Namespace";
        if (Json::looksLikeJson(namespaceName)) {
            deserializeAndPopulate(namespaceName);
            captureJsonSource(namespaceName);
        }
        else
            setDeclaredName(namespaceName);
    }

    bool Namespace::isImported() {
        return IsImported;
    }

    void Namespace::setIsImported(bool isImported) {
        IsImported = isImported;
    }

    std::vector<std::string> Namespace::namesOf(std::shared_ptr<Element> element) {
        std::vector<std::string> returnValue;

        std::string prefix = "";
        if (declaredName().has_value())
            prefix = declaredName().value() + "::";

        if (element->declaredName().has_value())
			returnValue.push_back(prefix + element->declaredName().value());

        if (element->declaredShortName().has_value())
			returnValue.push_back(prefix + element->declaredShortName().value());

        if (element->effectiveName().has_value())
			returnValue.push_back(prefix + element->effectiveName().value());

        if (element->effectiveShortName().has_value())
			returnValue.push_back(prefix + element->effectiveShortName().value());

        return returnValue;
    }

    VisibilityKind Namespace::visibilityOff(std::shared_ptr<Membership> mem) {
        return mem->visibility();
    }

    std::vector<std::shared_ptr<Membership>>
    Namespace::visibleMemberships(std::vector<std::shared_ptr<Namespace>> excluded, bool isRecursive, bool includeAll) {
        std::vector<std::shared_ptr<Membership>> returnValue;

        if(isRecursive) {
            for (const auto &ownedImport: ImportedMemberships) {
                if (std::find(excluded.begin(), excluded.end(), ownedImport->libraryNamespace()) == excluded.end()) {
                    if (includeAll)
                        returnValue.push_back(ownedImport);
                    else if (ownedImport->visibility() == PUBLIC)
                        returnValue.push_back(ownedImport);
                }

            }
        }

        for(const auto& ownedMembership: OwnedMembership) {
            if (std::find(excluded.begin(), excluded.end(), ownedMembership->libraryNamespace()) == excluded.end()) {
                if (includeAll)
                    returnValue.push_back(ownedMembership);
                else if (ownedMembership->visibility() == PUBLIC)
                    returnValue.push_back(ownedMembership);
            }
        }

        return returnValue;
    }

    std::vector<std::shared_ptr<Membership>>
    Namespace::importedMemberships(std::vector<std::shared_ptr<Namespace>> excluded) {
        std::vector<std::shared_ptr<Membership>> returnValue;
        for(const auto& ownedImport: OwnedImport) {
            if(std::find(excluded.begin(), excluded.end(), ownedImport->libraryNamespace()) == excluded.end())
                returnValue.insert(returnValue.end(),ownedImport->importedMemberships(excluded).begin(), ownedImport->importedMemberships(excluded).end());
        }
        return returnValue;
    }

    std::vector<std::shared_ptr<Membership>>
    Namespace::membershipsOfVisibility(std::optional<VisibilityKind> visiblity, std::vector<std::shared_ptr<Namespace>> namespaces) {
        std::vector<std::shared_ptr<Membership>> returnValue;
        for(const auto& one_namespace: namespaces) {
            for (const auto& ownedMembership: one_namespace->OwnedMembership) {
                if(visiblity.has_value() && ownedMembership->visibility() == visiblity.value())
                    returnValue.push_back(ownedMembership);
                else if(!visiblity.has_value() && ownedMembership->visibility() == PUBLIC)
                    returnValue.push_back(ownedMembership);
            }
        }
        return returnValue;
    }

    std::optional<std::shared_ptr<Membership>> Namespace::resolve(std::string qualifiedName) {
        return resolveGlobal(qualifiedName);
    }

    std::optional<std::shared_ptr<Membership>> Namespace::resolveGlobal(std::string qualifiedName) {
        for(const auto& ownedImport: ImportedMemberships) {
            if(qualifiedName.find(ownedImport->declaredName().value())!=std::string::npos)
                return ownedImport;
        }

        for(const auto& ownedMembership: OwnedMembership) {
            if(qualifiedName.find(ownedMembership->declaredName().value())!=std::string::npos)
                return ownedMembership;
        }

        return { };
    }

    std::optional<std::shared_ptr<Membership>> Namespace::resolveLocal(std::string qualifiedName) {

        for(const auto& ownedMembership: OwnedMembership) {
            if(qualifiedName.find(ownedMembership->declaredName().value())!=std::string::npos)
                return ownedMembership;
        }
        return { };
    }

    std::optional<std::shared_ptr<Membership>> Namespace::resolveVisible(std::string qualifiedName) {
        for(const auto& ownedImport: ImportedMemberships) {
            if((qualifiedName.find(ownedImport->declaredName().value())!=std::string::npos)&&(ownedImport->visibility()!=PRIVATE))
                return ownedImport;
        }

        for(const auto& ownedMembership: OwnedMembership) {
            if((qualifiedName.find(ownedMembership->declaredName().value())!=std::string::npos)&&(ownedMembership->visibility()!=PRIVATE))
                return ownedMembership;
        }

        return { };
    }

    std::string Namespace::qualificationOf(std::string ) {
        return std::string();
    }

    std::string Namespace::unqualifiedName(std::string ) {
        return std::string();
    }

    std::vector<std::shared_ptr<Membership>> Namespace::importedMemberships() const {
        return ImportedMemberships;
    }

    void Namespace::setImportedMemberships(std::vector<std::shared_ptr<Membership>> importedMemberships) {
        ImportedMemberships = importedMemberships;
    }

    void Namespace::appendImportedMemberships(std::shared_ptr<Membership> importedMembership) {
        ImportedMemberships.push_back(importedMembership);
    }

    void Namespace::appendImportedMemberships(std::vector<std::shared_ptr<Membership>> importedMemberships) {
        ImportedMemberships.insert(ImportedMemberships.end(),importedMemberships.begin(),importedMemberships.end());
    }

    std::vector<std::shared_ptr<Element>> Namespace::member() const {
        return Member;
    }

    void Namespace::setMember(std::vector<std::shared_ptr<Element>> member) {
        clearUnresolvedJsonReferences("member");
        Member = member;
    }

    void Namespace::appendMember(std::shared_ptr<Element> member) {
        Member.push_back(member);
    }

    void Namespace::appendMember(std::vector<std::shared_ptr<Element>> member) {
        Member.insert(Member.end(),member.begin(),member.end());
    }

    std::vector<std::shared_ptr<Membership>> Namespace::memberships() const {
        return Memberships;
    }

    void Namespace::setMemberships(std::vector<std::shared_ptr<Membership>> memberships) {
        Memberships = memberships;
    }

    void Namespace::appendMembership(std::shared_ptr<Membership> membership) {
        Memberships.push_back(membership);
    }

    void Namespace::appendMembership(std::vector<std::shared_ptr<Membership>> memberhsips) {
        Memberships.insert(Memberships.end(),memberhsips.begin(),memberhsips.end());
    }

    std::vector<std::shared_ptr<Import>> Namespace::ownedImport() const {
        return OwnedImport;
    }

    void Namespace::setOwnedImport(std::vector<std::shared_ptr<Import>> ownedImports) {
        clearUnresolvedJsonReferences("ownedImport");
        OwnedImport = ownedImports;
    }

    void Namespace::appendOwnedImport(std::shared_ptr<Import> ownedImport) {
        OwnedImport.push_back(ownedImport);
    }

    void Namespace::appendOwnedImport(std::vector<std::shared_ptr<Import>> ownedImport) {
        OwnedImport.insert(OwnedImport.end(),ownedImport.begin(),ownedImport.end());
    }

    std::vector<std::shared_ptr<Element>> Namespace::ownedMember() const {
        return OwnedMember;
    }

    void Namespace::setOwnedMember(std::vector<std::shared_ptr<Element>> ownedMemeber) {
        clearUnresolvedJsonReferences("ownedMember");
        OwnedMember = ownedMemeber;
    }

    void Namespace::appendOwnedMember(std::shared_ptr<Element> ownedMember) {
        OwnedMember.push_back(ownedMember);
    }

    void Namespace::appendOwnedMember(std::vector<std::shared_ptr<Element>> ownedMember) {
        OwnedMember.insert(OwnedMember.end(),ownedMember.begin(),ownedMember.end());
    }

    std::vector<std::shared_ptr<Membership>> Namespace::ownedMembership() const {
        return OwnedMembership;
    }

    void Namespace::setOwnedMembership(std::vector<std::shared_ptr<Membership>> ownedMembership) {
        clearUnresolvedJsonReferences("ownedMembership");
        OwnedMembership = ownedMembership;
    }

    void Namespace::appendOwnedMembership(std::shared_ptr<Membership> ownedMembership) {
        OwnedMembership.push_back(ownedMembership);
    }

    void Namespace::appendOwnedMembership(std::vector<std::shared_ptr<Membership>> ownedMembership) {
        OwnedMembership.insert(OwnedMembership.end(),ownedMembership.begin(),ownedMembership.end());
    }
} // KerML::Entities

// BEGIN GENERATED JSON (kerml/tools/generate_json.py): do not edit, run the script instead.
namespace KerML::Entities {
    std::string Namespace::serializeToJson() {
        nlohmann::json json = nlohmann::json::parse(Element::serializeToJson());
        json["membership"] = Json::reference(unresolvedJsonReferences("membership"), Namespace::membership());
        json["ownedImport"] = Json::reference(unresolvedJsonReferences("ownedImport"), Namespace::ownedImport());
        json["member"] = Json::reference(unresolvedJsonReferences("member"), Namespace::member());
        json["ownedMember"] = Json::reference(unresolvedJsonReferences("ownedMember"), Namespace::ownedMember());
        json["ownedMembership"] = Json::reference(unresolvedJsonReferences("ownedMembership"), Namespace::ownedMembership());
        json["importedMembership"] = Json::reference(unresolvedJsonReferences("importedMembership"), Namespace::importedMembership());
        return applyJsonSource(json.dump(JSON_INTENT));
    }

    void Namespace::deserializeAndPopulate(const std::string& jsonString) {
        Element::deserializeAndPopulate(jsonString);
        const nlohmann::json json = nlohmann::json::parse(jsonString);
        std::vector<boost::uuids::uuid> ids;
        if (Json::readReferences(json, "ownedImport", ids))
            setUnresolvedJsonReferences("ownedImport", ids);
        if (Json::readReferences(json, "member", ids))
            setUnresolvedJsonReferences("member", ids);
        if (Json::readReferences(json, "ownedMember", ids))
            setUnresolvedJsonReferences("ownedMember", ids);
        if (Json::readReferences(json, "ownedMembership", ids))
            setUnresolvedJsonReferences("ownedMembership", ids);
    }

    void Namespace::resolveJsonReferences(const std::function<std::shared_ptr<Element>(const boost::uuids::uuid&)>& lookup) {
        Element::resolveJsonReferences(lookup);
        if (const auto ids = unresolvedJsonReferences("ownedImport")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Import>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Import>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Namespace::setOwnedImport(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedImport");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedImport", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("member")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Namespace::setMember(std::move(resolved));
                    clearUnresolvedJsonReferences("member");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("member", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedMember")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Element>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Element>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Namespace::setOwnedMember(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedMember");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedMember", *ids);
            }
        }
        if (const auto ids = unresolvedJsonReferences("ownedMembership")) {
            try {
                std::vector<std::shared_ptr<KerML::Entities::Membership>> resolved;
                for (const auto& id : *ids) {
                    auto target = std::dynamic_pointer_cast<KerML::Entities::Membership>(lookup(id));
                    if (!target)
                        break;
                    resolved.push_back(std::move(target));
                }
                // (the setter forgets the ids, see clearUnresolvedJsonReferences)
                if (resolved.size() == ids->size()) {
                    Namespace::setOwnedMembership(std::move(resolved));
                    clearUnresolvedJsonReferences("ownedMembership");
                }
            } catch (const std::exception&) {
                // The reference stays unresolved if the model refuses it.
                setUnresolvedJsonReferences("ownedMembership", *ids);
            }
        }
    }
}
// END GENERATED JSON
