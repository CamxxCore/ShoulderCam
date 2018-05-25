#pragma once
class Game {
    static eGameState * m_pGameState;
    static rage::pgCollection<camBaseDirector*> * m_pCamDirectorPool;
    static rage::pgCollection<camMetadataRef*> * m_pCamMetadataPool;
  public:
    static bool Initialize( eGameVersion version );

    static decltype( m_pCamDirectorPool ) GetCamDirectorPool() {
        return m_pCamDirectorPool;
    }

    static decltype( m_pCamMetadataPool ) GetCamMetadataPool() {
        return m_pCamMetadataPool;
    }
};

