set(GLOBAL_HEADER
    include/sysml/sysml_global.h)

set(ACTIONS_HEADER
        include/sysml/actions/AcceptActionUsage.h
        include/sysml/actions/ActionDefinition.h
        include/sysml/actions/ActionUsage.h
        include/sysml/actions/AssignmentActionUsage.h
        include/sysml/actions/ControlNode.h
        include/sysml/actions/DecisionNode.h
        include/sysml/actions/ForkNode.h
        include/sysml/actions/ForLoopActionUsage.h
        include/sysml/actions/IfActionUsage.h
        include/sysml/actions/JoinNode.h
        include/sysml/actions/LoopActionUsage.h
        include/sysml/actions/MergeNode.h
        include/sysml/actions/PerformActionUsage.h
        include/sysml/actions/SendActionUsage.h
        include/sysml/actions/TerminateActionUsage.h
        include/sysml/actions/TriggerInvocationExpression.h
        include/sysml/actions/TriggerKind.h
        include/sysml/actions/WhileLoopActionUsage.h)

set(ALLOCATIONS_HEADER
        include/sysml/allocations/AllocationDefinition.h
        include/sysml/allocations/AllocationUsage.h)

set(ANALYSIS_CASES_HEADER
        include/sysml/analysiscases/AnalysisCaseDefinition.h
        include/sysml/analysiscases/AnalysisCaseUsage.h)

set(ATTRIBUTES_HEADER
        include/sysml/attributes/AttributeDefinition.h
        include/sysml/attributes/AttributeUsage.h)

set(CALCULATIONS_HEADER
        include/sysml/calculations/CalculationDefinition.h
        include/sysml/calculations/CalculationUsage.h)

set(CASES_HEADER
        include/sysml/cases/CaseDefinition.h
        include/sysml/cases/CaseUsage.h
        include/sysml/cases/ObjectiveMembership.h)

set(CONNECTIONS_HEADER
        include/sysml/connections/BindingConnectorAsUsage.h
        include/sysml/connections/ConnectionDefinition.h
        include/sysml/connections/ConnectorAsUsage.h
        include/sysml/connections/ConnectionUsage.h
        include/sysml/connections/SuccessionAsUsage.h)

set(CONSTRAINTS_HEADER
        include/sysml/constraints/AssertConstraintUsage.h
        include/sysml/constraints/ConstraintDefinition.h
        include/sysml/constraints/ConstraintUsage.h)

set(ENUMERATIONS_HEADER
        include/sysml/enumerations/EnumerationDefinition.h
        include/sysml/enumerations/EnumerationUsage.h)

set(FLOW_HEADER
        include/sysml/flows/FlowDefinition.h
        include/sysml/flows/FlowUsage.h
        include/sysml/flows/SuccessionFlowUsage.h)

set(INTERFACES_HEADER
        include/sysml/interfaces/InterfaceDefinition.h
        include/sysml/interfaces/InterfaceUsage.h)

set(ITEMS_HEADER
        include/sysml/items/ItemDefinition.h
        include/sysml/items/ItemUsage.h)

set(METADATA_HEADER
        include/sysml/metadata/MetadataDefinition.h
        include/sysml/metadata/MetadataUsage.h)

set(MODEL_HEADER
        include/sysml/model/Forward.h
        include/sysml/model/KerMLTypes.h
        include/sysml/model/Representation.h)

set(OCCURRENCES_HEADER
        include/sysml/occurrences/EventOccurrenceUsage.h
        include/sysml/occurrences/OccurrenceDefinition.h
        include/sysml/occurrences/OccurrenceUsage.h
        include/sysml/occurrences/PortionKind.h)

set(PARTS_HEADER
        include/sysml/parts/PartDefinition.h
        include/sysml/parts/PartUsage.h)

set(PORTS_HEADER
        include/sysml/ports/ConjugatedPortDefinition.h
        include/sysml/ports/ConjugatedPortTyping.h
        include/sysml/ports/PortConjugation.h
        include/sysml/ports/PortDefinition.h
        include/sysml/ports/PortUsage.h)

