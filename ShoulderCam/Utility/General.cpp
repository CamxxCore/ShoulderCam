#include "stdafx.h"
#include <iomanip>
#include <sstream>

HMODULE Utility::GetActiveModule() {

    HMODULE hModule = nullptr;

    GetModuleHandleEx( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCSTR>( &GetActiveModule ),
                       &hModule );

    return hModule;
}

std::string Utility::GetModuleName( HMODULE hModule ) {

    TCHAR inBuf[MAX_PATH];

    if ( !hModule )
        hModule = GetActiveModule();

    GetModuleFileName( hModule, inBuf, MAX_PATH );

    auto str = std::string( inBuf );

    auto seperator = str.find_last_of( "\\" );

    if ( seperator != std::string::npos )
        seperator += 1;

    return str.substr( seperator, str.find_last_of( "." ) - seperator );
}

std::string Utility::GetWorkingDirectory() {

    const auto hModule = GetActiveModule();

    TCHAR inBuf[MAX_PATH];

    GetModuleFileName( hModule, inBuf, MAX_PATH );

    auto str = std::string( inBuf );

    auto seperator = str.find_last_of( "\\" );

    if ( seperator != std::string::npos )
        seperator += 1;

    return str.substr( 0, seperator );
}

std::vector<std::string> Utility::TokenizeString( std::string& string, char delimiter ) {

    std::vector<std::string> result;

    auto str = string.c_str();

    do {
        const char *begin = str;

        while ( *str != delimiter && *str )
            str++;

        result.push_back( std::string( begin, str ) );

    } while ( 0 != *str++ );

    return result;
}

std::string Utility::TrimString( std::string& string ) {

    string.erase( 0, string.find_first_not_of( ' ' ) );
    string.erase( string.find_last_not_of( ' ' ) + 1 );
    string.erase( 0, string.find_first_not_of( '\x1F' ) );
    string.erase( string.find_last_not_of( '\x1F' ) + 1 );

    return string;
}

bool Utility::FileExists( const std::string& fileName ) {

    std::ifstream infile( fileName );

    return infile.good();
}

bool Utility::ModuleExists( const std::string & moduleName ) {

    return GetModuleHandleA( moduleName.c_str() ) != nullptr;
}

std::string Utility::VectorString( const float * vector, int size ) {

    std::stringstream ss;

    for ( auto i = 0; i < size; i++ ) {
        ss << vector[i];
        if ( i < size - 1 )
            ss << ", ";
    }

    return ss.str();
}

std::string Utility::HexString( BYTE * data, int len ) {

    std::stringstream ss;

    for ( int i = 0; i < len; ++i ) {
        ss << "\\x" <<
           std::uppercase <<
           std::setfill( '0' ) <<
           std::setw( 2 ) <<
           std::hex << static_cast<int>( data[i] );
    }

    return ss.str();
}

std::string Utility::GetShortTimeString() {

    time_t t = time( nullptr );

    struct tm timeinfo;

    localtime_s( &timeinfo, &t );

    return FormatString( "%02d:%02d:%02d",
                         timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec );
}

std::string Utility::GetShortDateString() {

    time_t t = time( nullptr );

    struct tm timeinfo;

    localtime_s( &timeinfo, &t );

    return FormatString( "%02d:%02d:%02d",
                         timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year - 100 );
}

std::string Utility::GetFilenameWithoutPath( std::string & string, bool removeExtension ) {

    auto pos = string.find_last_of( "/\\" );

    if ( pos == std::string::npos ) return string;

    pos += 1;

    return string.substr( pos, ( removeExtension ?
                                 string.find_first_of( '.' ) : string.length() ) - pos );
}

void Utility::CreateFolderTree( const std::string& s, const char delimiter ) {
    std::stringstream ss( s );
    std::string item;
    char combinedName[50] = { '\0' };
    while ( std::getline( ss, item, delimiter ) ) {
        sprintf( combinedName, "%s%s%c", combinedName, item.c_str(), delimiter );
        struct stat st = { 0 };
        if ( stat( combinedName, &st ) == -1 ) {
            CreateDirectoryA( combinedName, nullptr );
        }
    }
}

int Utility::ctol( const char c ) {

    if ( c >= '0' && c <= '9' )
        return c - '0';
    if ( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
    if ( c >= 'a' && c <= 'f' )
        return c - 'a' + 10;
    throw std::invalid_argument( "Invalid input string" );
}

bool Utility::PasteToClipboard( const std::string & text ) {

    bool succeeded = false;

    if ( const auto clipdata = GlobalAlloc( GMEM_FIXED, text.length() + 1 ) ) {
        std::memcpy( clipdata, text.data(), text.length() + 1 );

        if ( OpenClipboard( nullptr ) ) {
            if ( EmptyClipboard() && SetClipboardData( CF_TEXT, clipdata ) )
                succeeded = true;

            CloseClipboard();
        }

        if ( !succeeded )
            GlobalFree( clipdata );
    }

    return succeeded;
}
