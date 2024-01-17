import sys


def u8(f):
    return int.from_bytes(f.read(1), byteorder="little", signed=False)

def u8_peek(f):
    pos = f.tell()
    ret = int.from_bytes(f.read(1), byteorder="little", signed=False)
    f.seek(pos)
    return ret

def u16(f):
    return int.from_bytes(f.read(2), byteorder="little", signed=False)


def u32(f):
    return int.from_bytes(f.read(4), byteorder="little", signed=False)


def s8(f):
    return int.from_bytes(f.read(1), byteorder="little", signed=True)


def s16(f):
    return int.from_bytes(f.read(2), byteorder="little", signed=True)


def s32(f):
    return int.from_bytes(f.read(4), byteorder="little", signed=True)


def bool8(f):
    return "true" if u8(f) != 0 else "false"

#def sotn_str_to_utf8(ch):

def dakuten(chr, prev):
    if chr == "..":
        # print("prev", prev)
        if prev == "シ":
            return "ジ"
        if prev == "ク":
            return "グ"
        if prev == "て":
            return "で"
        if prev == "ト":
            return "ド"
        if prev == "サ":
            return "ザ"
        if prev == "タ":
            return "ダ"
        if prev == "か":
            return "が"
        if prev == "テ":
            return "デ"
        if prev == "ハ":
            return "バ"
        if prev == "セ":
            return "ゼ"
        if prev == "ホ":
            return "ボ"
        if prev == "ヒ":
            return "ビ"
        if prev == "こ":
            return "ご"
        if prev == "ふ":
            return "ぶ"
        if prev == "と":
            return "ど"
        if prev == "へ":
            return "べ"
        if prev == "ヘ":
            return "ベ"
        if prev == "ス":
            return "ズ"
        if prev == "カ":
            return "ガ"
        if prev == "ケ":
            return "ゲ"
        if prev == "シ":
            return "ジ"
        if prev == "し":
            return "じ"
        if prev == "き":
            return "ぎ"
        if prev == "は":
            return "ば"
        if prev == "フ":
            return "ブ"
        if prev == "ウ":
            return "ヴ"
        if prev == "さ":
            return "ざ"
        if prev == "ひ":
            return "び"
        if prev == "せ":
            return "ぜ"
        if prev == "コ":
            return "ゴ"
        if prev == "ほ":
            return "ぼ"
        if prev == "キ":
            return "ギ"
        if prev == "そ":
            return "ぞ"
        if prev == "た":
            return "だ"
        if prev == "ソ":
            return "ゾ"
        if prev == "く":
            return "ぐ"
        # return "\u3099"
        # return "periods"
    if chr == ".":
        if prev == "フ":
            return "プ"
        if prev == "ヒ":
            return "ピ"
        if prev == "ハ":
            return "パ"
        if prev == "ヘ":
            return "ペ"
        if prev == "ホ":
            return "ポ"        
        print(chr, prev)
        assert(False)
        return "period"
    print(chr)
    assert(False)

def get_chr(chr):
   table = [
        # 0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
        " ",     "!",  "\"", "#",   "$",   "%", "&", "'", "(", ")", "男", "+", ",", "-", ".", "/",
        "0",     "1",   "2",   "3",   "4", "5", "6", "7", "8", "9", ":", "人", "手", "=", "玉", "?",
        "石",    "A",   "B",   "C",   "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
        "P",     "Q",   "R",   "S",   "T", "U", "V", "W", "X", "Y", "Z", "[", "剣", "]", "盾", "_",
        "書",   "a",   "b",   "c",   "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
        "p",     "q",   "r",   "s",   "t", "u", "v", "w", "x", "y", "z", "炎", "氷", "雷", "~", "女",
        "力",    "。",   "「",   "」", "、", "・", "ヲ", "ァ", "ィ", "ゥ", "ェ", "ォ", "ャ", "ュ", "ョ", "ッ",
        "ー",    "ア",   "イ",   "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ",
        "タ",    "チ",   "ツ",   "テ", "ト", "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ", "マ",
        "ミ",    "ム",   "メ",   "モ", "ヤ", "ユ", "ヨ", "ラ", "リ", "ル", "レ", "ロ", "ワ", "ン", "..", ".", # fixme punctuation .. , .
        "子",    "悪",   "魔",   "人", "妖", "精", "を","ぁ", "ぃ", "ぅ", "ぇ", "ぉ", "ゃ", "ゅ", "ょ", "っ",
        "金",    "あ",   "い",   "う", "え", "お", "か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ",
        "た",    "ち",   "つ",  "て",  "と", "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ", "ま",
        "み",    "む",   "め",  "も",  "や", "ゆ", "よ", "ら", "り", "る", "れ", "ろ", "わ", "ん", "指", "輪",
        "←",     "↖",   "↑",   "↗",   "→", "↘", "↓", "↙", "○", "×", "□", "△", "名", "刀", "聖", "血",
        "i0",    "i1",  "i2" , "i3", "i4", "i5", "i6", "i7", "i8", "i9", "i10", "i11", "大", "光", "邪", "月"
    ]
   return table[chr]
