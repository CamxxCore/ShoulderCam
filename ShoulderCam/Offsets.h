#pragma once
#include <string>
#include <map>

class Offsets {
    static eGameVersion m_GameVersion;

    static std::map<std::string, uintptr_t> m_mapOffsets;

  public:
    static eGameVersion GetVersion() {
        return m_GameVersion;
    }

    static uintptr_t Get( std::string name );

    static void Insert( std::string name, uintptr_t offset );
};