#include "stdafx.h"

std::map<std::string, uintptr_t> Offsets::m_mapOffsets;

uintptr_t Offsets::Get( const std::string name ) {

    return m_mapOffsets[name];
}

void Offsets::Insert( const std::string name, const uintptr_t offset ) {

    m_mapOffsets[name] = offset;
}
