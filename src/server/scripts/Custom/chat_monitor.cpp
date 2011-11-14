#include "ScriptPCH.h"
#include "Channel.h"

enum ChatMonitor
{
    CHAT_MONITOR_WORD_COUNT = 13
};

class chat_monitor : public PlayerScript
{
public:
    chat_monitor() : PlayerScript("chat_monitor") {}

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg)
    {
        CheckMessage(player, msg, NULL, NULL, NULL, NULL);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Player* receiver)
    {
        CheckMessage(player, msg, receiver, NULL, NULL, NULL);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Group* group)
    {
        CheckMessage(player, msg, NULL, group, NULL, NULL);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Guild* guild)
    {
        CheckMessage(player, msg, NULL, NULL, guild, NULL);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 /*lang*/, std::string& msg, Channel* channel)
    {
        CheckMessage(player, msg, NULL, NULL, NULL, channel);
    }

    void CheckMessage(Player* player, std::string& msg, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
    {
        if (player->isGameMaster())
            return;

        // Send LFG messages to other team GMs
        if (channel && channel->IsLFG())
            sWorld->SendGMTextOtherTeam(LANG_CHAT_MONITOR_LFG, player->GetTeam(), player->GetName(), msg.c_str());

        bool found = false;

        std::string lower = msg;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        for (int i = 0; i < CHAT_MONITOR_WORD_COUNT; ++i)
        {
            if (lower.find(words[i]) != std::string::npos)
            {
                found = true;
                break;
            }
        }

        if (!found)
            return;

        std::string report = "|cFF00FFFF[|cFF60FF00" + std::string(player->GetName()) + "|cFF00FFFF] " + msg;

        WorldPacket data(SMSG_NOTIFICATION, (report.size() + 1));
        data << report;
        sWorld->SendGlobalGMMessage(&data);

        sWorld->SendGMText(LANG_CHAT_MONITOR, player->GetName(), msg.c_str());
    }

private:
    std::string static const words[CHAT_MONITOR_WORD_COUNT];
};

std::string const chat_monitor::words[CHAT_MONITOR_WORD_COUNT] = {
    "server", "servidor", "http", "www", "realm", "hack", "cheat",
    "emu", "sentinel", "pacote", "packet", "wpe", ".com"};

void AddSC_chat_monitor()
{
    new chat_monitor();
}
