// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/alucard/data", d60A5000, d_060A5000);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5060, func_060A5060);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A50E0, func_060A50E0);

// SAT: func_060A5558
void SetPlayerStep(PlayerSteps step) {
    PLAYER.step = step;
    PLAYER.step_s = 0;
}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5574, func_060A5574);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5594, func_060A5594);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A55B4, func_060A55B4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A55E4, func_060A55E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5614, func_060A5614);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5644, func_060A5644);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5674, func_060A5674);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56AC, func_060A56AC);

void func_060A56D8() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A56E4, func_060A56E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5738, func_060A5738);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A580C, func_060A580C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5938, func_060A5938);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A59E0, func_060A59E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5AF0, func_060A5AF0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5B94, func_060A5B94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5CD8, func_060A5CD8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5D50, func_060A5D50);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5E14, func_060A5E14);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5EA8, func_060A5EA8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A5F9C, func_060A5F9C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A605C, func_060A605C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A60EC, func_060A60EC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A61B0, func_060A61B0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6248, func_060A6248);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A62E4, func_060A62E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6314, func_060A6314);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6384, func_060A6384);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6420, func_060A6420);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6618, func_060A6618);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6688, func_060A6688);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A66FC, func_060A66FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A67B8, func_060A67B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A6A94, func_060A6A94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D3C, func_060A7D3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7D68, func_060A7D68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7DD0, func_060A7DD0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7DE8, func_060A7DE8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7E90, func_060A7E90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A7F28, func_060A7F28);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A80E0, func_060A80E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A81DC, func_060A81DC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8D78, func_060A8D78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A8DF4, func_060A8DF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9658, func_060A9658);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A96A0, func_060A96A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A972C, func_060A972C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9D90, func_060A9D90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60A9E3C, func_060A9E3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA0FC, func_060AA0FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA150, func_060AA150);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AA23C, func_060AA23C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AADE4, func_060AADE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB090, func_060AB090);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0BC, func_060AB0BC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB0E8, func_060AB0E8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB308, func_060AB308);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB37C, func_060AB37C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB3A8, func_060AB3A8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB44C, func_060AB44C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB4A4, func_060AB4A4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB558, func_060AB558);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB590, func_060AB590);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB5E0, func_060AB5E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB78C, func_060AB78C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AB814, func_060AB814);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ABCF0, func_060ABCF0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ABFA4, func_060ABFA4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC018, func_060AC018);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC0C8, func_060AC0C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC20C, func_060AC20C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC2F0, func_060AC2F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC574, func_060AC574);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AC8F4, func_060AC8F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACACC, func_060ACACC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACB6C, func_060ACB6C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ACF00, func_060ACF00);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD44C, func_060AD44C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD524, func_060AD524);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AD714, func_060AD714);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADACC, func_060ADACC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADB80, func_060ADB80);

void func_060ADD50() {}

void func_060ADD5C() {}

void func_060ADD68() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADD74, func_060ADD74);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADDDC, func_060ADDDC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60ADF3C, func_060ADF3C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE048, func_060AE048);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE184, func_060AE184);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE284, func_060AE284);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE36C, func_060AE36C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE544, func_060AE544);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE6F4, func_060AE6F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AE8E4, func_060AE8E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEAE8, func_060AEAE8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AECC4, func_060AECC4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEEE4, func_060AEEE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AEFBC, func_060AEFBC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF050, func_060AF050);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF124, func_060AF124);

void func_060AF1BC(int);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF1BC, func_060AF1BC);

