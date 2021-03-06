/* 
Copyright (C) 2011-2017 Robert DeSantis
hopluvr at gmail dot com

This file is part of DMX Studio.
 
DMX Studio is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.
 
DMX Studio is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
License for more details.
 
You should have received a copy of the GNU General Public License
along with DMX Studio; see the file _COPYING.txt.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA.
*/

#pragma once

#include "stdafx.h"
#include "StudioException.h"

#define LINK_BUFFER_LENGTH      (10*1024)    // Default buffer length for all link list requests

#define MAX_AUDIO_TEXT_LEN      256
#define MAX_LINK_SIZE           MAX_AUDIO_TEXT_LEN

#define PLAYED_PLAYLIST_LINK    "local:playlist:played"
#define QUEUED_PLAYLIST_LINK    "local:playlist:queued"

enum AudioStatus {
    FAILED = 0,                         // Request failed
    OK = 1,                             // Item processed
    QUEUED = 2,                         // Request queued
    NOT_AVAILABLE = 3                   // Resource is not available
};

struct AnalyzeInfo {
    char        link[256];
    UINT        duration_ms;            // Duration of each data point
    size_t      data_count;             // Number of data points
    uint16_t    data[1];                // Amplitude data (0 = 32767)
};

struct PlayerInfo {
	char        player_type[MAX_AUDIO_TEXT_LEN];
	char        player_name[MAX_AUDIO_TEXT_LEN];
	char        player_authorization[2048];
    char        player_authorization_url[512];
};

enum PlayerEvent {
    TRACK_PLAY = 1,                     // Track play start
    TRACK_STOP = 2,                     // Track stopped
    TRACK_PAUSE = 3,                    // Track paused
    TRACK_RESUME = 4,                   // Track resumed
    TRACK_POSITION = 5,                 // Track position,
    TRACK_QUEUES = 6,                   // Track queues changed
    PLAYLIST_ADDED = 7,                 // New playlist added
    PLAYLIST_REMOVED = 8,               // Playlist removed
    PLAYLIST_CHANGED = 9                // Playlist changed (tracks, name, etc)
};

struct PlayerEventData {
    PlayerEvent m_event;
    ULONG       m_event_ms;
    LPCSTR      m_link;
    ULONG       m_played_size;
    ULONG       m_queued_size;
};

class IPlayerEventCallback
{
public:
    virtual HRESULT STDMETHODCALLTYPE notify( PlayerEventData* pNotify ) = 0;
};

struct PlayerImage {
	char		m_href[MAX_LINK_SIZE];
	UINT		m_height;
	UINT		m_width;

	PlayerImage( LPCSTR href, UINT height, UINT width ) :
		m_height( height ),
		m_width( width )
	{
		strncpy_s( m_href, MAX_LINK_SIZE, href, strlen(href) );
	}

	PlayerImage() :
		m_height( 0 ),
		m_width( 0 )
	{
		m_href[0] = '\0';
	}
};

struct PlayingInfo {
	char        track_link[MAX_LINK_SIZE];
	DWORD       track_length;
	DWORD       time_remaining;
	UINT        queued_tracks;
	UINT        previous_tracks;
};

struct TrackInfo {
	char        track_link[MAX_LINK_SIZE];
	char        track_name[MAX_AUDIO_TEXT_LEN];
	char        artist_name[MAX_AUDIO_TEXT_LEN];
	char        album_name[MAX_AUDIO_TEXT_LEN];
	PlayerImage	image[3];
	DWORD       track_duration_ms;
};

struct PlaylistInfo {
	char        playlist_link[MAX_LINK_SIZE];
	char        playlist_name[MAX_AUDIO_TEXT_LEN];
	UINT        playlist_tracks;
};

