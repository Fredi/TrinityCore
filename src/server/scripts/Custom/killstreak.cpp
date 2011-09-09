#include "ScriptPCH.h"

class System_OnPvPKill : public PlayerScript
{
public:
    System_OnPvPKill() : PlayerScript("System_OnPvPKill") {}

    struct SystemInfo
    {
        uint32 KillStreak;
        uint32 LastGUIDKill;
    };

    static std::map<uint32, SystemInfo> KillingStreak;

    void OnPvPKill(Player* killer, Player* victim)
    {
        uint32 killerGUID = killer->GetGUID();
        uint32 victimGUID = victim->GetGUID();

        if (killerGUID == victimGUID || KillingStreak[killerGUID].LastGUIDKill == victimGUID)
            return;

        KillingStreak[killerGUID].KillStreak++;
        KillingStreak[victimGUID].KillStreak = 0;
        KillingStreak[killerGUID].LastGUIDKill = victimGUID;
        KillingStreak[victimGUID].LastGUIDKill = 0;

        switch (KillingStreak[killerGUID].KillStreak)
        {
            char msg[500];

            case 1:
                sprintf(msg, "[PvP System]: %s killed %s and is on a 1st kill streak. ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
            case 15:
                sprintf(msg, "[PvP System]: %s killed %s and is on a 15 kill streak. ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
            case 25:
                sprintf(msg, "[PvP System]: %s killed %s and is on a 25 kill streak. ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
            case 50:
                sprintf(msg, "[PvP System]: Wow, %s killed %s is already on a 50 kill streak. ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
            case 100:
                sprintf(msg, "[PvP System]: Amazing! %s killed %s and is on a 100 kill streak. ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
            case 250:
                sprintf(msg, "[PvP System]: Incredible! %s killed %s and is on a 250 kill streak!!! CAN NO ONE STOP THE TERROR?! ", killer->GetName(), victim->GetName());
                sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
                break;
        }
    }
};

void AddSC_killstreak()
{
    new System_OnPvPKill;
}
