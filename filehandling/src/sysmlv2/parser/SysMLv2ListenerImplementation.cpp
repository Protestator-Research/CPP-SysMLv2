#include <sysmlv2/parser/SysMLv2ListenerImplementation.h>
#include <sysml/SysML.h>
#include <kerml/KerML.h>
#include <sysmlv2/resolution/Retarget.h>
#include <iostream>
#include <algorithm>

namespace {
	using SysMLv2::Files::ReferenceKind;
	using SysMLv2::Files::ReferenceRole;
	using ElementPtr = std::shared_ptr<KerML::Entities::Element>;

	template <class T>
	std::shared_ptr<T> newPlaceholder(ReferenceKind kind, const std::string& name) {
		return std::dynamic_pointer_cast<T>(SysMLv2::Files::makePlaceholder(kind, name));
	}

	// A reference for which no scoped resolution is attempted yet (the target is a member of the value of another expression, or a
	// parameter of the invoked function). It keeps its placeholder and is reported as "not attempted".
	std::shared_ptr<KerML::Entities::Feature> notAttemptedFeature(SysMLv2::Files::ReferenceRecorder& recorder, const std::string& name,
		const std::shared_ptr<KerML::Entities::Element>& context, antlr4::ParserRuleContext* position) {
		return recorder.reference<KerML::Entities::Feature>(name, ReferenceKind::Feature, ReferenceRole::NotAttempted, context, false, nullptr,
			position, nullptr);
	}
}

namespace {
	using SysMLv2::Files::MembershipKind;

	// The rules that stand for a member with a particular kind of membership (looked up by rule index: the check runs for every rule entered).
	bool isKindRule(size_t ruleIndex) {
		static const std::vector<bool> kinds = [] {
			std::vector<bool> result(4096, false);
			for (const size_t index : {
			SysMLv2Parser::RuleAction_body_parameter_member,
			SysMLv2Parser::RuleActor_member,
			SysMLv2Parser::RuleAssignment_target_member,
			SysMLv2Parser::RuleConnector_end_member,
			SysMLv2Parser::RuleDo_action_member,
			SysMLv2Parser::RuleEffect_behavior_member,
			SysMLv2Parser::RuleEntry_action_member,
			SysMLv2Parser::RuleEnumeration_usage_member,
			SysMLv2Parser::RuleExit_action_member,
			SysMLv2Parser::RuleExpression_parameter_member,
			SysMLv2Parser::RuleFlow_end_member,
			SysMLv2Parser::RuleFramed_concern_member,
			SysMLv2Parser::RuleGuard_expression_member,
			SysMLv2Parser::RuleIf_node_parameter_member,
			SysMLv2Parser::RuleInterface_end_member,
			SysMLv2Parser::RuleNode_parameter_member,
			SysMLv2Parser::RuleObjective_member,
			SysMLv2Parser::RuleOwned_cross_feature_member,
			SysMLv2Parser::RulePayload_parameter_member,
			SysMLv2Parser::RuleRequirement_constraint_member,
			SysMLv2Parser::RuleRequirement_verification_member,
			SysMLv2Parser::RuleResult_expression_member,
			SysMLv2Parser::RuleReturn_parameter_member,
			SysMLv2Parser::RuleSatisfaction_subject_member,
			SysMLv2Parser::RuleSource_end_member,
			SysMLv2Parser::RuleStakeholder_member,
			SysMLv2Parser::RuleTrigger_action_member,
			SysMLv2Parser::RuleView_rendering_member}) {
				result[index] = true;
			}
			return result;
		}();
		return ruleIndex < kinds.size() && kinds[ruleIndex];
	}

	// The membership that a member rule of the grammar stands for (Automatic: the membership follows from the kind of the owner and the member).
	MembershipKind memberKindOf(antlr4::ParserRuleContext* ctx) {
		if (!isKindRule(ctx->getRuleIndex())) return MembershipKind::Automatic;
		if (dynamic_cast<SysMLv2Parser::Objective_memberContext*>(ctx)) return MembershipKind::Objective;
		if (auto* requirement = dynamic_cast<SysMLv2Parser::Requirement_constraint_memberContext*>(ctx)) {
			if (requirement->requriement_kind() != nullptr && requirement->requriement_kind()->KEYWORD_ASSUME() != nullptr) return MembershipKind::AssumedConstraint;
			return MembershipKind::RequiredConstraint;
		}
		if (dynamic_cast<SysMLv2Parser::Framed_concern_memberContext*>(ctx)) return MembershipKind::FramedConcern;
		if (dynamic_cast<SysMLv2Parser::Actor_memberContext*>(ctx)) return MembershipKind::Actor;
		if (dynamic_cast<SysMLv2Parser::Stakeholder_memberContext*>(ctx)) return MembershipKind::Stakeholder;
		if (dynamic_cast<SysMLv2Parser::Satisfaction_subject_memberContext*>(ctx)) return MembershipKind::Subject;
		if (dynamic_cast<SysMLv2Parser::View_rendering_memberContext*>(ctx)) return MembershipKind::ViewRendering;
		if (dynamic_cast<SysMLv2Parser::Requirement_verification_memberContext*>(ctx)) return MembershipKind::VerifiedRequirement;
		if (dynamic_cast<SysMLv2Parser::Entry_action_memberContext*>(ctx)) return MembershipKind::EntryAction;
		if (dynamic_cast<SysMLv2Parser::Do_action_memberContext*>(ctx)) return MembershipKind::DoAction;
		if (dynamic_cast<SysMLv2Parser::Exit_action_memberContext*>(ctx)) return MembershipKind::ExitAction;
		if (dynamic_cast<SysMLv2Parser::Trigger_action_memberContext*>(ctx)) return MembershipKind::TriggerAction;
		if (dynamic_cast<SysMLv2Parser::Guard_expression_memberContext*>(ctx)) return MembershipKind::GuardExpression;
		if (dynamic_cast<SysMLv2Parser::Effect_behavior_memberContext*>(ctx)) return MembershipKind::EffectBehavior;
		if (dynamic_cast<SysMLv2Parser::Return_parameter_memberContext*>(ctx)) return MembershipKind::ReturnParameter;
		if (dynamic_cast<SysMLv2Parser::Result_expression_memberContext*>(ctx)) return MembershipKind::ResultExpression;
		// The enumerated values of an enumeration definition are its variants.
		if (dynamic_cast<SysMLv2Parser::Enumeration_usage_memberContext*>(ctx)) return MembershipKind::Variant;
		if (dynamic_cast<SysMLv2Parser::Connector_end_memberContext*>(ctx) || dynamic_cast<SysMLv2Parser::Source_end_memberContext*>(ctx) ||
			dynamic_cast<SysMLv2Parser::Interface_end_memberContext*>(ctx) || dynamic_cast<SysMLv2Parser::Flow_end_memberContext*>(ctx))
			return MembershipKind::EndFeature;
		if (dynamic_cast<SysMLv2Parser::Payload_parameter_memberContext*>(ctx) || dynamic_cast<SysMLv2Parser::Node_parameter_memberContext*>(ctx) ||
			dynamic_cast<SysMLv2Parser::Assignment_target_memberContext*>(ctx) || dynamic_cast<SysMLv2Parser::Expression_parameter_memberContext*>(ctx) ||
			dynamic_cast<SysMLv2Parser::Action_body_parameter_memberContext*>(ctx) || dynamic_cast<SysMLv2Parser::If_node_parameter_memberContext*>(ctx))
			return MembershipKind::Parameter;
		if (dynamic_cast<SysMLv2Parser::Owned_cross_feature_memberContext*>(ctx)) return MembershipKind::Owning;
		return MembershipKind::Automatic;
	}
}

SysMLv2ListenerImplementation::SysMLv2ListenerImplementation() = default;
SysMLv2ListenerImplementation::~SysMLv2ListenerImplementation() = default;

void SysMLv2ListenerImplementation::enterStart(SysMLv2Parser::StartContext*) {
	Elements.clear();
	while (!ParentStack.empty()) ParentStack.pop();
	Recorder = SysMLv2::Files::ReferenceRecorder();
	VisibilityContexts.clear();
	PushedByContext.clear();
	OwnershipKinds.clear();
	MemberMarks.clear();
	SkippedCrossFeatures.clear();
}

void SysMLv2ListenerImplementation::enterEveryRule(antlr4::ParserRuleContext* ctx) {
	if (ParentStack.empty() || ctx == nullptr) return;
	SysMLv2::Files::beginMember(MemberMarks, ctx, memberKindOf(ctx), ParentStack.top());
}

void SysMLv2ListenerImplementation::exitEveryRule(antlr4::ParserRuleContext* ctx) {
	if (MemberMarks.empty() || ctx == nullptr) return;
	SysMLv2::Files::endMember(MemberMarks, ctx, ParentStack.empty() ? nullptr : ParentStack.top(), OwnershipKinds);
}

void SysMLv2ListenerImplementation::recordPush(antlr4::ParserRuleContext* ctx, const std::shared_ptr<KerML::Entities::Element>& elem) {
	if (!ctx || !elem) return;
	PushedByContext[ctx] = elem;
}

bool SysMLv2ListenerImplementation::shouldApplyToTop(antlr4::ParserRuleContext* ctx) const {
	if (ParentStack.empty()) return false;
	const auto& top = ParentStack.top();
	for (auto* c = ctx; c != nullptr; c = c->parent ? dynamic_cast<antlr4::ParserRuleContext*>(c->parent) : nullptr) {
		auto it = PushedByContext.find(c);
		if (it != PushedByContext.end()) {
			auto pushed = it->second.lock();
			// Found the nearest ancestor construct we know pushed something: only apply when what it
			// pushed is still the top of the stack (i.e. that construct, not some further-out one, owns
			// the current top). If it pushed something else (already popped, or a different element),
			// this identification does not belong to the current top - skip it rather than corrupt it.
			return pushed && pushed.get() == top.get();
		}
	}
	// No recorded ancestor at all: this construct's push sites are not (yet) covered by the guard.
	// Keep the previous, unguarded behavior so untracked constructs are not newly broken by this check.
	return true;
}

// Nothing is resolved here: the recorded references are resolved by a SysMLv2::Files::Workspace, over all loaded sources.
void SysMLv2ListenerImplementation::exitStart(SysMLv2Parser::StartContext*) {
	computeVisibilities();
	// The abstract-syntax ownership (memberships, owners, the root namespace) of the whole source.
	SysMLv2::Files::OwnershipInput input;
	input.elements = &Elements;
	input.kinds = std::move(OwnershipKinds);
	input.visibility = &Recorder.data.visibility;
	SysMLv2::Files::buildOwnership(input);
	OwnershipKinds.clear();
}

void SysMLv2ListenerImplementation::enterDependency(SysMLv2Parser::DependencyContext*) {
	const auto dep = std::make_shared<KerML::Entities::Dependency>();
	ParentStack.emplace(dep);
}

void SysMLv2ListenerImplementation::exitDependency(SysMLv2Parser::DependencyContext* ctx) {
	if (ParentStack.empty()) return;
	const auto dep = std::dynamic_pointer_cast<KerML::Entities::Dependency>(ParentStack.top());
	if (!dep) return;
	ParentStack.pop();

	if (ctx && ctx->dependency_declaration()) {
		auto decl = ctx->dependency_declaration();
		if (decl->identification()) {
			applyIdentification(decl->identification(), dep);
		}
		if (decl->KEYWORD_TO()) {
			size_t toIndex = decl->KEYWORD_TO()->getSymbol()->getTokenIndex();
			std::vector<std::shared_ptr<KerML::Entities::Element>> clients;
			std::vector<std::shared_ptr<KerML::Entities::Element>> suppliers;
			for (auto q : decl->qualified_name()) {
				const bool isClient = q->getStart()->getTokenIndex() < toIndex;
				// The ends of a dependency are resolved from the namespace that owns the dependency.
				auto elem = Recorder.replacing<KerML::Entities::Element>(q->getText(), SysMLv2::Files::ReferenceKind::Element,
					SysMLv2::Files::ReferenceRole::Plain, ParentStack.empty() ? nullptr : ParentStack.top(), false, nullptr, q,
					[dep, isClient](const std::shared_ptr<KerML::Entities::Element>& placeholder, const std::shared_ptr<KerML::Entities::Element>& target) {
						auto ends = isClient ? dep->client() : dep->supplier();
						SysMLv2::Files::replaceInVector(ends, placeholder, target);
						if (isClient) dep->setClient(ends);
						else dep->setSupplier(ends);
					});
				if (isClient) {
					clients.push_back(elem);
				}
				else {
					suppliers.push_back(elem);
				}
			}
			dep->setClient(clients);
			dep->setSupplier(suppliers);
		}
	}

	Elements.push_back(dep);
	if (!ParentStack.empty()) {
		ParentStack.top()->appendOwnedElement(dep);
	}
}

void SysMLv2ListenerImplementation::enterAnnotating_element(SysMLv2Parser::Annotating_elementContext*) {}
void SysMLv2ListenerImplementation::exitAnnotating_element(SysMLv2Parser::Annotating_elementContext*) {}

void SysMLv2ListenerImplementation::exitComment(SysMLv2Parser::CommentContext* ctx) {
	std::string identification = "";
	if (ctx->identification() != nullptr) {
		identification = ctx->identification()->getText();
	}

	const bool hasAbout = ctx->KEYWORD_ABOUT() != nullptr && !ctx->annotation().empty();
	std::string locale = "";
	if (ctx->KEYWORD_LOCALE() != nullptr && ctx->STRING_VALUE() != nullptr) {
		locale = ctx->STRING_VALUE()->getText();
	}

	std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
	const auto& comment = std::make_shared<KerML::Entities::Comment>(locale, body);
	Elements.push_back(comment);

	if (!identification.empty())
		comment->setDeclaredName(identification);

	if (hasAbout) {
		// `about` targets are resolved from the namespace that owns the comment; resolved targets are annotated by the comment.
		const auto owner = ParentStack.empty() ? nullptr : ParentStack.top();
		for (auto& about : ctx->annotation()) {
			Recorder.reference<KerML::Entities::Element>(about->getText(), SysMLv2::Files::ReferenceKind::Element,
				SysMLv2::Files::ReferenceRole::Plain, owner, false, nullptr, about,
				[comment](const std::shared_ptr<KerML::Entities::Element>& target) { comment->appendAnnotatedElement(target); });
		}
	}
	else if (!ParentStack.empty())
		comment->appendAnnotatedElement(ParentStack.top());

	if (!ParentStack.empty())
		ParentStack.top()->appendOwnedElement(comment);
}

void SysMLv2ListenerImplementation::exitDocumentation(SysMLv2Parser::DocumentationContext* ctx) {
	std::string identification = "";
	if (ctx->identification() != nullptr) {
		identification = ctx->identification()->getText();
	}
	std::string locale = "";
	if (ctx->KEYWORD_LOCALE() != nullptr && ctx->STRING_VALUE() != nullptr) {
		locale = ctx->STRING_VALUE()->getText();
	}
	std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
	auto parent = ParentStack.empty() ? nullptr : ParentStack.top();
	auto documentation = std::make_shared<KerML::Entities::Documentation>(parent, locale, body);
	documentation->setDeclaredName(identification);
	Elements.push_back(documentation);
	if (!ParentStack.empty()) {
		ParentStack.top()->appendOwnedElement(documentation);
	}
}

