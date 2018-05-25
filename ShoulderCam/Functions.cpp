#include "stdafx.h"

void notifyAboveMap( char * message ) {

    UI::_SET_NOTIFICATION_TEXT_ENTRY( "STRING" );
    UI::_ADD_TEXT_COMPONENT_STRING( message );
    UI::_DRAW_NOTIFICATION( 0, 0 );
}

void showSubtitle( const char * msg, const int duration ) {

    UI::_SET_TEXT_ENTRY_2( "CELL_EMAIL_BCON" );

    const unsigned int maxStringLength = 99;

    char subStr[maxStringLength];

    for ( unsigned int i = 0; i < strlen( msg ) + 1; i += maxStringLength ) {
        memcpy_s( subStr, sizeof( subStr ), &msg[i], min( maxStringLength - 1, strlen( msg ) + 1 - i ) );

        subStr[maxStringLength - 1] = '\0';

        UI::_ADD_TEXT_COMPONENT_STRING( subStr );
    }

    UI::_DRAW_SUBTITLE_TIMED( duration, 1 );
}

camBaseObjectMetadata * getCamMetadataForHash( const unsigned int hashName ) {

    auto metadataPool = Game::GetCamMetadataPool();

    for ( auto it = metadataPool->begin(); it != metadataPool->end(); it++ ) {
        if ( !it ) continue;

        for ( auto ref = *it; ref; ref = ref->pNext ) {
            if ( !ref->pData ) continue;

            if ( ref->pData->hashKey == hashName )
                return ref->pData;
        }
    }

    return nullptr;
}
