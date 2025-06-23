//
// Created by Moritz Herzog on 25.03.25.
//

#ifndef SYSMLV2_FEATURE_H
#define SYSMLV2_FEATURE_H

#include <optional>

#include <core/types/Type.h>

#include "FeatureDirectionKind.h"

namespace KerML::Entities {
    class Feature : public Type {
    public:
        Feature();
        ~Feature() override = default;

        void setIsUnique(bool isUnique);
        bool isUnique();

        void setIsOrdered(bool isOrdered);
        bool isOrdered();

        void setIsComposite(bool isComposite);
        bool isComposite();

        void setIsEnd(bool isEnd);
        bool isEnd();

        void setIsDerived(bool isDerived);
        bool isDerived();

        void setIsPortion(bool isPortion);
        bool isPortion();
        
        void setIsVariable(bool isVariable);
        bool isVariable();

        void setIsConstant(bool isConstant);
        bool isConstant();

        void setDirection(FeatureDirectionKind direction);
        std::optional<FeatureDirectionKind> direction();

        void setType(std::vector<std::shared_ptr<Type>> type);
        std::vector<std::shared_ptr<Type>> type() const;
        void appendType(std::vector<std::shared_ptr<Type>> type);
        void appendType(std::shared_ptr<Type> type);

    protected:
        void setFeaturingType(std::vector<std::shared_ptr<Type>> featuringType);
        std::vector<std::shared_ptr<Type>> featuringType() const;
        void appendFeaturingType(std::vector<std::shared_ptr<Type>> featuringType);
        void appendFeaturingType(std::shared_ptr<Type> featuringType);

    private:
        bool IsUnique;
        bool IsOrdered;
        bool IsComposite;
        bool IsEnd;
        bool IsDerived;
        bool IsPortion;
        bool IsVariable;
        bool IsConstant;

        std::optional<FeatureDirectionKind> Direction;

        std::vector<std::shared_ptr<Type>> _Type;
        std::vector<std::shared_ptr<Type>> FeaturingType;
    };
}

#endif //SYSMLV2_FEATURE_H
