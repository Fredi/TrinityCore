#include "ScriptPCH.h"
#include "Config.h"

class npc_vip : public CreatureScript
{
public:
    npc_vip() : CreatureScript("npc_vip") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (!pPlayer->GetSession()->IsVIP() && !pPlayer->isGameMaster())
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper("Desculpe $N, atendo somente VIPs.", pPlayer->GetGUID(), false);
            return true;
        }

        if (pCreature->isVendor())
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->GetSession()->SendListInventory(pCreature->GetGUID());
            return true;
        }

        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        pPlayer->ADD_GOSSIP_ITEM(9, "Heal"                     , GOSSIP_SENDER_MAIN, 1202);
        pPlayer->ADD_GOSSIP_ITEM(5, "Resetar talentos"          , GOSSIP_SENDER_MAIN, 4035);
        pPlayer->ADD_GOSSIP_ITEM(7, "[Morfar] ->"               , GOSSIP_SENDER_MAIN, 1203);
        pPlayer->ADD_GOSSIP_ITEM(7, "[Buffs] ->"                , GOSSIP_SENDER_MAIN, 1206);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        switch(uiAction)
        {
            case 1202: // Heal
                if (pPlayer->HasAura(45523))
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("Desculpe $N, não posso fazer isto nesse momento.", pPlayer->GetGUID(), false);
                }
                else
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->CastSpell(pPlayer, 39321, true);
                    pPlayer->CastSpell(pPlayer, 45523, true);
                }
                break;
            case 4035: // Reset talents
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SendTalentWipeConfirm(pCreature->GetGUID());
                break;
            case 1203: // Morphs
                pPlayer->ADD_GOSSIP_ITEM(5, "Illidan", GOSSIP_SENDER_MAIN, 500);
                pPlayer->ADD_GOSSIP_ITEM(5, "Akama", GOSSIP_SENDER_MAIN, 502);
                pPlayer->ADD_GOSSIP_ITEM(5, "Deathknight", GOSSIP_SENDER_MAIN, 503);
                pPlayer->ADD_GOSSIP_ITEM(5, "Tauren", GOSSIP_SENDER_MAIN, 504);
                pPlayer->ADD_GOSSIP_ITEM(5, "Undead", GOSSIP_SENDER_MAIN, 505);
                pPlayer->ADD_GOSSIP_ITEM(5, "Human", GOSSIP_SENDER_MAIN, 506);
                pPlayer->ADD_GOSSIP_ITEM(5, "Lich King", GOSSIP_SENDER_MAIN, 507);
                pPlayer->ADD_GOSSIP_ITEM(5, "Tirion", GOSSIP_SENDER_MAIN, 508);
                pPlayer->ADD_GOSSIP_ITEM(5, "Uther Lightbringer", GOSSIP_SENDER_MAIN, 509);
                pPlayer->ADD_GOSSIP_ITEM(5, "Arthas", GOSSIP_SENDER_MAIN, 510);
                pPlayer->ADD_GOSSIP_ITEM(5, "DESMORFAR", GOSSIP_SENDER_MAIN, 511);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

                break;
            case 500:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(21135);
                break;
            case 502:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(20681);
                break;
            case 503:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(16508);
                break;
            case 504:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(17332);
                break;
            case 505:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(2789);
                break;
            case 506:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(16280);
                break;
            case 507:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(24191);
                break;
            case 508:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(22209);
                break;
            case 509:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(23889);
                break;
            case 510:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SetDisplayId(24949);
                break;
            case 511:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->DeMorph();
                break;
            case 1206: // Buffs
                pPlayer->ADD_GOSSIP_ITEM(5, "Power Word: Fortitude, Rank 8", GOSSIP_SENDER_MAIN, 4000);
                pPlayer->ADD_GOSSIP_ITEM(5, "Greater Blessing of Kings", GOSSIP_SENDER_MAIN, 4001);
                pPlayer->ADD_GOSSIP_ITEM(5, "Greater Bleesing of Mights", GOSSIP_SENDER_MAIN,4002);
                pPlayer->ADD_GOSSIP_ITEM(5, "Greater Blessing of Wisdom", GOSSIP_SENDER_MAIN, 4003);
                pPlayer->ADD_GOSSIP_ITEM(5, "Mark of the Wild, Rank 9", GOSSIP_SENDER_MAIN, 4004);
                pPlayer->ADD_GOSSIP_ITEM(5, "Arcane Intellect, Rank 7", GOSSIP_SENDER_MAIN, 4005);
                pPlayer->ADD_GOSSIP_ITEM(5, "Thorns, Rank 8", GOSSIP_SENDER_MAIN, 4007);
                pPlayer->ADD_GOSSIP_ITEM(5, "Divine Spirit, Rank 8", GOSSIP_SENDER_MAIN, 4008);
                pPlayer->ADD_GOSSIP_ITEM(5, "Shadow Protection, Rank 5", GOSSIP_SENDER_MAIN, 4009);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());

                break;
            case 4000:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48161, false); // target, spellid, triggered-e
                break;
            case 4001:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 25898, false);
                break;
            case 4002:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48934, false);
                break;
            case 4003:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48938, false);
                break;
            case 4004:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48469, false);
                break;
            case 4005:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 42995, false);
                break;
            case 4007:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 53307, false);
                break;
            case 4008:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48073, false);
                break;
            case 4009:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->CastSpell(pPlayer, 48169, false);
                break;
        }

        return true;
    }
};

void AddSC_npc_vip()
{
    new npc_vip;
}
