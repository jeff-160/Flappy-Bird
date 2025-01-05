struct Sprite {
    string image;
    float x, y;
    int width, height;
    float rotation = 0;

    Sprite(string image, float x, float y, int width, int height):
        image(image), x(x), y(y), width(width), height(height) {}

    void Render() {
        if (
            this->x < -this->width || this->x > WINDOW_WIDTH ||
            this->y < -this->height || this->y > WINDOW_WIDTH
        ) return;

        if (!assets[this->image]) {
            LoadImage(this->image);
        }

        SDL_FRect bounds = { this->x, this->y, (float)this->width, (float)this->height };
        
        if (this->rotation){
            SDL_RenderCopyExF(renderer, assets[this->image], nullptr, &bounds, this->rotation * 180 / M_PI, NULL, SDL_FLIP_NONE);
        }
        
        else {
            SDL_RenderCopyF(renderer, assets[this->image], nullptr, &bounds);
        }
    }

    bool Collide(Sprite* other) {
        return (
            this->x < other->x + other->width &&
            this->x + this->width > other->x &&
            this->y < other->y + other->height &&
            this->y + this->height > other->y
        );
    }
};