# def convert(chrs):
#     out = ""
 
#     for chr in chrs:
#         out += table[chr]

#     return out

def convert_test(f):
    pos = 0
    str = ""
    prev = None
    prev_prev = None
    while True:
        ch = f[pos]
        prev_prev = prev
        prev = ch
        pos+=1
        if int(ch) == 0xFF:
            ch = f[pos]
            pos += 1

            if (ch == 0):
                break

            if ch != 0xFF:
                # if we dakuten, erase previous
                str = str[:-1]
                str += dakuten(get_chr(ch), get_chr(prev_prev))
        if ch != 158 and ch != 159:
            str += get_chr(ch)
    return str

counter = 0
def get_sotn_str(f, ptr):
    global counter
    prev = f.tell()
    # print(ptr)
    f.seek(ptr - 0x800A0000)

    str = "\""
    do_convert = True #counter != 125 #and counter != 169 and counter != 170 and counter < 172
    counter += 1
    orig_str = "\""
    if do_convert:
        chars = []
        while True:
            ch = u8(f)
            chars.append(ch)
            if int(ch) == 0xFF:
                ch = u8(f)
                chars.append(ch)
                if (ch == 0):
                    break
            # orig_str += f"\\x{ch:02X}"
        str += convert_test(chars)
    else:
        while True:
            ch = u8(f)
            if (ch == 0):
                break

            str += f"\\x{ch:02X}"

    str += '"'
    orig_str += '"'

    # if "ソ" in str:
    #     return orig_str

    f.seek(prev)
    if do_convert:
        return f"_S({str})"
    else:
        if str == "":
            return "\xFF"
        return str


def get_sjis_str(f, ptr):
    prev = f.tell()
    f.seek(ptr - 0x800A0000)

    data = []
    while True:
        ch = u8(f)
        if ch == 0:
            break
        data.append(ch)
    str = bytes(data).decode("shift_jis")

    f.seek(prev)
    return (
        f'"{str}"'
        # .replace("ソ", "\\x83\\x5C")
        # .replace("十", "\\x8F\\x5C")
        # .replace("能", "\\x94\\x5C")
        .replace("ソ", "ソ\\")
        .replace("十", "十\\")
        .replace("能", "能\\")
    )


def get_combo_str(f, ptr):
    prev = f.tell()
    f.seek(ptr - 0x800A0000)

    str = '"'
    while True:
        ch = u8(f)
        if ch == 0:
            break
        str += f"\\x{ch:02X}"
    str += '"'

    f.seek(prev)
    return str


