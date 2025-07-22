#include "FunctionVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h" // ✅ For llvm::outs()

bool FunctionVisitor::VisitFunctionDecl(clang::FunctionDecl* func) {
    if (!func->hasBody())
        return true;

    clang::SourceManager& SM = context->getSourceManager();
    clang::SourceLocation startLoc = func->getSourceRange().getBegin();
    clang::SourceLocation endLoc = func->getSourceRange().getEnd();

    unsigned startLine = SM.getSpellingLineNumber(startLoc);
    unsigned endLine = SM.getSpellingLineNumber(endLoc);
    std::string name = func->getNameInfo().getName().getAsString();

    for (const auto& range : lineRanges) {
        unsigned rangeStart = range.first;
        unsigned rangeEnd = range.second;
        if (isInRange(startLine, rangeStart, rangeEnd) ||
            isInRange(endLine, rangeStart, rangeEnd)) {
            printMatchingInfo(name, startLine, endLine, rangeStart, rangeEnd);
        }
    }

    return true;
}

bool FunctionVisitor::isInRange(unsigned line, unsigned rangeStart, unsigned rangeEnd) {
    return line >= rangeStart && line <= rangeEnd;
}

void FunctionVisitor::printMatchingInfo(const std::string& functionName,
                                        unsigned startLine, unsigned endLine,
                                        unsigned rangeStart, unsigned rangeEnd) {
    llvm::outs() << "🔍 Function `" << functionName << "` found at lines ["
                 << startLine << "-" << endLine << "] matches range ["
                 << rangeStart << "-" << rangeEnd << "]\n";
}

