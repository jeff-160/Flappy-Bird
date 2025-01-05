#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <functional>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
TTF_Font* font;

bool started = 0;
bool running = 1;

#define WINDOW_WIDTH 600
#define ERROR(msg) throw runtime_error((msg))

#include "src/utils.hpp"
#include "src/threading.hpp"
#include "src/assets.hpp"
#include "src/sprite.hpp"
#include "src/entities.hpp"

float gravity = 5;
const float acceleration = 0.5;

size_t score = 0;
vector<pair<Sprite*, Sprite*>> pipes;

size_t ticks = 0;
bool end_screen = 0;

#include "src/events.hpp"