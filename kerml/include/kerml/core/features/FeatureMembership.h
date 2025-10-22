//
// Created by Moritz Herzog on 25.03.25.
//
#pragma once

#include <kerml/root/namespaces/OwningMembership.h>

namespace KerML::Entities {
    class Feature;
    class Type;
}

namespace KerML::Entities {
    /**
     * @class FeatureMembership
     * @version 1.0 Beta 4
     * @author Moritz Herzog <herzogm@rptu.de>
     * @brief Representation of the Feature Membership according to the SysML Standard.
     */
    class FeatureMembership : public OwningMembership {
    public:
        FeatureMembership() = delete;
        FeatureMembership(std::shared_ptr<Feature> ownedMemberFeature, std::shared_ptr<Type> owningType,  std::vector<std::shared_ptr<Type>> type);
        ~FeatureMembership() override = default;


    protected:
        void setOwnedMemberFeature(std::shared_ptr<Feature> ownedMemberFeature);
        [[nodiscard]] std::shared_ptr<Feature> ownedMemberFeature() const;

        void setOwningType(std::shared_ptr<Type> owningType);
        [[nodiscard]] std::shared_ptr<Type> owningType() const;

        void setType(std::vector<std::shared_ptr<Type>> type);
        [[nodiscard]] std::vector<std::shared_ptr<Type>> type() const;
        void appendType(std::vector<std::shared_ptr<Type>> type);
        void appendType(std::shared_ptr<Type> type);

    private:
        std::shared_ptr<Feature> OwnedMemberFeature;
        std::shared_ptr<Type> OwningType;
        std::vector<std::shared_ptr<Type>> _Type;
    };
}
