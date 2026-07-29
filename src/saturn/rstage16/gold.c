// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

extern char g_RStage16GoldText1[];
extern char g_RStage16GoldText25[];
extern char g_RStage16GoldText50[];
extern char g_RStage16GoldText100[];
extern char g_RStage16GoldText250[];
extern char g_RStage16GoldText400[];
extern char g_RStage16GoldText700[];
extern char g_RStage16GoldText1000[];
extern char g_RStage16GoldText2000[];
extern char g_RStage16GoldText5000[];

char* g_RStage16GoldCollectTexts[10] = {
    g_RStage16GoldText1,    g_RStage16GoldText25,   g_RStage16GoldText50,
    g_RStage16GoldText100,  g_RStage16GoldText250,  g_RStage16GoldText400,
    g_RStage16GoldText700,  g_RStage16GoldText1000, g_RStage16GoldText2000,
    g_RStage16GoldText5000,
};
