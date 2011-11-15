#include "ScriptPCH.h"
#include "WorldPacket.h"

class npc_teleport : public CreatureScript
{
public:
    npc_teleport() : CreatureScript("npc_teleport") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        uint32 team = player->GetTeam();
        uint32 level = creature->getLevel(); // 80 = Both, 81 = Horde, 82 = Alliance

        if ((level == 81 && team != HORDE) || (level == 82 && team != ALLIANCE))
        {
            creature->MonsterWhisper("Te manda... Soh sirvo seus inimigos!", player->GetGUID());
            return true;
        }

        uint32 playerLevel = player->getLevel();

        player->ADD_GOSSIP_ITEM(10, "Custos por teleport:", GOSSIP_SENDER_MAIN, 6111);
        player->ADD_GOSSIP_ITEM(10, "Level 1-70 -> 50 pratas", GOSSIP_SENDER_MAIN, 6111);
        player->ADD_GOSSIP_ITEM(10, "Level 80 -> 1 gold", GOSSIP_SENDER_MAIN, 6111);
        player->ADD_GOSSIP_ITEM(10, " ", GOSSIP_SENDER_MAIN, 6111);

        if (team == ALLIANCE)
        {
            player->ADD_GOSSIP_ITEM(5, "Teleport para Stormwind", GOSSIP_SENDER_MAIN, 6201);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Ironforge", GOSSIP_SENDER_MAIN, 6202);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Darnassus", GOSSIP_SENDER_MAIN, 6203);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Exodar", GOSSIP_SENDER_MAIN, 6204);
        }
        else
        {
            player->ADD_GOSSIP_ITEM(5, "Teleport para Orgrimmar", GOSSIP_SENDER_MAIN, 6211);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Thunder Bluff", GOSSIP_SENDER_MAIN, 6212);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Undercity", GOSSIP_SENDER_MAIN, 6213);
            player->ADD_GOSSIP_ITEM(5, "Teleport para Silvermoon City", GOSSIP_SENDER_MAIN, 6214);
        }

        if (player->getClass() == 6) // Death Knight
        {
            player->ADD_GOSSIP_ITEM(5, "Teleport para Break Death", GOSSIP_SENDER_MAIN, 6206);
            player->ADD_GOSSIP_ITEM(5, "Тeleport para Acherus", GOSSIP_SENDER_MAIN, 6207);
        }

        if (playerLevel >= 30)
            player->ADD_GOSSIP_ITEM(5, "Teleport para Gurubashi Arena", GOSSIP_SENDER_MAIN, 6200);

        if (playerLevel >= 58)
            player->ADD_GOSSIP_ITEM(5, "Teleport para Shattrath", GOSSIP_SENDER_MAIN, 6208);

        if (playerLevel >= 65)
            player->ADD_GOSSIP_ITEM(5, "Teleport para Isle of Quel'Danas", GOSSIP_SENDER_MAIN, 6209);

        if (playerLevel >= 70)
            player->ADD_GOSSIP_ITEM(5, "Teleport para Dalaran", GOSSIP_SENDER_MAIN, 6210);

        if (team == ALLIANCE)
            player->ADD_GOSSIP_ITEM(5, "Teleport para Azshara Crater", GOSSIP_SENDER_MAIN, 6402);
        else
            player->ADD_GOSSIP_ITEM(5, "Teleport para Azshara Crater", GOSSIP_SENDER_MAIN, 6401);

        QueryResult result = WorldDatabase.PQuery("SELECT guild FROM creature_guild WHERE guid = %u", creature->GetGUIDLow());
        if (result)
        {
            if (player->GetGuildId() == (*result)[0].GetUInt32() || player->isGameMaster())
            {
                player->ADD_GOSSIP_ITEM(5, "Teleport para Wintergrasp", GOSSIP_SENDER_MAIN, 6403);
                player->ADD_GOSSIP_ITEM(5, "Teleport para Icecrown Citadel", GOSSIP_SENDER_MAIN, 6404);
            }
        }

        if (player->GetGuildId())
        {
            result = WorldDatabase.PQuery("SELECT mapId FROM guild_house WHERE guild = %u", player->GetGuildId());
            if (result)
                player->ADD_GOSSIP_ITEM(5, "Teleport para Guild Tower", GOSSIP_SENDER_MAIN, 6405);
        }

        player->PlayerTalkClass->SendGossipMenu(2713, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        switch (action)
        {
            case 6200:
                TeleportPlayer(0, -13234.1f, 217.387f, 31.6759f, 1.06815f, player, creature);
                break;
            case 6201:
                TeleportPlayer(0, -8908.96f, 556.3f, 93.5345f, 0.73f, player, creature);
                break;
            case 6202:
                TeleportPlayer(0, -4821.6f, -1155.58f, 502.2345f, 3.33532f, player, creature);
                break;
            case 6203:
                TeleportPlayer(1, 9947.53f, 2604.15f, 1316.19f, 4.223f, player, creature);
                break;
            case 6204:
                TeleportPlayer(530, -4054.75f, -11793.4f, 11.1139f, 1.51503f, player, creature);
                break;
            case 6205:
                TeleportPlayer(1, 45.951f, 1218.27f, 146.713f, 0.063138f, player, creature);
                break;
            case 6206:
                TeleportPlayer(609, 2362.29f, -5693.76f, 153.922f, 3.77816f, player, creature);
                break;
            case 6207:
                TeleportPlayer(609, 2348.74f, -5694.94f, 384.088f, 3.90954f, player, creature);
                break;
            case 6208:
                TeleportPlayer(530, -1879.5f, 5409.46f, -12.4277f, 1.0332f, player, creature);
                break;
            case 6209:
                TeleportPlayer(530, 13000.2f, -6907.51f, 12.0f, 1.06815f, player, creature);
                break;
            case 6210:
                TeleportPlayer(571, 5814.2f, 446.337f, 659.201f, 1.41145f, player, creature);
                break;
            case 6211:
                TeleportPlayer(1, 1677.91f, -4314.79f, 62.35f, 2.66969f, player, creature);
                break;
            case 6212:
                TeleportPlayer(1, -1197.18f, 29.2706f, 179.755f, 2.9666f, player, creature);
                break;
            case 6213:
                TeleportPlayer(0, 1568.48f, 268.52f, -42.1384f, 1.69719f, player, creature);
                break;
            case 6214:
                TeleportPlayer(530, 9373.08f, -7166.07f, 11.4763f, 5.38653f, player, creature);
                break;
            case 6215:
                TeleportPlayer(1, -1790.17f, 3055.44f, 9.35831f, 1.06815f, player, creature);
                break;
            case 6216:
                TeleportPlayer(1, -11846.4f, -4756.91f, 6.25831f, 0.305114f, player, creature);
                break;
            case 6401:
                TeleportPlayer(37, -28.6567f, 971.069f, 347.305f, 5.79912f, player, creature);
                break;
            case 6402:
                TeleportPlayer(37, 1094.2f, 298.032f, 338.616f, 3.21441f, player, creature);
                break;
            case 6403: // Wintergrasp
                player->TeleportTo(571, 4760.7f, 2143.7f, 423.0f, 1.13f);
                break;
            case 6404: // Icecrown Citadel
                player->TeleportTo(571, 5857.03f, 2102.8f, 635.933f, 3.58219f);
                break;
            case 6405: // Guild Tower
                QueryResult result = WorldDatabase.PQuery("SELECT mapId, posX, posY, posZ FROM guild_house WHERE guild = %u", player->GetGuildId());
                if (result)
                {
                    Field* fields = result->Fetch();
                    uint32 mapId = fields[0].GetUInt32();
                    float posX = fields[1].GetFloat();
                    float posY = fields[2].GetFloat();
                    float posZ = fields[3].GetFloat();
                    player->TeleportTo(mapId, posX, posY, posZ, player->GetOrientation());
                }
                break;
        }

        player->CLOSE_GOSSIP_MENU();
        return true;
    }

    void TeleportPlayer(uint32 a, float b, float c, float d, float e, Player* player, Creature* creature)
    {
        uint32 costs = (player->getLevel() <= 70) ? 5000 : 10000;

        if (player->GetMoney() < costs)
        {
            creature->MonsterWhisper("Voce nao tem dinheiro suficiente.", player->GetGUID());
            return;
        }

        player->ModifyMoney(costs * -1);

        creature->MonsterWhisper("Boa viajem!", player->GetGUID());

        player->TeleportTo(a, b, c, d, e);
        return;
    }
};

void AddSC_npc_teleport()
{
    new npc_teleport;
}
