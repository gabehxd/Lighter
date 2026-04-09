#pragma once

#include <dpp/dpp.h>

namespace utils
{
    dpp::task<std::map<dpp::snowflake, dpp::guild_member>> getMemberList(dpp::cluster &, const dpp::snowflake &);
    dpp::task<dpp::role *> getHighestRole(dpp::guild_member &);
}