struct AudioInfo {
	char        track_link[MAX_LINK_SIZE];
	char        id[MAX_LINK_SIZE];
	char        song_type[MAX_AUDIO_TEXT_LEN];  // Comman separated list of 'christmas', 'live', 'studio', 'acoustic' and 'electric'
	int         key;                            // Key of song C,C#,D,D#,E,F,F#,G,B#,B,B#,B (0-11)
	int         mode;                           // 0=minor, 1=major
	int         time_signature;                 // beats per measure
	double      energy;                         // 0.0 < energy < 1.0
	double      liveness;                       // 0.0 < liveness < 1.0
	double      tempo;                          // 0.0 < tempo < 500.0 (BPM)
	double      speechiness;                    // 0.0 < speechiness < 1.0
	double      acousticness;                   // 0.0 < acousticness < 1.0
	double      instrumentalness;
	double      duration;                       // Duration of the track
	double      loudness;                       // -100.0 < loudness < 100.0 (dB)
	double      valence;                        // Emotion 0=negative to 1=positive
	double      danceability;                   // 0.0 < danceability < 1.0
};

typedef DWORD (__cdecl *GetPlayerApiVersion)( void );
typedef bool (__cdecl *GetPlayerInfo)( PlayerInfo* player_info );
typedef bool (__cdecl *Connect)( void );
typedef bool (__cdecl *Disconnect)( void );
typedef bool (__cdecl *RegisterEventListener)( IPlayerEventCallback* listener );
typedef bool (__cdecl *UnregisterEventListener)( IPlayerEventCallback* listener );
typedef bool (__cdecl *Signon)( LPCSTR username, LPCSTR password );
typedef bool (__cdecl *AcceptAuthorization)( LPBYTE authorization_response, DWORD authorization_len );
typedef bool (__cdecl *GetPlaylists)( UINT* num_lists, LPSTR playlist_links, size_t buffer_length );
typedef bool (__cdecl *GetPlaylistInfo)( LPCSTR playlist_link, PlaylistInfo* playlist_info );
typedef bool (__cdecl *GetTracks)( LPCSTR playlist_link, UINT* num_tracks, LPSTR track_links, size_t buffer_length );
typedef bool (__cdecl *SearchTracks)( LPCSTR search_query, UINT* num_tracks, LPSTR track_links, size_t buffer_length );
typedef bool (__cdecl *PlayTrack)( LPCSTR track_link, DWORD seek_ms );
typedef bool (__cdecl *QueueTrack)( LPCSTR track_link );
typedef bool (__cdecl *PlayAllTracks)( LPCSTR playlist_link, bool queue );
typedef bool (__cdecl *ForwardTrack)( void );
typedef bool (__cdecl *BackTrack)( void );
typedef bool (__cdecl *StopTrack)( void );
typedef bool (__cdecl *PauseTrack)( bool pause );
typedef bool (__cdecl *GetPlayingTrack)( PlayingInfo* playing_info );
typedef bool (__cdecl *IsTrackPaused)( void );
typedef bool (__cdecl *IsLoggedIn)( void );
typedef bool (__cdecl *GetQueuedTracks)( UINT* num_tracks, LPSTR track_links, size_t buffer_length );
typedef bool (__cdecl *GetPlayedTracks)( UINT* num_tracks, LPSTR track_links, size_t buffer_length );
typedef bool (__cdecl *GetLastPlayerError)( LPSTR buffer, UINT buffer_length );
typedef bool (__cdecl *WaitOnTrackEvent)( DWORD wait_ms, LPSTR track_link, bool* paused );
typedef bool (__cdecl *GetTrackInfo)( LPCSTR track_link, TrackInfo* track_info );
typedef AudioStatus (__cdecl *GetTrackAudioInfo)( LPCSTR track_link, AudioInfo* audio_info, DWORD wait_ms );
typedef bool (__cdecl *GetTrackAnalysis)( LPCSTR track_link, AnalyzeInfo** analysis_info );

typedef std::vector<CString> PlayerItems;

class MusicPlayer
{
    CString                 m_dll_path;
    CString                 m_username;

    HMODULE                 m_library;
    bool                    m_logged_in;

	PlayerInfo				m_player_info;

