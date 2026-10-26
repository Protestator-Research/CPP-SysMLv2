//
// SysMLv2 C++ Library Implementation
// Copyright (C) 2025  Moritz Herzog
//
//This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//---------------------------------------------------------

//---------------------------------------------------------
// Constants, Definitions, Pragmas
//---------------------------------------------------------
#pragma once
//---------------------------------------------------------
// External Classes
//---------------------------------------------------------
#include <memory>
//---------------------------------------------------------
// Internal Classes
//---------------------------------------------------------
#include <sysmlv2/rest/versioning/VersionedData.h>

/**
 * Helpers that the three parts of the versioning logic share. Not installed.
 */
namespace SysMLv2::REST::Versioning::Detail {
    /**
     * The stored commit for a reference to a commit.
     * @throws std::runtime_error If the resolver does not know the commit.
     */
    std::shared_ptr<Commit> resolveCommit(const std::shared_ptr<Commit>& reference, const CommitResolver& resolver);

    /**
     * The stored commit for a commit that may be known only by reference; the commit itself if it is not stored.
     */
    std::shared_ptr<Commit> resolveOrSelf(const std::shared_ptr<Commit>& commit, const CommitResolver& resolver);

    /**
     * True if both versions are absent, or both have the same payload.
     */
    bool sameState(const std::shared_ptr<DataVersion>& first, const std::shared_ptr<DataVersion>& second);
}