void SysMLv2ListenerImplementation::exitTextual_representation(SysMLv2Parser::Textual_representationContext* ctx) {
	std::string language;
	if (ctx->KEYWORD_LANGUAGE() != nullptr && ctx->STRING_VALUE() != nullptr)
		language = ctx->STRING_VALUE()->getText();

	std::string body = ctx->REGULAR_COMMENT() ? ctx->REGULAR_COMMENT()->getText() : "";
	const auto textualRepresentation = std::make_shared<KerML::Entities::TextualRepresentation>(language, body);
	Elements.push_back(textualRepresentation);
	if (!ParentStack.empty())
		ParentStack.top()->appendOwnedElement(textualRepresentation);
}

void SysMLv2ListenerImplementation::enterPackage(SysMLv2Parser::PackageContext* ctx) {
	const auto package = std::make_shared<KerML::Entities::Package>();
	if (ctx && ctx->package_declaration() && ctx->package_declaration()->identification()) {
		applyIdentification(ctx->package_declaration()->identification(), package);
	}
	ParentStack.push(package);
	VisibilityContexts.emplace_back(ctx, package);
}

void SysMLv2ListenerImplementation::exitPackage(SysMLv2Parser::PackageContext*) {
	if (ParentStack.empty()) return;
	const auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top());
	ParentStack.pop();
	if (package) {
		Elements.push_back(package);
		if (!ParentStack.empty()) {
			package->setOwner(ParentStack.top());
			ParentStack.top()->appendOwnedElement(package);
		}
	}
}

void SysMLv2ListenerImplementation::enterPackage_declaration(SysMLv2Parser::Package_declarationContext*) {}
void SysMLv2ListenerImplementation::exitPackage_declaration(SysMLv2Parser::Package_declarationContext* ctx) {
	if (ParentStack.empty()) return;
	if (auto package = std::dynamic_pointer_cast<KerML::Entities::Package>(ParentStack.top())) {
		if (ctx && ctx->identification()) {
			applyIdentification(ctx->identification(), package);
		}
	}
}

void SysMLv2ListenerImplementation::enterAlias_member(SysMLv2Parser::Alias_memberContext*) {}
void SysMLv2ListenerImplementation::exitAlias_member(SysMLv2Parser::Alias_memberContext* ctx) {
	if (!ctx || !ctx->qualified_name()) return;
	const std::string targetName = ctx->qualified_name()->getText();
	const auto names = ctx->sysml_name();
	std::string aliasName;
	std::string shortName;
	if (ctx->SYMBOL_SMALLER() != nullptr) {
		if (!names.empty()) shortName = names[0]->getText();
		if (names.size() > 1) aliasName = names[1]->getText();
	}
	else if (!names.empty()) {
		aliasName = names[0]->getText();
	}
	if (aliasName.empty() && shortName.empty()) return;

	// An alias is a non-owning membership of the target in the namespace that declares it.
	auto membership = std::make_shared<KerML::Entities::Membership>();
	if (!aliasName.empty()) membership->setMemberName(aliasName);
	if (!shortName.empty()) membership->setMemberShortName(shortName);
	// The member_prefix is a direct child of the alias_member rule.
	KerML::Entities::VisibilityKind visibility = KerML::Entities::PUBLIC;
	if (ctx->member_prefix() != nullptr && ctx->member_prefix()->visibility_indicator() != nullptr) {
		const auto indicator = ctx->member_prefix()->visibility_indicator();
		if (indicator->KEYWORD_PRIVATE() != nullptr) visibility = KerML::Entities::PRIVATE;
		else if (indicator->KEYWORD_PROTECTED() != nullptr) visibility = KerML::Entities::PROTECTED;
	}
	membership->setVisibility(visibility);
	const auto owner = ParentStack.empty() ? nullptr : ParentStack.top();
	if (owner) {
		membership->setMembershipOwningNamespace(std::dynamic_pointer_cast<KerML::Entities::Namespace>(owner));
		membership->setOwner(owner);
		owner->appendOwnedElement(membership);
	}
	Elements.push_back(membership);

	auto record = std::make_shared<SysMLv2::Files::AliasRecord>();
	record->owner = owner;
	record->membership = membership;
	record->name = aliasName;
	record->shortName = shortName;
	record->target = targetName;
	record->visibility = visibility;
	if (ctx->getStart() != nullptr) {
		record->line = static_cast<int>(ctx->getStart()->getLine());
		record->column = static_cast<int>(ctx->getStart()->getCharPositionInLine());
	}
	Recorder.data.aliases.push_back(record);

	// The alias name is also recorded on the target as an alternative identifier.
	const std::string aliasId = names.back()->getText();
	Recorder.reference<KerML::Entities::Element>(targetName, SysMLv2::Files::ReferenceKind::Element, SysMLv2::Files::ReferenceRole::Alias,
		owner, false, nullptr, ctx->qualified_name(), [record, membership, aliasId](const std::shared_ptr<KerML::Entities::Element>& target) {
			record->resolvedTarget = target;
			membership->setMemberElement(target);
			target->appendAliasId(aliasId);
		});
}

void SysMLv2ListenerImplementation::enterDefinition_declaration(SysMLv2Parser::Definition_declarationContext*) {}
void SysMLv2ListenerImplementation::exitDefinition_declaration(SysMLv2Parser::Definition_declarationContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (!shouldApplyToTop(ctx)) return;
	auto topElem = ParentStack.top();
	if (ctx->identification()) {
		applyIdentification(ctx->identification(), topElem);
	}
}

void SysMLv2ListenerImplementation::exitSubsclassification_part(SysMLv2Parser::Subsclassification_partContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	auto classifier = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
	if (!classifier) return;
	for (auto subCtx : ctx->owned_subclassification()) {
		addSubclassification(classifier, subCtx->getText(), subCtx);
	}
}

void SysMLv2ListenerImplementation::enterVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext* ctx) {
	auto vm = std::make_shared<SysMLv2::Entities::VariantMembership>();
	ParentStack.push(vm);
	recordPush(ctx, vm);
}

void SysMLv2ListenerImplementation::exitVariant_usage_member(SysMLv2Parser::Variant_usage_memberContext*) {
	if (ParentStack.empty()) return;
	auto vm = std::dynamic_pointer_cast<SysMLv2::Entities::VariantMembership>(ParentStack.top());
	if (!vm) return;
	ParentStack.pop();

	if (!vm->ownedElements().empty()) {
		for (const auto& child : vm->ownedElements()) {
			if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::Usage>(child)) {
				vm->setOwnedVariantUsage(usage);
				vm->setMemberElement(usage);
				vm->setOwnedMemberElement(usage);
				break;
			}
		}
	}

	Elements.push_back(vm);
	if (!ParentStack.empty()) {
		vm->setOwner(ParentStack.top());
		ParentStack.top()->appendOwnedElement(vm);
		if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(ParentStack.top())) {
			def->appendOwnedMembership(vm);
		}
	}
}

void SysMLv2ListenerImplementation::enterSubject_member(SysMLv2Parser::Subject_memberContext* ctx) {
	auto sm = std::make_shared<SysMLv2::Entities::SubjectMembership>();
	ParentStack.push(sm);
	recordPush(ctx, sm);
}

void SysMLv2ListenerImplementation::exitSubject_member(SysMLv2Parser::Subject_memberContext*) {
	if (ParentStack.empty()) return;
	auto sm = std::dynamic_pointer_cast<SysMLv2::Entities::SubjectMembership>(ParentStack.top());
	if (!sm) return;
	ParentStack.pop();

	if (!sm->ownedElements().empty()) {
		for (const auto& child : sm->ownedElements()) {
			if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::Usage>(child)) {
				sm->setOwnedSubjectParameter(usage);
				sm->setMemberElement(usage);
				sm->setOwnedMemberElement(usage);
				break;
			}
		}
	}

	Elements.push_back(sm);
	if (!ParentStack.empty()) {
		sm->setOwner(ParentStack.top());
		ParentStack.top()->appendOwnedElement(sm);
		if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top())) {
			ns->appendOwnedMembership(sm);
		}
	}
}

void SysMLv2ListenerImplementation::enterSubject_usage(SysMLv2Parser::Subject_usageContext* ctx) {
	// SubjectUsage : ReferenceUsage (SysML 8.2.2.x)
	auto u = std::make_shared<SysMLv2::Entities::ReferenceUsage>();
	ParentStack.push(u);
	recordPush(ctx, u);
}

void SysMLv2ListenerImplementation::exitSubject_usage(SysMLv2Parser::Subject_usageContext*) {
	if (ParentStack.empty()) return;
	auto u = std::dynamic_pointer_cast<SysMLv2::Entities::ReferenceUsage>(ParentStack.top());
	if (!u) return;
	ParentStack.pop();

	Elements.push_back(u);
	if (!ParentStack.empty()) {
		u->setOwner(ParentStack.top());
		ParentStack.top()->appendOwnedElement(u);
	}
}

// EndUsagePrefix = isEnd ?= 'end' ( OwnedCrossFeatureMember )?
void SysMLv2ListenerImplementation::exitEnd_usage_prefix(SysMLv2Parser::End_usage_prefixContext* ctx) {
	if (ParentStack.empty() || !ctx || !shouldApplyToTop(ctx)) return;
	if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
		feat->setIsEnd(true);
	}
}

// OwnedCrossFeature : ReferenceUsage = BasicUsagePrefix UsageDeclaration. The cross feature declared between 'end' and
// the kind keyword of an end usage is a ReferenceUsage owned by that end usage (through an OwningMembership, so it is not
// one of the end usage's featured members). It gets its own stack entry so that its name and multiplicity do not
// land on the end usage.
void SysMLv2ListenerImplementation::enterOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext* ctx) {
	// The grammar takes everything between `end` and the kind keyword as the cross feature. There is no cross feature if nothing is
	// written there (`end part x`), and none either if no kind keyword follows (`end x : T :>> y;` declares the end feature itself):
	// the name, typing and multiplicity then belong to the end usage.
	bool declaresCrossFeature = ctx != nullptr && !ctx->getText().empty();
	if (declaresCrossFeature) {
		for (antlr4::ParserRuleContext* c = ctx; c != nullptr; c = c->parent ? dynamic_cast<antlr4::ParserRuleContext*>(c->parent) : nullptr) {
			if (auto* redefinition = dynamic_cast<SysMLv2Parser::Redefinition_usage_elementContext*>(c)) {
				if (redefinition->KEYWORD_ATTRIBUTE() == nullptr && redefinition->KEYWORD_PART() == nullptr && redefinition->KEYWORD_ITEM() == nullptr &&
					redefinition->KEYWORD_PORT() == nullptr && redefinition->KEYWORD_ACTION() == nullptr && redefinition->KEYWORD_CALC() == nullptr &&
					redefinition->KEYWORD_CONSTRAINT() == nullptr)
					declaresCrossFeature = false;
				break;
			}
			if (PushedByContext.count(c) != 0) break;
		}
	}
	if (!declaresCrossFeature) {
		SkippedCrossFeatures.insert(ctx);
		return;
	}
	auto cross = std::make_shared<SysMLv2::Entities::ReferenceUsage>();
	ParentStack.push(cross);
	recordPush(ctx, cross);
}

void SysMLv2ListenerImplementation::exitOwned_cross_feature(SysMLv2Parser::Owned_cross_featureContext* ctx) {
	if (SkippedCrossFeatures.erase(ctx) != 0) return;
	if (ParentStack.empty()) return;
	auto cross = std::dynamic_pointer_cast<SysMLv2::Entities::ReferenceUsage>(ParentStack.top());
	if (!cross) return;
	ParentStack.pop();
	Elements.push_back(cross);
	if (ParentStack.empty()) return;
	cross->setOwner(ParentStack.top());
	// The cross feature is owned through an OwnedCrossFeatureMember (an OwningMembership), not as a feature of the end feature.
	OwnershipKinds[cross.get()] = SysMLv2::Files::MembershipKind::Owning;
	ParentStack.top()->appendOwnedElement(cross);
	if (auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
		endFeature->setCrossFeature(cross);
	}
}

// Crosses = CROSSES OwnedCrossSubsetting
void SysMLv2ListenerImplementation::exitOwned_cross_subsetting(SysMLv2Parser::Owned_cross_subsettingContext* ctx) {
	if (ParentStack.empty() || !ctx || !ctx->general_type() || !shouldApplyToTop(ctx)) return;
	auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!feature) return;
	const std::string crossedName = ctx->general_type()->getText();
	auto placeholder = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, crossedName);
	auto crossSubsetting = std::make_shared<KerML::Entities::CrossSubsetting>(placeholder, feature);
	feature->setOwnedCrossSubsetting(crossSubsetting);
	feature->appendOwnedElement(crossSubsetting);
	Elements.push_back(crossSubsetting);
	Recorder.record(placeholder, crossedName, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, ctx,
		[crossSubsetting](const ElementPtr& element) {
			if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) {
				SysMLv2::Files::Retarget::crossSubsetting(*crossSubsetting, target);
			}
		});
}

void SysMLv2ListenerImplementation::enterUsage_declaration(SysMLv2Parser::Usage_declarationContext*) {}
void SysMLv2ListenerImplementation::exitUsage_declaration(SysMLv2Parser::Usage_declarationContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (!shouldApplyToTop(ctx)) return;
	// The control nodes (`merge`, `decide`, `join`, `fork`) do not create an element yet, and neither do the nodes that are not usages
	// of their own: their identification and specialization must not be applied to the definition or usage that encloses them (that
	// used to rename, for example, `action def ForLoopAction` to the name of its nested `action whileLoop while ...`). The
	// `assign`, `while`, `for`, `if`, `send` and `accept` nodes push their own usage, which ends the walk up below.
	for (antlr4::ParserRuleContext* c = ctx; c != nullptr; c = c->parent ? dynamic_cast<antlr4::ParserRuleContext*>(c->parent) : nullptr) {
		if (dynamic_cast<SysMLv2Parser::Action_nodeContext*>(c) != nullptr) return;
		if (c != ctx && PushedByContext.count(c) != 0) break;
	}
	auto topElem = ParentStack.top();
	if (ctx->identification()) {
		applyIdentification(ctx->identification(), topElem);
	}
	if (ctx->feature_specialization_part()) {
		if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(topElem)) {
			applyFeatureSpecializationPart(ctx->feature_specialization_part(), feat);
		}
	}
}

static void applyFeatureDirectionFromContext(SysMLv2Parser::Feature_directionContext* dirCtx, const std::shared_ptr<KerML::Entities::Feature>& feature) {
	if (!dirCtx || !feature) return;
	if (dirCtx->KEYWORD_INOUT() != nullptr) feature->setDirection(KerML::Entities::IN_OUT);
	else if (dirCtx->KEYWORD_IN() != nullptr) feature->setDirection(KerML::Entities::IN);
	else if (dirCtx->KEYWORD_OUT() != nullptr) feature->setDirection(KerML::Entities::OUT);
}

