/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
Name: vip_commandscript
%Complete: 100
Comment: All vip related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "Chat.h"

class vip_commandscript : public CommandScript
{
public:
    vip_commandscript() : CommandScript("vip_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand vipTokenCommandTable[] =
        {
            { "add",              SEC_ADMINISTRATOR,  false, &HandleVIPTokenAddCommand,       "", NULL },
            { "",                 SEC_PLAYER,         true,  &HandleVIPTokenCommand,          "", NULL },
            { NULL,               0,                  false, NULL,                            "", NULL }
        };
        static ChatCommand vipCommandTable[] =
        {
            { "add",            SEC_ADMINISTRATOR,  false, &HandleVIPAddCommand,              "", NULL },
            { "token",          SEC_PLAYER,         true,  NULL,              "", vipTokenCommandTable },
            { "",               SEC_PLAYER,         true,  &HandleVIPCommand,                 "", NULL },
            { NULL,             0,                  false, NULL,                              "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "vip",            SEC_PLAYER,         false, NULL,                    "", vipCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool GetAccountId(ChatHandler* handler, char const* args, uint32& accountId)
    {
        if (AccountMgr::IsModeratorAccount(handler->GetSession()->GetSecurity()))
        {
            if (!*args)
                return false;

            std::string accountName = strtok((char*)args, " ");

            if (!AccountMgr::normalizeString(accountName))
            {
                handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }

            accountId = AccountMgr::GetId(accountName);
            if (!accountId)
            {
                handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
                handler->SetSentErrorMessage(true);
                return false;
            }
        }
        else
            accountId = handler->GetSession()->GetAccountId();

        return true;
    }

    static uint32 GetTokens(uint32 accountId)
    {
        QueryResult result = LoginDatabase.PQuery("SELECT vip_tokens FROM account WHERE id = '%u'", accountId);
        return (*result)[0].GetUInt32();
    }

    static bool HandleVIPAddCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        ///- Get the command line arguments
        char* account = strtok ((char*)args, " ");
        char* duration = strtok (NULL," ");

        if (!account || !duration || !atoi(duration))
            return false;

        std::string accountName = account;
        uint32 durationSecs = atoi(duration) * 86400;
        std::string gm = handler->GetSession()->GetPlayerName();

        if (!AccountMgr::normalizeString(accountName))
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 targetAccountId = AccountMgr::GetId(accountName);
        if (!targetAccountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        /// can set vip only for target with less security
        /// This is also reject self apply in fact
        if (handler->HasLowerSecurityAccount(NULL, targetAccountId, true))
            return false;

        QueryResult resultLogin = LoginDatabase.PQuery("SELECT active FROM account_vip WHERE id = %u AND active = 1", targetAccountId);
        if (resultLogin)
        {
            LoginDatabase.PExecute("UPDATE account_vip "
                "SET gm = '%s', unsetdate = unsetdate + %u "
                "WHERE id = %u", gm.c_str(), durationSecs, targetAccountId);

            handler->PSendSysMessage("VIP atualizado.");

            return true;
        }

        LoginDatabase.PExecute("DELETE FROM account_vip WHERE id = %u", targetAccountId);

        LoginDatabase.PExecute("INSERT INTO account_vip "
            "(id, gm, setdate, unsetdate, active) "
            "VALUES ('%u', '%s', UNIX_TIMESTAMP(), UNIX_TIMESTAMP() + %u, 1)",
            targetAccountId, gm.c_str(), durationSecs);

        handler->PSendSysMessage("VIP setado com sucesso.");

        return true;
    }

    static bool HandleVIPCommand(ChatHandler* handler, char const* args)
    {
        uint32 accountId;

        if (!vip_commandscript::GetAccountId(handler, args, accountId))
            return false;

        uint32 days = AccountMgr::VipDaysLeft(accountId);

        if (days > 0)
            handler->PSendSysMessage("[VIP] O VIP expira em %u dia(s).", days);
        else
            handler->PSendSysMessage("[VIP] Esta conta não é VIP.");

        return true;
    }

    static bool HandleVIPTokenCommand(ChatHandler* handler, char const* args)
    {
        uint32 accountId;

        if (!vip_commandscript::GetAccountId(handler, args, accountId))
            return false;

        handler->PSendSysMessage("Tokens: %u", vip_commandscript::GetTokens(accountId));

        return true;
    }

    static bool HandleVIPTokenAddCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        ///- Get the command line arguments
        char* account = strtok((char*)args, " ");
        char* toAdd = strtok(NULL," ");

        if (!account || !toAdd || !atoi(toAdd))
            return false;

        std::string accountName = account;
        int32 tokens = atoi(toAdd);

        if (!AccountMgr::normalizeString(accountName))
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 accountId = AccountMgr::GetId(accountName);
        if (!accountId)
        {
            handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 have = vip_commandscript::GetTokens(accountId);
        int32 newTokens = int32(have) + tokens;

        if (newTokens <= 0)
        {
            handler->PSendSysMessage("Você removeu todos os tokens da conta  %s", accountName.c_str());
            newTokens = 0;
        }
        else
            handler->PSendSysMessage("Tokens da conta %s: %u", uint32(newTokens), accountName.c_str());

        LoginDatabase.PQuery("UPDATE account SET vip_tokens = %u WHERE id = '%u'", uint32(newTokens), accountId);
    }
};

void AddSC_vip_commandscript()
{
    new vip_commandscript();
}
