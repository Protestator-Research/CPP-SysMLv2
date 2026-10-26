//
// Created by Moritz Herzog on 11.03.25.
//

#ifndef CPP_SYSMLV2_LIB_MERGERESULT_H
#define CPP_SYSMLV2_LIB_MERGERESULT_H

#include <vector>
#include <memory>
#include <string>
#include <sysmlv2/rest/entities/IEntity.h>
#include <sysmlv2/rest/sysmlv2rest_global.h>

namespace SysMLv2::REST {
    class Commit;
    class DataIdentity;

    /**
     * The result of a merge (MergeResult of the SysML v2 API). In the REST API the response is either the Commit of a
     * successful merge or an array of the DataIdentity that are in conflict.
     */
    class SYSMLV2REST_EXPORT MergeResult : public IEntity {
    public:
        MergeResult(std::shared_ptr<Commit> mergeCommit = nullptr, std::vector<std::shared_ptr<DataIdentity>> conflict = std::vector<std::shared_ptr<DataIdentity>>());

        MergeResult(const MergeResult& other);
        MergeResult(MergeResult&& other) noexcept;
        MergeResult& operator=(const MergeResult& other);
        MergeResult& operator=(MergeResult&& other) noexcept;

        ~MergeResult() override = default;

        /**
         * Reads the response of a merge: a JSON object is the merge commit, a JSON array holds the conflicting
         * DataIdentity.
         * @throws std::invalid_argument If the text is neither valid JSON object nor array or an entry is invalid.
         */
        static MergeResult fromJson(const std::string& jsonString);

        std::vector<std::shared_ptr<DataIdentity>> conflict() const;
        std::shared_ptr<Commit> mergeCommit() const;

        /**
         * The Commit as JSON object if there is a merge commit, otherwise the array of the conflicting DataIdentity
         * (like the REST response). A merge commit and conflicts at the same time cannot be written; the commit counts.
         */
        std::string serializeToJson() override;

    protected:
        void deserializeAndPopulate(const std::string& jsonString) override;

        std::shared_ptr<Commit> MergeCommit = nullptr;
        std::vector<std::shared_ptr<DataIdentity>> Conflict;
    };
} // SysMLv2

#endif //CPP_SYSMLV2_LIB_MERGERESULT_H
