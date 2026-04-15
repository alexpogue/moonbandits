#include "app.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

struct app {
    SDL_Window *window;
    SDL_Renderer *renderer;
    float t;
};

SDL_AppResult app_init(app_t **out, int argc, char **argv) {
    app_t *app = malloc(sizeof *app);
    app->t = 0.0f;
    if (!app) {
        SDL_LogError(APP_LOG_GENERIC, "Allocation failure while initializing SDL: app");
        return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_LogError(APP_LOG_GENERIC, "Failed to initialize SDL: %s", SDL_GetError());
        free(app);
        return SDL_APP_FAILURE;
    }

    app->window = SDL_CreateWindow("MoonBandits", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!app->window) {
        SDL_LogError(APP_LOG_GENERIC, "Window creation failed: %s", SDL_GetError());
        free(app);
        return SDL_APP_FAILURE;
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        SDL_LogError(APP_LOG_GENERIC, "Renderer creation failed: %s", SDL_GetError());
        SDL_DestroyWindow(app->window);
        free(app);
        return SDL_APP_FAILURE;
    }

    *out = app;

    return SDL_APP_CONTINUE;
}


SDL_AppResult app_iterate(app_t *app) {
    app->t += 0.01f;

    // Animate color (RGB shifts over time)
    Uint8 r = (Uint8)(127 + 127 * SDL_sinf(app->t));
    Uint8 g = (Uint8)(127 + 127 * SDL_sinf(app->t + 2.0f));
    Uint8 b = (Uint8)(127 + 127 * SDL_sinf(app->t + 4.0f));

    SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult app_event(app_t *app, SDL_Event *event) {
    switch(event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        default:
            return SDL_APP_CONTINUE;
    }
}

void app_quit(app_t *app, SDL_AppResult result) {
    if (!app) {
        return;
    }
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    free(app);
}
