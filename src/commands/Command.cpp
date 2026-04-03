#include "Command.h"

dpp::slashcommand Command::BuildCommand(const dpp::snowflake &id)
{
    dpp::slashcommand command(getCommand(), getDescription(), id);
    addOptions(command);
    return command;
}