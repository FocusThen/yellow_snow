#include "player.h"
#include "main.h"

bool player_new(struct Player **player, SDL_Renderer *renderer,
                SDL_Texture *image) {

  *player = calloc(1, sizeof(struct Player));
  if (*player == NULL) {
    fprintf(stderr, "Error in calloc on new player. \n");
    return true;
  }

  struct Player *p = *player;

  p->renderer = renderer;
  p->image = image;
  p->keystate = SDL_GetKeyboardState(NULL);
  p->speed = 5;
  p->top_offset = 10;
  p->left_offset = 47;
  p->right_offset = 43;

  if (SDL_QueryTexture(p->image, NULL, NULL, &p->rect.w, &p->rect.h)) {
    fprintf(stderr, "Error querying Texture player: %s\n", SDL_GetError());
    return true;
  }

  player_reset(p);

  return false;
}
void player_free(struct Player **player) {
  if (*player) {
    (*player)->image = NULL;
    (*player)->keystate = NULL;
    (*player)->renderer = NULL;
    free(*player);
    *player = NULL;
  }
}

int player_left(struct Player *p) { return p->rect.x + p->left_offset; }
int player_right(struct Player *p) {
  return p->rect.x + p->rect.w - p->right_offset;
}
int player_top(struct Player *p) { return p->rect.y + p->top_offset; }

void player_reset(struct Player *p){
  p->flip = SDL_FLIP_NONE;
  p->rect.x = (WINDOW_WIDTH - p->rect.w) / 2;
  p->rect.y = 377;
}

void player_update(struct Player *p) {
  if (p->keystate[SDL_SCANCODE_LEFT] || p->keystate[SDL_SCANCODE_A]) {
    p->rect.x -= p->speed;
    if (p->rect.x + p->left_offset < 0) {
      p->rect.x = -p->left_offset;
    }
    p->flip = SDL_FLIP_HORIZONTAL;
  }
  if (p->keystate[SDL_SCANCODE_RIGHT] || p->keystate[SDL_SCANCODE_D]) {
    p->rect.x += p->speed;
    if (p->rect.x + p->rect.w - p->right_offset > WINDOW_WIDTH) {
      p->rect.x = WINDOW_WIDTH - p->rect.w + p->right_offset;
    }
    p->flip = SDL_FLIP_NONE;
  }
}
void player_draw(struct Player *p) {
  SDL_RenderCopyEx(p->renderer, p->image, NULL, &p->rect, 0, NULL, p->flip);
}
