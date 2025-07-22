#include "FunctionScopeAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include <sstream>
#include <vector>
#include <memory>

using namespace clang::tooling;
using namespace llvm;

static cl::OptionCategory ToolCategory("function-scope-identifier options");

// ✅ Required option: Line range argument (e.g., 3-6)
static cl::opt<std::string> IdentifyScopeRange(
    "identify-scope-range",
    cl::desc("Specify line ranges to check (e.g. 12-17,19-22)"),
    cl::value_desc("ranges"),
    cl::Required,
    cl::cat(ToolCategory));

// ✅ Only one source file required
static cl::list<std::string> SourcePaths(
    cl::Positional,
    cl::desc("<source>"),
    cl::OneOrMore,  // ✅ This fixes the issue!
    cl::cat(ToolCategory));

// ✅ Helper to parse 12-15,20-23
std::vector<std::pair<unsigned, unsigned>> parseLineRanges(const std::string& input) {
    std::vector<std::pair<unsigned, unsigned>> ranges;
    std::stringstream ss(input);
    std::string token;
    while (std::getline(ss, token, ',')) {
        size_t dash = token.find('-');
        if (dash != std::string::npos) {
            unsigned start = std::stoi(token.substr(0, dash));
            unsigned end = std::stoi(token.substr(dash + 1));
            ranges.emplace_back(start, end);
        }
    }
    return ranges;
}

int main(int argc, const char **argv) {
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, ToolCategory);
    if (!ExpectedParser) {
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }

    CommonOptionsParser& OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());
    auto ranges = parseLineRanges(IdentifyScopeRange);

    class ActionFactory : public FrontendActionFactory {
        std::vector<std::pair<unsigned, unsigned>> Ranges;
    public:
        explicit ActionFactory(std::vector<std::pair<unsigned, unsigned>> r) : Ranges(std::move(r)) {}
        std::unique_ptr<clang::FrontendAction> create() override {
            return std::make_unique<FunctionScopeAction>(Ranges);
        }
    };

    return Tool.run(std::make_unique<ActionFactory>(ranges).get());
}