static void applyPortionKind(SysMLv2Parser::Portion_kindContext* pkCtx, const std::shared_ptr<SysMLv2::Entities::OccurrenceUsage>& occUsage) {
	if (!pkCtx || !occUsage) return;
	if (pkCtx->KEYWORD_SNAPSHOT() != nullptr) occUsage->setPortionKind(SysMLv2::Entities::PortionKind::snapshot);
	else if (pkCtx->KEYWORD_TIMESLICE() != nullptr) occUsage->setPortionKind(SysMLv2::Entities::PortionKind::timeslice);
}

void SysMLv2ListenerImplementation::applyUsagePrefix(SysMLv2Parser::Usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature) {
	if (!prefix || !feature) return;
	auto unextended = prefix->unextended_usage_prefix();
	if (!unextended) return;
	auto basicPrefix = unextended->basic_usage_prefix();
	if (!basicPrefix) return;
	auto refPrefix = basicPrefix->ref_prefix();
	if (!refPrefix) return;
	applyFeatureDirectionFromContext(refPrefix->feature_direction(), feature);
}

void SysMLv2ListenerImplementation::applyOccurrenceUsagePrefix(SysMLv2Parser::Occurrence_usage_prefixContext* prefix, const std::shared_ptr<KerML::Entities::Feature>& feature) {
	if (!prefix || !feature) return;
	auto basicPrefix = prefix->basic_usage_prefix();
	if (!basicPrefix) return;
	auto refPrefix = basicPrefix->ref_prefix();
	if (!refPrefix) return;
	applyFeatureDirectionFromContext(refPrefix->feature_direction(), feature);
}

void SysMLv2ListenerImplementation::applyFeatureSpecializationPart(SysMLv2Parser::Feature_specialization_partContext* part, const std::shared_ptr<KerML::Entities::Feature>& feature) {
	if (!part || !feature) return;
	applyFeatureSpecifications(part->feature_specialization(), feature);
}

void SysMLv2ListenerImplementation::applyFeatureSpecifications(const std::vector<SysMLv2Parser::Feature_specializationContext*>& specifications, const std::shared_ptr<KerML::Entities::Feature>& feature) {
	if (!feature) return;
	for (auto spec : specifications) {
		if (spec->typings()) {
			for (auto typingCtx : spec->typings()->owned_feature_typing()) {
				addTyping(feature, typingCtx->getText(), typingCtx);
			}
			if (spec->typings()->typed_by() && spec->typings()->typed_by()->owned_feature_typing()) {
				auto* typingCtx = spec->typings()->typed_by()->owned_feature_typing();
				addTyping(feature, typingCtx->getText(), typingCtx);
			}
		}
		if (spec->subsettings()) {
			if (spec->subsettings()->subsets() && spec->subsettings()->subsets()->owned_subsetting()) {
				auto* subsetCtx = spec->subsettings()->subsets()->owned_subsetting();
				addSubsetting(feature, subsetCtx->getText(), subsetCtx);
			}
			for (auto subsetCtx : spec->subsettings()->owned_subsetting()) {
				addSubsetting(feature, subsetCtx->getText(), subsetCtx);
			}
		}
		if (spec->references() && spec->references()->owned_reference_subsetting()) {
			auto* refCtx = spec->references()->owned_reference_subsetting();
			addReferenceSubsetting(feature, refCtx->getText(), refCtx);
		}
		if (spec->redefinitions()) {
			if (spec->redefinitions()->redefines() && spec->redefinitions()->redefines()->owned_redefinition()) {
				auto* redefCtx = spec->redefinitions()->redefines()->owned_redefinition();
				addRedefinition(feature, redefCtx->getText(), redefCtx);
			}
			for (auto redefCtx : spec->redefinitions()->owned_redefinition()) {
				addRedefinition(feature, redefCtx->getText(), redefCtx);
			}
		}
	}
}

void SysMLv2ListenerImplementation::exitMultiplicity_part(SysMLv2Parser::Multiplicity_partContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!feature) return;
	std::string text = ctx->getText();
	if (text.find("nonunique") != std::string::npos) feature->setIsUnique(false);
	if (text.find("ordered") != std::string::npos) feature->setIsOrdered(true);
	else feature->setIsOrdered(false);
}

void SysMLv2ListenerImplementation::enterMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext*) {}
void SysMLv2ListenerImplementation::exitOccurrence_definition_prefix(SysMLv2Parser::Occurrence_definition_prefixContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
		std::string text = ctx->getText();
		if (text.find("abstract") != std::string::npos) type->setAbstract(true);
		if (text.find("variation") != std::string::npos) {
			if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(type)) {
				def->setIsVariation(true);
			}
		}
	}
	if (ctx->KEYWORD_INDIVIDUAL() != nullptr) {
		if (auto occDef = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceDefinition>(ParentStack.top())) {
			occDef->setIsIndividual(true);
		}
	}
}

void SysMLv2ListenerImplementation::exitDefinition_prefix(SysMLv2Parser::Definition_prefixContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
		std::string text = ctx->getText();
		if (text.find("abstract") != std::string::npos) type->setAbstract(true);
		if (text.find("variation") != std::string::npos) {
			if (auto def = std::dynamic_pointer_cast<SysMLv2::Entities::Definition>(type)) {
				def->setIsVariation(true);
			}
		}
	}
}

void SysMLv2ListenerImplementation::exitUsage_prefix(SysMLv2Parser::Usage_prefixContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
		applyUsagePrefix(ctx, feat);
	}
}

void SysMLv2ListenerImplementation::exitOccurrence_usage_prefix(SysMLv2Parser::Occurrence_usage_prefixContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
		applyOccurrenceUsagePrefix(ctx, feat);
	}
	if (auto occUsage = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceUsage>(ParentStack.top())) {
		if (ctx->KEYWORD_INDIVIDUAL() != nullptr) {
			occUsage->setIsIndividual(true);
		}
		applyPortionKind(ctx->portion_kind(), occUsage);
	}
}

template<typename T>
static void handleUsageEnter(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack,
                              std::map<antlr4::ParserRuleContext*, std::weak_ptr<KerML::Entities::Element>>* pushMap = nullptr,
                              antlr4::ParserRuleContext* ctx = nullptr) {
	auto usage = std::make_shared<T>();
	parentStack.push(usage);
	if (pushMap && ctx) (*pushMap)[ctx] = usage;
}

template<typename T>
static void handleUsageExit(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, std::vector<std::shared_ptr<KerML::Entities::Element>>& elements) {
	if (parentStack.empty()) return;
	auto usage = std::dynamic_pointer_cast<T>(parentStack.top());
	if (!usage) return;
	parentStack.pop();

	elements.push_back(usage);
	if (!parentStack.empty()) {
		usage->setOwner(parentStack.top());
		parentStack.top()->appendOwnedElement(usage);
		if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(parentStack.top())) {
			if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(usage)) {
				type->appendOwnedFeature(feat);
				feat->setOwningType(type);
			}
		}
	}
}

void SysMLv2ListenerImplementation::enterEnumerated_value(SysMLv2Parser::Enumerated_valueContext* ctx) {
	handleUsageEnter<SysMLv2::Entities::EnumerationUsage>(ParentStack, &PushedByContext, ctx);
}

void SysMLv2ListenerImplementation::exitEnumerated_value(SysMLv2Parser::Enumerated_valueContext*) {
	handleUsageExit<SysMLv2::Entities::EnumerationUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::exitMultiplicity_range(SysMLv2Parser::Multiplicity_rangeContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
	if (!type || ctx->multiplicity_expression_member().empty()) return;

	std::shared_ptr<KerML::Entities::Multiplicity> multiplicity;
	try {
		if (ctx->multiplicity_expression_member().size() > 1) {
			unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
			if (ctx->multiplicity_expression_member().back()->getText() == "*") {
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, true);
			}
			else {
				unsigned maximum = std::stoul(ctx->multiplicity_expression_member().back()->getText());
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, maximum);
			}
		}
		else {
			if (ctx->multiplicity_expression_member().front()->getText() == "*") {
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(0, true);
			}
			else {
				unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum);
			}
		}
	}
	catch (...) {
		// Ignore non-numeric multiplicity expressions (e.g. invalid syntax, expressions or units)
	}
	if (multiplicity) {
		type->setMultiplicity(multiplicity);
		type->appendOwnedElement(multiplicity);
		Elements.push_back(multiplicity);
	}
}

void SysMLv2ListenerImplementation::enterConnector_end(SysMLv2Parser::Connector_endContext* ctx) {
	auto endFeature = std::make_shared<KerML::Entities::Feature>();
	endFeature->setIsEnd(true);
	ParentStack.push(endFeature);
	recordPush(ctx, endFeature);
}

void SysMLv2ListenerImplementation::exitConnector_end(SysMLv2Parser::Connector_endContext* ctx) {
	if (ParentStack.empty()) return;
	auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!endFeature) return;
	ParentStack.pop();

	if (ctx && ctx->owned_reference_subsetting() && ctx->owned_reference_subsetting()->general_type()) {
		addReferenceSubsetting(endFeature, ctx->owned_reference_subsetting()->general_type()->getText(), ctx->owned_reference_subsetting());
	}

	Elements.push_back(endFeature);
	if (!ParentStack.empty()) {
		ParentStack.top()->appendOwnedElement(endFeature);
		if (auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top())) {
			conn->appendConnectorEnd(endFeature);
			conn->appendOwnedFeature(endFeature);
		}
	}
}

void SysMLv2ListenerImplementation::exitMultiplicity_bounds(SysMLv2Parser::Multiplicity_boundsContext* ctx) {
	if (ParentStack.empty() || !ctx) return;
	auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
	if (!type || ctx->multiplicity_expression_member().empty()) return;

	std::shared_ptr<KerML::Entities::Multiplicity> multiplicity;
	try {
		if (ctx->multiplicity_expression_member().size() > 1) {
			unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
			if (ctx->multiplicity_expression_member().back()->getText() == "*") {
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, true);
			}
			else {
				unsigned maximum = std::stoul(ctx->multiplicity_expression_member().back()->getText());
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum, maximum);
			}
		}
		else {
			if (ctx->multiplicity_expression_member().front()->getText() == "*") {
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(0, true);
			}
			else {
				unsigned minimum = std::stoul(ctx->multiplicity_expression_member().front()->getText());
				multiplicity = std::make_shared<KerML::Entities::Multiplicity>(minimum);
			}
		}
	}
	catch (...) {
		// Ignore non-numeric multiplicity expressions (e.g. invalid syntax, expressions or units)
	}
	if (multiplicity) {
		type->setMultiplicity(multiplicity);
		type->appendOwnedElement(multiplicity);
		Elements.push_back(multiplicity);
	}
}

// Definition-Family Implementierungen
template<typename T>
static void handleDefEnter(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, antlr4::ParserRuleContext* ctx,
                            std::map<antlr4::ParserRuleContext*, std::weak_ptr<KerML::Entities::Element>>* pushMap = nullptr) {
	auto def = std::make_shared<T>();
	parentStack.push(def);
	if (pushMap && ctx) (*pushMap)[ctx] = def;
}

template<typename T>
static void handleDefExit(std::stack<std::shared_ptr<KerML::Entities::Element>>& parentStack, std::vector<std::shared_ptr<KerML::Entities::Element>>& elements, antlr4::ParserRuleContext* ctx = nullptr) {
	if (parentStack.empty()) return;
	auto def = std::dynamic_pointer_cast<T>(parentStack.top());
	if (!def) return;
	parentStack.pop();

	if (ctx) {
		std::string text = ctx->getText();
		if (text.find("abstract") != std::string::npos) def->setAbstract(true);
		if (text.find("variation") != std::string::npos) def->setIsVariation(true);
	}

	elements.push_back(def);
	if (!parentStack.empty()) {
		def->setOwner(parentStack.top());
		parentStack.top()->appendOwnedElement(def);
	}
}

#define DEFINE_DEF_METHODS(Name, Type) \
void SysMLv2ListenerImplementation::enter##Name(SysMLv2Parser::Name##Context* ctx) { \
    handleDefEnter<Type>(ParentStack, ctx, &PushedByContext); \
} \
void SysMLv2ListenerImplementation::exit##Name(SysMLv2Parser::Name##Context* ctx) { \
    handleDefExit<Type>(ParentStack, Elements, ctx); \
}

DEFINE_DEF_METHODS(Part_definition, SysMLv2::Entities::PartDefinition)
DEFINE_DEF_METHODS(Attribute_definition, SysMLv2::Entities::AttributeDefinition)
DEFINE_DEF_METHODS(Item_definition, SysMLv2::Entities::ItemDefinition)
DEFINE_DEF_METHODS(Port_definition, SysMLv2::Entities::PortDefinition)
DEFINE_DEF_METHODS(Connection_definition, SysMLv2::Entities::ConnectionDefinition)
DEFINE_DEF_METHODS(Interface_definition, SysMLv2::Entities::InterfaceDefinition)
DEFINE_DEF_METHODS(Allocation_definition, SysMLv2::Entities::AllocationDefinition)
DEFINE_DEF_METHODS(Action_definition, SysMLv2::Entities::ActionDefinition)
DEFINE_DEF_METHODS(Calculation_definition, SysMLv2::Entities::CalculationDefinition)
DEFINE_DEF_METHODS(Requirement_definition, SysMLv2::Entities::RequirementDefinition)
DEFINE_DEF_METHODS(Concern_definition, SysMLv2::Entities::ConcernDefinition)
DEFINE_DEF_METHODS(Case_definition, SysMLv2::Entities::CaseDefinition)
DEFINE_DEF_METHODS(Analysis_case_definition, SysMLv2::Entities::AnalysisCaseDefinition)
DEFINE_DEF_METHODS(Verification_case_definition, SysMLv2::Entities::VerificationCaseDefinition)
DEFINE_DEF_METHODS(View_definition, SysMLv2::Entities::ViewDefinition)
DEFINE_DEF_METHODS(Viewpoint_definition, SysMLv2::Entities::ViewpointDefinition)
DEFINE_DEF_METHODS(Rendering_definition, SysMLv2::Entities::RenderingDefinition)
DEFINE_DEF_METHODS(Metadata_definition, SysMLv2::Entities::MetadataDefinition)
DEFINE_DEF_METHODS(Enumeration_definition, SysMLv2::Entities::EnumerationDefinition)
DEFINE_DEF_METHODS(State_definition, SysMLv2::Entities::StateDefinition)
DEFINE_DEF_METHODS(Constraint_definition, SysMLv2::Entities::ConstraintDefinition)
DEFINE_DEF_METHODS(Extended_definition, SysMLv2::Entities::Definition)
DEFINE_DEF_METHODS(Occurrence_definition, SysMLv2::Entities::OccurrenceDefinition)
DEFINE_DEF_METHODS(Flow_definition, SysMLv2::Entities::FlowDefinition)
// Fix (review defect B): Use_case_definition had an empty enter/exit handler, so
// exitDefinition_declaration's ParentStack.top() identification landed on the ENCLOSING
// element instead (e.g. the package). Wiring it through DEFINE_DEF_METHODS gives it the
// same push/identify/pop/attach behavior as every other *_definition rule.
DEFINE_DEF_METHODS(Use_case_definition, SysMLv2::Entities::UseCaseDefinition)

