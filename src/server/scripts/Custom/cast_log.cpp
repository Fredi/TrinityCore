#include "ScriptPCH.h"
#include "Spell.h"
#include "Log.h"
#include "Config.h"
#include <sstream>

class cast_log : public PlayerScript
{
public:
    cast_log() : PlayerScript("cast_log") {}

    void OnSpellCast(Player* player, Spell* spell, bool /*skipCheck*/)
    {
        if (!sWorld->getBoolConfig(CONFIG_CASTLOG_ENABLED))
            return;

        if (spell->GetOriginalCaster() != player)
            return;

        Player* target = NULL;
        if (spell->m_targets.GetUnitTarget())
            target = spell->m_targets.GetUnitTarget()->ToPlayer();

        if (!target)
            return;

        if (player->GetBattleground() || player->duel || target == player)
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

            if (target == player)
                sLog->outCast("Player %s (%u) casts %u on self",
                    player->GetName(), player->GetGUIDLow(), spell->GetSpellInfo()->Id);
            else
                sLog->outCast("Player %s (%u) casts %u - Target: %s (%u)",
                    player->GetName(), player->GetGUIDLow(), spell->GetSpellInfo()->Id, target->GetName(), target->GetGUIDLow());
        }
    }
};

void AddSC_cast_log()
{
    new cast_log();
}
