#ifndef FUNCTION_VISITOR_H
#define FUNCTION_VISITOR_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTContext.h"
#include <vector>
#include <string>

class FunctionVisitor : public clang::RecursiveASTVisitor<FunctionVisitor> {
public:
    FunctionVisitor(clang::ASTContext* context, const std::vector<std::pair<unsigned, unsigned>>& lineRanges)
        : context(context), lineRanges(lineRanges) {}

    bool VisitFunctionDecl(clang::FunctionDecl* func);

private:
    clang::ASTContext* context;
    std::vector<std::pair<unsigned, unsigned>> lineRanges;

    bool isInRange(unsigned line, unsigned rangeStart, unsigned rangeEnd);
    void printMatchingInfo(const std::string& functionName,
                           unsigned startLine, unsigned endLine,
                           unsigned rangeStart, unsigned rangeEnd);
};

#endif // FUNCTION_VISITOR_H