void func_060AF4A0(void) { func_060AF1BC(1); }

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF4B8, func_060AF4B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF550, func_060AF550);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF654, func_060AF654);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF7F0, func_060AF7F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF8E0, func_060AF8E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AF9D4, func_060AF9D4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60AFA20, func_060AFA20);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0310, func_060B0310);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0584, func_060B0584);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B0638, func_060B0638);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B071C, func_060B071C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B24E0, func_060B24E0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B25F4, func_060B25F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B2B30, func_060B2B30);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B2DE4, func_060B2DE4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B2E40, func_060B2E40);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3024, func_060B3024);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B349C, func_060B349C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B38B4, func_060B38B4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3A90, func_060B3A90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3C70, func_060B3C70);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3D28, func_060B3D28);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3DF8, func_060B3DF8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B3F78, func_060B3F78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4024, func_060B4024);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B41C8, func_060B41C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4328, func_060B4328);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B446C, func_060B446C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4B90, func_060B4B90);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4E38, func_060B4E38);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B4F78, func_060B4F78);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B537C, func_060B537C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5634, func_060B5634);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B57F4, func_060B57F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5920, func_060B5920);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5AF4, func_060B5AF4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5C68, func_060B5C68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B5E94, func_060B5E94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6768, func_060B6768);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6AA4, func_060B6AA4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B6D94, func_060B6D94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7214, func_060B7214);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B761C, func_060B761C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7848, func_060B7848);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7994, func_060B7994);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B79B8, func_060B79B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7A6C, func_060B7A6C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7B0C, func_060B7B0C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B7BB4, func_060B7BB4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B86F4, func_060B86F4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8B40, func_060B8B40);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8F68, func_060B8F68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B8FE0, func_060B8FE0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9130, func_060B9130);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B92B8, func_060B92B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B92F8, func_060B92F8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9340, func_060B9340);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B93C4, func_060B93C4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B94F8, func_060B94F8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B95C8, func_060B95C8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9610, func_060B9610);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9694, func_060B9694);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60B9DC0, func_060B9DC0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA4CC, func_060BA4CC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA604, func_060BA604);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA6B8, func_060BA6B8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA90C, func_060BA90C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BA9A0, func_060BA9A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAA20, func_060BAA20);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAB00, func_060BAB00);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAD84, func_060BAD84);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAE70, func_060BAE70);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BAF44, func_060BAF44);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB070, func_060BB070);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB4FC, func_060BB4FC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB678, func_060BB678);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB7A8, func_060BB7A8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB8A8, func_060BB8A8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BB968, func_060BB968);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BBD9C, func_060BBD9C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BBF08, func_060BBF08);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BBF5C, func_060BBF5C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BC01C, func_060BC01C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BCD98, func_060BCD98);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD214, func_060BD214);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD2B0, func_060BD2B0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD39C, func_060BD39C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD5A4, func_060BD5A4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD61C, func_060BD61C);

void func_0600FFB8();

void func_060BD6A8(void) { func_0600FFB8(); }

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD6C0, func_060BD6C0);

void func_060BD6CC() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD6D8, func_060BD6D8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BD8F8, func_060BD8F8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BDA44, func_060BDA44);

void func_060BE354() {}

const u32 DAT_060be360 = 0xBA2E8BA3;

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE364, func_060BE364);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE620, func_060BE620);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE7DC, func_060BE7DC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BE888, func_060BE888);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BEEF8, func_060BEEF8);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BF470, func_060BF470);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BF894, func_060BF894);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BFADC, func_060BFADC);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60BFB2C, func_060BFB2C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C0014, func_060C0014);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C01C0, func_060C01C0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C06A0, func_060C06A0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C07F0, func_060C07F0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C08A8, func_060C08A8);

void func_060C0BE8() {}

INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C0BF4, func_060C0BF4);
INCLUDE_ASM("asm/saturn/alucard/data", d60C0E48, d_060C0E48);
INCLUDE_ASM("asm/saturn/alucard/data", d60C1378, d_060C1378);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C4DA0, func_060C4DA0);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C4E5C, func_060C4E5C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C5320, func_060C5320);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C593C, func_060C593C);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C5C94, func_060C5C94);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C6070, func_060C6070);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C61E4, func_060C61E4);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C6F68, func_060C6F68);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C7154, func_060C7154);
INCLUDE_ASM("asm/saturn/alucard/f_nonmat", f60C75A8, func_060C75A8);
INCLUDE_ASM("asm/saturn/alucard/data", d60C7FA0, d_060C7FA0);
INCLUDE_ASM_NO_ALIGN("asm/saturn/alucard/data", d60C84B6, d_060C84B6);
