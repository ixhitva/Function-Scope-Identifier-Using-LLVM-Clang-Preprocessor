#ifndef FUNCTION_SCOPE_CONSUMER_H
#define FUNCTION_SCOPE_CONSUMER_H

#include "FunctionVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"

class FunctionScopeConsumer : public clang::ASTConsumer {
public:
    FunctionScopeConsumer(clang::ASTContext* context,
                          const std::vector<std::pair<unsigned, unsigned>>& lineRanges)
        : visitor(context, lineRanges) {}

    void HandleTranslationUnit(clang::ASTContext& context) override;

private:
    FunctionVisitor visitor;
};

#endif // FUNCTION_SCOPE_CONSUMER_H
