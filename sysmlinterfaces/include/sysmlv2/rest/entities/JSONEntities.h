//
// Created by Moritz Herzog on 22.02.24.
//
//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <string>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------

//---------------------------------------------------------
// Forwarding
//---------------------------------------------------------

namespace SysMLv2::REST {
    // Generally used
    const std::string JSON_ID_ENTITY = "@id";
    const std::string JSON_TYPE_ENTITY = "@type";

    // Used for Record and the Superclasses
    const std::string JSON_NAME_ENTITY = "name";
    const std::string JSON_ALIAS_ENTITY = "alias";
    const std::string JSON_DESCRIPTION_ENTITY = "description";
    const std::string JSON_OWNING_PROJECT = "owningProject";

    // Used for Project
    const std::string JSON_DEFAULT_BRANCH_ENTITY = "defaultBranch";
    const std::string JSON_CREATION_ENTITY = "created";
    const std::string JSON_BRANCHES_LIST = "branchesList";
    const std::string JSON_COMMIT_LIST = "commits";
    const std::string JSON_HEAD_ID_LIST = "heads";

    // Used for Digital Twin
    const std::string JSON_CONNECTED_MODELS = "connectedModels";
    const std::string JSON_PARENT_PROJECT = "parentProject";
    const std::string JSON_BRANCH_ID = "branchId";
    const std::string JSON_COMMIT_ID = "commitId";

    // Used for Branches
    const std::string JSON_HEAD_ID = "head";
    const std::string JSON_REFERENCE_COMMIT = "referencedCommit";

    // Used for Data Identity
    const std::string JSON_IDENTITY_ENTITY = "identity";
    const std::string JSON_PAYLOAD_ENTITY = "payload";

    // Used for Commit
    const std::string JSON_CHANGE_ENTITY = "change";
    const std::string JSON_TIMESTAMP_ENTITY = "timestamp";
    const std::string JSON_PREV_COMMITS = "previousCommit";

    // Used for CommitRefence
    const std::string JSON_CREATED_ENTITY = "created";
    const std::string JSON_DELETED_ENTITY = "deleted";

    // Used for DataIdentity
    const std::string JSON_DATA_VER_ENTITIY = "dataVersions";

    // Used for Queries
    const std::string JSON_SELECT_ENTITY = "select";
    const std::string JSON_SCOPE_ENTITY = "scope";
    const std::string JSON_ORDER_ENTITY = "order";

    //Used for Data & Element / Relationship
    const std::string JSON_SPECIFICATION_ENTITY = "specification";
    const std::string JSON_LANGUAGE_ENTITY = "language";
    const std::string JSON_RESOURCE_IDENTIFIER_ENTITY = "resourceIdentifier";
    const std::string JSON_USED_COMMIT_ENTITY = "usedCommit";
    const std::string JSON_SHORT_NAME_ENTITY = "shortName";
    const std::string JSON_DECLARED_NAME_ENTITY = "declaredName";
    const std::string JSON_DECLARED_SHORT_NAME_ENTITY = "declaredShortName";
    const std::string JSON_OWNED_ELEMENTS_ENTITY = "ownedElements";
    const std::string JSON_OWNER_ENTITY = "owner";
    const std::string JSON_OWNING_MEMBERSHIP_ENTITY = "owningMembership";
    const std::string JSON_OWNING_NAMESPACE_ENTITY = "owningNamespace";
    const std::string JSON_OWNING_RELATIONSHIP_ENTITY = "owningRelationship";
    const std::string JSON_DIRECTION_ENTITY = "direction";
    const std::string JSON_IMPORTED_MEMBER_NAME_ENTITY = "importedMemberName";
    const std::string JSON_IMPORTED_NAMESPACE_ENTITY = "importedNamespace";
    const std::string JSON_BODY_ENTITY = "body";
    const std::string JSON_SOURCE_ENTITY = "source";
    const std::string JSON_TARGET_ENTITY = "target";
    const std::string JSON_IS_STANDARD_ENTITY = "isStandard";
    const std::string JSON_IS_LIBRARY_ELEMENT_ENTITY = "isLibraryElement";
    const std::string JSON_IS_IMPLIED_ELEMENT_ENTITY = "isImplied";
    const std::string JSON_IS_IMPLIED_INCLUDED_ENTITY = "isImpliedIncluded";
    const std::string JSON_DOCUMENTATION_ENTITY = "documentation";
    const std::string JSON_TEXTUAL_REPRESENTATION_ENTITY = "textualRepresentation";
    const std::string JSON_ALIAS_ID_ENTITY = "aliasIds";
    const std::string JSON_ELEMENT_ID_ENTITY = "elementId";
    const std::string JSON_OWNED_RELATIONSHIPS_ENTITY = "ownedRelationships";
    const std::string JSON_QUALIFIED_NAME_ENTITY = "qualifiedName";
    const std::string JSON_OWNED_ANNOTATION_ENTITY = "ownedAnnotation";

    //Type Strings
    const std::string PROJECT_TYPE="project";
    const std::string DATA_IDENTITY_TYPE="dataidentity";
    const std::string BRANCH_TYPE="branch";
    const std::string TAG_TYPE = "tag";
    const std::string QUERY_TYPE = "query";
    const std::string COMMIT_TYPE = "commit";
    const std::string FEATURE_TYPE = "feature";
    const std::string FEATURE_TYPE_TYPE = "featuretyping";
    const std::string ASSOCIATION_TYPE = "association";
    const std::string ELEMENT_TYPE = "element";
    const std::string SPECIALIZATION_TYPE = "specialization";
    const std::string PACKAGE_TYPE = "package";
    const std::string EXPRESSION_TYPE = "expression";
    const std::string MULTIPLICITY_TYPE = "multiplicity";
    const std::string DATA_TYPE_TYPE = "datatype";
    const std::string RELATIONSHIP_TYPE="relationship";
    const std::string COMMENT_TYPE="comment";
    const std::string DOCUMENTATION_TYPE="documentation";
    const std::string CLASS_TYPE = "class";
    const std::string ANNOTATING_ELEMENT_TYPE = "annotatingelement";
    const std::string TEXTUAL_REPRESENTATION_TYPE = "textualrepresentation";
    const std::string CLASSIFIER_TYPE = "classifier";
    const std::string NAMESPACE_TYPE = "namespace";
    const std::string TYPE_TYPE = "type";
    const std::string DIGITAL_TWIN_TYPE = "digitaltwin";
    const std::string DATA_TYPE = "data";
    const std::string DATA_VERSION_TYPE = "dataversion";
    const std::string PAYLOAD_TYPE = "payload";
}
