unordered_map<string, SDL_Texture*> assets;
unordered_map<string, Mix_Music*> audio;

void LoadImage(const string& src) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ("assets\\" + src).c_str());
                    
    if (!texture) {
        ERROR("Failed to load image: " + src);
    }
    
    assets[src] = texture;
}

void LoadMusic(const string& src) {
    Mix_Music* music = Mix_LoadMUS(("assets\\" + src).c_str());

    if (music == nullptr) {
        ERROR("Failed to load audio: " + src);
    }

    audio[src] = music;
}