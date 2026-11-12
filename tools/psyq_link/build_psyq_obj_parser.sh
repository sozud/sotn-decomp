#!/bin/sh
set -e

OUT="$1"
[ -z "$OUT" ] && { echo "usage: $0 <output binary>" 1>&2; exit 1; }
REDUX_URL=https://github.com/grumpycoders/pcsx-redux.git
REDUX_REV=7637751dc246876ee658e94825d9c91129fef820
SRC="$(dirname "$OUT")/pcsx-redux"

if [ ! -d "$SRC/.git" ]; then
    git init -q "$SRC"
    git -C "$SRC" remote add origin "$REDUX_URL"
fi
if [ "$(git -C "$SRC" rev-parse -q --verify HEAD 2>/dev/null)" != "$REDUX_REV" ]; then
    git -C "$SRC" fetch -q --depth 1 --filter=blob:none origin "$REDUX_REV"
    git -C "$SRC" checkout -q FETCH_HEAD
fi
git -C "$SRC" submodule update -q --init --depth 1 \
    third_party/args third_party/ELFIO third_party/fmt third_party/magic_enum

${CXX:-c++} -std=c++20 -O2 -DFMT_HEADER_ONLY \
    -I"$SRC" -I"$SRC/src" -I"$SRC/third_party" \
    -I"$SRC/third_party/ELFIO" \
    -I"$SRC/third_party/fmt/include" \
    -I"$SRC/third_party/magic_enum/include" \
    -o "$OUT" \
    "$SRC/tools/psyq-obj-parser/psyq-obj-parser.cc" \
    "$SRC/src/supportpsx/psyq-obj.cc" \
    "$SRC/src/support/file.cc"
