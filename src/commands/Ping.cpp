#include <dpp/dpp.h>
#include "Ping.h"

using namespace std;

std::string Ping::getCommand() const
{
    return "ping";
}

std::string Ping::getDescription() const
{
    return "Pong";
}

dpp::task<void> Ping::run(dpp::cluster &, const dpp::slashcommand_t &event)
{
    co_await event.co_reply("Pong");
    co_return;
}

void Ping::addOptions(dpp::slashcommand &cmd)
{
    cmd.set_interaction_contexts({dpp::itc_bot_dm, dpp::itc_guild, dpp::itc_private_channel});
}
