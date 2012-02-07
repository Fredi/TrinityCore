# Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/duel_reset.cpp
  Custom/npc_teleport.cpp
  Custom/npc_vip.cpp
  Custom/custom_fixes.cpp
  Custom/npc_legion_master.cpp
  Custom/killstreak.cpp
  Custom/level_rewards.cpp
  Custom/chat_monitor.cpp
  Custom/npc_icc_ring_recover.cpp
  Custom/guild_house.cpp
  Custom/ArgentTournament.cpp
  Custom/cast_log.cpp
  Custom/npc_custom_vendor.cpp
)

message("  -> Prepared: Custom")
