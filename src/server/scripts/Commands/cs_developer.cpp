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
 *
 * This script was made by Rochet2
 */

#include "ScriptPCH.h"
#include "Chat.h"

class developer_commandscript : public CommandScript
{
public:
    developer_commandscript() : CommandScript("developer_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand commandTable[] =
        {
            { "developer",      SEC_GAMEMASTER,     false,  &HandleDeveloperCommand,    "", NULL },
            { NULL,             0,                  false,  NULL,                       "", NULL }
        };
        return commandTable;
    }

    static bool HandleDeveloperCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            if (handler->GetSession()->GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER))
                handler->GetSession()->SendAreaTriggerMessage("|cffff0000Dev mode is ON|r");
            else
                handler->GetSession()->SendAreaTriggerMessage("|cffff0000Dev mode is OFF|r");
            return true;
        }

        std::string argstr = (char*)args;

        if (argstr == "on")
        {
            handler->GetSession()->SendAreaTriggerMessage("|cffff0000Dev mode is ON|r");
            handler->GetSession()->GetPlayer()->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER);
            return true;
        }

        if (argstr == "off")
        {
            handler->GetSession()->SendAreaTriggerMessage("|cffff0000Dev mode is OFF|r");
            handler->GetSession()->GetPlayer()->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_DEVELOPER);
            return true;
        }

        handler->SendSysMessage(LANG_USE_BOL);
        handler->SetSentErrorMessage(true);
        return false;
    }
};

void AddSC_developer_commandscript()
{
    new developer_commandscript();
}
