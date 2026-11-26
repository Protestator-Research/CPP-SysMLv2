//
// The ids of the elements of the model libraries (KerML 1.0, clause 9.1 "Model Libraries").
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <cstddef>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <kerml/root/elements/Element.h>
#include <kerml/kerml_global.h>
//---------------------------------------------------------

namespace KerML::Entities {
    /**
     * The language of a model library: it decides the URL that the id of its top-level package is made of.
     */
    enum class LibraryLanguage {
        /// A library of the textual notation of KerML (.kerml, .kermlx): "https://www.omg.org/spec/KerML/".
        KerML,
        /// A library of the textual notation of SysML (.sysml, .sysmlx): "https://www.omg.org/spec/SysML/".
        SysML
    };

    /**
     * The id of a top-level library package: the name based UUID (version 5) of the URL "https://www.omg.org/spec/KerML/" or
     * "https://www.omg.org/spec/SysML/" (by @p language) followed by the name of the package, in the namespace of the URLs (6ba7b811-9dad-11d1-80b4-00c04fd430c8).
     * @param language The language of the library.
     * @param packageName The (declared) name of the package.
     * @return The id of the package.
     */
    KERML_EXPORT boost::uuids::uuid libraryPackageId(LibraryLanguage language, const std::string& packageName);

    /**
     * The base of the URLs that the ids of the packages of the non-standard libraries are made of, if nothing else is chosen:
     * "https://sysml.protestator-research.com/".
     * @return The default vendor base.
     */
    KERML_EXPORT const std::string& defaultLibraryVendorBase();

    /**
     * The vendor base as it is used: an empty string is the default base (defaultLibraryVendorBase()), a base that does not end with "/" gets one
     * appended (so that "https://example.org/sysml" and "https://example.org/sysml/" are the same base). White space around the base is removed.
     * Nothing else is changed. The name of a package is appended to the base as it is (UTF-8, no percent-encoding).
     * @param vendorBase The base as it was given.
     * @return The base to build URLs from.
     */
    KERML_EXPORT std::string normalizeLibraryVendorBase(const std::string& vendorBase);

    /**
     * The id of a top-level package of a library that is not a standard library: the name based UUID (version 5) of the normalised vendor
     * base (see normalizeLibraryVendorBase()) followed by the name of the package, in the namespace of the URLs. The URL does not depend on the
     * language of the library: the same package name gives the same id for a .kerml and a .sysml file.
     * @param vendorBase The base of the URL of the vendor, for example "https://sysml.protestator-research.com/".
     * @param packageName The (declared) name of the package.
     * @return The id of the package.
     */
    KERML_EXPORT boost::uuids::uuid vendorPackageId(const std::string& vendorBase, const std::string& packageName);

    /**
     * The id of a top-level library package: the policy that decides it is this function, nothing else chooses between the two kinds of URL.
     * A package that is declared `standard` (LibraryPackage::isStandard()) has libraryPackageId(): its URL starts with
     * "https://www.omg.org/spec/KerML/" or "https://www.omg.org/spec/SysML/" (by @p language). Every other library package has vendorPackageId(): its
     * URL starts with the vendor base, so a user package that is named like a package of the standard library (`library package ScalarValues`) does not
     * get the id of the standard one.
     * @param package The package, with a declared name.
     * @param language The language of the file the package was read from.
     * @param vendorBase The base of the URLs of the packages that are not standard (it is normalised).
     * @return The id of the package.
     */
    KERML_EXPORT boost::uuids::uuid libraryPackageIdOf(const LibraryPackage& package, LibraryLanguage language, const std::string& vendorBase);

    /**
     * The id of an element that a top-level library package contains (directly or indirectly), or of the relationships and the root namespace
     * around the package: the name based UUID (version 5) of @p path in the namespace of the id of the package.
     * @param packageId The id of the top-level library package, see libraryPackageId().
     * @param path The path of the element (Element::path()), as UTF-8 text.
     * @return The id of the element.
     */
    KERML_EXPORT boost::uuids::uuid libraryElementId(const boost::uuids::uuid& packageId, const std::string& path);

    /**
     * Whether the ids of the model libraries are assigned to a package (and to what it owns): the one place that decides which packages are
     * model libraries. Today every top-level LibraryPackage with a name is one (the standard ones, `standard library package`, and the
     * others, `library package`); the alternative is to ask LibraryPackage::isStandard() as well.
     * @param package Any element.
     * @return True for a LibraryPackage with a declared name that is owned by an OwningMembership of a root namespace.
     */
    KERML_EXPORT bool getsLibraryIds(const std::shared_ptr<Element>& package);

    /**
     * Assigns the ids of the model libraries to a top-level library package (see getsLibraryIds()) and to the elements of it that a name identifies
     * (Element::assignElementId()):
     *  - the package gets libraryPackageIdOf(),
     *  - every element that it contains (directly or indirectly) and that has a qualified name gets libraryElementId() of the qualified name
     *    (which is its path()); this includes the result parameters that have an implied name (Feature::impliedName()),
     *  - the OwningMembership of such an element, and the one that owns the package, get the id of their path ("<qualified name>/owningMembership"),
     *  - the root namespace that owns the membership of the package gets libraryElementId() of "<qualified name of the package>/owner", if the package
     *    is the first thing that the root namespace owns (the rule that the ids of the official XMI files follow). The stand-alone Element::path() of the
     *    root namespace is "": this id is not the one of its path.
     * Everything else (unnamed elements, the relationships that are not such a membership, the members that are not the first with their name) has
     * a path made of positions ("/<n>") and keeps the id it has (a random one), unless getsPositionalId() in LibraryElementIds.cpp says otherwise: the
     * structure that the text parser builds for them is not the one of the official model, so the positions would put official ids on other elements.
     * The qualified names and the paths are made top-down during one walk (those of an element come from those of its owner), so the work is
     * linear in the number of the elements (and in the length of their names). They are the ones of Element::computeQualifiedName() and
     * Element::path(): of the members of a namespace that have the same name only the first has a qualified name.
     * The ids depend on the names of the elements, also on the implied ones (the name that a feature gets from the feature it redefines, resolved
     * only after the references of the package were resolved), so the function has to be called again then; it can be called repeatedly, an element
     * whose path did not change gets the same id. The ids are final only after that.
     * It must be called before the ids are put into an index or are sent anywhere: the elements that were identified by the old ids are not found by them anymore.
     * An element that is not found in the list of its owner (an inconsistent model), and an element whose id is already in @p taken (or that
     * an earlier element of the walk got), keeps the id it has.
     * @param package The top-level library package.
     * @param language The language of the file the package was read from.
     * @param assigned If it is not null, the elements that got an id are appended to it.
     * @param taken If it is not null, the ids that other elements have already (the packages of a source, or of the whole workspace, share it): no
     * id of it is assigned again, and the ids that are assigned are added to it.
     * @param vendorBase The base of the URLs of the packages that are not standard (see libraryPackageIdOf(), normalizeLibraryVendorBase()).
     * @return The number of elements that got an id.
     */
    KERML_EXPORT std::size_t assignLibraryElementIds(const std::shared_ptr<Element>& package, LibraryLanguage language,
                                                     std::vector<Element*>* assigned = nullptr, std::set<boost::uuids::uuid>* taken = nullptr,
                                                     const std::string& vendorBase = std::string());
} // KerML::Entities
