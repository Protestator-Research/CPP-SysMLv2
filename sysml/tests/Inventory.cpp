// Generated; exercises the complete class inventory.
#include <sysml/SysML.h>
#include <type_traits>
#include <stdexcept>
using namespace SysMLv2::Entities;
void checkInventory() {
static_assert(std::is_abstract_v<FlowDefinition> == false);
static_assert(std::is_convertible_v<FlowDefinition*, ActionDefinition*>);
static_assert(std::is_convertible_v<FlowDefinition*, KerML::Entities::Interaction*>);
static_assert(std::is_convertible_v<FlowDefinition*, KerML::Entities::Element*>);
{ FlowDefinition value; if (value.metaclassName() != "FlowDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<FlowUsage> == false);
static_assert(std::is_convertible_v<FlowUsage*, ConnectorAsUsage*>);
static_assert(std::is_convertible_v<FlowUsage*, KerML::Entities::Flow*>);
static_assert(std::is_convertible_v<FlowUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<FlowUsage*, KerML::Entities::Element*>);
{ FlowUsage value; if (value.metaclassName() != "FlowUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<SuccessionFlowUsage> == false);
static_assert(std::is_convertible_v<SuccessionFlowUsage*, KerML::Entities::SuccessionFlow*>);
static_assert(std::is_convertible_v<SuccessionFlowUsage*, FlowUsage*>);
static_assert(std::is_convertible_v<SuccessionFlowUsage*, KerML::Entities::Element*>);
{ SuccessionFlowUsage value; if (value.metaclassName() != "SuccessionFlowUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<EnumerationDefinition> == false);
static_assert(std::is_convertible_v<EnumerationDefinition*, AttributeDefinition*>);
static_assert(std::is_convertible_v<EnumerationDefinition*, KerML::Entities::Element*>);
{ EnumerationDefinition value; if (value.metaclassName() != "EnumerationDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<EnumerationUsage> == false);
static_assert(std::is_convertible_v<EnumerationUsage*, AttributeUsage*>);
static_assert(std::is_convertible_v<EnumerationUsage*, KerML::Entities::Element*>);
{ EnumerationUsage value; if (value.metaclassName() != "EnumerationUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RequirementUsage> == false);
static_assert(std::is_convertible_v<RequirementUsage*, ConstraintUsage*>);
static_assert(std::is_convertible_v<RequirementUsage*, KerML::Entities::Element*>);
{ RequirementUsage value; if (value.metaclassName() != "RequirementUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConcernUsage> == false);
static_assert(std::is_convertible_v<ConcernUsage*, RequirementUsage*>);
static_assert(std::is_convertible_v<ConcernUsage*, KerML::Entities::Element*>);
{ ConcernUsage value; if (value.metaclassName() != "ConcernUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<FramedConcernMembership> == false);
static_assert(std::is_convertible_v<FramedConcernMembership*, RequirementConstraintMembership*>);
static_assert(std::is_convertible_v<FramedConcernMembership*, KerML::Entities::Element*>);
{ FramedConcernMembership value; if (value.metaclassName() != "FramedConcernMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ActorMembership> == false);
static_assert(std::is_convertible_v<ActorMembership*, KerML::Entities::ParameterMembership*>);
static_assert(std::is_convertible_v<ActorMembership*, KerML::Entities::Element*>);
{ ActorMembership value; if (value.metaclassName() != "ActorMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<StakeholderMembership> == false);
static_assert(std::is_convertible_v<StakeholderMembership*, KerML::Entities::ParameterMembership*>);
static_assert(std::is_convertible_v<StakeholderMembership*, KerML::Entities::Element*>);
{ StakeholderMembership value; if (value.metaclassName() != "StakeholderMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<SubjectMembership> == false);
static_assert(std::is_convertible_v<SubjectMembership*, KerML::Entities::ParameterMembership*>);
static_assert(std::is_convertible_v<SubjectMembership*, KerML::Entities::Element*>);
{ SubjectMembership value; if (value.metaclassName() != "SubjectMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConcernDefinition> == false);
static_assert(std::is_convertible_v<ConcernDefinition*, RequirementDefinition*>);
static_assert(std::is_convertible_v<ConcernDefinition*, KerML::Entities::Element*>);
{ ConcernDefinition value; if (value.metaclassName() != "ConcernDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RequirementDefinition> == false);
static_assert(std::is_convertible_v<RequirementDefinition*, ConstraintDefinition*>);
static_assert(std::is_convertible_v<RequirementDefinition*, KerML::Entities::Element*>);
{ RequirementDefinition value; if (value.metaclassName() != "RequirementDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RequirementConstraintMembership> == false);
static_assert(std::is_convertible_v<RequirementConstraintMembership*, KerML::Entities::FeatureMembership*>);
static_assert(std::is_convertible_v<RequirementConstraintMembership*, KerML::Entities::Element*>);
{ RequirementConstraintMembership value; if (value.metaclassName() != "RequirementConstraintMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<SatisfyRequirementUsage> == false);
static_assert(std::is_convertible_v<SatisfyRequirementUsage*, RequirementUsage*>);
static_assert(std::is_convertible_v<SatisfyRequirementUsage*, AssertConstraintUsage*>);
static_assert(std::is_convertible_v<SatisfyRequirementUsage*, KerML::Entities::Element*>);
{ SatisfyRequirementUsage value; if (value.metaclassName() != "SatisfyRequirementUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<CalculationDefinition> == false);
static_assert(std::is_convertible_v<CalculationDefinition*, ActionDefinition*>);
static_assert(std::is_convertible_v<CalculationDefinition*, KerML::Entities::Function*>);
static_assert(std::is_convertible_v<CalculationDefinition*, KerML::Entities::Element*>);
{ CalculationDefinition value; if (value.metaclassName() != "CalculationDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<CalculationUsage> == false);
static_assert(std::is_convertible_v<CalculationUsage*, KerML::Entities::Expression*>);
static_assert(std::is_convertible_v<CalculationUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<CalculationUsage*, KerML::Entities::Element*>);
{ CalculationUsage value; if (value.metaclassName() != "CalculationUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<MetadataDefinition> == false);
static_assert(std::is_convertible_v<MetadataDefinition*, ItemDefinition*>);
static_assert(std::is_convertible_v<MetadataDefinition*, KerML::Entities::Metaclass*>);
static_assert(std::is_convertible_v<MetadataDefinition*, KerML::Entities::Element*>);
{ MetadataDefinition value; if (value.metaclassName() != "MetadataDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<MetadataUsage> == false);
static_assert(std::is_convertible_v<MetadataUsage*, KerML::Entities::MetadataFeature*>);
static_assert(std::is_convertible_v<MetadataUsage*, ItemUsage*>);
static_assert(std::is_convertible_v<MetadataUsage*, KerML::Entities::Element*>);
{ MetadataUsage value; if (value.metaclassName() != "MetadataUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AssertConstraintUsage> == false);
static_assert(std::is_convertible_v<AssertConstraintUsage*, KerML::Entities::Invariant*>);
static_assert(std::is_convertible_v<AssertConstraintUsage*, ConstraintUsage*>);
static_assert(std::is_convertible_v<AssertConstraintUsage*, KerML::Entities::Element*>);
{ AssertConstraintUsage value; if (value.metaclassName() != "AssertConstraintUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConstraintDefinition> == false);
static_assert(std::is_convertible_v<ConstraintDefinition*, OccurrenceDefinition*>);
static_assert(std::is_convertible_v<ConstraintDefinition*, KerML::Entities::Predicate*>);
static_assert(std::is_convertible_v<ConstraintDefinition*, KerML::Entities::Element*>);
{ ConstraintDefinition value; if (value.metaclassName() != "ConstraintDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConstraintUsage> == false);
static_assert(std::is_convertible_v<ConstraintUsage*, OccurrenceUsage*>);
static_assert(std::is_convertible_v<ConstraintUsage*, KerML::Entities::BooleanExpression*>);
static_assert(std::is_convertible_v<ConstraintUsage*, KerML::Entities::Element*>);
{ ConstraintUsage value; if (value.metaclassName() != "ConstraintUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<CaseUsage> == false);
static_assert(std::is_convertible_v<CaseUsage*, CalculationUsage*>);
static_assert(std::is_convertible_v<CaseUsage*, KerML::Entities::Element*>);
{ CaseUsage value; if (value.metaclassName() != "CaseUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<CaseDefinition> == false);
static_assert(std::is_convertible_v<CaseDefinition*, CalculationDefinition*>);
static_assert(std::is_convertible_v<CaseDefinition*, KerML::Entities::Element*>);
{ CaseDefinition value; if (value.metaclassName() != "CaseDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ObjectiveMembership> == false);
static_assert(std::is_convertible_v<ObjectiveMembership*, KerML::Entities::FeatureMembership*>);
static_assert(std::is_convertible_v<ObjectiveMembership*, KerML::Entities::Element*>);
{ ObjectiveMembership value; if (value.metaclassName() != "ObjectiveMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<TransitionFeatureMembership> == false);
static_assert(std::is_convertible_v<TransitionFeatureMembership*, KerML::Entities::FeatureMembership*>);
static_assert(std::is_convertible_v<TransitionFeatureMembership*, KerML::Entities::Element*>);
{ TransitionFeatureMembership value; if (value.metaclassName() != "TransitionFeatureMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ExhibitStateUsage> == false);
static_assert(std::is_convertible_v<ExhibitStateUsage*, PerformActionUsage*>);
static_assert(std::is_convertible_v<ExhibitStateUsage*, StateUsage*>);
static_assert(std::is_convertible_v<ExhibitStateUsage*, KerML::Entities::Element*>);
{ ExhibitStateUsage value; if (value.metaclassName() != "ExhibitStateUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<StateSubactionMembership> == false);
static_assert(std::is_convertible_v<StateSubactionMembership*, KerML::Entities::FeatureMembership*>);
static_assert(std::is_convertible_v<StateSubactionMembership*, KerML::Entities::Element*>);
{ StateSubactionMembership value; if (value.metaclassName() != "StateSubactionMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<StateUsage> == false);
static_assert(std::is_convertible_v<StateUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<StateUsage*, KerML::Entities::Element*>);
{ StateUsage value; if (value.metaclassName() != "StateUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<StateDefinition> == false);
static_assert(std::is_convertible_v<StateDefinition*, ActionDefinition*>);
static_assert(std::is_convertible_v<StateDefinition*, KerML::Entities::Element*>);
{ StateDefinition value; if (value.metaclassName() != "StateDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<TransitionUsage> == false);
static_assert(std::is_convertible_v<TransitionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<TransitionUsage*, KerML::Entities::Element*>);
{ TransitionUsage value; if (value.metaclassName() != "TransitionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<UseCaseUsage> == false);
static_assert(std::is_convertible_v<UseCaseUsage*, CaseUsage*>);
static_assert(std::is_convertible_v<UseCaseUsage*, KerML::Entities::Element*>);
{ UseCaseUsage value; if (value.metaclassName() != "UseCaseUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<IncludeUseCaseUsage> == false);
static_assert(std::is_convertible_v<IncludeUseCaseUsage*, UseCaseUsage*>);
static_assert(std::is_convertible_v<IncludeUseCaseUsage*, PerformActionUsage*>);
static_assert(std::is_convertible_v<IncludeUseCaseUsage*, KerML::Entities::Element*>);
{ IncludeUseCaseUsage value; if (value.metaclassName() != "IncludeUseCaseUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<UseCaseDefinition> == false);
static_assert(std::is_convertible_v<UseCaseDefinition*, CaseDefinition*>);
static_assert(std::is_convertible_v<UseCaseDefinition*, KerML::Entities::Element*>);
{ UseCaseDefinition value; if (value.metaclassName() != "UseCaseDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PerformActionUsage> == false);
static_assert(std::is_convertible_v<PerformActionUsage*, EventOccurrenceUsage*>);
static_assert(std::is_convertible_v<PerformActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<PerformActionUsage*, KerML::Entities::Element*>);
{ PerformActionUsage value; if (value.metaclassName() != "PerformActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ActionDefinition> == false);
static_assert(std::is_convertible_v<ActionDefinition*, OccurrenceDefinition*>);
static_assert(std::is_convertible_v<ActionDefinition*, KerML::Entities::Behavior*>);
static_assert(std::is_convertible_v<ActionDefinition*, KerML::Entities::Element*>);
{ ActionDefinition value; if (value.metaclassName() != "ActionDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ActionUsage> == false);
static_assert(std::is_convertible_v<ActionUsage*, KerML::Entities::Step*>);
static_assert(std::is_convertible_v<ActionUsage*, OccurrenceUsage*>);
static_assert(std::is_convertible_v<ActionUsage*, KerML::Entities::Element*>);
{ ActionUsage value; if (value.metaclassName() != "ActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AssignmentActionUsage> == false);
static_assert(std::is_convertible_v<AssignmentActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<AssignmentActionUsage*, KerML::Entities::Element*>);
{ AssignmentActionUsage value; if (value.metaclassName() != "AssignmentActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ForLoopActionUsage> == false);
static_assert(std::is_convertible_v<ForLoopActionUsage*, LoopActionUsage*>);
static_assert(std::is_convertible_v<ForLoopActionUsage*, KerML::Entities::Element*>);
{ ForLoopActionUsage value; if (value.metaclassName() != "ForLoopActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<TriggerInvocationExpression> == false);
static_assert(std::is_convertible_v<TriggerInvocationExpression*, KerML::Entities::InvocationExpression*>);
static_assert(std::is_convertible_v<TriggerInvocationExpression*, KerML::Entities::Element*>);
{ TriggerInvocationExpression value; if (value.metaclassName() != "TriggerInvocationExpression") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<LoopActionUsage> == true);
static_assert(std::is_convertible_v<LoopActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<LoopActionUsage*, KerML::Entities::Element*>);
static_assert(std::is_abstract_v<DecisionNode> == false);
static_assert(std::is_convertible_v<DecisionNode*, ControlNode*>);
static_assert(std::is_convertible_v<DecisionNode*, KerML::Entities::Element*>);
{ DecisionNode value; if (value.metaclassName() != "DecisionNode") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ForkNode> == false);
static_assert(std::is_convertible_v<ForkNode*, ControlNode*>);
static_assert(std::is_convertible_v<ForkNode*, KerML::Entities::Element*>);
{ ForkNode value; if (value.metaclassName() != "ForkNode") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<JoinNode> == false);
static_assert(std::is_convertible_v<JoinNode*, ControlNode*>);
static_assert(std::is_convertible_v<JoinNode*, KerML::Entities::Element*>);
{ JoinNode value; if (value.metaclassName() != "JoinNode") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ControlNode> == true);
static_assert(std::is_convertible_v<ControlNode*, ActionUsage*>);
static_assert(std::is_convertible_v<ControlNode*, KerML::Entities::Element*>);
static_assert(std::is_abstract_v<MergeNode> == false);
static_assert(std::is_convertible_v<MergeNode*, ControlNode*>);
static_assert(std::is_convertible_v<MergeNode*, KerML::Entities::Element*>);
{ MergeNode value; if (value.metaclassName() != "MergeNode") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<TerminateActionUsage> == false);
static_assert(std::is_convertible_v<TerminateActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<TerminateActionUsage*, KerML::Entities::Element*>);
{ TerminateActionUsage value; if (value.metaclassName() != "TerminateActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AcceptActionUsage> == false);
static_assert(std::is_convertible_v<AcceptActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<AcceptActionUsage*, KerML::Entities::Element*>);
{ AcceptActionUsage value; if (value.metaclassName() != "AcceptActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<WhileLoopActionUsage> == false);
static_assert(std::is_convertible_v<WhileLoopActionUsage*, LoopActionUsage*>);
static_assert(std::is_convertible_v<WhileLoopActionUsage*, KerML::Entities::Element*>);
{ WhileLoopActionUsage value; if (value.metaclassName() != "WhileLoopActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<SendActionUsage> == false);
static_assert(std::is_convertible_v<SendActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<SendActionUsage*, KerML::Entities::Element*>);
{ SendActionUsage value; if (value.metaclassName() != "SendActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<IfActionUsage> == false);
static_assert(std::is_convertible_v<IfActionUsage*, ActionUsage*>);
static_assert(std::is_convertible_v<IfActionUsage*, KerML::Entities::Element*>);
{ IfActionUsage value; if (value.metaclassName() != "IfActionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ItemUsage> == false);
static_assert(std::is_convertible_v<ItemUsage*, OccurrenceUsage*>);
static_assert(std::is_convertible_v<ItemUsage*, KerML::Entities::Element*>);
{ ItemUsage value; if (value.metaclassName() != "ItemUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ItemDefinition> == false);
static_assert(std::is_convertible_v<ItemDefinition*, KerML::Entities::Structure*>);
static_assert(std::is_convertible_v<ItemDefinition*, OccurrenceDefinition*>);
static_assert(std::is_convertible_v<ItemDefinition*, KerML::Entities::Element*>);
{ ItemDefinition value; if (value.metaclassName() != "ItemDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<EventOccurrenceUsage> == false);
static_assert(std::is_convertible_v<EventOccurrenceUsage*, OccurrenceUsage*>);
static_assert(std::is_convertible_v<EventOccurrenceUsage*, KerML::Entities::Element*>);
{ EventOccurrenceUsage value; if (value.metaclassName() != "EventOccurrenceUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<OccurrenceUsage> == false);
static_assert(std::is_convertible_v<OccurrenceUsage*, Usage*>);
static_assert(std::is_convertible_v<OccurrenceUsage*, KerML::Entities::Element*>);
{ OccurrenceUsage value; if (value.metaclassName() != "OccurrenceUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<OccurrenceDefinition> == false);
static_assert(std::is_convertible_v<OccurrenceDefinition*, Definition*>);
static_assert(std::is_convertible_v<OccurrenceDefinition*, KerML::Entities::Class*>);
static_assert(std::is_convertible_v<OccurrenceDefinition*, KerML::Entities::Element*>);
{ OccurrenceDefinition value; if (value.metaclassName() != "OccurrenceDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<Usage> == false);
static_assert(std::is_convertible_v<Usage*, KerML::Entities::Feature*>);
static_assert(std::is_convertible_v<Usage*, KerML::Entities::Element*>);
{ Usage value; if (value.metaclassName() != "Usage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ReferenceUsage> == false);
static_assert(std::is_convertible_v<ReferenceUsage*, Usage*>);
static_assert(std::is_convertible_v<ReferenceUsage*, KerML::Entities::Element*>);
{ ReferenceUsage value; if (value.metaclassName() != "ReferenceUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<VariantMembership> == false);
static_assert(std::is_convertible_v<VariantMembership*, KerML::Entities::OwningMembership*>);
static_assert(std::is_convertible_v<VariantMembership*, KerML::Entities::Element*>);
{ VariantMembership value; if (value.metaclassName() != "VariantMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<Definition> == false);
static_assert(std::is_convertible_v<Definition*, KerML::Entities::Classifier*>);
static_assert(std::is_convertible_v<Definition*, KerML::Entities::Element*>);
{ Definition value; if (value.metaclassName() != "Definition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AttributeDefinition> == false);
static_assert(std::is_convertible_v<AttributeDefinition*, KerML::Entities::DataType*>);
static_assert(std::is_convertible_v<AttributeDefinition*, Definition*>);
static_assert(std::is_convertible_v<AttributeDefinition*, KerML::Entities::Element*>);
{ AttributeDefinition value; if (value.metaclassName() != "AttributeDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AttributeUsage> == false);
static_assert(std::is_convertible_v<AttributeUsage*, Usage*>);
static_assert(std::is_convertible_v<AttributeUsage*, KerML::Entities::Element*>);
{ AttributeUsage value; if (value.metaclassName() != "AttributeUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PartDefinition> == false);
static_assert(std::is_convertible_v<PartDefinition*, ItemDefinition*>);
static_assert(std::is_convertible_v<PartDefinition*, KerML::Entities::Element*>);
{ PartDefinition value; if (value.metaclassName() != "PartDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PartUsage> == false);
static_assert(std::is_convertible_v<PartUsage*, ItemUsage*>);
static_assert(std::is_convertible_v<PartUsage*, KerML::Entities::Element*>);
{ PartUsage value; if (value.metaclassName() != "PartUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AnalysisCaseUsage> == false);
static_assert(std::is_convertible_v<AnalysisCaseUsage*, CaseUsage*>);
static_assert(std::is_convertible_v<AnalysisCaseUsage*, KerML::Entities::Element*>);
{ AnalysisCaseUsage value; if (value.metaclassName() != "AnalysisCaseUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AnalysisCaseDefinition> == false);
static_assert(std::is_convertible_v<AnalysisCaseDefinition*, CaseDefinition*>);
static_assert(std::is_convertible_v<AnalysisCaseDefinition*, KerML::Entities::Element*>);
{ AnalysisCaseDefinition value; if (value.metaclassName() != "AnalysisCaseDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PortConjugation> == false);
static_assert(std::is_convertible_v<PortConjugation*, KerML::Entities::Conjugation*>);
static_assert(std::is_convertible_v<PortConjugation*, KerML::Entities::Element*>);
{ PortConjugation value; if (value.metaclassName() != "PortConjugation") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConjugatedPortDefinition> == false);
static_assert(std::is_convertible_v<ConjugatedPortDefinition*, PortDefinition*>);
static_assert(std::is_convertible_v<ConjugatedPortDefinition*, KerML::Entities::Element*>);
{ ConjugatedPortDefinition value; if (value.metaclassName() != "ConjugatedPortDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PortDefinition> == false);
static_assert(std::is_convertible_v<PortDefinition*, KerML::Entities::Structure*>);
static_assert(std::is_convertible_v<PortDefinition*, OccurrenceDefinition*>);
static_assert(std::is_convertible_v<PortDefinition*, KerML::Entities::Element*>);
{ PortDefinition value; if (value.metaclassName() != "PortDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConjugatedPortTyping> == false);
static_assert(std::is_convertible_v<ConjugatedPortTyping*, KerML::Entities::FeatureTyping*>);
static_assert(std::is_convertible_v<ConjugatedPortTyping*, KerML::Entities::Element*>);
{ ConjugatedPortTyping value; if (value.metaclassName() != "ConjugatedPortTyping") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<PortUsage> == false);
static_assert(std::is_convertible_v<PortUsage*, OccurrenceUsage*>);
static_assert(std::is_convertible_v<PortUsage*, KerML::Entities::Element*>);
{ PortUsage value; if (value.metaclassName() != "PortUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ViewUsage> == false);
static_assert(std::is_convertible_v<ViewUsage*, PartUsage*>);
static_assert(std::is_convertible_v<ViewUsage*, KerML::Entities::Element*>);
{ ViewUsage value; if (value.metaclassName() != "ViewUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<Expose> == true);
static_assert(std::is_convertible_v<Expose*, KerML::Entities::Import*>);
static_assert(std::is_convertible_v<Expose*, KerML::Entities::Element*>);
static_assert(std::is_abstract_v<ViewDefinition> == false);
static_assert(std::is_convertible_v<ViewDefinition*, PartDefinition*>);
static_assert(std::is_convertible_v<ViewDefinition*, KerML::Entities::Element*>);
{ ViewDefinition value; if (value.metaclassName() != "ViewDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RenderingUsage> == false);
static_assert(std::is_convertible_v<RenderingUsage*, PartUsage*>);
static_assert(std::is_convertible_v<RenderingUsage*, KerML::Entities::Element*>);
{ RenderingUsage value; if (value.metaclassName() != "RenderingUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ViewpointDefinition> == false);
static_assert(std::is_convertible_v<ViewpointDefinition*, RequirementDefinition*>);
static_assert(std::is_convertible_v<ViewpointDefinition*, KerML::Entities::Element*>);
{ ViewpointDefinition value; if (value.metaclassName() != "ViewpointDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RenderingDefinition> == false);
static_assert(std::is_convertible_v<RenderingDefinition*, PartDefinition*>);
static_assert(std::is_convertible_v<RenderingDefinition*, KerML::Entities::Element*>);
{ RenderingDefinition value; if (value.metaclassName() != "RenderingDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<MembershipExpose> == false);
static_assert(std::is_convertible_v<MembershipExpose*, KerML::Entities::MembershipImport*>);
static_assert(std::is_convertible_v<MembershipExpose*, Expose*>);
static_assert(std::is_convertible_v<MembershipExpose*, KerML::Entities::Element*>);
{ MembershipExpose value; if (value.metaclassName() != "MembershipExpose") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<NamespaceExpose> == false);
static_assert(std::is_convertible_v<NamespaceExpose*, Expose*>);
static_assert(std::is_convertible_v<NamespaceExpose*, KerML::Entities::NamespaceImport*>);
static_assert(std::is_convertible_v<NamespaceExpose*, KerML::Entities::Element*>);
{ NamespaceExpose value; if (value.metaclassName() != "NamespaceExpose") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ViewRenderingMembership> == false);
static_assert(std::is_convertible_v<ViewRenderingMembership*, KerML::Entities::FeatureMembership*>);
static_assert(std::is_convertible_v<ViewRenderingMembership*, KerML::Entities::Element*>);
{ ViewRenderingMembership value; if (value.metaclassName() != "ViewRenderingMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ViewpointUsage> == false);
static_assert(std::is_convertible_v<ViewpointUsage*, RequirementUsage*>);
static_assert(std::is_convertible_v<ViewpointUsage*, KerML::Entities::Element*>);
{ ViewpointUsage value; if (value.metaclassName() != "ViewpointUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConnectorAsUsage> == true);
static_assert(std::is_convertible_v<ConnectorAsUsage*, Usage*>);
static_assert(std::is_convertible_v<ConnectorAsUsage*, KerML::Entities::Connector*>);
static_assert(std::is_convertible_v<ConnectorAsUsage*, KerML::Entities::Element*>);
static_assert(std::is_abstract_v<ConnectionUsage> == false);
static_assert(std::is_convertible_v<ConnectionUsage*, PartUsage*>);
static_assert(std::is_convertible_v<ConnectionUsage*, ConnectorAsUsage*>);
static_assert(std::is_convertible_v<ConnectionUsage*, KerML::Entities::Element*>);
{ ConnectionUsage value; if (value.metaclassName() != "ConnectionUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<SuccessionAsUsage> == false);
static_assert(std::is_convertible_v<SuccessionAsUsage*, ConnectorAsUsage*>);
static_assert(std::is_convertible_v<SuccessionAsUsage*, KerML::Entities::Succession*>);
static_assert(std::is_convertible_v<SuccessionAsUsage*, KerML::Entities::Element*>);
{ SuccessionAsUsage value; if (value.metaclassName() != "SuccessionAsUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<ConnectionDefinition> == false);
static_assert(std::is_convertible_v<ConnectionDefinition*, KerML::Entities::AssociationStructure*>);
static_assert(std::is_convertible_v<ConnectionDefinition*, PartDefinition*>);
static_assert(std::is_convertible_v<ConnectionDefinition*, KerML::Entities::Element*>);
{ ConnectionDefinition value; if (value.metaclassName() != "ConnectionDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<BindingConnectorAsUsage> == false);
static_assert(std::is_convertible_v<BindingConnectorAsUsage*, KerML::Entities::BindingConnector*>);
static_assert(std::is_convertible_v<BindingConnectorAsUsage*, ConnectorAsUsage*>);
static_assert(std::is_convertible_v<BindingConnectorAsUsage*, KerML::Entities::Element*>);
{ BindingConnectorAsUsage value; if (value.metaclassName() != "BindingConnectorAsUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<InterfaceUsage> == false);
static_assert(std::is_convertible_v<InterfaceUsage*, ConnectionUsage*>);
static_assert(std::is_convertible_v<InterfaceUsage*, KerML::Entities::Element*>);
{ InterfaceUsage value; if (value.metaclassName() != "InterfaceUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<InterfaceDefinition> == false);
static_assert(std::is_convertible_v<InterfaceDefinition*, ConnectionDefinition*>);
static_assert(std::is_convertible_v<InterfaceDefinition*, KerML::Entities::Element*>);
{ InterfaceDefinition value; if (value.metaclassName() != "InterfaceDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AllocationDefinition> == false);
static_assert(std::is_convertible_v<AllocationDefinition*, ConnectionDefinition*>);
static_assert(std::is_convertible_v<AllocationDefinition*, KerML::Entities::Element*>);
{ AllocationDefinition value; if (value.metaclassName() != "AllocationDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<AllocationUsage> == false);
static_assert(std::is_convertible_v<AllocationUsage*, ConnectionUsage*>);
static_assert(std::is_convertible_v<AllocationUsage*, KerML::Entities::Element*>);
{ AllocationUsage value; if (value.metaclassName() != "AllocationUsage") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<RequirementVerificationMembership> == false);
static_assert(std::is_convertible_v<RequirementVerificationMembership*, RequirementConstraintMembership*>);
static_assert(std::is_convertible_v<RequirementVerificationMembership*, KerML::Entities::Element*>);
{ RequirementVerificationMembership value; if (value.metaclassName() != "RequirementVerificationMembership") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<VerificationCaseDefinition> == false);
static_assert(std::is_convertible_v<VerificationCaseDefinition*, CaseDefinition*>);
static_assert(std::is_convertible_v<VerificationCaseDefinition*, KerML::Entities::Element*>);
{ VerificationCaseDefinition value; if (value.metaclassName() != "VerificationCaseDefinition") throw std::runtime_error("incorrect metaclass identity"); }
static_assert(std::is_abstract_v<VerificationCaseUsage> == false);
static_assert(std::is_convertible_v<VerificationCaseUsage*, CaseUsage*>);
static_assert(std::is_convertible_v<VerificationCaseUsage*, KerML::Entities::Element*>);
{ VerificationCaseUsage value; if (value.metaclassName() != "VerificationCaseUsage") throw std::runtime_error("incorrect metaclass identity"); }
}
