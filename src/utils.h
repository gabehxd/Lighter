#pragma once

#include <dpp/dpp.h>

namespace utils
{
    dpp::task<std::map<dpp::snowflake, dpp::guild_member>> getMemberList(dpp::cluster &, const dpp::snowflake &);
    dpp::task<dpp::role *> getHighestRole(dpp::guild_member &);
    template <typename T>
    T getOrDefault(dpp::command_value value, T fallback)
    {
        try
        {
            T res = get<T>(value);
            return res;
        }
        catch (std::bad_variant_access &ex)
        {
            return fallback;
        }
    }
}