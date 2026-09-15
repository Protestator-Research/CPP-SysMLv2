#include <sysml/SysML.h>
#include <sysml/attibutes/AttributeDefinition.h>
#include <stdexcept>
#include <iostream>
#include <boost/uuid/uuid_io.hpp>

void checkInventory();
void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
int main() {
    try {
        checkInventory();
        using namespace SysMLv2::Entities;
        require(metaclasses().size() == 93, "metaclass inventory size");
        std::size_t properties = 0;
        for (const auto& descriptor : metaclasses()) {
            properties += descriptor.declaredPropertyCount;
            if (!descriptor.isAbstract)
                require(createRepresentation(descriptor.name)->metaclassName() == descriptor.name,
                        "factory must retain metaclass identity");
        }
        require(properties == 218, "property inventory size");
        for (const auto name : {"ControlNode", "NotASysMLClass"}) {
            bool rejected = false;
            try { (void)createRepresentation(name); }
            catch (const std::invalid_argument&) { rejected = true; }
            require(rejected, "factory must reject abstract and unknown types");
        }
        const auto id = boost::uuids::random_generator()();
        KerML::Entities::Classifier classifier("named", id);
        require(classifier.elementId() == boost::uuids::to_string(id), "virtual base preserves explicit identity");
        require(classifier.declaredName() == "named", "virtual base preserves name");
        auto part = std::make_shared<PartDefinition>();
        auto usage = std::make_shared<PartUsage>();
        usage->setIsVariation(true);
        require(usage->isVariation(), "variation flag");
        usage->appendType(part);
        require(usage->definition().size() == 1, "typing derivation");
        require(usage->definition().front() == part, "typing identity");
        part->appendOwnedFeature(usage);
        require(part->ownedPart().size() == 1, "owned part derivation");
        require(part->ownedPart().front() == usage, "owned part identity");
        part->setOwnedFeature({});
        require(part->ownedPart().empty(), "derived view must follow graph edits");
        usage->setOwningType(part);
        require(usage->owningDefinition() == part, "owning definition derivation");
        FlowDefinition flow;
        flow.setFlowEnd({usage});
        for (const auto& invalid : std::vector<std::vector<std::shared_ptr<Usage>>>{{usage, usage}, {nullptr}}) {
            bool rejected = false;
            try { flow.setFlowEnd(invalid); }
            catch (const std::invalid_argument&) { rejected = true; }
            require(rejected, "invalid collection entry must be rejected");
            require(flow.flowEnd().size() == 1 && flow.flowEnd().front() == usage,
                    "failed update must preserve collection");
        }
        auto connection = std::make_shared<ConnectionUsage>();
        KerML::Entities::Element* throughPart = static_cast<PartUsage*>(connection.get());
        KerML::Entities::Element* throughConnector = static_cast<ConnectorAsUsage*>(connection.get());
        require(throughPart == throughConnector, "multiple inheritance must share Element");
        ReferenceUsage reference;
        require(reference.isReference(), "reference default");
        reference.setIsComposite(true);
        require(!reference.isReference(), "reference derivation must follow composition");
        OccurrenceUsage occurrence;
        require(!occurrence.portionKind().has_value(), "optional enumeration default");
        occurrence.setPortionKind(PortionKind::snapshot);
        require(occurrence.portionKind() == PortionKind::snapshot, "optional enumeration roundtrip");
        occurrence.setPortionKind(static_cast<PortionKind>(99));
        require(!occurrence.validateRepresentation().empty(), "invalid enumeration must be diagnosed");
        MembershipExpose expose;
        require(expose.isImportAll(), "expose import default");
        require(expose.visibility() == KerML::Entities::PROTECTED, "expose visibility default");
        require(static_cast<KerML::Entities::Import&>(expose).isImportAll(), "shared import state");
        RequirementConstraintMembership membership;
        require(membership.validateRepresentation().empty(), "derived references are not required before evaluation");
        require(!membership.validateRepresentation(true).empty(), "strict snapshot validation");
        auto constraint = std::make_shared<ConstraintUsage>();
        membership.setOwnedConstraint(constraint);
        membership.setReferencedConstraint(constraint);
        require(membership.validateRepresentation(true).empty(), "complete membership snapshot");
        std::cout << "SysML representation checks passed\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
