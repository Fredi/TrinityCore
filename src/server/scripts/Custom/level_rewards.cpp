#include "ScriptPCH.h"

enum LevelRewards
{
    EMBLEM_OF_CONQUEST  = 45624
};

class level_rewards : public PlayerScript
{
public:
    level_rewards() : PlayerScript("level_rewards") {}

    void OnLevelChanged(Player* player, uint8 newLevel)
    {
        if (player->isGameMaster())
            return;

        if (newLevel % 10 != 0) // return if not multiple of ten
            return;

        uint32 money = 0;

        switch (newLevel)
        {
            case 10:
                money = 150000;
                break;
            case 20:
                money = 250000;
                break;
            case 30:
                money = 400000;
                break;
            case 40:
                money = 500000;
                break;
            case 50:
                money = 600000;
                break;
            case 60:
                money = 1000000;
                break;
            case 70:
                money = 1500000;
                break;
            case 80:
                money = 2000000;
                break;
            default:
                return;
        }

        MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

        MailDraft draft("Parabéns", "Você está avançando no jogo e merece uma recompensa. Pegue isto e gaste em algo útil. :)");

        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        if (money > 0)
            draft.AddMoney(money);

        if (newLevel == 80)
        {
            Item* item = Item::CreateItem(EMBLEM_OF_CONQUEST, 300, 0);
            item->SaveToDB(trans);
            draft.AddItem(item);
        }

        draft.SendMailTo(trans, MailReceiver(player), sender);
        CharacterDatabase.CommitTransaction(trans);
    }
};

void AddSC_level_rewards()
{
    new level_rewards;
}
