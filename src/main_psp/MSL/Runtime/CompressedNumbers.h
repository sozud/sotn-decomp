// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef MSL_RUNTIME_COMPRESSEDNUMBERS_H
#define MSL_RUNTIME_COMPRESSEDNUMBERS_H

char* __DecodeAddress(char* p, void** paddr);
char* __DecodeSignedNumber(unsigned char* p, long* pnum);
char* __DecodeUnsignedNumber(unsigned char* p, unsigned long* pnum);

#endif // MSL_RUNTIME_COMPRESSEDNUMBERS_H