set(REQUIREMENTS_HEADER
        include/sysml/requirements/ActorMembership.h
        include/sysml/requirements/ConcernDefinition.h
        include/sysml/requirements/ConcernUsage.h
        include/sysml/requirements/FramedConcernMembership.h
        include/sysml/requirements/RequirementConstraintKind.h
        include/sysml/requirements/RequirementConstraintMembership.h
        include/sysml/requirements/RequirementDefinition.h
        include/sysml/requirements/RequirementUsage.h
        include/sysml/requirements/SatisfyRequirementUsage.h
        include/sysml/requirements/StakeholderMembership.h
        include/sysml/requirements/SubjectMembership.h)

set(STATES_HEADER
        include/sysml/states/ExhibitStateUsage.h
        include/sysml/states/StateDefinition.h
        include/sysml/states/StateSubactionKind.h
        include/sysml/states/StateSubactionMembership.h
        include/sysml/states/StateUsage.h
        include/sysml/states/TransitionFeatureKind.h
        include/sysml/states/TransitionUsage.h)

set(USAGE_HEADER
        include/sysml/usage/Definition.h
        include/sysml/usage/ReferenceUsage.h
        include/sysml/usage/Usage.h
        include/sysml/usage/VariantMembership.h)

set(USE_CASES_HEADER
        include/sysml/usecases/IncludeUseCaseUsage.h
        include/sysml/usecases/UseCaseDefinition.h
        include/sysml/usecases/UseCaseUsage.h)

set(VERIFICATION_CASES_HEADER
        include/sysml/verificationcases/RequirementVerificationMembership.h
        include/sysml/verificationcases/VerificationCaseUsage.h
        include/sysml/verificationcases/VerificationCaseDefinition.h)

set(VIEWS_HEADER
        include/sysml/views/Expose.h
        include/sysml/views/MembershipExpose.h
        include/sysml/views/NamespaceExpose.h
        include/sysml/views/ViewDefinition.h
        include/sysml/views/RenderingDefinition.h
        include/sysml/views/RenderingUsage.h
        include/sysml/views/ViewpointDefinition.h
        include/sysml/views/ViewRenderingMembership.h
        include/sysml/views/ViewUsage.h)

