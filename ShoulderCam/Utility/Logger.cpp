#include "stdafx.h"

static char g_logBuffer[4000];

namespace Utility {
Logger::Logger() : path( GetModuleName( nullptr ) + ".log" )
{ }

void Logger::Write( const char * format, ... ) const {

    va_list va;
    va_start( va, format );
    vsprintf_s( g_logBuffer, format, va );
    va_end( va );

    std::ofstream ofs( path, std::ios::app );

    const auto str = FormatString( "[%s] [LOG] %s\n", GetShortTimeString().c_str(), g_logBuffer );

    ofs << str;

    ofs.close();

#ifdef _DEBUG
    OutputDebugStringA( str.c_str() );
#endif
}

void Logger::Remove() const {

    if ( !FileExists( path ) ) return;

    remove( path.c_str() );
}

Logger::~Logger() {

    Remove();
}
}
