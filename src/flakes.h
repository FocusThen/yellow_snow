
#ifndef FLAKES_H
#define FLAKES_H

#include "main.h"

struct Flake {
  struct Flake *next;
  SDL_Renderer *renderer;
  SDL_Texture *image;
  SDL_Rect rect;
};


bool flake_new(struct Flake **f, SDL_Renderer *renderer, SDL_Texture *image);
void flake_free(struct Flake **f);
void flake_update(struct Flake *f);
void flake_draw(struct Flake *f);

#endif
