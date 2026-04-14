#ifndef APP_GUARD
#define APP_GUARD

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

typedef struct app app_t;

SDL_AppResult init(app_t *app, int argc, char **argv);
SDL_AppResult iterate(app_t *app);
SDL_AppResult event(app_t *app, SDL_Event *event);
void quit(app_t *app, SDL_AppResult result);

typedef enum {
    APP_LOG_GENERIC = SDL_LOG_CATEGORY_CUSTOM,
} AppLogCategory;

#endif
