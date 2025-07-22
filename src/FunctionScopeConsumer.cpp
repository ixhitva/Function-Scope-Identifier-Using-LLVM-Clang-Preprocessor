#include "FunctionScopeConsumer.h"

void FunctionScopeConsumer::HandleTranslationUnit(clang::ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
}