add_library(sysml
        ${GLOBAL_HEADER}
        ${ACTIONS_HEADER}
        ${ALLOCATIONS_HEADER}
        ${ANALYSIS_CASES_HEADER}
        ${ATTRIBUTES_HEADER}
        ${CALCULATIONS_HEADER}
        ${CASES_HEADER}
        ${CONNECTIONS_HEADER}
        ${CONSTRAINTS_HEADER}
        ${ENUMERATIONS_HEADER}
        ${FLOW_HEADER}
        ${INTERFACES_HEADER}
        ${ITEMS_HEADER}
        ${METADATA_HEADER}
        ${OCCURRENCES_HEADER}
        ${PORTS_HEADER}
        ${REQUIREMENTS_HEADER}
        ${STATES_HEADER}
        ${USAGE_HEADER}
        ${USE_CASES_HEADER}
        ${VERIFICATION_CASES_HEADER}
        ${VIEWS_HEADER}
        src/sysml/flows/FlowDefinition.cpp
        src/sysml/flows/FlowUsage.cpp
        src/sysml/flows/SuccessionFlowUsage.cpp
        src/sysml/enumerations/EnumerationDefinition.cpp
        src/sysml/enumerations/EnumerationUsage.cpp
        src/sysml/requirements/RequirementUsage.cpp
        src/sysml/requirements/ConcernUsage.cpp
        src/sysml/requirements/FramedConcernMembership.cpp
        src/sysml/requirements/ActorMembership.cpp
        src/sysml/requirements/StakeholderMembership.cpp
        src/sysml/requirements/SubjectMembership.cpp
        src/sysml/requirements/ConcernDefinition.cpp
        src/sysml/requirements/RequirementDefinition.cpp
        src/sysml/requirements/RequirementConstraintMembership.cpp
        src/sysml/requirements/SatisfyRequirementUsage.cpp
        src/sysml/calculations/CalculationDefinition.cpp
        src/sysml/calculations/CalculationUsage.cpp
        src/sysml/metadata/MetadataDefinition.cpp
        src/sysml/metadata/MetadataUsage.cpp
        src/sysml/constraints/AssertConstraintUsage.cpp
        src/sysml/constraints/ConstraintDefinition.cpp
        src/sysml/constraints/ConstraintUsage.cpp
        src/sysml/cases/CaseUsage.cpp
        src/sysml/cases/CaseDefinition.cpp
        src/sysml/cases/ObjectiveMembership.cpp
        src/sysml/states/TransitionFeatureMembership.cpp
        src/sysml/states/ExhibitStateUsage.cpp
        src/sysml/states/StateSubactionMembership.cpp
        src/sysml/states/StateUsage.cpp
        src/sysml/states/StateDefinition.cpp
        src/sysml/states/TransitionUsage.cpp
        src/sysml/usecases/UseCaseUsage.cpp
        src/sysml/usecases/IncludeUseCaseUsage.cpp
        src/sysml/usecases/UseCaseDefinition.cpp
        src/sysml/actions/PerformActionUsage.cpp
        src/sysml/actions/ActionDefinition.cpp
        src/sysml/actions/ActionUsage.cpp
        src/sysml/actions/AssignmentActionUsage.cpp
        src/sysml/actions/ForLoopActionUsage.cpp
        src/sysml/actions/TriggerInvocationExpression.cpp
        src/sysml/actions/LoopActionUsage.cpp
        src/sysml/actions/DecisionNode.cpp
        src/sysml/actions/ForkNode.cpp
        src/sysml/actions/JoinNode.cpp
        src/sysml/actions/ControlNode.cpp
        src/sysml/actions/MergeNode.cpp
        src/sysml/actions/TerminateActionUsage.cpp
        src/sysml/actions/AcceptActionUsage.cpp
        src/sysml/actions/WhileLoopActionUsage.cpp
        src/sysml/actions/SendActionUsage.cpp
        src/sysml/actions/IfActionUsage.cpp
        src/sysml/items/ItemUsage.cpp
        src/sysml/items/ItemDefinition.cpp
        src/sysml/occurrences/EventOccurrenceUsage.cpp
        src/sysml/occurrences/OccurrenceUsage.cpp
        src/sysml/occurrences/OccurrenceDefinition.cpp
        src/sysml/usage/Usage.cpp
        src/sysml/usage/ReferenceUsage.cpp
        src/sysml/usage/VariantMembership.cpp
        src/sysml/usage/Definition.cpp
        src/sysml/attributes/AttributeDefinition.cpp
        src/sysml/attributes/AttributeUsage.cpp
        src/sysml/parts/PartDefinition.cpp
        src/sysml/parts/PartUsage.cpp
        src/sysml/analysiscases/AnalysisCaseUsage.cpp
        src/sysml/analysiscases/AnalysisCaseDefinition.cpp
        src/sysml/ports/PortConjugation.cpp
        src/sysml/ports/ConjugatedPortDefinition.cpp
        src/sysml/ports/PortDefinition.cpp
        src/sysml/ports/ConjugatedPortTyping.cpp
        src/sysml/ports/PortUsage.cpp
        src/sysml/views/ViewUsage.cpp
        src/sysml/views/Expose.cpp
        src/sysml/views/ViewDefinition.cpp
        src/sysml/views/RenderingUsage.cpp
        src/sysml/views/ViewpointDefinition.cpp
        src/sysml/views/RenderingDefinition.cpp
        src/sysml/views/MembershipExpose.cpp
        src/sysml/views/NamespaceExpose.cpp
        src/sysml/views/ViewRenderingMembership.cpp
        src/sysml/views/ViewpointUsage.cpp
        src/sysml/connections/ConnectorAsUsage.cpp
        src/sysml/connections/ConnectionUsage.cpp
        src/sysml/connections/SuccessionAsUsage.cpp
        src/sysml/connections/ConnectionDefinition.cpp
        src/sysml/connections/BindingConnectorAsUsage.cpp
        src/sysml/interfaces/InterfaceUsage.cpp
        src/sysml/interfaces/InterfaceDefinition.cpp
        src/sysml/allocations/AllocationDefinition.cpp
        src/sysml/allocations/AllocationUsage.cpp
        src/sysml/verificationcases/RequirementVerificationMembership.cpp
        src/sysml/verificationcases/VerificationCaseDefinition.cpp
        src/sysml/verificationcases/VerificationCaseUsage.cpp)

