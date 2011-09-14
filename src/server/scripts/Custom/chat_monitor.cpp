#include "ScriptPCH.h"

enum ChatMonitor
{
    CHAT_MONITOR_WORD_COUNT = 8
};

class chat_monitor : public PlayerScript
{
public:
    chat_monitor() : PlayerScript("chat_monitor") {}

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg)
    {
        CheckMessage(player, msg, NULL, NULL, NULL, NULL);
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver)
    {
        CheckMessage(player, msg, receiver, NULL, NULL, NULL);
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group)
    {
        CheckMessage(player, msg, NULL, group, NULL, NULL);
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild)
    {
        CheckMessage(player, msg, NULL, NULL, guild, NULL);
    }

    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel)
    {
        CheckMessage(player, msg, NULL, NULL, NULL, channel);
    }

    void CheckMessage(Player* player, std::string& msg, Player* receiver, Group* group, Guild* guild, Channel* channel)
    {
        if (player->isGameMaster())
            return;

        std::string words[CHAT_MONITOR_WORD_COUNT] = {"server", "servidor", "http", "www", "@", "realm", "hack", "cheat"};
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
    }
};

void AddSC_chat_monitor()
{
    new chat_monitor();
}