    // DLL function pointers
    GetPlayerInfo           m_GetPlayerInfo;
    Connect                 m_Connect;
    Disconnect              m_Disconnect;
    RegisterEventListener   m_RegisterEventListener;
    UnregisterEventListener m_UnregisterEventListener;
    Signon                  m_Signon;
	AcceptAuthorization		m_AcceptAuthorization;
    GetPlaylists            m_GetPlaylists;
    GetPlaylistInfo         m_GetPlaylistInfo;
    GetTracks               m_GetTracks;
	SearchTracks            m_SearchTracks;
    QueueTrack              m_QueueTrack;
    PlayAllTracks           m_PlayAllTracks;
    ForwardTrack            m_ForwardTrack;
    BackTrack               m_BackTrack;
    StopTrack               m_StopTrack;
    PauseTrack              m_PauseTrack;
    GetPlayingTrack         m_GetPlayingTrack;
    IsTrackPaused           m_IsTrackPaused;
    GetTrackInfo            m_GetTrackInfo;
    GetTrackAudioInfo       m_GetTrackAudioInfo;
    IsLoggedIn              m_IsLoggedIn;
    GetQueuedTracks         m_GetQueuedTracks;
    GetPlayedTracks         m_GetPlayedTracks;
    GetLastPlayerError      m_GetLastPlayerError;
    WaitOnTrackEvent        m_WaitOnTrackEvent;
    PlayTrack               m_PlayTrack;
    GetTrackAnalysis        m_GetTrackAnalysis;

public:
    MusicPlayer( LPCSTR library_path, LPCSTR username );
    ~MusicPlayer(void);

    void initialize( );

    template <class T>
    T getAddress( LPCSTR function_name ) {
        T funcptr = (T) GetProcAddress( m_library, function_name );
        STUDIO_ASSERT( funcptr, "Music controller '%s' missing '%s()'", function_name, m_dll_path );
        return funcptr;
    }

    LPCSTR getUsername() const {
        return m_username;
    }

    inline bool isLoaded() const {
        return m_library != NULL;
    }

	inline LPCSTR getPlayerName( void ) {
		return m_player_info.player_name;
	}

	inline LPCSTR getPlayerType( void ) {
		return m_player_info.player_type;
	}

	inline LPCSTR getPlayerAuthorization( void ) {
		return m_player_info.player_authorization;
	}

    inline LPCSTR getPlayerAuthorizationURL( void ) {
        return m_player_info.player_authorization_url;
    }

    bool connect( void );
    bool disconnect( void );    
	bool registerEventListener( IPlayerEventCallback* listener );
    bool unregisterEventListener( IPlayerEventCallback* listener );
	bool getPlayerInfo( PlayerInfo* player_info );
    bool signon( LPCSTR username, LPCSTR password );
	bool acceptAuthorization( LPBYTE authorization_response, DWORD authorization_len );

    bool getPlaylists( PlayerItems& playlists );
    bool getTracks( LPCSTR playlist_link, PlayerItems& tracks );
	bool searchTracks( LPCSTR search_query, PlayerItems& tracks );
    bool getQueuedTracks( PlayerItems& queued_tracks );
    bool getPlayedTracks( PlayerItems& queued_tracks );
    bool getPlaylistInfo( LPCSTR playlist_link, PlaylistInfo* playlist_info );
    CString getTrackFullName( LPCSTR track_link );
    bool playAllTracks( LPCSTR playlist_link, bool queue );
    bool playTrack( LPCSTR track_link, DWORD seek_ms );
    bool queueTrack( LPCSTR track_link );
    bool forwardTrack( void );
    bool backTrack( void );
    bool stopTrack( void );
    bool pauseTrack( bool pause );
    bool isLoggedIn( void );
    bool isTrackPaused( void );
    AudioStatus getTrackAudioInfo( LPCSTR track_link, AudioInfo* audio_info, DWORD wait_ms );
    bool getPlayingTrack( PlayingInfo* playing_info );
    CString getLastPlayerError( void );
    bool waitOnTrackEvent( DWORD wait_ms, CString& track_link, bool* paused );
    bool getTrackInfo( LPCSTR track_link, TrackInfo* track_info );
    bool getTrackAnalysis( LPCSTR track_link, AnalyzeInfo** info );
};