void SysMLv2ListenerImplementation::enterIndividual_definition(SysMLv2Parser::Individual_definitionContext* ctx) {
	auto def = std::make_shared<SysMLv2::Entities::OccurrenceDefinition>();
	def->setIsIndividual(true);
	ParentStack.push(def);
	recordPush(ctx, def);
}
void SysMLv2ListenerImplementation::exitIndividual_definition(SysMLv2Parser::Individual_definitionContext*) {
	handleDefExit<SysMLv2::Entities::OccurrenceDefinition>(ParentStack, Elements);
}

// Usage-Family Implementierungen

#define DEFINE_USAGE_METHODS(Name, Type) \
void SysMLv2ListenerImplementation::enter##Name(SysMLv2Parser::Name##Context* ctx) { \
    handleUsageEnter<Type>(ParentStack, &PushedByContext, ctx); \
} \
void SysMLv2ListenerImplementation::exit##Name(SysMLv2Parser::Name##Context*) { \
    handleUsageExit<Type>(ParentStack, Elements); \
}

DEFINE_USAGE_METHODS(Part_usage, SysMLv2::Entities::PartUsage)
DEFINE_USAGE_METHODS(Attribute_usage, SysMLv2::Entities::AttributeUsage)
DEFINE_USAGE_METHODS(Item_usage, SysMLv2::Entities::ItemUsage)
DEFINE_USAGE_METHODS(Port_usage, SysMLv2::Entities::PortUsage)
DEFINE_USAGE_METHODS(Interface_usage, SysMLv2::Entities::InterfaceUsage)
DEFINE_USAGE_METHODS(Allocation_usage, SysMLv2::Entities::AllocationUsage)
DEFINE_USAGE_METHODS(Action_usage, SysMLv2::Entities::ActionUsage)
DEFINE_USAGE_METHODS(Calculation_usage, SysMLv2::Entities::CalculationUsage)
DEFINE_USAGE_METHODS(Requirement_usage, SysMLv2::Entities::RequirementUsage)
DEFINE_USAGE_METHODS(Concern_usage, SysMLv2::Entities::ConcernUsage)
DEFINE_USAGE_METHODS(Case_usage, SysMLv2::Entities::CaseUsage)
DEFINE_USAGE_METHODS(Analysis_case_usage, SysMLv2::Entities::AnalysisCaseUsage)
DEFINE_USAGE_METHODS(Verification_case_usage, SysMLv2::Entities::VerificationCaseUsage)
DEFINE_USAGE_METHODS(View_usage, SysMLv2::Entities::ViewUsage)
DEFINE_USAGE_METHODS(Viewpoint_usage, SysMLv2::Entities::ViewpointUsage)
DEFINE_USAGE_METHODS(Rendering_usage, SysMLv2::Entities::RenderingUsage)
DEFINE_USAGE_METHODS(Metadata_usage, SysMLv2::Entities::MetadataUsage)
DEFINE_USAGE_METHODS(Occurrence_usage, SysMLv2::Entities::OccurrenceUsage)
DEFINE_USAGE_METHODS(Enumeration_usage, SysMLv2::Entities::EnumerationUsage)
DEFINE_USAGE_METHODS(State_usage, SysMLv2::Entities::StateUsage)
DEFINE_USAGE_METHODS(Constraint_usage, SysMLv2::Entities::ConstraintUsage)
DEFINE_USAGE_METHODS(Extended_usage, SysMLv2::Entities::Usage)
DEFINE_USAGE_METHODS(Perform_action_usage, SysMLv2::Entities::PerformActionUsage)

// The action nodes that are usages of their own (`action n assign x := 1;`, `while`, `for`, `if`, `send`, `accept`): a node that is
// declared with a name (`action initialization assign ...`) is a member of the action with that name.
DEFINE_USAGE_METHODS(Accept_node, SysMLv2::Entities::AcceptActionUsage)
DEFINE_USAGE_METHODS(Send_node, SysMLv2::Entities::SendActionUsage)
DEFINE_USAGE_METHODS(Assignment_node, SysMLv2::Entities::AssignmentActionUsage)
DEFINE_USAGE_METHODS(If_node, SysMLv2::Entities::IfActionUsage)
DEFINE_USAGE_METHODS(While_loop_node, SysMLv2::Entities::WhileLoopActionUsage)
DEFINE_USAGE_METHODS(For_loop_node, SysMLv2::Entities::ForLoopActionUsage)

// The payload of an `accept` (of a transition or of an accept node) is a parameter (a ReferenceUsage with direction in).
void SysMLv2ListenerImplementation::enterPayload_parameter(SysMLv2Parser::Payload_parameterContext* ctx) {
	auto payload = std::make_shared<SysMLv2::Entities::ReferenceUsage>();
	payload->setDirection(KerML::Entities::IN);
	ParentStack.push(payload);
	PushedByContext[ctx] = payload;
	if (!ctx) return;
	auto* feature = ctx->payload_feature();
	if (auto* identification = feature ? feature->identification() : ctx->identification()) applyIdentification(identification, payload);
	// (the payload parameter of a transition is a parameter of the transition that is not typed: the payload of its trigger is)
	for (antlr4::ParserRuleContext* c = ctx; c != nullptr; c = c->parent ? dynamic_cast<antlr4::ParserRuleContext*>(c->parent) : nullptr) {
		if (dynamic_cast<SysMLv2Parser::Trigger_actionContext*>(c) != nullptr) return;
	}
	auto* specialization = feature ? feature->payload_feature_specialization_part() : ctx->payload_feature_specialization_part();
	if (specialization) applyFeatureSpecifications(specialization->feature_specialization(), payload);
	if (feature && feature->owned_feature_typing()) addTyping(payload, feature->owned_feature_typing()->getText(), feature->owned_feature_typing());
}
void SysMLv2ListenerImplementation::exitPayload_parameter(SysMLv2Parser::Payload_parameterContext*) {
	handleUsageExit<SysMLv2::Entities::ReferenceUsage>(ParentStack, Elements);
}
DEFINE_USAGE_METHODS(Exhibit_state_usage, SysMLv2::Entities::ExhibitStateUsage)
// DefaultReferenceUsage = RefPrefix Usage and ReferenceUsage = ( EndUsagePrefix | RefPrefix ) 'ref' Usage: the direction of
// the RefPrefix ('in x : T;', 'inout ref y;') belongs to the reference usage.
void SysMLv2ListenerImplementation::enterDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext* ctx) {
	handleUsageEnter<SysMLv2::Entities::ReferenceUsage>(ParentStack, &PushedByContext, ctx);
}
void SysMLv2ListenerImplementation::exitDefault_reference_usage(SysMLv2Parser::Default_reference_usageContext* ctx) {
	if (!ParentStack.empty() && ctx && ctx->ref_prefix()) {
		if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::ReferenceUsage>(ParentStack.top())) {
			applyFeatureDirectionFromContext(ctx->ref_prefix()->feature_direction(), usage);
		}
	}
	handleUsageExit<SysMLv2::Entities::ReferenceUsage>(ParentStack, Elements);
}
void SysMLv2ListenerImplementation::enterReference_usage(SysMLv2Parser::Reference_usageContext* ctx) {
	handleUsageEnter<SysMLv2::Entities::ReferenceUsage>(ParentStack, &PushedByContext, ctx);
}
void SysMLv2ListenerImplementation::exitReference_usage(SysMLv2Parser::Reference_usageContext* ctx) {
	if (!ParentStack.empty() && ctx && ctx->ref_prefix()) {
		if (auto usage = std::dynamic_pointer_cast<SysMLv2::Entities::ReferenceUsage>(ParentStack.top())) {
			applyFeatureDirectionFromContext(ctx->ref_prefix()->feature_direction(), usage);
		}
	}
	handleUsageExit<SysMLv2::Entities::ReferenceUsage>(ParentStack, Elements);
}
DEFINE_USAGE_METHODS(Variant_reference, SysMLv2::Entities::ReferenceUsage)
DEFINE_USAGE_METHODS(Assert_constriant_usage, SysMLv2::Entities::AssertConstraintUsage)
DEFINE_USAGE_METHODS(Satisfy_requirement_usage, SysMLv2::Entities::SatisfyRequirementUsage)
DEFINE_USAGE_METHODS(Use_case_usage, SysMLv2::Entities::UseCaseUsage)
DEFINE_USAGE_METHODS(Include_use_case_usage, SysMLv2::Entities::IncludeUseCaseUsage)
DEFINE_USAGE_METHODS(Flow_usage, SysMLv2::Entities::FlowUsage)
DEFINE_USAGE_METHODS(Succession_flow_usage, SysMLv2::Entities::SuccessionFlowUsage)
DEFINE_USAGE_METHODS(Message, SysMLv2::Entities::FlowUsage)

// Fix (review defect B): the 14 handlers below previously had EMPTY enter/exit bodies.
// Because exitUsage_declaration applies identification to ParentStack.top(), an empty
// handler for the enclosing construct let a nested declaration's name overwrite the
// enclosing element instead (see repro snippets in TestSysMLParser.cpp). Wiring each
// through DEFINE_USAGE_METHODS gives it the same push/identify/pop/attach behavior as
// every other *_usage rule, using the closest existing metaclass. Each element is
// attached as an owned element/feature of its parent, like all the other usages handled
// by this same macro (Concern_usage, Case_usage, Requirement_usage, ...) - i.e. the
// simple fallback the review explicitly allowed. Dedicated Membership wrapper classes
// (ActorMembership, StakeholderMembership, ObjectiveMembership,
// RequirementConstraintMembership, FramedConcernMembership, StateSubactionMembership,
// ViewRenderingMembership) exist in sysml/{requirements,states,views} but are NOT wired
// in here; using them would require extra kind-setting/attach logic beyond a single macro
// line and is left open, consistent with how the pre-existing sibling usages above (e.g.
// Concern_usage, Requirement_usage) also do not use their dedicated Membership classes.
DEFINE_USAGE_METHODS(Actor_usage, SysMLv2::Entities::PartUsage)
DEFINE_USAGE_METHODS(Stakeholder_usage, SysMLv2::Entities::PartUsage)
DEFINE_USAGE_METHODS(Objective_requirement_usage, SysMLv2::Entities::RequirementUsage)
DEFINE_USAGE_METHODS(Requirement_constraint_usage, SysMLv2::Entities::ConstraintUsage)
DEFINE_USAGE_METHODS(Framed_concern_usage, SysMLv2::Entities::ConcernUsage)
DEFINE_USAGE_METHODS(Empty_action_usage, SysMLv2::Entities::ActionUsage)
// State_perform_action_uage is not in the review's explicit list of 15, but is the actual
// rule matched by the review's own "entry action e;" repro (entry_action_member ->
// state_action_usage -> state_perform_action_uage -> perform_action_usage_declaration),
// and it had the identical empty-handler bug, so it is fixed here too for correctness.
DEFINE_USAGE_METHODS(State_perform_action_uage, SysMLv2::Entities::PerformActionUsage)
DEFINE_USAGE_METHODS(State_accept_action_usage, SysMLv2::Entities::AcceptActionUsage)
DEFINE_USAGE_METHODS(State_send_action_usage, SysMLv2::Entities::SendActionUsage)
DEFINE_USAGE_METHODS(State_assignment_action_usage, SysMLv2::Entities::AssignmentActionUsage)
DEFINE_USAGE_METHODS(Transition_usage, SysMLv2::Entities::TransitionUsage)
DEFINE_USAGE_METHODS(Target_transition_usage, SysMLv2::Entities::TransitionUsage)
DEFINE_USAGE_METHODS(View_rendering_usage, SysMLv2::Entities::RenderingUsage)
DEFINE_USAGE_METHODS(Metadata_body_usage, SysMLv2::Entities::ReferenceUsage)

void SysMLv2ListenerImplementation::enterRedefinition_usage_element(SysMLv2Parser::Redefinition_usage_elementContext* ctx) {
	std::shared_ptr<KerML::Entities::Feature> feature;
	if (ctx && ctx->KEYWORD_ATTRIBUTE()) {
		feature = std::make_shared<SysMLv2::Entities::AttributeUsage>();
	} else if (ctx && ctx->KEYWORD_PART()) {
		feature = std::make_shared<SysMLv2::Entities::PartUsage>();
	} else if (ctx && ctx->KEYWORD_ITEM()) {
		feature = std::make_shared<SysMLv2::Entities::ItemUsage>();
	} else if (ctx && ctx->KEYWORD_PORT()) {
		feature = std::make_shared<SysMLv2::Entities::PortUsage>();
	} else if (ctx && ctx->KEYWORD_ACTION()) {
		feature = std::make_shared<SysMLv2::Entities::ActionUsage>();
	} else if (ctx && ctx->KEYWORD_CALC()) {
		feature = std::make_shared<SysMLv2::Entities::CalculationUsage>();
	} else if (ctx && ctx->KEYWORD_CONSTRAINT()) {
		feature = std::make_shared<SysMLv2::Entities::ConstraintUsage>();
	} else {
		// A usage without a kind keyword is a reference usage.
		feature = std::make_shared<SysMLv2::Entities::ReferenceUsage>();
	}
	if (ctx && ctx->usage_prefix()) {
		applyUsagePrefix(ctx->usage_prefix(), feature);
	}
	ParentStack.push(feature);
	recordPush(ctx, feature);
}

void SysMLv2ListenerImplementation::exitRedefinition_usage_element(SysMLv2Parser::Redefinition_usage_elementContext*) {
	handleUsageExit<KerML::Entities::Feature>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterRedefinition_usage(SysMLv2Parser::Redefinition_usageContext*) {}

void SysMLv2ListenerImplementation::exitRedefinition_usage(SysMLv2Parser::Redefinition_usageContext* ctx) {
	if (ParentStack.empty()) return;
	auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!feature) return;

	if (ctx) {
		if (!ctx->qualified_name().empty()) {
			std::string fullName = ctx->qualified_name(0)->getText();
			std::string shortName = fullName;
			size_t lastColon = shortName.rfind("::");
			if (lastColon != std::string::npos) {
				shortName = shortName.substr(lastColon + 2);
			}
			feature->setDeclaredName(shortName);
		}
		for (auto qNameCtx : ctx->qualified_name()) {
			addRedefinition(feature, qNameCtx->getText(), qNameCtx);
		}
		if (ctx->feature_specialization_part()) {
			applyFeatureSpecializationPart(ctx->feature_specialization_part(), feature);
		}
	}
}

