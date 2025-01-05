struct {
    bool space = false;
} keys;

void DestroyPipe(int index) {
    auto p = pipes[index];
    pipes.erase(pipes.begin() + index);

    delete p.first;
    delete p.second;
}

void Restart() {
    bird->y = WINDOW_WIDTH / 2;
    bird->rotation = 0;

    score = 0;
    ticks = 0;
    gravity = 5;

    for (int i = pipes.size() - 1 ; i >= 0 ; i--) {
        DestroyPipe(i);
    }

    started = 0;
    running = 1;
    end_screen = 0;
}

void CheckEvents() {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            if (!started) {
                started = true;

                Mix_PlayMusic(audio["song.wav"], -1);
            }
            
            keys.space = true;
        }
    }

    else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            keys.space = false;
        }

        else if (event.key.keysym.sym == SDLK_RETURN && end_screen) {
            Restart();
        }
    }
}