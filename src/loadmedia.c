#include "loadmedia.h"
#include "SDL2/SDL_mixer.h"

bool game_load_media(struct Game *g) {
  g->background_image = IMG_LoadTexture(g->renderer, "images/background.png");
  if (!g->background_image) {
    fprintf(stderr, "Error Loading Texture: %s\n", IMG_GetError());
    return true;
  }

  if (SDL_QueryTexture(g->background_image, NULL, NULL, &g->background_rect.w,
                       &g->background_rect.h)) {
    fprintf(stderr, "Error querying Texture: %s\n", SDL_GetError());
    return true;
  }

  g->player_image = IMG_LoadTexture(g->renderer, "images/player.png");
  if (!g->player_image) {
    fprintf(stderr, "Error Loading Player Image: %s\n", IMG_GetError());
    return true;
  }

  g->yellow_image = IMG_LoadTexture(g->renderer, "images/yellow.png");
  if (!g->yellow_image) {
    fprintf(stderr, "Error Loading Yellow Flake Image: %s\n", IMG_GetError());
    return true;
  }

  g->white_image = IMG_LoadTexture(g->renderer, "images/white.png");
  if (!g->white_image) {
    fprintf(stderr, "Error Loading White Flake Image: %s\n", IMG_GetError());
    return true;
  }

  g->hit_sound = Mix_LoadWAV("sounds/hit.ogg");
  if (!g->hit_sound) {
    fprintf(stderr, "Error Loading hit sound: %s\n", Mix_GetError());
    return true;
  }

  g->collect_sound = Mix_LoadWAV("sounds/collect.ogg");
  if (!g->collect_sound) {
    fprintf(stderr, "Error Loading collect sound: %s\n", Mix_GetError());
    return true;
  }

  return false;
}