void SysMLv2ListenerImplementation::enterIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) {
	auto u = std::make_shared<SysMLv2::Entities::OccurrenceUsage>();
	u->setIsIndividual(true);
	ParentStack.push(u);
	recordPush(ctx, u);
}
void SysMLv2ListenerImplementation::exitIndividual_usage(SysMLv2Parser::Individual_usageContext* ctx) {
	if (!ParentStack.empty() && ctx) {
		if (auto occUsage = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceUsage>(ParentStack.top())) {
			if (ctx->basic_usage_prefix() && ctx->basic_usage_prefix()->ref_prefix()) {
				applyFeatureDirectionFromContext(ctx->basic_usage_prefix()->ref_prefix()->feature_direction(), occUsage);
			}
			applyPortionKind(ctx->portion_kind(), occUsage);
		}
	}
	handleUsageExit<SysMLv2::Entities::OccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) {
	auto u = std::make_shared<SysMLv2::Entities::OccurrenceUsage>();
	ParentStack.push(u);
	recordPush(ctx, u);
}
void SysMLv2ListenerImplementation::exitPortion_usage(SysMLv2Parser::Portion_usageContext* ctx) {
	if (!ParentStack.empty() && ctx) {
		if (auto occUsage = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceUsage>(ParentStack.top())) {
			if (ctx->basic_usage_prefix() && ctx->basic_usage_prefix()->ref_prefix()) {
				applyFeatureDirectionFromContext(ctx->basic_usage_prefix()->ref_prefix()->feature_direction(), occUsage);
			}
			if (ctx->KEYWORD_INDIVIDUAL() != nullptr) {
				occUsage->setIsIndividual(true);
			}
			applyPortionKind(ctx->portion_kind(), occUsage);
		}
	}
	handleUsageExit<SysMLv2::Entities::OccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext* ctx) {
	auto u = std::make_shared<SysMLv2::Entities::EventOccurrenceUsage>();
	ParentStack.push(u);
	recordPush(ctx, u);
}
void SysMLv2ListenerImplementation::exitEvent_occurrence_usage(SysMLv2Parser::Event_occurrence_usageContext*) {
	handleUsageExit<SysMLv2::Entities::EventOccurrenceUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnection_usage(SysMLv2Parser::Connection_usageContext* ctx) {
	auto conn = std::make_shared<SysMLv2::Entities::ConnectionUsage>();
	ParentStack.push(conn);
	recordPush(ctx, conn);
}
void SysMLv2ListenerImplementation::exitConnection_usage(SysMLv2Parser::Connection_usageContext*) {
	handleUsageExit<SysMLv2::Entities::ConnectionUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnecotr_end(SysMLv2Parser::Connecotr_endContext* ctx) {
	auto endFeature = std::make_shared<KerML::Entities::Feature>();
	endFeature->setIsEnd(true);
	ParentStack.push(endFeature);
	recordPush(ctx, endFeature);
}

void SysMLv2ListenerImplementation::exitConnecotr_end(SysMLv2Parser::Connecotr_endContext* ctx) {
	if (ParentStack.empty()) return;
	auto endFeature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!endFeature) return;
	ParentStack.pop();

	if (ctx && ctx->owned_reference_subsetting() && ctx->owned_reference_subsetting()->general_type()) {
		addReferenceSubsetting(endFeature, ctx->owned_reference_subsetting()->general_type()->getText(), ctx->owned_reference_subsetting());
	}

	Elements.push_back(endFeature);
	if (!ParentStack.empty()) {
		ParentStack.top()->appendOwnedElement(endFeature);
		if (auto conn = std::dynamic_pointer_cast<KerML::Entities::Connector>(ParentStack.top())) {
			conn->appendConnectorEnd(endFeature);
			conn->appendOwnedFeature(endFeature);
		}
	}
}

void SysMLv2ListenerImplementation::enterPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext*) {}
void SysMLv2ListenerImplementation::exitPerform_action_usage_declaration(SysMLv2Parser::Perform_action_usage_declarationContext*) {}

void SysMLv2ListenerImplementation::enterBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext* ctx) {
	auto bc = std::make_shared<SysMLv2::Entities::BindingConnectorAsUsage>();
	ParentStack.push(bc);
	recordPush(ctx, bc);
}
void SysMLv2ListenerImplementation::exitBinding_connector_as_usage(SysMLv2Parser::Binding_connector_as_usageContext*) {
	handleUsageExit<SysMLv2::Entities::BindingConnectorAsUsage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext* ctx) {
	auto sc = std::make_shared<SysMLv2::Entities::SuccessionAsUsage>();
	ParentStack.push(sc);
	recordPush(ctx, sc);
}
void SysMLv2ListenerImplementation::exitSuccession_as_usage(SysMLv2Parser::Succession_as_usageContext*) {
	handleUsageExit<SysMLv2::Entities::SuccessionAsUsage>(ParentStack, Elements);
}

// Ausdrücke und Literale
void SysMLv2ListenerImplementation::enterFeature_value(SysMLv2Parser::Feature_valueContext* ctx) {
	auto fv = std::make_shared<KerML::Entities::FeatureValue>();
	if (ctx && ctx->KEYWORD_DEFAULT()) fv->setIsDefault(true);
	ParentStack.push(fv);
	recordPush(ctx, fv);
}

void SysMLv2ListenerImplementation::exitFeature_value(SysMLv2Parser::Feature_valueContext*) {
	if (ParentStack.empty()) return;
	auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
	if (!fv) return;
	ParentStack.pop();
	Elements.push_back(fv);
	if (!ParentStack.empty()) {
		if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
			fv->setFeatureWithValue(feat);
		}
		ParentStack.top()->appendOwnedElement(fv);
	}
}

void SysMLv2ListenerImplementation::enterFeature_assignment(SysMLv2Parser::Feature_assignmentContext* ctx) {
	auto fv = std::make_shared<KerML::Entities::FeatureValue>();
	ParentStack.push(fv);
	recordPush(ctx, fv);
}

void SysMLv2ListenerImplementation::exitFeature_assignment(SysMLv2Parser::Feature_assignmentContext*) {
	if (ParentStack.empty()) return;
	auto fv = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top());
	if (!fv) return;
	ParentStack.pop();
	Elements.push_back(fv);
	if (!ParentStack.empty()) {
		if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top())) {
			fv->setFeatureWithValue(feat);
		}
		ParentStack.top()->appendOwnedElement(fv);
	}
}

void SysMLv2ListenerImplementation::enterConditionalExpr(SysMLv2Parser::ConditionalExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitConditionalExpr(SysMLv2Parser::ConditionalExprContext* ctx) {
	finishOperatorExpression("if");
}

void SysMLv2ListenerImplementation::enterBinaryExpr(SysMLv2Parser::BinaryExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitBinaryExpr(SysMLv2Parser::BinaryExprContext* ctx) {
	finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string());
}

void SysMLv2ListenerImplementation::enterUnaryExpr(SysMLv2Parser::UnaryExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitUnaryExpr(SysMLv2Parser::UnaryExprContext* ctx) {
	finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string());
}

void SysMLv2ListenerImplementation::enterClassificationExpr(SysMLv2Parser::ClassificationExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitClassificationExpr(SysMLv2Parser::ClassificationExprContext* ctx) {
	finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string("as"));
}

void SysMLv2ListenerImplementation::enterMetaclassificationExpr(SysMLv2Parser::MetaclassificationExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitMetaclassificationExpr(SysMLv2Parser::MetaclassificationExprContext* ctx) {
	finishOperatorExpression(ctx && ctx->op ? ctx->op->getText() : std::string("meta"));
}

void SysMLv2ListenerImplementation::enterExtentExpr(SysMLv2Parser::ExtentExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitExtentExpr(SysMLv2Parser::ExtentExprContext* ctx) {
	finishOperatorExpression("all");
}

void SysMLv2ListenerImplementation::enterBracketExpr(SysMLv2Parser::BracketExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitBracketExpr(SysMLv2Parser::BracketExprContext* ctx) {
	finishOperatorExpression("[");
}

void SysMLv2ListenerImplementation::enterSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitSequence_operator_expression(SysMLv2Parser::Sequence_operator_expressionContext* ctx) {
	finishOperatorExpression(",");
}

void SysMLv2ListenerImplementation::enterIndexExpr(SysMLv2Parser::IndexExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::IndexExpression>());
}

void SysMLv2ListenerImplementation::exitIndexExpr(SysMLv2Parser::IndexExprContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::IndexExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	expr->setOperatorName("#");
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterCollectExpr(SysMLv2Parser::CollectExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::CollectExpression>());
}

void SysMLv2ListenerImplementation::exitCollectExpr(SysMLv2Parser::CollectExprContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::CollectExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterSelectExpr(SysMLv2Parser::SelectExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::SelectExpression>());
}

void SysMLv2ListenerImplementation::exitSelectExpr(SysMLv2Parser::SelectExprContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::SelectExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterFeatureChainExpr(SysMLv2Parser::FeatureChainExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::FeatureChainExpression>());
}

void SysMLv2ListenerImplementation::exitFeatureChainExpr(SysMLv2Parser::FeatureChainExprContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::FeatureChainExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	expr->setOperatorName(".");
	if (ctx && ctx->feature_reference_member()) {
		const auto scope = ParentStack.empty() ? nullptr : ParentStack.top();
		const std::string left = ctx->owned_expression() ? ctx->owned_expression()->getText() : std::string();
		const std::string target = ctx->feature_reference_member()->getText();
		if (SysMLv2::Files::isPlainNameChain(left)) {
			// `a.b`: the target is a feature of the value of `a`; the feature chain a.b is resolved as a whole.
			auto placeholder = Recorder.reference<KerML::Entities::Feature>(left + "." + target, ReferenceKind::Feature, ReferenceRole::Plain,
				scope, false, nullptr, ctx->feature_reference_member(),
				[expr](const std::shared_ptr<KerML::Entities::Feature>& feature) { expr->setTargetFeature(feature); });
			placeholder->setDeclaredName(target);
			expr->setTargetFeature(placeholder);
		}
		else {
			// The left operand is a computed value: no scoped lookup is attempted for the target.
			expr->setTargetFeature(notAttemptedFeature(Recorder, target, scope, ctx->feature_reference_member()));
		}
	}
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterFunctionOperationExpr(SysMLv2Parser::FunctionOperationExprContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::OperatorExpression>());
}

void SysMLv2ListenerImplementation::exitFunctionOperationExpr(SysMLv2Parser::FunctionOperationExprContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	expr->setOperatorName("->");
	if (ctx && ctx->reference_typing()) {
		expr->setInstantiatedType(expressionTypeReference(ctx->reference_typing()->getText(), ctx->reference_typing(),
			[expr](const std::shared_ptr<KerML::Entities::Type>& target) { expr->setInstantiatedType(target); }));
	}
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterConstructor_expression(SysMLv2Parser::Constructor_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::ConstructorExpression>());
}

void SysMLv2ListenerImplementation::exitConstructor_expression(SysMLv2Parser::Constructor_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::ConstructorExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	if (ctx && ctx->owned_feature_typing() && ctx->owned_feature_typing()->general_type()) {
		expr->setInstantiatedType(expressionTypeReference(ctx->owned_feature_typing()->general_type()->getText(), ctx->owned_feature_typing(),
			[expr](const std::shared_ptr<KerML::Entities::Type>& target) { expr->setInstantiatedType(target); }));
	}
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterInvocation_expression(SysMLv2Parser::Invocation_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::InvocationExpression>());
}

void SysMLv2ListenerImplementation::exitInvocation_expression(SysMLv2Parser::Invocation_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::InvocationExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	if (ctx && ctx->internal_invocation_expression() && ctx->internal_invocation_expression()->owned_feature_typing() &&
		ctx->internal_invocation_expression()->owned_feature_typing()->general_type()) {
		expr->setInstantiatedType(expressionTypeReference(ctx->internal_invocation_expression()->owned_feature_typing()->general_type()->getText(),
			ctx->internal_invocation_expression()->owned_feature_typing(),
			[expr](const std::shared_ptr<KerML::Entities::Type>& target) { expr->setInstantiatedType(target); }));
	}
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterNull_expression(SysMLv2Parser::Null_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::NullExpression>());
}

void SysMLv2ListenerImplementation::exitNull_expression(SysMLv2Parser::Null_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::NullExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::FeatureReferenceExpression>());
}

void SysMLv2ListenerImplementation::exitFeature_reference_expression(SysMLv2Parser::Feature_reference_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::FeatureReferenceExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	if (ctx) {
		expr->setReferent(expressionFeatureReference(ctx->getText(), ctx,
			[expr](const std::shared_ptr<KerML::Entities::Feature>& target) { expr->setReferent(target); }));
	}
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::MetadataAccessExpression>());
}

void SysMLv2ListenerImplementation::exitMetadata_access_expression(SysMLv2Parser::Metadata_access_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::MetadataAccessExpression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterBody_expression(SysMLv2Parser::Body_expressionContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::Expression>());
}

void SysMLv2ListenerImplementation::exitBody_expression(SysMLv2Parser::Body_expressionContext* ctx) {
	if (ParentStack.empty()) return;
	const auto expr = std::dynamic_pointer_cast<KerML::Entities::Expression>(ParentStack.top());
	if (!expr) return;
	ParentStack.pop();
	attachExpression(expr);
}

void SysMLv2ListenerImplementation::enterType_reference(SysMLv2Parser::Type_referenceContext*) {}

void SysMLv2ListenerImplementation::exitType_reference(SysMLv2Parser::Type_referenceContext* ctx) {
	if (!ctx || !ctx->reference_typing()) return;
	auto expression = std::make_shared<KerML::Entities::InstantiationExpression>();
	expression->setInstantiatedType(expressionTypeReference(ctx->reference_typing()->getText(), ctx->reference_typing(),
		[expression](const std::shared_ptr<KerML::Entities::Type>& target) { expression->setInstantiatedType(target); }));
	attachExpression(expression);
}

void SysMLv2ListenerImplementation::enterFunction_reference(SysMLv2Parser::Function_referenceContext*) {}

void SysMLv2ListenerImplementation::exitFunction_reference(SysMLv2Parser::Function_referenceContext* ctx) {
	if (!ctx || !ctx->reference_typing()) return;
	auto expression = std::make_shared<KerML::Entities::InstantiationExpression>();
	expression->setInstantiatedType(expressionTypeReference(ctx->reference_typing()->getText(), ctx->reference_typing(),
		[expression](const std::shared_ptr<KerML::Entities::Type>& target) { expression->setInstantiatedType(target); }));
	attachExpression(expression);
}

void SysMLv2ListenerImplementation::enterNamed_argument(SysMLv2Parser::Named_argumentContext*) {
	ParentStack.push(std::make_shared<KerML::Entities::Expression>());
}

void SysMLv2ListenerImplementation::exitNamed_argument(SysMLv2Parser::Named_argumentContext*) {
	if (ParentStack.empty()) return;
	const auto argument = std::dynamic_pointer_cast<KerML::Entities::Expression>(ParentStack.top());
	if (!argument) return;
	ParentStack.pop();
	attachExpression(argument);
}

void SysMLv2ListenerImplementation::enterParameter_redefinition(SysMLv2Parser::Parameter_redefinitionContext*) {}

void SysMLv2ListenerImplementation::exitParameter_redefinition(SysMLv2Parser::Parameter_redefinitionContext* ctx) {
	if (!ctx || !ctx->qualified_name() || ParentStack.empty()) return;
	const auto argument = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!argument) return;
	argument->setDeclaredName(ctx->qualified_name()->getText());
	// The name of a named argument is a parameter of the invoked function: not resolved yet (see notAttemptedFeature).
	const auto redefinition = std::make_shared<KerML::Entities::Redefinition>(
		notAttemptedFeature(Recorder, ctx->qualified_name()->getText(), argument, ctx->qualified_name()), argument);
	argument->appendOwnedRedefinition(redefinition);
	argument->appendOwnedElement(redefinition);
	Elements.push_back(redefinition);
}