with open("disks/pspeu/PSP_GAME/USRDIR/res/ps/hdbin/dra.bin", "rb") as f:
    # assert("ミリカンの石刀" == convert([0x90, 0x98, 0x76, 0x9D, 0xC9, 0x20, 0xED]))
    # assert("シャーマンの盾" == convert([0x7C, 0x6C, 0x70, 0x8F, 0x9D, 0xC9, 0x3E]))
    # assert("つかい魔の剣" == convert([0xC2, 0xB6, 0xB2, 0xA2, 0xC9, 0x3C]))
    # assert("←↖↑↗→" == convert([0xE0, 0xE1, 0xE2, 0xE3, 0xE4]))

    result = convert_test([0x9A, 0x7C, 0xFF, 0x9E, 0x7D, 0x84, 0x8C, 0x67, 0x72, 0x71, 0xFF, 0])
    # print(result)
    assert(result == "レジストファイア")
    # result = convert_test([0x8A,0xFF,0x9E,0x99,0x7B,0xFF,0x9E,0x72,0xC9,0xB4,0xDD,0xFF,0xFF, 0xED, 0xFF, 0])
    # print(result)
    # assert(result == "バルザイのえん月刀")

    # exit(0)
    f.seek(0x4A10)
    print('#include "game.h"')

    print("""
// !!! IMPORTANT !!!
// There is a bug in the compiler where certain characters are not properly
// encoded. Characters such as 'ソ' have a byte sequence of 83 5C. But as the
// compiler thinks that 5C is a backslash it tries to escape the character
// right after. This is why in the code 'ソ' and other characters are
// immediately followed by a '\\'.""")
    print("")
    print("// clang-format off")

    print("SubweaponDef g_SubwpnDefs[] = {")
    rows = []
    for i in range(0, 13):
        str = "    {"
        str += ", ".join(
            [
                f"{s16(f)}",
                f"{s16(f)}",
                f"0x{u16(f):04X}",
                f"{u8(f)}",
                f"0x{u8(f):02X}",
                f"{u16(f)}",
                f"0x{u8(f):02X}",
                f"0x{u8(f):02X}",
                f"{u16(f)}",
                f"0x{u16(f):02X}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u16(f)}",
            ]
        )
        str += "},"
        rows.append(str)
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 217):
        name_ptr = u32(f)
        desc_ptr = u32(f)

        str = "    {"
        str += ", ".join(
            [
                get_sotn_str(f, name_ptr),
                get_sjis_str(f, desc_ptr),
                f"{s16(f)}",
                f"{s16(f)}",
                f"{u16(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{bool8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u32(f)}",
                f"{u32(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
            ]
        )
        str += "},"
        rows.append(str)
    print("")
    print("Equipment g_EquipDefs[] = {")
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 90):
        name_ptr = u32(f)
        desc_ptr = u32(f)

        str = "    {"
        str += ", ".join(
            [
                get_sotn_str(f, name_ptr),
                get_sjis_str(f, desc_ptr),
                f"{s16(f)}",
                f"{s16(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"{u16(f)}",
                f"0x{u16(f):04X}",
                f"0x{u16(f):04X}",
                f"0x{u16(f):04X}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
            ]
        )
        str += "},"
        rows.append(str)
    print("")
    print("Accessory g_AccessoryDefs[] = {")
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 85):
        name_ptr = u32(f)
        rows.append(f"    {get_sotn_str(f, name_ptr)},")
    print("")
    print("const char* g_MenuStr[] = {")
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 28):
        name_ptr = u32(f)
        combo_ptr = u32(f)
        desc_ptr = u32(f)

        str = "    {"
        str += ", ".join(
            [
                get_sjis_str(f, name_ptr),
                get_sotn_str(f, combo_ptr),
                get_sjis_str(f, desc_ptr),
                f"{u8(f)}",
                f"{s8(f)}",
                f"{s16(f)}",
                f"0x{u16(f):02X}",
                f"0x{u16(f):02X}",
                f"0x{u16(f):02X}",
                f"0x{u16(f):04X}",
                f"{s16(f)}",
                f"{s16(f)}",
            ]
        )
        str += "},"
        rows.append(str)
    print("")
    print("SpellDef g_SpellDefs[] = {")
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 30):
        name_ptr = u32(f)
        desc_ptr = u32(f)

        str = "    {"
        str += ", ".join(
            [
                get_sjis_str(f, name_ptr),
                get_sjis_str(f, desc_ptr),
                f"{u16(f)}",
                f"{u16(f)}",
                f"{s32(f)}",
            ]
        )
        str += "},"
        rows.append(str)
    print("")
    print("RelicDesc g_RelicDefs[] = {")
    print("\n".join(rows))
    print("};")

    rows = []
    for i in range(0, 400):
        name_ptr = u32(f)
        str = "    {"
        str += ", ".join(
            [
                get_sotn_str(f, name_ptr),
                f"{s16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{s16(f)}",
                f"{u16(f)}",
                f"0x{u16(f):04X}",
                f"0x{u16(f):04X}",
                f"0x{u16(f):04X}",
                f"0x{u16(f):04X}",
                f"{s16(f)}",
                f"{s16(f)}",
                f"{s16(f)}",
                f"{s16(f)}",
                f"{u16(f)}",
                f"{u16(f)}",
                f"{u8(f)}",
                f"{u8(f)}",
                f"0x{u32(f):08X}",
            ]
        )
        str += "},"
        rows.append(str)
    print("")
    print("EnemyDef g_EnemyDefs[] = {")
    print("\n".join(rows))
    print("};")

    print(f"offset at 0x{f.tell():X}", file=sys.stderr)
