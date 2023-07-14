extern crate clang;

use clang::{Cursor, Index, TranslationUnit};

fn traverse(cursor: &Cursor) {
    if cursor.kind() == clang::CursorKind::FunctionDecl {
        if let Some(name) = cursor.spelling() {
            println!("Function declaration: {}", name);
        }
    }

    for child in cursor.children() {
        traverse(&child);
    }
}

fn main() {
    let index = Index::create(false, true);
    let path_to_header_file = "/path/to/header.h";
    let tu = index.parser(path_to_header_file)
                  .arguments(&["-I/path/to/headers"])
                  .parse();

    if let Ok(tu) = tu {
        traverse(&tu.cursor());
    } else if let Err(diagnostic_set) = tu {
        for diag in diagnostic_set.diagnostics() {
            println!("Diagnostic: {:?}", diag);
        }
    }
}
// libclang-dev