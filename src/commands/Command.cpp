#include "Command.h"

dpp::slashcommand Command::BuildCommand(const dpp::snowflake &id)
{
    dpp::slashcommand command(getCommand(), getDescription(), id);
    addOptions(command);
    command.set_interaction_contexts(getInteractionsContext());
    return command;
}
