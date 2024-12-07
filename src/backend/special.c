#include "../../includes/backend/special.h"

#include <stdlib.h>

#include "../../includes/config/config.h"
#include "../../includes/utils/utils.h"

Special *init_special() {
  Special *special = (Special *)malloc(sizeof(Special));
  must_init(special, "Special Attack");
  special->gun = create_gun(PLAYER);
  special->is_active = 0;
  return special;
}