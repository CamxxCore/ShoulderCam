#pragma once
class ConfigParser {
  public:
    static void WriteBool( const std::string & section, const std::string & key, bool b );
    static void WriteInt( const std::string & section, const std::string & key, int value );
    static void WriteFloat( const std::string & section, const std::string & key, float value );
    static void WriteColor( const std::string & section, const std::string & key, color_s color );
    static void WriteText( const std::string & section, const std::string & key, std::string & text );
    static bool GetBool( const std::string & section, const std::string & key, bool defaultValue = false );
    static int32_t GetInt( const std::string & section, const std::string & key, int32_t defaultValue = 0 );
    static uint32_t GetUInt( const std::string & section, const std::string & key, uint32_t defaultValue = 0 );
    static int64_t GetInt64( const std::string & section, const std::string & key, int64_t defaultValue = 0 );
    static uint64_t GetUInt64( const std::string & section, const std::string & key, uint64_t defaultValue = 0 );
    static float GetFloat( const std::string & section, const std::string & key, float defaultValue = 0 );
    static color_s GetColor( const std::string & section, const std::string & key, color_s defaultValue = 0 );
    static std::string GetText( const std::string & section, const std::string & key, const std::string & defaultValue = "" );
    static uint32_t GetKey( const std::string & section, const std::string & key, uint32_t defaultValue = 0 );
};
