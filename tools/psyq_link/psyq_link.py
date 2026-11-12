#!/usr/bin/env python3
import os
import struct
import subprocess
import sys
import tempfile


def lib_member(path: str, name: str) -> bytes:
    data = open(path, "rb").read()
    if data[:4] != b"LIB\x01":
        raise SystemExit(f"{path}: not a Psy-Q library")
    pos = 4
    while pos + 20 <= len(data):
        member = data[pos : pos + 8].decode("ascii").rstrip()
        _, offset, size = struct.unpack_from("<III", data, pos + 8)
        if member == name.upper():
            return data[pos + offset : pos + size]
        pos += size
    raise SystemExit(f"{path}: no member named {name}")


def main():
    if len(sys.argv) != 6:
        raise SystemExit(
            f"usage: {sys.argv[0]} <psyq-obj-parser> <objcopy> <LIB> <member> <out.o>"
        )
    parser, objcopy, lib, member, out = sys.argv[1:]
    os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
    with tempfile.TemporaryDirectory() as tmp:
        lnk = os.path.join(tmp, f"{member}.OBJ")
        elf = os.path.join(tmp, f"{member}.o")
        with open(lnk, "wb") as f:
            f.write(lib_member(lib, member))
        subprocess.run(
            [parser, lnk, "-n", "-c", "-o", elf],
            check=True,
            stdout=subprocess.DEVNULL,
        )
        subprocess.run(
            [objcopy, "--rename-section", ".rdata=.rodata", elf, out], check=True
        )


if __name__ == "__main__":
    main()
