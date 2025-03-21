#include "flakes.h"

bool flake_new(struct Flake **flake, SDL_Renderer *renderer,
               SDL_Texture *image, bool is_white) {
  struct Flake *new_flake = calloc(1, sizeof(struct Flake));
  if (!new_flake) {
    fprintf(stderr, "Error in calloc of new flake\n");
    return true;
  }

  new_flake->renderer = renderer;
  new_flake->image = image;
  new_flake->speed = 5;
  new_flake->ground = 514;
  new_flake->is_white = is_white;

  if (SDL_QueryTexture(new_flake->image, NULL, NULL, &new_flake->rect.w,
                       &new_flake->rect.h)) {
    fprintf(stderr, "Error querying Texture Flake: %s\n", SDL_GetError());
    return true;
  }

  flake_reset(new_flake, true);

  new_flake->next = *flake;
  *flake = new_flake;

  return false;
}

void flake_reset(struct Flake *f, bool full) {
  int height = full ? WINDOW_HEIGHT * 2 : WINDOW_HEIGHT;
  f->rect.y = -((rand() % height) + f->rect.h);
  f->rect.x = rand() % (WINDOW_WIDTH - f->rect.w);
}

void flakes_reset(struct Flake *f) {
  while (f) {
    flake_reset(f, true);
    f = f->next;
  }
}

void flake_free(struct Flake **flake) {
  struct Flake *f = *flake;
  while (f) {
    struct Flake *next = f->next;
    f->image = NULL;
    f->renderer = NULL;
    f->next = NULL;
    free(f);
    f = next;
  }
  *flake = NULL;
}

int flake_left(struct Flake *f) { return f->rect.x; }
int flake_right(struct Flake *f) { return f->rect.x + f->rect.w; }
int flake_bottom(struct Flake *f) { return f->rect.y + f->rect.h; }

void flake_update(struct Flake *f) {
  while (f) {
    f->rect.y += f->speed;
    if (f->rect.y > f->ground) {
      flake_reset(f, false);
    }
    f = f->next;
  }
}
void flake_draw(struct Flake *f) {
  while (f) {
    SDL_RenderCopy(f->renderer, f->image, NULL, &f->rect);
    f = f->next;
  }
}
