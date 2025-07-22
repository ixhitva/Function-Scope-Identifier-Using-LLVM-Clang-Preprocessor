#include "FunctionScopeAction.h"
#include "FunctionScopeConsumer.h"

std::unique_ptr<clang::ASTConsumer>
FunctionScopeAction::CreateASTConsumer(clang::CompilerInstance& CI, llvm::StringRef file) {
    return std::make_unique<FunctionScopeConsumer>(&CI.getASTContext(), ranges);
}
