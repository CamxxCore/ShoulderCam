#pragma once

void notifyAboveMap( char* message );

void showSubtitle( const char * msg, int duration = 5000 );

camBaseObjectMetadata* getCamMetadataForHash( unsigned int hashName );
