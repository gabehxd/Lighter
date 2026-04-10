#pragma once

#include <string>
#include <dpp/dpp.h>

class Command
{
public:
    virtual ~Command() = default;
    virtual std::string getCommand() const = 0;
    virtual std::string getDescription() const = 0;
    virtual dpp::task<void> run(dpp::cluster &, const dpp::slashcommand_t &) = 0;
    dpp::slashcommand BuildCommand(const dpp::snowflake &);
    virtual void addOptions(dpp::slashcommand &) {}
    virtual void createAutoComplete(dpp::cluster &, const dpp::autocomplete_t &, const dpp::command_option &) {}
    virtual std::vector<dpp::interaction_context_type> getInteractionsContext()
    {
        return {dpp::itc_bot_dm, dpp::itc_guild, dpp::itc_private_channel};
    }
};
