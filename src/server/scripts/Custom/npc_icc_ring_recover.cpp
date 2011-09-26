#include "ScriptPCH.h"

enum AshenRingRecover
{
    FACTION_ASHEN_VEREDICT          = 1156,
    QUEST_CHOOSE_YOUR_PATH          = 24815,
    NPC_TEXT_ID                     = 537006
};

class npc_icc_ring_recover : public CreatureScript
{
public:
    npc_icc_ring_recover() : CreatureScript("npc_icc_ring_recover") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_CHOOSE_YOUR_PATH) != QUEST_STATUS_COMPLETE)
            return true;

        for (int i = 0; i < 20; ++i)
        {
            if (player->HasItemCount(rings[i], 1, true)) // Check items also in bank
                return true;
        }

        switch (player->GetReputationRank(FACTION_ASHEN_VEREDICT))
        {
            case REP_FRIENDLY:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Caster DPS (Friendly)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Healer (Friendly)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Strength (Friendly)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Agility (Friendly)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank (Friendly)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                break;
            case REP_HONORED:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Caster DPS (Honored)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Healer (Honored)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Strength (Honored)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Agility (Honored)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank (Honored)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                break;
            case REP_REVERED:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Caster DPS (Revered)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Healer (Revered)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Strength (Revered)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Agility (Revered)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank (Revered)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                break;
            case REP_EXALTED:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Caster DPS (Exalted)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Healer (Exalted)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Strength (Exalted)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Melee - Agility (Exalted)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tank (Exalted)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                break;
            default:
                return true;
        }

        player->SEND_GOSSIP_MENU(NPC_TEXT_ID, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->AddItem(rings[0], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->AddItem(rings[1], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->AddItem(rings[2], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->AddItem(rings[3], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->AddItem(rings[4], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->AddItem(rings[5], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->AddItem(rings[6], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->AddItem(rings[7], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                player->AddItem(rings[8], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:
                player->AddItem(rings[9], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:
                player->AddItem(rings[10], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:
                player->AddItem(rings[11], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:
                player->AddItem(rings[12], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 14:
                player->AddItem(rings[13], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 15:
                player->AddItem(rings[14], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 16:
                player->AddItem(rings[15], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 17:
                player->AddItem(rings[16], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 18:
                player->AddItem(rings[17], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 19:
                player->AddItem(rings[18], 1);
                break;
            case GOSSIP_ACTION_INFO_DEF + 20:
                player->AddItem(rings[19], 1);
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

private:
    uint32 static const rings[20];
};

uint32 const npc_icc_ring_recover::rings[20] = {
    50377, // Caster Friendly
    50378, // Healer Friendly
    52569, // Melee Strength Friendly
    50376, // Melee Agility Friendly
    50375, // Tank Friendly
    50384, // Caster Honored
    50386, // Healer Honored
    52570, // Melee Strength Honored
    50387, // Melee Agility Honored
    50388, // Tank Honored
    50397, // Caster Revered
    50399, // Healer Revered
    52571, // Melee Strength Revered
    50401, // Melee Agility Revered
    50403, // Tank Revered
    50398, // Caster Exalted
    50400, // Healer Exalted
    52572, // Melee Strength Exalted
    50402, // Melee Agility Exalted
    50404  // Tank Exalted
};

void AddSC_npc_icc_ring_recover()
{
    new npc_icc_ring_recover();
}
