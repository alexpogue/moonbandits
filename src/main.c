#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include "app.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    app_t *app = NULL;

    printf("SDL video driver: %s\n", SDL_GetCurrentVideoDriver());
    printf("Available drivers:\n");
    for (int i = 0; i < SDL_GetNumVideoDrivers(); i++) {
        printf("  %s\n", SDL_GetVideoDriver(i));
    }
    SDL_AppResult res = app_init(&app, argc, argv);
    if (res != SDL_APP_CONTINUE) {
        return res;
    }
    *appstate = app;
    return res;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    app_t *app = appstate;
    return app_iterate(app);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    app_t *app = appstate;
    return app_event(app, event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    app_t *app = appstate;
    app_quit(app, result);
}
