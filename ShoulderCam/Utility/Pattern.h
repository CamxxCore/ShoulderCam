#pragma once
#include <Psapi.h>
#include <future>

namespace Utility {
template <typename T>
class PatternMatch {
  public:
    uintptr_t result;

    PatternMatch( const uintptr_t addr ) : result( addr ) {};

    T get( int offset = 0 ) {
        return reinterpret_cast<T>( result + offset );
    }

    T getTargetRel5( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 1 ) + addr + 5;
    }

    T getCall( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 1 ) + addr + 5;
    }

    T getTargetRel6( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 2 ) + addr + 6;
    }

    T getTargetRel7( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 3 ) + addr + 7;
    }

    T getCmp( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 2 ) + addr + 7;
    }

    T getCmp2( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 3 ) + addr + 8;
    }

    T getTargetRel8( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 4 ) + addr + 8;
    }

    T getTargetRel9( int offset = 0 ) {
        auto addr = reinterpret_cast<T>( result + offset );
        return *reinterpret_cast<int32_t*>( addr + 5 ) + addr + 9;
    }
};

template <typename T>
class Pattern {
    char m_patternData[64];
    char m_dataStrMask[64];
    std::string m_moduleName;
    bool m_bFindAllMatches;
    std::vector<PatternMatch<T>> m_vecMatches;

    void search() {
        MODULEINFO module = {};

        GetModuleInformation( GetCurrentProcess(), GetModuleHandle( m_moduleName[0] == '\0' ? nullptr : m_moduleName.c_str() ), &module, sizeof( MODULEINFO ) );

        auto address = reinterpret_cast<BYTE*>( module.lpBaseOfDll );

        const auto address_end = address + module.SizeOfImage;

        for ( ; address < address_end; address++ ) {
            if ( bCompare( address, reinterpret_cast<PBYTE>( m_patternData ), m_dataStrMask ) ) {
#ifdef _DEBUG
                LOG( "PatternSearch: Found match (%s : %s) @ %p",
                     HexString( reinterpret_cast<PBYTE>( m_patternData ), static_cast<int>( strlen( m_dataStrMask ) ) ).c_str(), m_dataStrMask, address );
#endif
                m_vecMatches.push_back( PatternMatch<T>( reinterpret_cast<uintptr_t>( address ) ) );

                if ( !m_bFindAllMatches ) return;
            }
        }
#ifdef _DEBUG
        if ( m_vecMatches.empty() )
            LOG( "PatternSearch: failed to find address in module (%s : %s)",
                 HexString( reinterpret_cast<PBYTE>( m_patternData ), static_cast<int>( strlen( m_dataStrMask ) ) ).c_str(), m_dataStrMask );
#endif
    }

    static void convert( const char * idaPattern, char * outBytes, char * outMask ) {
        int i = 0;
        auto str = &idaPattern[0];
        while ( *str != 0 ) {
            if ( *str != ' ' ) {
                if ( *str == '?' ) {
                    outBytes[i] = '\x00';
                    outMask[i] = *str;
                    //while (*str == '?')
                    //	str++;
                } else {
                    outBytes[i] = ctol( *str ) * 16 + ctol( str[1] );
                    outMask[i] = 'x';
                    str++;
                }

                i++;
            }
            str++;
        }

        outMask[i] = '\0';
    }

    static bool bCompare( const BYTE* pData, const BYTE* bMask, const char* szMask ) {
        for ( ; *szMask; ++szMask, ++pData, ++bMask )
            if ( *szMask == 'x' && *pData != *bMask )
                return false;
        return ( *szMask ) == NULL;
    }

  public:
    Pattern( const BYTE* bMask, const char* szMask, const bool findAllMatches = false ) : m_bFindAllMatches( findAllMatches ) {
        m_moduleName = std::string();
        memcpy( m_patternData, bMask, sizeof( m_patternData ) );
        strncpy( m_dataStrMask, szMask, sizeof( m_dataStrMask ) );
        search();
    }

    Pattern( const std::string& patternString, const bool findAllMatches = false ) : m_bFindAllMatches( findAllMatches ) {
        m_moduleName = std::string();
        convert( patternString.c_str(), m_patternData, m_dataStrMask );
        search();
    }

    Pattern( const std::string& patternString, const std::string& moduleName, const bool findAllMatches = false ) : m_bFindAllMatches( findAllMatches ) {
        m_moduleName = moduleName;
        convert( patternString.c_str(), m_patternData, m_dataStrMask );
        search();
    }


    PatternMatch<T> first() {
        return m_vecMatches.size() > 0 ? m_vecMatches.at( 0 ) : 0;
    }

    PatternMatch<T> get( int index = 0 ) {
        return m_vecMatches.size() > index ? m_vecMatches.at( index ) : 0;
    }

    size_t size() {
        return m_vecMatches.size();
    }
};

class BytePattern : public Pattern<BYTE*> {
  public:
    BytePattern( const BYTE* bMask, const char* szMask, const bool findAllMatches = false ) :
        Pattern<BYTE*>( bMask, szMask, findAllMatches ) {}

    BytePattern( const std::string& patternString, const bool findAllMatches = false ) :
        Pattern<BYTE*>( patternString, findAllMatches ) {}

    BytePattern( const std::string& patternString, const char * moduleName, const bool findAllMatches = false ) :
        Pattern<BYTE*>( patternString, moduleName, findAllMatches ) {}
};
}