target_link_libraries(sysml PUBLIC
        kerml
        sysmlv2interfaces
        boost::boost
        nlohmann_json::nlohmann_json
        date::date)

target_include_directories(sysml PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
if(MSVC)
    target_compile_options(sysml PRIVATE /W4 /WX- /bigobj)
else()
    target_compile_options(sysml PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

include(GNUInstallDirs)
install(TARGETS sysml ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS sysml RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/sysml DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${GLOBAL_HEADER} DESTINATION include/sysml)
install(FILES ${ACTIONS_HEADER} DESTINATION  include/sysml/actions)
install(FILES ${ALLOCATIONS_HEADER} DESTINATION include/sysml/allocations)
install(FILES ${ANALYSIS_CASES_HEADER} DESTINATION include/sysml/analysiscases)
install(FILES ${ATTRIBUTES_HEADER} DESTINATION include/sysml/attributes)
install(FILES ${CALCULATIONS_HEADER} DESTINATION include/sysml/calculations)
install(FILES ${CASES_HEADER} DESTINATION include/sysml/cases)
install(FILES ${CONNECTIONS_HEADER} DESTINATION include/sysml/connections)
install(FILES ${CONSTRAINTS_HEADER} DESTINATION include/sysml/constraints)
install(FILES ${ENUMERATIONS_HEADER} DESTINATION include/sysml/enumerations)
install(FILES ${FLOW_HEADER} DESTINATION include/sysml/flows)
install(FILES ${INTERFACES_HEADER} DESTINATION include/sysml/interfaces)
install(FILES ${ITEMS_HEADER} DESTINATION include/sysml/items)
install(FILES ${METADATA_HEADER} DESTINATION include/sysml/metadata)
install(FILES ${OCCURRENCES_HEADER} DESTINATION include/sysml/occurrences)
install(FILES ${PORTS_HEADER} DESTINATION include/sysml/ports)
install(FILES ${REQUIREMENTS_HEADER} DESTINATION include/sysml/requirements)
install(FILES ${STATES_HEADER} DESTINATION include/sysml/states)
install(FILES ${USAGE_HEADER} DESTINATION include/sysml/usage)
install(FILES ${USE_CASES_HEADER} DESTINATION include/sysml/usecases)
install(FILES ${VERIFICATION_CASES_HEADER} DESTINATION include/sysml/verificationcases)
install(FILES ${VIEWS_HEADER} DESTINATION include/sysml/views)

file(GLOB_RECURSE _source_list *.cpp* *.h* *.hpp*)
foreach(_source IN ITEMS ${_source_list})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()


#if(BUILD_TESTING)
#    add_executable(sysml-representation-test tests/Representation.cpp tests/Inventory.cpp)
#    target_link_libraries(sysml-representation-test PRIVATE sysml)
#    add_test(NAME sysml-representation COMMAND sysml-representation-test)
#    find_package(Python3 COMPONENTS Interpreter QUIET)
#    if(Python3_Interpreter_FOUND)
#        add_test(NAME sysml-generated-files
#                COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tools/generate_abstract_syntax.py --check)
#    endif()
#endif()
