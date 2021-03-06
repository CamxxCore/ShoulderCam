#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS

// Windows Header Files:
#include <windows.h>
#include <cstdio>
#include <inttypes.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "inc/enums.h"
#include "inc/natives.h"
#include "inc/types.h"
#include "inc/main.h"

#include "Utility/General.h"
#include "Utility/Logger.h"
#include "Utility/Pattern.h"
#include "Utility/MathEx.h"
#include "Utility/keymap.h"
#include "Utility/Config.h"

#include "Offsets.h"
#include "Types.h"
#include "Enums.h"

#include "Game.h"
#include "Functions.h"

void scriptKeyboardEvent(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
