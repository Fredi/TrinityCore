#include "ScriptPCH.h"
#include "Spell.h"
#include "Log.h"
#include "Config.h"
#include <sstream>

class cast_log : public PlayerScript
{
public:
    cast_log() : PlayerScript("cast_log") {}

    void OnSpellCast(Player* player, Spell* spell, bool skipCheck)
    {
        if (!sWorld->getBoolConfig(CONFIG_CASTLOG_ENABLED))
            return;

        if (spell->GetOriginalCaster() != player)
            return;

        Battleground* bg = player->GetBattleground();
        if (bg || player->duel)
        {
            bool found = false;
            uint32 accountId;
            std::istringstream ss(ConfigMgr::GetStringDefault("CastLogs.Accounts", ""));

            while (ss >> accountId)
            {
                if (accountId == player->GetSession()->GetAccountId())
                {
                    found = true;
                    break;
                }
            }

            if (!found)
                return;

            sLog->outCast("Player %s (GuidLow: %u) casts %u",
                player->GetName(), player->GetGUIDLow(), spell->GetSpellInfo()->Id);
        }
    }
};

void AddSC_cast_log()
{
    new cast_log();
}
