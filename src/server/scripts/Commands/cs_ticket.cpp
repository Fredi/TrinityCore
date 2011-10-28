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
Name: ticket_commandscript
%Complete: 100
Comment: All ticket related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "AccountMgr.h"
#include "TicketMgr.h"
#include "Chat.h"

class ticket_commandscript : public CommandScript
{
public:
    ticket_commandscript() : CommandScript("ticket_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand ticketResponseCommandTable[] =
        {
            { "append",         SEC_MODERATOR,      false, &HandleGMTicketResponseAppendCommand,   "", NULL },
            { "appendln",       SEC_MODERATOR,      false, &HandleGMTicketResponseAppendLnCommand, "", NULL },
            { NULL,             0,                  false, NULL,                                   "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "list",           SEC_MODERATOR,      false, &HandleGMTicketListCommand,             "", NULL },
            { "onlinelist",     SEC_MODERATOR,      false, &HandleGMTicketListOnlineCommand,       "", NULL },
            { "viewname",       SEC_MODERATOR,      false, &HandleGMTicketGetByNameCommand,        "", NULL },
            { "viewid",         SEC_MODERATOR,      false, &HandleGMTicketGetByIdCommand,          "", NULL },
            { "close",          SEC_MODERATOR,      false, &HandleGMTicketCloseByIdCommand,        "", NULL },
            { "closedlist",     SEC_MODERATOR,      false, &HandleGMTicketListClosedCommand,       "", NULL },
            { "escalatedlist",  SEC_GAMEMASTER,     false, &HandleGMTicketListEscalatedCommand,    "", NULL },
            { "delete",         SEC_ADMINISTRATOR,  false, &HandleGMTicketDeleteByIdCommand,       "", NULL },
            { "reset",          SEC_ADMINISTRATOR,  false, &HandleGMTicketResetCommand,            "", NULL },
            { "assign",         SEC_GAMEMASTER,     false, &HandleGMTicketAssignToCommand,         "", NULL },
            { "unassign",       SEC_GAMEMASTER,     false, &HandleGMTicketUnAssignCommand,         "", NULL },
            { "comment",        SEC_MODERATOR,      false, &HandleGMTicketCommentCommand,          "", NULL },
            { "togglesystem",   SEC_ADMINISTRATOR,  false, &HandleToggleGMTicketSystem,            "", NULL },
            { "escalate",       SEC_MODERATOR,      false, &HandleGMTicketEscalateCommand,         "", NULL },
            { "response",       SEC_MODERATOR,      false, NULL,             "", ticketResponseCommandTable },
            { "complete",       SEC_MODERATOR,      false, &HandleGMTicketCompleteCommand,         "", NULL },
            { NULL,             0,                  false, NULL,                                   "", NULL }
        };
        return commandTable;
    }

    static bool HandleGMTicketListCommand(ChatHandler* handler, char const* /*args*/)
    {
        sTicketMgr->ShowList(*handler, false);
        return true;
    }

    static bool HandleGMTicketListOnlineCommand(ChatHandler* handler, char const* /*args*/)
    {
        sTicketMgr->ShowList(*handler, true);
        return true;
    }

    static bool HandleGMTicketListClosedCommand(ChatHandler* handler, char const* /*args*/)
    {
        sTicketMgr->ShowClosedList(*handler);
        return true;
    }

    static bool HandleGMTicketListEscalatedCommand(ChatHandler* handler, char const* /*args*/)
    {
        sTicketMgr->ShowEscalatedList(*handler);
        return true;
    }

    static bool HandleGMTicketGetByIdCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || ticket->IsClosed() || ticket->IsCompleted())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }

        SQLTransaction trans = SQLTransaction(NULL);
        ticket->SetViewed();
        ticket->SaveToDB(trans);

        handler->SendSysMessage(ticket->FormatMessageString(*handler, true).c_str());
        return true;
    }

    static bool HandleGMTicketGetByNameCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        std::string name(args);
        if (!normalizePlayerName(name))
            return false;

        // Detect target's GUID
        uint64 guid = 0;
        if (Player* player = sObjectAccessor->FindPlayerByName(name.c_str()))
            guid = player->GetGUID();
        else
            guid = sObjectMgr->GetPlayerGUIDByName(name);
        // Target must exist
        if (!guid)
        {
            handler->SendSysMessage(LANG_NO_PLAYERS_FOUND);
            return true;
        }
        // Ticket must exist
        GmTicket *ticket = sTicketMgr->GetTicketByPlayer(guid);
        if (!ticket)
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }

        SQLTransaction trans = SQLTransaction(NULL);
        ticket->SetViewed();
        ticket->SaveToDB(trans);

        handler->SendSysMessage(ticket->FormatMessageString(*handler, true).c_str());
        return true;
    }

    static bool HandleGMTicketCloseByIdCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || ticket->IsClosed() || ticket->IsCompleted())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }
        // Ticket must be assigned to player, who tries to close it.
        uint64 guid = handler->GetSession()->GetPlayer()->GetGUID();
        if (ticket->IsAssignedNotTo(guid))
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETCANNOTCLOSE, ticket->GetId());
            return true;
        }
        sTicketMgr->CloseTicket(ticket->GetId(), guid);
        sTicketMgr->UpdateLastChange();

        std::string msg = ticket->FormatMessageString(*handler, handler->GetSession()->GetPlayer()->GetName(), NULL, NULL, NULL);
        handler->SendGlobalGMSysMessage(msg.c_str());

        // Inform player, who submitted this ticket, that it is closed
        if (Player* player = ticket->GetPlayer())
            if (player->IsInWorld())
            {
                WorldPacket data(SMSG_GMTICKET_DELETETICKET, 4);
                data << uint32(GMTICKET_RESPONSE_TICKET_DELETED);
                player->GetSession()->SendPacket(&data);
            }
        return true;
    }

    static bool HandleGMTicketAssignToCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* sTicketId = strtok((char*)args, " ");
        uint32 ticketId = atoi(sTicketId);

        char* sTarget = strtok(NULL, " ");
        if (!sTarget)
            return false;

        std::string target(sTarget);
        if (!normalizePlayerName(target))
            return false;

        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || ticket->IsClosed())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }

        // Get target information
        uint64 targetGuid = sObjectMgr->GetPlayerGUIDByName(target.c_str());
        uint64 targetAccId = sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);
        uint32 targetGmLevel = AccountMgr::GetSecurity(targetAccId, realmID);
        // Target must exist and have administrative rights
        if (!targetGuid || AccountMgr::IsPlayerAccount(targetGmLevel))
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETASSIGNERROR_A);
            return true;
        }
        // If already assigned, leave
        if (ticket->IsAssignedTo(targetGuid))
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETASSIGNERROR_B, ticket->GetId());
            return true;
        }
        // If assigned to different player other than current, leave
        Player* player = handler->GetSession()->GetPlayer();
        if (ticket->IsAssignedNotTo(player->GetGUID()))
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETALREADYASSIGNED, ticket->GetId(), target.c_str());
            return true;
        }
        // Assign ticket
        SQLTransaction trans = SQLTransaction(NULL);
        ticket->SetAssignedTo(targetGuid, AccountMgr::IsAdminAccount(targetGmLevel));
        ticket->SaveToDB(trans);
        sTicketMgr->UpdateLastChange();

        std::string msg = ticket->FormatMessageString(*handler, NULL, target.c_str(), NULL, NULL);
        handler->SendGlobalGMSysMessage(msg.c_str());
        return true;
    }

    static bool HandleGMTicketUnAssignCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket *ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || ticket->IsClosed())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }
        // Ticket must be assigned
        if (!ticket->IsAssigned())
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETNOTASSIGNED, ticket->GetId());
            return true;
        }
        // Get security level of player, whom this ticket is assigned to
        uint32 security = SEC_PLAYER;
        Player* assignedPlayer = ticket->GetAssignedPlayer();
        if (assignedPlayer && assignedPlayer->IsInWorld())
            security = assignedPlayer->GetSession()->GetSecurity();
        else
        {
            uint64 guid = ticket->GetAssignedToGUID();
            uint32 accountId = sObjectMgr->GetPlayerAccountIdByGUID(guid);
            security = AccountMgr::GetSecurity(accountId, realmID);
        }
        // Check security
        Player* player = handler->GetSession()->GetPlayer();
        if (security > uint32(player->GetSession()->GetSecurity()))
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETUNASSIGNSECURITY);
            return true;
        }

        SQLTransaction trans = SQLTransaction(NULL);
        ticket->SetUnassigned();
        ticket->SaveToDB(trans);
        sTicketMgr->UpdateLastChange();

        std::string msg = ticket->FormatMessageString(*handler, NULL, ticket->GetAssignedToName().c_str(), player->GetName(), NULL);
        handler->SendGlobalGMSysMessage(msg.c_str());
        return true;
    }

    static bool HandleGMTicketCommentCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* tguid = strtok((char*)args, " ");
        uint32 ticketId = atoi(tguid);

        char* comment = strtok(NULL, "\n");
        if (!comment)
            return false;

        GmTicket *ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || ticket->IsClosed())
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }
        // Cannot comment ticket assigned to someone else
        Player* player = handler->GetSession()->GetPlayer();
        if (ticket->IsAssignedNotTo(player->GetGUID()))
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETALREADYASSIGNED, ticket->GetId());
            return true;
        }

        SQLTransaction trans = SQLTransaction(NULL);
        ticket->SetComment(comment);
        ticket->SaveToDB(trans);
        sTicketMgr->UpdateLastChange();

        std::string msg = ticket->FormatMessageString(*handler, NULL, ticket->GetAssignedToName().c_str(), NULL, NULL);
        msg += handler->PGetParseString(LANG_COMMAND_TICKETLISTADDCOMMENT, player->GetName(), comment);
        handler->SendGlobalGMSysMessage(msg.c_str());

        return true;
    }

    static bool HandleGMTicketDeleteByIdCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket)
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }
        if (!ticket->IsClosed())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETCLOSEFIRST);
            return true;
        }

        std::string msg = ticket->FormatMessageString(*handler, NULL, NULL, NULL, handler->GetSession()->GetPlayer()->GetName());
        handler->SendGlobalGMSysMessage(msg.c_str());

        sTicketMgr->RemoveTicket(ticket->GetId());
        sTicketMgr->UpdateLastChange();

        if (Player* player = ticket->GetPlayer())
            if (player->IsInWorld())
            {
                // Force abandon ticket
                WorldPacket data(SMSG_GMTICKET_DELETETICKET, 4);
                data << uint32(GMTICKET_RESPONSE_TICKET_DELETED);
                player->GetSession()->SendPacket(&data);
            }
        return true;
    }

    static bool HandleGMTicketResetCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (sTicketMgr->GetOpenTicketCount() > 0)
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETPENDING);
            return true;
        }
        else
        {
            sTicketMgr->ResetTickets();
            handler->SendSysMessage(LANG_COMMAND_TICKETRESET);
        }

        return true;
    }

    static bool HandleToggleGMTicketSystem(ChatHandler* handler, char const* /*args*/)
    {
        bool status = !sTicketMgr->GetStatus();
        sTicketMgr->SetStatus(status);
        handler->PSendSysMessage(status ? LANG_ALLOW_TICKETS : LANG_DISALLOW_TICKETS);
        return true;
    }

    static bool HandleGMTicketEscalateCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || !ticket->IsClosed() || ticket->IsCompleted() || ticket->GetEscalatedStatus() != TICKET_UNASSIGNED)
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }

        ticket->SetEscalatedStatus(TICKET_IN_ESCALATION_QUEUE);

        if (Player* player = ticket->GetPlayer())
            if (player->IsInWorld())
                sTicketMgr->SendTicket(player->GetSession(), ticket);

        sTicketMgr->UpdateLastChange();
        return true;
    }

    static bool HandleGMTicketCompleteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        uint32 ticketId = atoi(args);
        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || !ticket->IsClosed() || ticket->IsCompleted())
        {
            handler->SendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }

        if (Player* player = ticket->GetPlayer())
            if (player->IsInWorld())
                ticket->SendResponse(player->GetSession());

        sTicketMgr->UpdateLastChange();
        return true;
    }

    inline static bool _HandleGMTicketResponseAppendCommand(ChatHandler* handler, char const* args, bool newLine)
    {
        if (!*args)
            return false;

        char* sTicketId = strtok((char*)args, " ");
        uint32 ticketId = atoi(sTicketId);

        char* response = strtok(NULL, "\n");
        if (!response)
            return false;

        GmTicket* ticket = sTicketMgr->GetTicket(ticketId);
        if (!ticket || !ticket->IsClosed())
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETNOTEXIST);
            return true;
        }
        // Cannot add response to ticket, assigned to someone else
        Player* player = handler->GetSession()->GetPlayer();
        if (ticket->IsAssignedNotTo(player->GetGUID()))
        {
            handler->PSendSysMessage(LANG_COMMAND_TICKETALREADYASSIGNED, ticket->GetId());
            return true;
        }

        SQLTransaction trans = SQLTransaction(NULL);
        ticket->AppendResponse(response);
        if (newLine)
            ticket->AppendResponse("\n");
        ticket->SaveToDB(trans);

        return true;
    }

    static bool HandleGMTicketResponseAppendCommand(ChatHandler* handler, char const* args)
    {
        return _HandleGMTicketResponseAppendCommand(handler, args, false);
    }

    static bool HandleGMTicketResponseAppendLnCommand(ChatHandler* handler, char const* args)
    {
        return _HandleGMTicketResponseAppendCommand(handler, args, true);
    }
};

void AddSC_ticket_commandscript()
{
    new ticket_commandscript();
}
