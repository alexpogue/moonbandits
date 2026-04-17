#include "app.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

struct app {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint64 lastTime;
    float deltaTime;
    float rect_x;
    float rect_y;
    float t;
};

SDL_AppResult app_init(app_t **out, int argc, char **argv) {
    app_t *app = malloc(sizeof *app);
    app->t = 0.0f;
    app->rect_x = 0.0f;
    app->rect_y = 0.0f;
    app->lastTime = SDL_GetTicks();
    app->deltaTime = 0.0f;
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
    const Uint32 targetFrameMs = 16; // ~60 FPS (1000 / 60 ≈ 16.67)

    Uint64 frameStart = SDL_GetTicks();

    float dt = app->deltaTime;
    float speed = 300.0f;

    const bool *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT]) {
        app->rect_x -= speed * dt;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        app->rect_x += speed * dt;
    }
    if (keys[SDL_SCANCODE_UP]) {
        app->rect_y -= speed * dt;
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        app->rect_y += speed * dt;
    }

    app->t += 0.01f;

    // Animate color (RGB shifts over time)
    Uint8 r = (Uint8)(127 + 127 * SDL_sinf(app->t));
    Uint8 g = (Uint8)(127 + 127 * SDL_sinf(app->t + 2.0f));
    Uint8 b = (Uint8)(127 + 127 * SDL_sinf(app->t + 4.0f));

    SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
    SDL_RenderClear(app->renderer);

    SDL_FRect rect = {
        .x = app->rect_x,
        .y = app->rect_y,
        .w = 100,
        .h = 150
    };

    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(app->renderer, &rect);

    SDL_RenderPresent(app->renderer);

    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime < targetFrameMs) {
        SDL_Delay(targetFrameMs - frameTime);
    }

    Uint64 now = SDL_GetTicks();
    app->deltaTime = (now - app->lastTime) / 1000.0f;
    if (app->deltaTime > 0.05f) {
        app->deltaTime = 0.05f; // cap at 50ms (~20 FPS worst-case)
    }
    app->lastTime = now;

    return SDL_APP_CONTINUE;
}

SDL_AppResult app_event(app_t *app, SDL_Event *event) {
    switch(event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void app_quit(app_t *app, SDL_AppResult result) {
    if (!app) {
        return;
    }
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    free(app);
}
