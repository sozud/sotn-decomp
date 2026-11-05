// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"

void entrypoint(void);

void satz_saturn_main(void) { entrypoint(); }

void sotn_satz_unimplemented(const char* name) {
    satz_die("unimplemented: %s (still assembly)", name);
}
