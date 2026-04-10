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
