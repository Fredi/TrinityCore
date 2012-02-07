#include "ScriptPCH.h"
#include "Chat.h"
#include "AccountMgr.h"

class npc_custom_vendor : public CreatureScript
{
public:
    npc_custom_vendor() : CreatureScript("npc_custom_vendor") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        QueryResult result = CharacterDatabase.PQuery("SELECT at_login FROM characters WHERE guid = '%u'", player->GetGUIDLow());
        uint32 atLogin = (*result)[0].GetUInt32();
        if (atLogin & (AT_LOGIN_RENAME | AT_LOGIN_CUSTOMIZE | AT_LOGIN_CHANGE_RACE | AT_LOGIN_CHANGE_FACTION))
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterWhisper("Você já escolheu uma mudança, por favor relogue sua conta.", player->GetGUID(), false);
            return true;
        }

        result = LoginDatabase.PQuery("SELECT vip_tokens FROM account where id = '%u'", player->GetSession()->GetAccountId());
        uint32 tokens = (*result)[0].GetUInt32();
        if (!tokens)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->MonsterWhisper("Desculpe $N, você nao possui tokens.", player->GetGUID(), false);
            return true;
        }

        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero VIP (30 dias)", GOSSIP_SENDER_MAIN, 1000);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero VIP (60 dias)", GOSSIP_SENDER_MAIN, 1001);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero VIP (90 dias)", GOSSIP_SENDER_MAIN, 1002);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero mudar meu nome!", GOSSIP_SENDER_MAIN, 1003);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero customizar meu char! (aparencia/genero/nome)", GOSSIP_SENDER_MAIN, 1004);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero mudar minha raça!", GOSSIP_SENDER_MAIN, 1005);
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Quero mudar minha facção!", GOSSIP_SENDER_MAIN, 1006);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        player->CLOSE_GOSSIP_MENU();

        QueryResult result = LoginDatabase.PQuery("SELECT vip_tokens FROM account where id = '%u'", player->GetSession()->GetAccountId());
        uint32 tokens = (*result)[0].GetUInt32();
        if (!tokens)
            return true;

        switch(action)
        {
            case 1000: // VIP (30 days)
                if (!Buy(player, tokens, 10))
                    return true;
                RewardVIP(player, 30);
                break;
            case 1001: // VIP (60 days)
                if (!Buy(player, tokens, 18))
                    return true;
                RewardVIP(player, 60);
                break;
            case 1002: // VIP (90 days)
                if (!Buy(player, tokens, 25))
                    return true;
                RewardVIP(player, 90);
                break;
            case 1003: // Change name
                if (!Buy(player, tokens, 10))
                    return true;
                player->SetAtLoginFlag(AT_LOGIN_RENAME);
                break;
            case 1004: // Customize
                if (!Buy(player, tokens, 15))
                    return true;
                player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                break;
            case 1005: // Change race
                if (!Buy(player, tokens, 10))
                    return true;
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                break;
            case 1006: // Change faction
                if (!Buy(player, tokens, 30))
                    return true;
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                break;
        }

        creature->MonsterWhisper("Obrigado $N! Talvez seja necessário relogar para ativar sua recompensa.", player->GetGUID(), false);

        return true;
    }

    bool Buy(Player* player, uint32 have, uint32 need)
    {
        if (need > have)
        {
            ChatHandler(player).PSendSysMessage("Você não possui tokens suficientes.");
            return false;
        }

        LoginDatabase.PExecute("UPDATE account SET vip_tokens = vip_tokens - %u WHERE id = %u", need, player->GetSession()->GetAccountId());

        return true;
    }

    void RewardVIP(Player* player, uint32 days)
    {
        uint32 accountId = player->GetSession()->GetAccountId();
        uint32 durationSecs = days * 86400;

        QueryResult result = LoginDatabase.PQuery("SELECT active FROM account_vip WHERE id = %u AND active = 1", accountId);
        if (result)
        {
            LoginDatabase.PExecute("UPDATE account_vip "
                "SET gm = '%s', unsetdate = unsetdate + %u "
                "WHERE id = %u", "NPC", durationSecs, accountId);
        }
        else
        {
            LoginDatabase.PExecute("DELETE FROM account_vip WHERE id = %u", accountId);
            LoginDatabase.PExecute("INSERT INTO account_vip "
                "(id, gm, setdate, unsetdate, active) "
                "VALUES ('%u', '%s', UNIX_TIMESTAMP(), UNIX_TIMESTAMP() + %u, 1)",
                accountId, "NPC", durationSecs);
        }

        ChatHandler(player).PSendSysMessage("Você possui %u dias de VIP.", AccountMgr::VipDaysLeft(accountId));
    }
};

void AddSC_npc_custom_vendor()
{
    new npc_custom_vendor;
}
