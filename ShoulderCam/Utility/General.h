#pragma once

namespace Utility {
HMODULE GetActiveModule();

std::string GetModuleName( HMODULE hModule );

std::string GetWorkingDirectory();

std::vector<std::string> TokenizeString( std::string& string, char delimiter = ' ' );

std::string TrimString( std::string& string );

std::string VectorString( const float * vector, int size );

std::string HexString( BYTE * data, int len );

std::string GetShortTimeString();

std::string GetShortDateString();

std::string GetFilenameWithoutPath( std::string& string, bool removeExtension = false );

void CreateFolderTree( const std::string& s, char delimiter );

bool FileExists( const std::string& fileName );

bool ModuleExists( const std::string& moduleName );
/**
* \brief char to long integer
*/
int ctol( char c );

bool PasteToClipboard( const std::string& text );

template<typename ... Args>
std::string FormatString( const std::string& format, Args ... args ) {
    const size_t size = ::snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    std::unique_ptr<char[]> buf( new char[size] );
    snprintf( buf.get(), size, format.c_str(), args... );
    return std::string( buf.get(), buf.get() + size - 1 );
}
}