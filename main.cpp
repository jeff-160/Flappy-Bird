#include "include.hpp"

void Init() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    SDL_Init(SDL_INIT_VIDEO);

    LoadMusic("song.wav");

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("assets/font.ttf", 30);

    if (!font) {
        ERROR("failed to load font");
    }

    srand((unsigned) time(NULL));
}

void SpawnPipe() {
    const int width = 80, height = WINDOW_WIDTH / 2;

    const int max = 50;

    Sprite* up_pipe = new Sprite("pipe.png", WINDOW_WIDTH, 0, width, std::max(height, height + RandInt(-max, max)));

    const int down_y = up_pipe->height + RandInt(130, 200);
    Sprite* down_pipe = new Sprite("pipe.png", WINDOW_WIDTH, down_y, width, std::max(height, WINDOW_WIDTH - down_y));

    up_pipe->rotation = M_PI;

    pipes.push_back({ up_pipe, down_pipe });
}

void RenderScene() {
    if (end_screen) {
        RenderText("Score: " + to_string(score), WINDOW_WIDTH / 2 - 70, WINDOW_WIDTH / 2 - 30);
        RenderText("Press ENTER to restart", WINDOW_WIDTH / 4, WINDOW_WIDTH / 2 + 30);
    }
    
    else {
        background->Render();

        for (auto pipe_pair : pipes) {
            pipe_pair.first->Render();
            pipe_pair.second->Render();
        }

        bird->Render();

        RenderText("Score: " + to_string(score), 10, 10);
    }

    SDL_RenderPresent(renderer);
}

void Lose() {
    running = 0;

    Mix_FadeOutMusic(1000);

    Threading::RunAsync([]() {
        Threading::Delay(1000);

        end_screen = 1;
    });
}

void Bobble() {
    const float freq = 0.1;
    const int amp = 10;
    
    bird->y = WINDOW_WIDTH / 2 + amp * sin(freq * ticks);
}

void GameLoop() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (started && ticks >= 150) {
        SpawnPipe();
        ticks = 0;
    }

    const float rot_speed = 0.1;
    const float max = M_PI / 4;

    if (!end_screen) {
        if (started) {
            bird->y += gravity;
            gravity += acceleration;

            bird->y = std::max(0.0f, bird->y);
        }
        else {
            Bobble();
        }
    }

    if (!started) {
        bird->rotation = 0;
    }
    else if (gravity > 0) {
        if (bird->rotation < max)
            bird->rotation += rot_speed;
    }
    else if (bird->rotation > -max) {
        bird->rotation -= rot_speed;
    }

    RenderScene();

    if (!running)
        return;

    if (bird->y > WINDOW_WIDTH) {
        Lose();

        return;
    }

    for (int i = pipes.size() - 1 ; i >= 0 ; i--) {
        auto p = pipes[i];

        if (p.first->x < -p.first->width) {
            DestroyPipe(i);
        }

        if (bird->Collide(p.first) || bird->Collide(p.second)) {
            Lose();

            return;
        }

        if (bird->x == p.first->x + p.first->width) {
            score++;
        }

        p.first->x = p.second->x = p.first->x - 2;
    }

    if (keys.space) {
        gravity = -7;
    }

    ticks++;
}

int main(int argc, char* argv[]) {
    Init();

    const int fps = 60;
    const int frame_delay = 1000 / fps;
    Uint32 frame_start;
    int frame_time;

    while (1) {
        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                Mix_Quit();
                TTF_Quit();

                exit(0);
            }

            CheckEvents();          
        }
 
        GameLoop();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time)
            SDL_Delay(frame_delay - frame_time);
    }

    return 0;
}