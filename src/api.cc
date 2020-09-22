/**
 * \file
 * \brief Api main class implementation.
 */
#include "api.h"

#include "access_listener.h"
#include "create_playlist_listener.h"
#include "search_music_listener.h"

namespace espotifai_api {

Api::Api(const std::shared_ptr<SpotifyAuth> &auth,
         const std::shared_ptr<MusicSearcher> &searcher,
         const std::shared_ptr<PlaylistMgr> &mgr)
    : sptf_auth_{auth ? auth : std::make_shared<SpotifyAuth>()},
      sptf_searcher_{searcher ? searcher : std::make_shared<MusicSearcher>()},
      playlist_mgr_{mgr ? mgr : std::make_shared<PlaylistMgr>()}
{
}

void Api::RequestAccess(AccessListener &listener, const std::string &client_id,
    const std::string &client_secret) const
{
    // TODO: make it async?

    try {
        auto token = sptf_auth_->AuthUser(client_id, client_secret);

        listener.OnAccessGuaranteed(token);
    } catch(const std::exception &e) {
        listener.OnAccessDenied(e.what());
    }
}

void Api::SearchMusic(SearchMusicListener &listener, const std::string &token,
    const std::string &name) const
{
    // TODO: make it async?

    try {
        auto musics = sptf_searcher_->Search(token, name);

        listener.OnMusicFound(musics);
    } catch(const std::exception &e) {
        listener.OnMusicSearchError(e.what());
    }
}

void Api::CreatePlaylist(CreatePlaylistListener &listener, const std::string &name,
    const std::string &owner) const
{
    // TODO: make it async?

    try {
        playlist_mgr_->Create(name, owner);

        listener.OnPlaylistCreated();
    } catch(const std::exception &e) {
        listener.OnPlaylistCreationError(e.what());
    }
}

}  // namespace espotifai_api