void SysMLv2ListenerImplementation::enterSequenceExpr(SysMLv2Parser::SequenceExprContext*) {}

void SysMLv2ListenerImplementation::exitSequenceExpr(SysMLv2Parser::SequenceExprContext*) {}

void SysMLv2ListenerImplementation::enterBaseExpr(SysMLv2Parser::BaseExprContext*) {}

void SysMLv2ListenerImplementation::exitBaseExpr(SysMLv2Parser::BaseExprContext*) {}

void SysMLv2ListenerImplementation::enterFunction_operation_arguments(SysMLv2Parser::Function_operation_argumentsContext*) {}

void SysMLv2ListenerImplementation::exitFunction_operation_arguments(SysMLv2Parser::Function_operation_argumentsContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_expression(SysMLv2Parser::Literal_expressionContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_expression(SysMLv2Parser::Literal_expressionContext* ctx) {
	if (!ctx) return;
	std::shared_ptr<KerML::Entities::LiteralExpression> literal;
	if (ctx->KEYWORD_TRUE()) {
		auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
		b->setValue(true);
		literal = b;
	}
	else if (ctx->KEYWORD_FALSE()) {
		auto b = std::make_shared<KerML::Entities::LiteralBoolean>();
		b->setValue(false);
		literal = b;
	}
	else if (ctx->literal_string()) {
		auto s = std::make_shared<KerML::Entities::LiteralString>();
		std::string t = ctx->literal_string()->getText();
		if (t.size() >= 2 && t.front() == '"' && t.back() == '"') t = t.substr(1, t.size() - 2);
		s->setValue(t);
		literal = s;
	}
	else if (ctx->literal_integer()) {
		auto i = std::make_shared<KerML::Entities::LiteralInteger>();
		i->setValue(std::stoll(ctx->literal_integer()->getText()));
		literal = i;
	}
	else if (ctx->literal_real()) {
		auto r = std::make_shared<KerML::Entities::LiteralRational>();
		r->setValue(std::stod(ctx->literal_real()->getText()));
		literal = r;
	}
	else if (ctx->literal_infinity()) {
		literal = std::make_shared<KerML::Entities::LiteralInfinity>();
	}
	if (literal) attachExpression(literal);
}

void SysMLv2ListenerImplementation::enterLiteral_boolean(SysMLv2Parser::Literal_booleanContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_boolean(SysMLv2Parser::Literal_booleanContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_string(SysMLv2Parser::Literal_stringContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_string(SysMLv2Parser::Literal_stringContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_integer(SysMLv2Parser::Literal_integerContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_integer(SysMLv2Parser::Literal_integerContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_real(SysMLv2Parser::Literal_realContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_real(SysMLv2Parser::Literal_realContext*) {}

void SysMLv2ListenerImplementation::enterLiteral_infinity(SysMLv2Parser::Literal_infinityContext*) {}
void SysMLv2ListenerImplementation::exitLiteral_infinity(SysMLv2Parser::Literal_infinityContext*) {}

void SysMLv2ListenerImplementation::enterMultiplicity(SysMLv2Parser::MultiplicityContext*) {}
void SysMLv2ListenerImplementation::exitMultiplicity(SysMLv2Parser::MultiplicityContext*) {}

// KerML-Stubs & Namespaces
void SysMLv2ListenerImplementation::enterNamespace(SysMLv2Parser::NamespaceContext* ctx) {
	auto ns = std::make_shared<KerML::Entities::Namespace>();
	ParentStack.push(ns);
	recordPush(ctx, ns);
}
void SysMLv2ListenerImplementation::exitNamespace(SysMLv2Parser::NamespaceContext*) {
	if (ParentStack.empty()) return;
	auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(ParentStack.top());
	ParentStack.pop();
	if (ns) {
		Elements.push_back(ns);
		if (!ParentStack.empty()) {
			ns->setOwner(ParentStack.top());
			ParentStack.top()->appendOwnedElement(ns);
		}
	}
}

void SysMLv2ListenerImplementation::enterNamespace_import(SysMLv2Parser::Namespace_importContext* ctx) {
	auto ni = std::make_shared<KerML::Entities::NamespaceImport>();
	ParentStack.push(ni);
	recordPush(ctx, ni);
}
void SysMLv2ListenerImplementation::exitNamespace_import(SysMLv2Parser::Namespace_importContext* ctx) {
	if (ParentStack.empty()) return;
	auto ni = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(ParentStack.top());
	if (!ni) return;
	ParentStack.pop();

	// One import element per import: `import A::B;` is a MembershipImport (of the membership of B), `import A::*;` and `import A::**;` are
	// NamespaceImports. The element pushed by enterNamespace_import is the NamespaceImport; a membership import replaces it.
	std::shared_ptr<KerML::Entities::Import> import = ni;
	if (ctx && ctx->import_declaration()) {
		auto* membershipImport = ctx->import_declaration()->membership_import();
		if (!membershipImport && ctx->import_declaration()->filter_package()) {
			membershipImport = ctx->import_declaration()->filter_package()->membership_import();
		}
		std::string importedNsName = ctx->import_declaration()->getText();
		bool star = false;
		bool recursive = false;
		if (membershipImport && membershipImport->qualified_name()) {
			importedNsName = membershipImport->qualified_name()->getText();
			recursive = membershipImport->SYMBOL_DOUBLE_STAR() != nullptr;
			star = membershipImport->SYMBOL_STAR() != nullptr;
		}
		const bool isAll = ctx->KEYWORD_ALL() != nullptr;
		std::shared_ptr<KerML::Entities::Membership> importedMembership;
		if (membershipImport && membershipImport->qualified_name() && !star && !recursive) {
			auto memberImport = std::make_shared<KerML::Entities::MembershipImport>();
			importedMembership = std::make_shared<KerML::Entities::Membership>();
			importedMembership->setMemberName(importedNsName);
			memberImport->setImportedMembership(importedMembership);
			import = memberImport;
			recordPush(ctx, import);
		}
		else {
			// The model keeps the imported namespace by name until the reference is resolved (see recordImport).
			auto importedNs = std::make_shared<KerML::Entities::Namespace>(importedNsName, true);
			ni->setImportedNamespace(importedNs);
		}
		import->setIsImportAll(isAll);
		import->setIsRecursive(recursive);
		// An import without a visibility keyword is private (KerML 8.3.2.4.2).
		// SysML v2 writes the keyword in the member prefix of the member that contains the import.
		KerML::Entities::VisibilityKind visibility = KerML::Entities::PRIVATE;
		if (auto* indicator = ctx->visibility_indicator()) {
			if (indicator->KEYWORD_PUBLIC() != nullptr) visibility = KerML::Entities::PUBLIC;
			else if (indicator->KEYWORD_PROTECTED() != nullptr) visibility = KerML::Entities::PROTECTED;
		}
		else if (const auto written = explicitVisibility(ctx)) {
			visibility = *written;
		}
		import->setVisibility(visibility);
		recordImport(import, ctx, importedNsName, star, recursive, isAll, visibility, importedMembership);
	}

	Elements.push_back(import);
	if (!ParentStack.empty()) {
		ParentStack.top()->appendOwnedElement(import);
	}
}

void SysMLv2ListenerImplementation::enterType(SysMLv2Parser::TypeContext* ctx) {
	auto t = std::make_shared<KerML::Entities::Type>();
	ParentStack.push(t);
	recordPush(ctx, t);
}
void SysMLv2ListenerImplementation::exitType(SysMLv2Parser::TypeContext*) {
	if (ParentStack.empty()) return;
	auto t = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top());
	ParentStack.pop();
	if (t) {
		Elements.push_back(t);
		if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(t);
	}
}

void SysMLv2ListenerImplementation::enterSpecialization(SysMLv2Parser::SpecializationContext*) {}
void SysMLv2ListenerImplementation::exitSpecialization(SysMLv2Parser::SpecializationContext* ctx) {
	if (!ctx) return;
	const auto scope = ParentStack.empty() ? nullptr : ParentStack.top();
	auto s = std::make_shared<KerML::Entities::Specialization>();
	auto gen = Recorder.reference<KerML::Entities::Type>(ctx->general_type()->getText(), ReferenceKind::Type, ReferenceRole::Plain, scope, false,
		nullptr, ctx->general_type(), [s](const std::shared_ptr<KerML::Entities::Type>& target) { s->setGeneral(target); });
	auto spec = Recorder.reference<KerML::Entities::Type>(ctx->specific_type()->getText(), ReferenceKind::Type, ReferenceRole::Plain, scope, false,
		nullptr, ctx->specific_type(), [s](const std::shared_ptr<KerML::Entities::Type>& target) { s->setSpecific(target); });
	s->setGeneral(gen);
	s->setSpecific(spec);
	Elements.push_back(s);
	if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(s);
}

void SysMLv2ListenerImplementation::enterConjunction(SysMLv2Parser::ConjunctionContext*) {}
void SysMLv2ListenerImplementation::exitConjunction(SysMLv2Parser::ConjunctionContext*) {}
void SysMLv2ListenerImplementation::enterDisjoining(SysMLv2Parser::DisjoiningContext*) {}
void SysMLv2ListenerImplementation::exitDisjoining(SysMLv2Parser::DisjoiningContext*) {}

void SysMLv2ListenerImplementation::enterClassifier(SysMLv2Parser::ClassifierContext* ctx) {
	auto c = std::make_shared<KerML::Entities::Classifier>();
	ParentStack.push(c);
	recordPush(ctx, c);
}
void SysMLv2ListenerImplementation::exitClassifier(SysMLv2Parser::ClassifierContext*) {
	if (ParentStack.empty()) return;
	auto c = std::dynamic_pointer_cast<KerML::Entities::Classifier>(ParentStack.top());
	ParentStack.pop();
	if (c) {
		Elements.push_back(c);
		if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(c);
	}
}

void SysMLv2ListenerImplementation::enterSubclassification(SysMLv2Parser::SubclassificationContext*) {}
void SysMLv2ListenerImplementation::exitSubclassification(SysMLv2Parser::SubclassificationContext*) {}

void SysMLv2ListenerImplementation::enterFeature(SysMLv2Parser::FeatureContext* ctx) {
	auto f = std::make_shared<KerML::Entities::Feature>();
	ParentStack.push(f);
	recordPush(ctx, f);
}
void SysMLv2ListenerImplementation::exitFeature(SysMLv2Parser::FeatureContext* ctx) {
	if (ParentStack.empty()) return;
	auto f = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	ParentStack.pop();

	if (ctx->feature_prefix() != nullptr)
	{
		// FeaturePrefix = ( EndFeaturePrefix ( OwnedCrossFeatureMember )? | BasicFeaturePrefix ) PrefixMetadataMember*
		if (ctx->feature_prefix()->end_feature_prefix() != nullptr)
			f->setIsEnd(true);
		const auto basicPrefix = ctx->feature_prefix()->basic_feature_prefix();
		if (basicPrefix != nullptr && basicPrefix->feature_direction() != nullptr)
		{
			if (basicPrefix->feature_direction()->KEYWORD_IN() != nullptr)
				f->setDirection(KerML::Entities::FeatureDirectionKind::IN);
			if (basicPrefix->feature_direction()->KEYWORD_INOUT() != nullptr)
				f->setDirection(KerML::Entities::FeatureDirectionKind::IN_OUT);
			if (basicPrefix->feature_direction()->KEYWORD_OUT() != nullptr)
				f->setDirection(KerML::Entities::FeatureDirectionKind::OUT);
		}
	}

	if (ctx->feature_declaration() != nullptr)
	{
		if (ctx->feature_declaration()->feature_identification() != nullptr) {
			const auto idCtx = ctx->feature_declaration()->feature_identification();

			auto names = idCtx->NAME();

			if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() >= 2) {
				f->setDeclaredShortName(names[0]->getText());
				f->setDeclaredName(names[1]->getText());
			}
			else if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() == 1) {
				f->setDeclaredShortName(names[0]->getText());
			}
			else {
				f->setDeclaredName(names[0]->getText());
			}
		}

		if (ctx->feature_declaration()->feature_specialization_part() != nullptr && f)
		{
			applyFeatureSpecializationPart(ctx->feature_declaration()->feature_specialization_part(), f);
		}
	}

	if (f) {
		Elements.push_back(f);
		if (!ParentStack.empty()) ParentStack.top()->appendOwnedElement(f);
	}
}

void SysMLv2ListenerImplementation::enterFeature_typing(SysMLv2Parser::Feature_typingContext*) {}
void SysMLv2ListenerImplementation::exitFeature_typing(SysMLv2Parser::Feature_typingContext*) {}
void SysMLv2ListenerImplementation::enterSubsetting(SysMLv2Parser::SubsettingContext*) {}
void SysMLv2ListenerImplementation::exitSubsetting(SysMLv2Parser::SubsettingContext*) {}
void SysMLv2ListenerImplementation::enterRedefinition(SysMLv2Parser::RedefinitionContext* ctx) {
	// `:>> x = v;` in the body of a definition or usage is a reference usage (DefaultReferenceUsage).
	auto feature = std::make_shared<SysMLv2::Entities::ReferenceUsage>();
	ParentStack.push(feature);
	recordPush(ctx, feature);
}

void SysMLv2ListenerImplementation::exitRedefinition(SysMLv2Parser::RedefinitionContext* ctx) {
	if (ParentStack.empty()) return;
	auto feature = std::dynamic_pointer_cast<KerML::Entities::Feature>(ParentStack.top());
	if (!feature) return;
	ParentStack.pop();

	if (ctx && ctx->qualified_name()) {
		std::string redefName = ctx->qualified_name()->getText();
		std::string shortName = redefName;
		size_t lastColon = shortName.rfind("::");
		if (lastColon != std::string::npos) {
			shortName = shortName.substr(lastColon + 2);
		}
		feature->setDeclaredName(shortName);
		addRedefinition(feature, redefName, ctx->qualified_name());
	}
	// `:>> x : T :> y;` (the typing and the subsetting of the redefining feature)
	if (ctx && ctx->typed_by() && ctx->typed_by()->owned_feature_typing()) {
		auto* typingCtx = ctx->typed_by()->owned_feature_typing();
		addTyping(feature, typingCtx->getText(), typingCtx);
	}
	if (ctx && ctx->subsets() && ctx->subsets()->owned_subsetting()) {
		auto* subsetCtx = ctx->subsets()->owned_subsetting();
		addSubsetting(feature, subsetCtx->getText(), subsetCtx);
	}

	Elements.push_back(feature);
	if (!ParentStack.empty()) {
		feature->setOwner(ParentStack.top());
		ParentStack.top()->appendOwnedElement(feature);
		if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
			type->appendOwnedFeature(feature);
			feature->setOwningType(type);
		}
	}
}
void SysMLv2ListenerImplementation::enterFeature_inverting(SysMLv2Parser::Feature_invertingContext*) {}
void SysMLv2ListenerImplementation::exitFeature_inverting(SysMLv2Parser::Feature_invertingContext*) {}
void SysMLv2ListenerImplementation::enterType_featuring(SysMLv2Parser::Type_featuringContext*) {}
void SysMLv2ListenerImplementation::exitType_featuring(SysMLv2Parser::Type_featuringContext*) {}

void SysMLv2ListenerImplementation::enterData_type(SysMLv2Parser::Data_typeContext* ctx) {
	auto dt = std::make_shared<KerML::Entities::DataType>();
	ParentStack.push(dt);
	recordPush(ctx, dt);
}
void SysMLv2ListenerImplementation::exitData_type(SysMLv2Parser::Data_typeContext*) {
	handleUsageExit<KerML::Entities::DataType>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterClass(SysMLv2Parser::ClassContext* ctx) {
	auto cl = std::make_shared<KerML::Entities::Class>();
	ParentStack.push(cl);
	recordPush(ctx, cl);
}
void SysMLv2ListenerImplementation::exitClass(SysMLv2Parser::ClassContext*) {
	handleUsageExit<KerML::Entities::Class>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterStructure(SysMLv2Parser::StructureContext* ctx) {
	auto st = std::make_shared<KerML::Entities::Structure>();
	ParentStack.push(st);
	recordPush(ctx, st);
}
void SysMLv2ListenerImplementation::exitStructure(SysMLv2Parser::StructureContext*) {
	handleUsageExit<KerML::Entities::Structure>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterAssociation(SysMLv2Parser::AssociationContext* ctx) {
	auto a = std::make_shared<KerML::Entities::Association>();
	ParentStack.push(a);
	recordPush(ctx, a);
}
void SysMLv2ListenerImplementation::exitAssociation(SysMLv2Parser::AssociationContext*) {
	handleUsageExit<KerML::Entities::Association>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterAssociation_structure(SysMLv2Parser::Association_structureContext* ctx) {
	auto as = std::make_shared<KerML::Entities::AssociationStructure>();
	ParentStack.push(as);
	recordPush(ctx, as);
}
void SysMLv2ListenerImplementation::exitAssociation_structure(SysMLv2Parser::Association_structureContext*) {
	handleUsageExit<KerML::Entities::AssociationStructure>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterConnector(SysMLv2Parser::ConnectorContext* ctx) {
	auto c = std::make_shared<KerML::Entities::Connector>();
	ParentStack.push(c);
	recordPush(ctx, c);
}
void SysMLv2ListenerImplementation::exitConnector(SysMLv2Parser::ConnectorContext*) {
	handleUsageExit<KerML::Entities::Connector>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBinding_connector(SysMLv2Parser::Binding_connectorContext* ctx) {
	auto bc = std::make_shared<KerML::Entities::BindingConnector>();
	ParentStack.push(bc);
	recordPush(ctx, bc);
}
void SysMLv2ListenerImplementation::exitBinding_connector(SysMLv2Parser::Binding_connectorContext*) {
	handleUsageExit<KerML::Entities::BindingConnector>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterSuccession(SysMLv2Parser::SuccessionContext* ctx) {
	auto s = std::make_shared<KerML::Entities::Succession>();
	ParentStack.push(s);
	recordPush(ctx, s);
}
void SysMLv2ListenerImplementation::exitSuccession(SysMLv2Parser::SuccessionContext*) {
	handleUsageExit<KerML::Entities::Succession>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBehavior(SysMLv2Parser::BehaviorContext* ctx) {
	auto b = std::make_shared<KerML::Entities::Behavior>();
	ParentStack.push(b);
	recordPush(ctx, b);
}
void SysMLv2ListenerImplementation::exitBehavior(SysMLv2Parser::BehaviorContext*) {
	handleUsageExit<KerML::Entities::Behavior>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterStep(SysMLv2Parser::StepContext* ctx) {
	auto s = std::make_shared<KerML::Entities::Step>();
	ParentStack.push(s);
	recordPush(ctx, s);
}
void SysMLv2ListenerImplementation::exitStep(SysMLv2Parser::StepContext*) {
	handleUsageExit<KerML::Entities::Step>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterFunction(SysMLv2Parser::FunctionContext* ctx) {
	auto f = std::make_shared<KerML::Entities::Function>();
	ParentStack.push(f);
	recordPush(ctx, f);
}
void SysMLv2ListenerImplementation::exitFunction(SysMLv2Parser::FunctionContext* ctx) {
	if (ParentStack.empty()) return;
	auto usage = std::dynamic_pointer_cast<KerML::Entities::Function>(ParentStack.top());
	if (!usage) return;
	ParentStack.pop();
	applyIdentification(ctx->classifier_declaration()->identification(), usage);


	Elements.push_back(usage);

	if (!ParentStack.empty()) {
		usage->setOwner(ParentStack.top());
		ParentStack.top()->appendOwnedElement(usage);
		if (auto type = std::dynamic_pointer_cast<KerML::Entities::Type>(ParentStack.top())) {
			if (auto feat = std::dynamic_pointer_cast<KerML::Entities::Feature>(usage)) {
				type->appendOwnedFeature(feat);
				feat->setOwningType(type);
			}
		}
	}

}

void SysMLv2ListenerImplementation::enterPredicate(SysMLv2Parser::PredicateContext* ctx) {
	auto p = std::make_shared<KerML::Entities::Predicate>();
	ParentStack.push(p);
	recordPush(ctx, p);
}
void SysMLv2ListenerImplementation::exitPredicate(SysMLv2Parser::PredicateContext* ctx) {
	if (!ParentStack.empty() && ctx && ctx->classifier_declaration() && ctx->classifier_declaration()->identification()) {
		if (auto predicate = std::dynamic_pointer_cast<KerML::Entities::Predicate>(ParentStack.top())) {
			applyIdentification(ctx->classifier_declaration()->identification(), predicate);
		}
	}
	handleUsageExit<KerML::Entities::Predicate>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterBoolean_expression(SysMLv2Parser::Boolean_expressionContext* ctx) {
	auto be = std::make_shared<KerML::Entities::BooleanExpression>();
	ParentStack.push(be);
	recordPush(ctx, be);
}
void SysMLv2ListenerImplementation::exitBoolean_expression(SysMLv2Parser::Boolean_expressionContext*) {
	handleUsageExit<KerML::Entities::BooleanExpression>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterInvariant(SysMLv2Parser::InvariantContext* ctx) {
	auto inv = std::make_shared<KerML::Entities::Invariant>();
	ParentStack.push(inv);
	recordPush(ctx, inv);
}
void SysMLv2ListenerImplementation::exitInvariant(SysMLv2Parser::InvariantContext*) {
	handleUsageExit<KerML::Entities::Invariant>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterInteraction(SysMLv2Parser::InteractionContext*) {}
void SysMLv2ListenerImplementation::exitInteraction(SysMLv2Parser::InteractionContext*) {}
void SysMLv2ListenerImplementation::enterItem_flow(SysMLv2Parser::Item_flowContext*) {}
void SysMLv2ListenerImplementation::exitItem_flow(SysMLv2Parser::Item_flowContext*) {}
void SysMLv2ListenerImplementation::enterSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext*) {}
void SysMLv2ListenerImplementation::exitSuccession_item_flow(SysMLv2Parser::Succession_item_flowContext*) {}

void SysMLv2ListenerImplementation::enterMetaclass(SysMLv2Parser::MetaclassContext* ctx) {
	auto mc = std::make_shared<KerML::Entities::Metaclass>();
	ParentStack.push(mc);
	recordPush(ctx, mc);
}
void SysMLv2ListenerImplementation::exitMetaclass(SysMLv2Parser::MetaclassContext*) {
	handleUsageExit<KerML::Entities::Metaclass>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterMetadata_feature(SysMLv2Parser::Metadata_featureContext* ctx) {
	auto mf = std::make_shared<KerML::Entities::MetadataFeature>();
	ParentStack.push(mf);
	recordPush(ctx, mf);
}
void SysMLv2ListenerImplementation::exitMetadata_feature(SysMLv2Parser::Metadata_featureContext*) {
	handleUsageExit<KerML::Entities::MetadataFeature>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterLibrary_package(SysMLv2Parser::Library_packageContext* ctx) {
	auto lp = std::make_shared<KerML::Entities::LibraryPackage>();
	if (ctx && ctx->KEYWORD_STANDARD()) lp->setIsStandard(true);
	ParentStack.push(lp);
	recordPush(ctx, lp);
}
void SysMLv2ListenerImplementation::exitLibrary_package(SysMLv2Parser::Library_packageContext*) {
	handleUsageExit<KerML::Entities::LibraryPackage>(ParentStack, Elements);
}

void SysMLv2ListenerImplementation::enterMeta_assignment(SysMLv2Parser::Meta_assignmentContext*) {}
void SysMLv2ListenerImplementation::exitMeta_assignment(SysMLv2Parser::Meta_assignmentContext*) {}

std::vector<std::shared_ptr<KerML::Entities::Element>> SysMLv2ListenerImplementation::getElements() const {
	return Elements;
}

// Hilfsmethoden
void SysMLv2ListenerImplementation::attachExpression(const std::shared_ptr<KerML::Entities::Expression>& expression) {
	if (!expression) return;
	Elements.push_back(expression);
	if (ParentStack.empty()) return;
	expression->setOwner(ParentStack.top());
	ParentStack.top()->appendOwnedElement(expression);
	if (auto invocation = std::dynamic_pointer_cast<KerML::Entities::InstantiationExpression>(ParentStack.top())) {
		invocation->appendArgument(expression);
	}
	if (auto value = std::dynamic_pointer_cast<KerML::Entities::FeatureValue>(ParentStack.top())) {
		value->setValue(expression);
	}
}

void SysMLv2ListenerImplementation::finishOperatorExpression(const std::string& operatorName) {
	if (ParentStack.empty()) return;
	auto expression = std::dynamic_pointer_cast<KerML::Entities::OperatorExpression>(ParentStack.top());
	if (!expression) return;
	ParentStack.pop();
	expression->setOperatorName(operatorName);
	attachExpression(expression);
}

void SysMLv2ListenerImplementation::applyIdentification(SysMLv2Parser::IdentificationContext* idCtx, const std::shared_ptr<KerML::Entities::Element>& elem) {
	if (!idCtx || !elem) return;
	auto names = idCtx->sysml_name();
	if (names.empty()) return;
	if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() >= 2) {
		elem->setDeclaredShortName(names[0]->getText());
		elem->setDeclaredName(names[1]->getText());
	}
	else if (idCtx->SYMBOL_SMALLER() != nullptr && names.size() == 1) {
		elem->setDeclaredShortName(names[0]->getText());
	}
	else {
		elem->setDeclaredName(names[0]->getText());
	}
}

// Populates a derived "...Definition" snapshot vector property (e.g. PartUsage::partDefinition)
// with the resolved type, if it is of the property's element type and not already present.
template<typename UsageT, typename ElemT>
static void appendDerivedDefinitionIfMissing(
	const std::shared_ptr<KerML::Entities::Feature>& feature,
	const std::shared_ptr<KerML::Entities::Type>& typeTarget,
	std::vector<std::shared_ptr<ElemT>> (UsageT::* getter)() const,
	void (UsageT::* appender)(std::shared_ptr<ElemT>)) {
	auto usage = std::dynamic_pointer_cast<UsageT>(feature);
	if (!usage) return;
	auto value = std::dynamic_pointer_cast<ElemT>(typeTarget);
	if (!value) return;
	auto existing = (usage.get()->*getter)();
	if (std::find(existing.begin(), existing.end(), value) == existing.end()) {
		(usage.get()->*appender)(value);
	}
}

// Populates a derived single-valued "...Definition" snapshot property (e.g. CalculationUsage::calculationDefinition)
// with the resolved type, if it is of the property's element type.
template<typename UsageT, typename ElemT>
static void setDerivedDefinition(
	const std::shared_ptr<KerML::Entities::Feature>& feature,
	const std::shared_ptr<KerML::Entities::Type>& typeTarget,
	void (UsageT::* setter)(std::shared_ptr<ElemT>)) {
	auto usage = std::dynamic_pointer_cast<UsageT>(feature);
	if (!usage) return;
	auto value = std::dynamic_pointer_cast<ElemT>(typeTarget);
	if (!value) return;
	(usage.get()->*setter)(value);
}

// ---------------------------------------------------------------------------------------------------------------------
// Name references
//
// The listener never resolves a name itself. Every reference is recorded (name, scope, kind, position) together with a patch
// that puts the resolved element into the model; a SysMLv2::Files::Workspace resolves all recorded references of all
// loaded sources over the union of their namespaces. Until a reference is resolved, the model uses a placeholder element
// (SysMLv2::Files::UnresolvedType / UnresolvedClassifier / UnresolvedFeature / UnresolvedElement), which is never part
// of the element list.
// ---------------------------------------------------------------------------------------------------------------------
std::shared_ptr<KerML::Entities::Type> SysMLv2ListenerImplementation::typeReference(const std::string& name,
	const std::shared_ptr<KerML::Entities::Element>& context, antlr4::ParserRuleContext* position,
	std::function<void(const std::shared_ptr<KerML::Entities::Type>&)> patch) {
	return Recorder.reference<KerML::Entities::Type>(name, ReferenceKind::Type, ReferenceRole::Plain, context, false, nullptr, position, std::move(patch));
}

std::shared_ptr<KerML::Entities::Feature> SysMLv2ListenerImplementation::featureReference(const std::string& name,
	const std::shared_ptr<KerML::Entities::Element>& context, antlr4::ParserRuleContext* position,
	std::function<void(const std::shared_ptr<KerML::Entities::Feature>&)> patch) {
	return Recorder.reference<KerML::Entities::Feature>(name, ReferenceKind::Feature, ReferenceRole::Plain, context, false, nullptr, position, std::move(patch));
}

// References that occur inside expressions are resolved from the scope the expression is written in: the innermost
// element on the parent stack.
std::shared_ptr<KerML::Entities::Feature> SysMLv2ListenerImplementation::expressionFeatureReference(const std::string& name,
	antlr4::ParserRuleContext* position, std::function<void(const std::shared_ptr<KerML::Entities::Feature>&)> patch) {
	return featureReference(name, ParentStack.empty() ? nullptr : ParentStack.top(), position, std::move(patch));
}

std::shared_ptr<KerML::Entities::Type> SysMLv2ListenerImplementation::expressionTypeReference(const std::string& name,
	antlr4::ParserRuleContext* position, std::function<void(const std::shared_ptr<KerML::Entities::Type>&)> patch) {
	return typeReference(name, ParentStack.empty() ? nullptr : ParentStack.top(), position, std::move(patch));
}

static void applyDerivedDefinitions(const std::shared_ptr<KerML::Entities::Feature>& feature,
	const std::shared_ptr<KerML::Entities::Type>& typeTarget) {
	// OccurrenceUsage family: occurrenceDefinition (+ individualDefinition when the
	// resolved OccurrenceDefinition is itself individual).
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::OccurrenceUsage, KerML::Entities::Class>(
		feature, typeTarget,
		&SysMLv2::Entities::OccurrenceUsage::occurrenceDefinition,
		&SysMLv2::Entities::OccurrenceUsage::appendOccurrenceDefinition);
	if (auto occUsage = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceUsage>(feature)) {
		if (auto occDef = std::dynamic_pointer_cast<SysMLv2::Entities::OccurrenceDefinition>(typeTarget)) {
			if (occDef->isIndividual()) {
				occUsage->setIndividualDefinition(occDef);
			}
		}
	}
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::ItemUsage, KerML::Entities::Structure>(
		feature, typeTarget,
		&SysMLv2::Entities::ItemUsage::itemDefinition,
		&SysMLv2::Entities::ItemUsage::appendItemDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::PartUsage, SysMLv2::Entities::PartDefinition>(
		feature, typeTarget,
		&SysMLv2::Entities::PartUsage::partDefinition,
		&SysMLv2::Entities::PartUsage::appendPartDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::PortUsage, SysMLv2::Entities::PortDefinition>(
		feature, typeTarget,
		&SysMLv2::Entities::PortUsage::portDefinition,
		&SysMLv2::Entities::PortUsage::appendPortDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::AttributeUsage, KerML::Entities::DataType>(
		feature, typeTarget,
		&SysMLv2::Entities::AttributeUsage::attributeDefinition,
		&SysMLv2::Entities::AttributeUsage::appendAttributeDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::ActionUsage, KerML::Entities::Behavior>(
		feature, typeTarget,
		&SysMLv2::Entities::ActionUsage::actionDefinition,
		&SysMLv2::Entities::ActionUsage::appendActionDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::StateUsage, KerML::Entities::Behavior>(
		feature, typeTarget,
		&SysMLv2::Entities::StateUsage::stateDefinition,
		&SysMLv2::Entities::StateUsage::appendStateDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::ConnectionUsage, KerML::Entities::AssociationStructure>(
		feature, typeTarget,
		&SysMLv2::Entities::ConnectionUsage::connectionDefinition,
		&SysMLv2::Entities::ConnectionUsage::appendConnectionDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::InterfaceUsage, SysMLv2::Entities::InterfaceDefinition>(
		feature, typeTarget,
		&SysMLv2::Entities::InterfaceUsage::interfaceDefinition,
		&SysMLv2::Entities::InterfaceUsage::appendInterfaceDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::AllocationUsage, SysMLv2::Entities::AllocationDefinition>(
		feature, typeTarget,
		&SysMLv2::Entities::AllocationUsage::allocationDefinition,
		&SysMLv2::Entities::AllocationUsage::appendAllocationDefinition);
	appendDerivedDefinitionIfMissing<SysMLv2::Entities::FlowUsage, KerML::Entities::Interaction>(
		feature, typeTarget,
		&SysMLv2::Entities::FlowUsage::flowDefinition,
		&SysMLv2::Entities::FlowUsage::appendFlowDefinition);

	setDerivedDefinition<SysMLv2::Entities::CalculationUsage, KerML::Entities::Function>(
		feature, typeTarget, &SysMLv2::Entities::CalculationUsage::setCalculationDefinition);
	setDerivedDefinition<SysMLv2::Entities::ConstraintUsage, KerML::Entities::Predicate>(
		feature, typeTarget, &SysMLv2::Entities::ConstraintUsage::setConstraintDefinition);
	setDerivedDefinition<SysMLv2::Entities::EnumerationUsage, SysMLv2::Entities::EnumerationDefinition>(
		feature, typeTarget, &SysMLv2::Entities::EnumerationUsage::setEnumerationDefinition);
	setDerivedDefinition<SysMLv2::Entities::MetadataUsage, KerML::Entities::Metaclass>(
		feature, typeTarget, &SysMLv2::Entities::MetadataUsage::setMetadataDefinition);
	setDerivedDefinition<SysMLv2::Entities::RequirementUsage, SysMLv2::Entities::RequirementDefinition>(
		feature, typeTarget, &SysMLv2::Entities::RequirementUsage::setRequirementDefinition);
	setDerivedDefinition<SysMLv2::Entities::ConcernUsage, SysMLv2::Entities::ConcernDefinition>(
		feature, typeTarget, &SysMLv2::Entities::ConcernUsage::setConcernDefinition);
	setDerivedDefinition<SysMLv2::Entities::CaseUsage, SysMLv2::Entities::CaseDefinition>(
		feature, typeTarget, &SysMLv2::Entities::CaseUsage::setCaseDefinition);
	setDerivedDefinition<SysMLv2::Entities::AnalysisCaseUsage, SysMLv2::Entities::AnalysisCaseDefinition>(
		feature, typeTarget, &SysMLv2::Entities::AnalysisCaseUsage::setAnalysisCaseDefinition);
	setDerivedDefinition<SysMLv2::Entities::VerificationCaseUsage, SysMLv2::Entities::VerificationCaseDefinition>(
		feature, typeTarget, &SysMLv2::Entities::VerificationCaseUsage::setVerificationCaseDefinition);
	setDerivedDefinition<SysMLv2::Entities::UseCaseUsage, SysMLv2::Entities::UseCaseDefinition>(
		feature, typeTarget, &SysMLv2::Entities::UseCaseUsage::setUseCaseDefinition);
	setDerivedDefinition<SysMLv2::Entities::ViewUsage, SysMLv2::Entities::ViewDefinition>(
		feature, typeTarget, &SysMLv2::Entities::ViewUsage::setViewDefinition);
	setDerivedDefinition<SysMLv2::Entities::ViewpointUsage, SysMLv2::Entities::ViewpointDefinition>(
		feature, typeTarget, &SysMLv2::Entities::ViewpointUsage::setViewpointDefinition);
	setDerivedDefinition<SysMLv2::Entities::RenderingUsage, SysMLv2::Entities::RenderingDefinition>(
		feature, typeTarget, &SysMLv2::Entities::RenderingUsage::setRenderingDefinition);
}

void SysMLv2ListenerImplementation::addTyping(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::string& typeName,
	antlr4::ParserRuleContext* position) {
	if (!feature) return;
	auto placeholder = newPlaceholder<KerML::Entities::Type>(ReferenceKind::Type, typeName);
	auto typing = std::make_shared<KerML::Entities::FeatureTyping>(placeholder, feature);
	feature->appendType(placeholder);
	feature->appendOwnedTyping(typing);
	feature->appendOwnedElement(typing);
	Elements.push_back(typing);
	Recorder.record(placeholder, typeName, ReferenceKind::Type, ReferenceRole::Generalization, feature, true, feature, position,
		[feature, typing, placeholder](const ElementPtr& element) {
			auto target = std::dynamic_pointer_cast<KerML::Entities::Type>(element);
			if (!target) return;
			SysMLv2::Files::Retarget::featureTyping(*typing, target);
			auto types = feature->type();
			SysMLv2::Files::replaceInVector(types, placeholder, target);
			feature->setType(types);
			applyDerivedDefinitions(feature, target);
		});
}

void SysMLv2ListenerImplementation::addSubclassification(const std::shared_ptr<KerML::Entities::Classifier>& classifier,
	const std::string& superName, antlr4::ParserRuleContext* position) {
	if (!classifier) return;
	auto placeholder = newPlaceholder<KerML::Entities::Classifier>(ReferenceKind::Classifier, superName);
	auto sub = std::make_shared<KerML::Entities::Subclassification>(placeholder, classifier);
	classifier->appendOwnedSubclassification(sub);
	classifier->appendOwnedSpecialization(sub);
	classifier->appendOwnedElement(sub);
	Elements.push_back(sub);
	Recorder.record(placeholder, superName, ReferenceKind::Classifier, ReferenceRole::Generalization, classifier, true, classifier, position,
		[sub](const ElementPtr& element) {
			if (auto target = std::dynamic_pointer_cast<KerML::Entities::Classifier>(element)) {
				SysMLv2::Files::Retarget::subclassification(*sub, target);
			}
		});
}

void SysMLv2ListenerImplementation::addSubsetting(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::string& name,
	antlr4::ParserRuleContext* position) {
	if (!feature) return;
	auto placeholder = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, name);
	auto subsetting = std::make_shared<KerML::Entities::Subsetting>(placeholder, feature);
	feature->appendOwnedSubsetting(subsetting);
	feature->appendOwnedSpecialization(subsetting);
	feature->appendOwnedElement(subsetting);
	Elements.push_back(subsetting);
	Recorder.record(placeholder, name, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, position,
		[subsetting](const ElementPtr& element) {
			if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) {
				SysMLv2::Files::Retarget::subsetting(*subsetting, target);
			}
		});
}

void SysMLv2ListenerImplementation::addRedefinition(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::string& name,
	antlr4::ParserRuleContext* position) {
	if (!feature) return;
	auto placeholder = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, name);
	auto redef = std::make_shared<KerML::Entities::Redefinition>(placeholder, feature);
	redef->setOwner(feature);
	feature->appendOwnedRedefinition(redef);
	feature->appendOwnedSubsetting(redef);
	feature->appendOwnedSpecialization(redef);
	feature->appendOwnedElement(redef);
	Elements.push_back(redef);
	Recorder.record(placeholder, name, ReferenceKind::Feature, ReferenceRole::Redefinition, feature, true, feature, position,
		[redef](const ElementPtr& element) {
			if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) {
				SysMLv2::Files::Retarget::redefinition(*redef, target);
			}
		});
}

void SysMLv2ListenerImplementation::addReferenceSubsetting(const std::shared_ptr<KerML::Entities::Feature>& feature, const std::string& name,
	antlr4::ParserRuleContext* position) {
	if (!feature) return;
	auto placeholder = newPlaceholder<KerML::Entities::Feature>(ReferenceKind::Feature, name);
	auto refSub = std::make_shared<KerML::Entities::ReferenceSubsetting>(placeholder, feature);
	feature->setOwnedReferenceSubsetting(refSub);
	feature->appendOwnedElement(refSub);
	Elements.push_back(refSub);
	Recorder.record(placeholder, name, ReferenceKind::Feature, ReferenceRole::Generalization, feature, true, feature, position,
		[refSub](const ElementPtr& element) {
			if (auto target = std::dynamic_pointer_cast<KerML::Entities::Feature>(element)) {
				SysMLv2::Files::Retarget::referenceSubsetting(*refSub, target);
			}
		});
}

// `import` declarations: `import A::B;` imports the membership of B, `import A::*;` the visible members of A and `import A::**;`
// additionally those of all (visible) owned namespaces, recursively. `import all` ignores the declared visibility of the members.
// A filter package `import A::*[expr]` is imported like `import A::*` (the filter is not evaluated).
void SysMLv2ListenerImplementation::recordImport(const std::shared_ptr<KerML::Entities::Element>& importElement,
	antlr4::ParserRuleContext* importCtx, const std::string& target, bool star, bool recursive, bool importAll,
	KerML::Entities::VisibilityKind visibility, const std::shared_ptr<KerML::Entities::Membership>& importedMembership) {
	auto record = std::make_shared<SysMLv2::Files::ImportRecord>();
	record->owner = ParentStack.empty() ? nullptr : ParentStack.top();
	record->element = importElement;
	record->isImportAll = importAll;
	record->visibility = visibility;
	record->target = target;
	record->isRecursive = recursive;
	record->isMembershipImport = !star && !recursive;
	if (importCtx != nullptr && importCtx->getStart() != nullptr) {
		record->line = static_cast<int>(importCtx->getStart()->getLine());
		record->column = static_cast<int>(importCtx->getStart()->getCharPositionInLine());
	}
	Recorder.data.imports.push_back(record);

	const auto kind = record->isMembershipImport ? ReferenceKind::Element : ReferenceKind::Namespace;
	Recorder.record(newPlaceholder<KerML::Entities::Element>(ReferenceKind::Element, target), target, kind, ReferenceRole::Import,
		record->owner, false, nullptr, importCtx, [record, importedMembership](const ElementPtr& element) {
			record->resolvedTarget = element;
			if (importedMembership) importedMembership->setMemberElement(element);
			if (auto namespaceImport = std::dynamic_pointer_cast<KerML::Entities::NamespaceImport>(record->element)) {
				if (auto ns = std::dynamic_pointer_cast<KerML::Entities::Namespace>(element)) namespaceImport->setImportedNamespace(ns);
			}
		});
}

// The declared visibility of the member declared by `ctx`: the visibility_indicator of the member_prefix that precedes it in the
// enclosing *_member rule (public if there is none). Starting at the context that declares the element, climb while the context
// is the first child of its parent (after keywords); the first parent that has a member_prefix child decides.
KerML::Entities::VisibilityKind SysMLv2ListenerImplementation::declaredVisibility(antlr4::ParserRuleContext* ctx) const {
	return explicitVisibility(ctx).value_or(KerML::Entities::PUBLIC);
}

std::optional<KerML::Entities::VisibilityKind> SysMLv2ListenerImplementation::explicitVisibility(antlr4::ParserRuleContext* ctx) const {
	auto visibilityOf = [](SysMLv2Parser::Member_prefixContext* prefix) -> std::optional<KerML::Entities::VisibilityKind> {
		if (prefix != nullptr && prefix->visibility_indicator() != nullptr) {
			auto indicator = prefix->visibility_indicator();
			if (indicator->KEYWORD_PRIVATE() != nullptr) return KerML::Entities::PRIVATE;
			if (indicator->KEYWORD_PROTECTED() != nullptr) return KerML::Entities::PROTECTED;
			if (indicator->KEYWORD_PUBLIC() != nullptr) return KerML::Entities::PUBLIC;
		}
		return std::nullopt;
	};
	for (auto* current = ctx; current != nullptr;) {
		auto* parent = current->parent ? dynamic_cast<antlr4::ParserRuleContext*>(current->parent) : nullptr;
		if (parent == nullptr) break;
		// Stop at the context of another element: the visibility above it belongs to that element.
		if (current != ctx && PushedByContext.count(current) != 0) break;
		bool first = true;
		for (auto* child : parent->children) {
			if (child == current) break;
			if (auto* prefix = dynamic_cast<SysMLv2Parser::Member_prefixContext*>(child)) return visibilityOf(prefix);
			if (dynamic_cast<antlr4::ParserRuleContext*>(child) != nullptr) first = false;
		}
		if (!first) break;
		current = parent;
	}
	return std::nullopt;
}

void SysMLv2ListenerImplementation::computeVisibilities() {
	auto note = [this](antlr4::ParserRuleContext* ctx, const std::shared_ptr<KerML::Entities::Element>& element) {
		if (!ctx || !element) return;
		const auto visibility = declaredVisibility(ctx);
		if (visibility != KerML::Entities::PUBLIC) Recorder.data.visibility[element.get()] = visibility;
	};
	for (const auto& [ctx, weak] : PushedByContext) note(ctx, weak.lock());
	for (const auto& [ctx, weak] : VisibilityContexts) note(ctx, weak.lock());
}

SysMLv2::Files::ResolutionData SysMLv2ListenerImplementation::takeResolutionData() {
	return std::move(Recorder.data);
}
