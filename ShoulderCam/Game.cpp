#include "stdafx.h"
#include "Game.h"

using namespace Utility;

eGameState * Game::m_pGameState = nullptr;

rage::pgCollection<camBaseDirector*> * Game::m_pCamDirectorPool = nullptr;

rage::pgCollection<camMetadataRef*> * Game::m_pCamMetadataPool = nullptr;

bool Game::Initialize( eGameVersion version ) {

    uintptr_t result;

    #pragma region Game State

    // get pointer to game state..
    auto patternResult = BytePattern( ( BYTE* )"\x0F\x29\x74\x24\x00\x85\xDB", "xxxx?xx" );

    if ( patternResult.size() ) {

        result = ( uintptr_t )patternResult.get().get();

        LOG( "Game state found at 0x%llX", result );
    }

    else {
        LOG( "[ERROR] Failed to find game state" );
        return false;
    }

    m_pGameState = reinterpret_cast<eGameState*>( *reinterpret_cast<int *>( result - 4 ) + result );

    #pragma endregion


    #pragma region Cam Metadata Pool

    patternResult = BytePattern( ( BYTE* )"\x88\x50\x41\x48\x8B\x47\x40", "xxxxxxx" );

    if ( patternResult.size() ) {

        result = ( uintptr_t )patternResult.get().get( -0x30 );

        LOG( "CamMetadataPool found at 0x%llX", result );
    }

    else {
        LOG( "[ERROR] Failed to find CamMetadataPool" );
        return false;
    }

    result = *reinterpret_cast<int *>( result - 4 ) + result + 6;

    m_pCamMetadataPool = reinterpret_cast<rage::pgCollection<camMetadataRef*>*>( ( *reinterpret_cast<int *>( result + 3 ) + result - 1 ) );

    #pragma endregion

    return true;
}
