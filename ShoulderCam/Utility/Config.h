#pragma once
#include <sstream>

namespace Utility {
class CConfig {
    const std::string m_filename;
  public:
    CConfig( std::string fileName ) : m_filename( fileName ) {}
    CConfig() : CConfig( GetWorkingDirectory() + GetModuleName( nullptr ) + ".ini" ) { }

    template<unsigned int _Size>
    bool getText( char( &outBuffer )[_Size], const char * section, const char * key ) const {

        GetPrivateProfileString( TEXT( section ),
                                 TEXT( key ),
                                 nullptr,
                                 outBuffer,
                                 _Size,
                                 TEXT( m_filename.c_str() ) );

        return *outBuffer != '\0' &&
               GetLastError() == ERROR_SUCCESS;
    }

    void setText( const char * section, const char * key, const char * value ) const {

        WritePrivateProfileString( TEXT( section ),
                                   TEXT( key ),
                                   TEXT( value ),
                                   m_filename.c_str() );
    }

    std::string getPath() {
        return m_filename;
    }
};
}
