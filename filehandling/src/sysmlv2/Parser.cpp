//
// Created by Moritz Herzog on 30.04.25.
//

#include <sysmlv2/Parser.h>
#include <sysmlv2/Workspace.h>

namespace SysMLv2::Files {
    namespace {
        using Result = std::pair<std::vector<std::shared_ptr<KerML::Entities::Element>>, std::vector<std::shared_ptr<ParserError>>>;

        // Every single-source parse is a workspace of one source: the names of the source are resolved among themselves and
        // against nothing else (load the library into a Workspace to resolve against it).
        Result finish(Workspace& workspace, bool reportUnresolvedAsWarnings) {
            workspace.resolve();
            auto errors = workspace.errors(0);
            if (reportUnresolvedAsWarnings) {
                const auto warnings = workspace.unresolvedAsWarnings(0);
                errors.insert(errors.end(), warnings.begin(), warnings.end());
            }
            return std::make_pair(workspace.elements(0), errors);
        }
    }

    Result Parser::parseKerML(std::string text, std::string sourceName, bool reportUnresolvedAsWarnings) {
        Workspace workspace;
        workspace.addText(std::move(text), std::move(sourceName), SourceLanguage::KerML);
        return finish(workspace, reportUnresolvedAsWarnings);
    }

    Result Parser::parseSysMLv2(std::string text, std::string sourceName, bool reportUnresolvedAsWarnings) {
        Workspace workspace;
        workspace.addText(std::move(text), std::move(sourceName), SourceLanguage::SysML);
        return finish(workspace, reportUnresolvedAsWarnings);
    }

    Result Parser::parseFile(const std::string& path, bool reportUnresolvedAsWarnings) {
        Workspace workspace;
        workspace.addFile(path);
        return finish(workspace, reportUnresolvedAsWarnings);
    }
}
