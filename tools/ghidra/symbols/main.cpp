#include <iostream>
#include <clang-c/Index.h>

void traverse(CXCursor cursor) {
    if (clang_getCursorKind(cursor) == CXCursor_FunctionDecl) {
        CXString name = clang_getCursorSpelling(cursor);
        std::cout << "Function declaration: " << clang_getCString(name) << std::endl;
        clang_disposeString(name);
    }

    clang_visitChildren(cursor, [](CXCursor child, CXCursor parent, CXClientData client_data) -> CXChildVisitResult {
        traverse(child);
        return CXChildVisit_Continue;
    }, nullptr);
}

int main() {
    CXIndex index = clang_createIndex(0, 0);
    const char* path_to_header_file = "/path/to/header.h";
    const char* args[] = {"-I/path/to/headers"};
    int num_args = sizeof(args) / sizeof(args[0]);

    CXTranslationUnit tu = clang_parseTranslationUnit(index, path_to_header_file, args, num_args, nullptr, 0, CXTranslationUnit_None);
    
    if (tu) {
        CXCursor root = clang_getTranslationUnitCursor(tu);
        traverse(root);
        clang_disposeTranslationUnit(tu);
    } else {
        unsigned num_diagnostics = clang_getNumDiagnostics(tu);
        for (unsigned i = 0; i < num_diagnostics; ++i) {
            CXDiagnostic diagnostic = clang_getDiagnostic(tu, i);
            CXString diagnostic_string = clang_formatDiagnostic(diagnostic, clang_defaultDiagnosticDisplayOptions());
            std::cout << "Diagnostic: " << clang_getCString(diagnostic_string) << std::endl;
            clang_disposeString(diagnostic_string);
        }
    }
    
    clang_disposeIndex(index);

    return 0;
}
