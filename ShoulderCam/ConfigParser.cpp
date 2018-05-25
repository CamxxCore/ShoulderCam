#include "stdafx.h"
#include "ConfigParser.h"
#include <iomanip>

static Utility::CConfig g_configFile;

static char g_charBuffer[0x200];

void ConfigParser::WriteText( const std::string & section, const std::string & key, std::string & text ) {

    g_configFile.setText( section.c_str(), key.c_str(), text.c_str() );
}

void ConfigParser::WriteBool( const std::string & section, const std::string & key, bool b ) {

    std::ostringstream sstream;
    sstream << std::boolalpha << b;
    auto result = sstream.str();
    WriteText( section, key, result );
}

void ConfigParser::WriteInt( const std::string & section, const std::string & key, int value ) {

    std::ostringstream sstream;
    sstream << value;
    auto result = sstream.str();
    WriteText( section, key, result );
}

void ConfigParser::WriteFloat( const std::string & section, const std::string & key, float value ) {

    std::ostringstream sstream;
    sstream.imbue( std::locale( "en-us" ) );
    sstream << value;
    auto result = sstream.str();
    WriteText( section, key, result );
}

void ConfigParser::WriteColor( const std::string & section, const std::string & key, color_s color ) {

    std::ostringstream sstream;
    sstream << std::hex << std::setw( 8 );
    sstream << std::setfill( '0' ) << _byteswap_ulong( color.rgba );
    auto result = sstream.str();
    WriteText( section, key, result );
}

bool ConfigParser::GetBool( const std::string & section, const std::string & key, const bool defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    bool result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> std::boolalpha >> result;
    return result;
}

int32_t ConfigParser::GetInt( const std::string & section, const std::string & key, const int32_t defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    int32_t result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> result;
    return result;
}

uint32_t ConfigParser::GetUInt( const std::string & section, const std::string & key, const uint32_t defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;
    uint32_t result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> result;
    return result;
}

int64_t ConfigParser::GetInt64( const std::string & section, const std::string & key, const int64_t defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    int64_t result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> result;
    return result;
}

uint64_t ConfigParser::GetUInt64( const std::string & section, const std::string & key, uint64_t defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    uint64_t result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> result;
    return result;
}

float ConfigParser::GetFloat( const std::string & section, const std::string & key, const float defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    float result;
    std::stringstream sstream;
    sstream << g_charBuffer;
    sstream >> result;
    return result;
}

color_s ConfigParser::GetColor( const std::string & section, const std::string & key, const color_s defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    int r, g, b;
    sscanf( g_charBuffer, "%02x%02x%02x", &r, &g, &b );

    return color_s( r, g, b );
}

std::string ConfigParser::GetText( const std::string & section, const std::string & key, const std::string & defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    return g_charBuffer;
}

uint32_t ConfigParser::GetKey( const std::string& section, const std::string& key, uint32_t defaultValue ) {

    if ( !g_configFile.getText( g_charBuffer, section.c_str(), key.c_str() ) )
        return defaultValue;

    if ( _stricmp( g_charBuffer, "none" ) != 0 )
        return defaultValue;

    return keyFromString( g_charBuffer, defaultValue );
}
