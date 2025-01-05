string Replace(string str, const string& a, const string& b) {
    size_t pos = str.find(a);

    if (pos != string::npos) {
        str.replace(pos, a.size(), b);
    }

    return str;
}

void RenderText(const string& text, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(
        font, text.c_str(), 
        SDL_Color{ 255, 255, 255, 255 }, 
        WINDOW_WIDTH
    );

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect bounds = { x, y, surface->w, surface->h };

    SDL_RenderCopy(renderer, texture, NULL, &bounds);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}