#include "stdafx.h"
#include "ConfigParser.h"

using namespace Utility;

#define THIRD_PERSON_ONFOOT_METADATA 0xFBE36564
#define THIRD_PERSON_ONFOOT_AIM_METADATA 0xBB570E9E
#define THIRD_PERSON_ONFOOT_AIM_FROM_COVER_METADATA 0xD2B17AE4

bool bScriptRunning = true;

struct CConfigSettings {
    float fCamYOffset = -0.54f;
    float fCamZOffset = -0.022f;
    float fCamLerpDuration = 0.3f;
    float fCamLerpExtent = 0.7f;
    float fCamForwardLerpExtent = 0.8f;

} g_config;

float fLerpPosX = 1.f,
      fLerpPosY = g_config.fCamYOffset;

float fHorzLerpTime = 0.f, fForwardLerpTime = 0.f;

bool bReverseLerp = false;

camBaseObjectMetadata * metadata = nullptr;

void lerpCameraFrame() {

    if ( fHorzLerpTime < 1.f ) {

        fHorzLerpTime += GAMEPLAY::GET_FRAME_TIME() / g_config.fCamLerpDuration;

        float fResult = 0.f;

        Math::smoothStep( 0.0f, 1.0f, fHorzLerpTime, fResult );

        Math::lerp( 0.0f, g_config.fCamLerpExtent, fResult, fLerpPosX );
    }

    if ( fForwardLerpTime < 1.f ) {

        fForwardLerpTime += GAMEPLAY::GET_FRAME_TIME() / g_config.fCamLerpDuration;

        float fResult = 0.f;

        Math::smoothStep( 0.0f, 1.0f, fForwardLerpTime, fResult );

        Math::lerp( 0.0f, g_config.fCamForwardLerpExtent, fResult, fLerpPosY );

        if ( fForwardLerpTime > 0.5f )
            fLerpPosY = g_config.fCamForwardLerpExtent - fLerpPosY;
    }
}

void mainLoop() {

    do {
        const auto player = PLAYER::PLAYER_ID();

        if ( PLAYER::IS_PLAYER_FREE_AIMING( player ) ) {

            lerpCameraFrame();

            if ( !metadata ) {
                metadata = getCamMetadataForHash( THIRD_PERSON_ONFOOT_AIM_METADATA );

                *reinterpret_cast<float*>( reinterpret_cast<uintptr_t>( metadata ) + Offsets::Get( "TPA_BoundingBoxPivotScaleOverride" ) ) = 1.f;
            }

            auto pVec = *reinterpret_cast<vec3_t*>( reinterpret_cast<uintptr_t>( metadata ) + Offsets::Get( "TPA_PivotPosition" ) );

            pVec[0] = bReverseLerp ? fLerpPosX - 0.7f : -fLerpPosX;

            pVec[1] = g_config.fCamYOffset + fLerpPosY;

            pVec[2] = g_config.fCamZOffset;
        }

        WAIT( 0 );
    }

    while ( bScriptRunning );
}

void loadConfig() {

    g_config.fCamYOffset = ConfigParser::GetFloat( "Camera", "ForwardOffset", g_config.fCamYOffset );

    g_config.fCamZOffset = ConfigParser::GetFloat( "Camera", "VerticalOffset", g_config.fCamZOffset );

    g_config.fCamLerpDuration = ConfigParser::GetFloat( "Camera", "LerpDuration", g_config.fCamLerpDuration );

    g_config.fCamLerpExtent = ConfigParser::GetFloat( "Camera", "LerpExtent", g_config.fCamLerpExtent );

    g_config.fCamForwardLerpExtent = ConfigParser::GetFloat( "Camera", "ForwardLerpExtent", g_config.fCamForwardLerpExtent );
}

void scriptMain() {

    const auto version = getGameVersion();

    if ( !Game::Initialize( version ) )
        return;

    Offsets::Insert( "TP_PivotPosition", version < VER_1_0_791_2_STEAM ? 232 : version < VER_1_0_944_2_STEAM ? 240 : version < VER_1_0_1290_1_STEAM ? 256 : version < VER_1_0_1365_1_STEAM ? 248 : 240 );

    Offsets::Insert( "TPA_PivotPosition", version < VER_1_0_791_2_STEAM ? 232 : version < VER_1_0_944_2_STEAM ? 240 : version < VER_1_0_1011_1_STEAM ? 256 : version < VER_1_0_1365_1_STEAM ? 248 : 240 );

    Offsets::Insert( "TPA_BoundingBoxPivotScaleOverride", 380 );

    mainLoop();
}

void scriptKeyboardEvent( DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow ) {

    if ( key == VK_F7 ) {
        if ( !wasDownBefore ) {
            fLerpPosX = 0.f;
            fHorzLerpTime = 0.f;
            fForwardLerpTime = 0.f;
            fLerpPosY = g_config.fCamYOffset;
            bReverseLerp = !bReverseLerp;
        }
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     ) {
    switch ( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH: {
        scriptRegister( hModule, scriptMain );
        keyboardHandlerRegister( scriptKeyboardEvent );
        break;
    }
    case DLL_PROCESS_DETACH: {
        scriptUnregister( hModule );
        keyboardHandlerUnregister( scriptKeyboardEvent );
        break;
    }
    }
    return TRUE;
}

