#include "../../includes/backend/special.h"

#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Special *init_special() {
  Special *special = (Special *)malloc(sizeof(Special));
  must_init(special, "Special Attack");
  special->gun = create_gun(PLAYER);
  special->is_active = 0;
  special->on_map = 0;
  return special;
}

void spawn_special_attack(Special *sp) {
  if (sp->on_map || difftime(time(NULL), sp->spawn_time) <= 2) return;

  sp->x = SCREEN_WIDTH + 100;
  sp->y = rand_between(30, 500);
  sp->type = rand_between(0, 2);
  switch (sp->type) {
    case SPECIAL_GUN_ONE:
      sp->damage = 2;
      break;
    case SPECIAL_GUN_TWO:
      sp->damage = 5;
      break;
  }

  sp->on_map = 1;
}

void update_special_attack(Special *sp) {
  if (!sp->on_map) return;

  sp->x -= SPECIAL_ITEM_SPEED;

  if (sp->x <= 0) {
    sp->on_map = 0;
    sp->spawn_time = time(NULL);
    return;
  }
}

void destroy_special_attack(Special *sp) {
  free(sp->gun);
  free(sp);
}