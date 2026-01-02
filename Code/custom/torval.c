#include <libdl/player.h>
#include <libdl/utils.h>
#include "utils.h"
#include "shared.h"

//--------------------------------------------------------------------------
void gambitsWeaponLifeHookAfterDecHitPoints(Player* player)
{
  if (!player->IsLocal) return;

  int weaponId = player->WeaponHeldId;
  int weaponLevel = player->GadgetBox->Gadgets[weaponId].Level;
  if (weaponLevel > 0) {
    player->GadgetBox->Gadgets[weaponId].Level--;
    playerSetHealth(player, player->MaxHealth);
  } else {
    playerSetHealth(player, 0);
  }
}

//--------------------------------------------------------------------------
void gambitWeaponLifeInit(void)
{
  HOOK_J_OP(0x005d1138, &gambitsWeaponLifeHookAfterDecHitPoints, 0x00A02021);
}

//--------------------------------------------------------------------------
void gambitBigMobsOnlyInit(void)
{
  int i;

  // disable zombies and swarmers
  MapConfig.DefaultSpawnParams[5].Probability = 0; // zombies
  MapConfig.DefaultSpawnParams[6].Probability = 0; // swarmers

  // have all mobs spawn at start
  for (i = 0; i < MapConfig.DefaultSpawnParamsCount; ++i)
    MapConfig.DefaultSpawnParams[i].MinRound = 0;
}

//--------------------------------------------------------------------------
void gambitVampireInit(void)
{
  int i;

  // set vampire perks
  for (i = 0; i < GAME_MAX_PLAYERS; ++i) {
    MapConfig.State->PlayerStates[i].State.ItemStackable[STACKABLE_ITEM_VAMPIRE] = 10;
  }
}
