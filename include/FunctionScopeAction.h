#ifndef FUNCTION_SCOPE_ACTION_H
#define FUNCTION_SCOPE_ACTION_H

#include "FunctionScopeConsumer.h"
#include "clang/Frontend/FrontendAction.h"
#include <utility>
#include <vector>

class FunctionScopeAction : public clang::ASTFrontendAction {
public:
    explicit FunctionScopeAction(const std::vector<std::pair<unsigned, unsigned>>& lineRanges)
        : ranges(lineRanges) {}

    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance& CI, llvm::StringRef file) override;

private:
    std::vector<std::pair<unsigned, unsigned>> ranges;
};

#endif // FUNCTION_SCOPE_ACTION_H
