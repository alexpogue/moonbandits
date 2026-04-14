#include "app.h"

#include <SDL3/SDL.h>

struct app {
    SDL_Window window;
}

SDL_AppResult app_init(app_t *app, int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(APP_LOG_GENERIC, "Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}
SDL_AppResult app_iterate(app_t *app) {
    return SDL_APP_CONTINUE;
}
SDL_AppResult app_event(app_t *app, SDL_Event *event) {
    return SDL_APP_CONTINUE;
}
void app_quit(app_t *app, SDL_AppResult result) {
}
