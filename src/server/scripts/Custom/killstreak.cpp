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
	
void OnPvPKill(Player *pKiller, Player *pVictim)
	{
		uint32 kGUID; 
		uint32 vGUID;
		kGUID = pKiller->GetGUID();
		vGUID = pVictim->GetGUID();	
		if(kGUID == vGUID)
		{
			return;
		}
		if(KillingStreak[kGUID].LastGUIDKill == vGUID)
		{
			return;
		}
		
		KillingStreak[kGUID].KillStreak++;
		KillingStreak[vGUID].KillStreak = 0;
		KillingStreak[kGUID].LastGUIDKill = vGUID;
		KillingStreak[vGUID].LastGUIDKill = 0;
		
		switch(KillingStreak[kGUID].KillStreak)
		{
                        char msg[500];

			case 1:
			sprintf(msg, "[PvP System]: %s killed %s and is on a 1st kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;

                        case 15:
			sprintf(msg, "[PvP System]: %s killed %s and is on a 15 kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;

                        case 25:
			sprintf(msg, "[PvP System]: %s killed %s and is on a 25 kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;

                        case 50:
			sprintf(msg, "[PvP System]: Wow, %s killed %s is already on a 50 kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;

                        case 100:
			sprintf(msg, "[PvP System]: Amazing! %s killed %s and is on a 100 kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;

                        case 250:
			sprintf(msg, "[PvP System]: Incredible! %s killed %s and is on a 250 kill streak!!! CAN NO ONE STOP THE TERROR?! ", pKiller->GetName(), pVictim->GetName());
			sWorld->SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;
		}
	}
};

void AddSC_killstreak()
{
    new System_OnPvPKill;
}