# Function-Scope-Identifier-Using-LLVM-Clang-Preprocessor
The project analyzes C/C++ source files and identifies which functions are defined within or overlap with user-specified line ranges. It is built using Clang's LibTooling, which allows deep analysis of C/C++ code.

Commands:
<img width="712" height="17" alt="cmd1" src="https://github.com/user-attachments/assets/6e305959-139c-4886-92a2-f417caa64a82" />

<img width="1207" height="48" alt="cmd2" src="https://github.com/user-attachments/assets/1a610e6e-ce08-44b5-acdd-732dbb9dd340" />

<img width="1205" height="43" alt="cmd3" src="https://github.com/user-attachments/assets/0404c65d-8300-4393-ac69-3ee1b80ca0e2" />



1. How It Works (Detailed Flow)

A. Command-Line Interface
The tool is run from the command line.
The user provides:
The source file to analyze.
The line ranges to check (e.g., 12-17,19-22).

B. Parsing Line Ranges
The main program parses the line range string into a vector of pairs, each representing a start and end line.

C. Clang Tooling Setup
The tool uses Clang's ASTFrontendAction to process the source file and build an Abstract Syntax Tree (AST).

D. Custom Action and Consumer
FunctionScopeAction: Inherits from clang::ASTFrontendAction. It receives the parsed line ranges and creates a custom AST consumer.
FunctionScopeConsumer: Inherits from clang::ASTConsumer. It creates a FunctionVisitor and starts traversing the AST.

E. AST Traversal and Function Detection
FunctionVisitor: Inherits from clang::RecursiveASTVisitor.
For each function declaration (FunctionDecl), it checks if the function has a body.
It retrieves the start and end line numbers of the function using Clang's SourceManager.
For each user-specified line range, it checks if the function's start or end line falls within the range.
If a match is found, it prints the function's name, its line span, and the matching range.

2. Key Classes and Their Roles
FunctionScopeAction
Entry point for AST processing.
Receives the line ranges and passes them to the consumer.
FunctionScopeConsumer
Receives the AST context and line ranges.
Creates a FunctionVisitor and starts the traversal.
FunctionVisitor
Visits each function in the AST.
Checks if the function's lines overlap with any specified range.
Prints detailed information about matching functions.

3. Example Usage
Suppose you have a file test.c and want to know which functions are defined between lines 10-20 and 30-40:

4. Technical Stack
C++: Main implementation language.
Clang LibTooling: For parsing and analyzing C/C++ code.
LLVM: For command-line parsing and output.

<img width="1230" height="680" alt="op" src="https://github.com/user-attachments/assets/c02a5613-8cbc-403d-a06c-04a5c7ee3b41" />
