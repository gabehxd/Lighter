#include "utils.h"

using namespace std;

namespace utils
{
    dpp::task<map<dpp::snowflake, dpp::guild_member>> getMemberList(dpp::cluster &bot, const dpp::snowflake &guild_id)
    {
        size_t cnt;
        int highest = 0;
        map<dpp::snowflake, dpp::guild_member> list;
        do
        {
            dpp::confirmation_callback_t confirm = co_await bot.co_guild_get_members(guild_id, 1000, highest);
            dpp::guild_member_map members = confirm.get<dpp::guild_member_map>();
            cnt = members.size();
            ranges::max_element(members, [](auto &a, auto &b)
                                { return a.first < b.first; });
            list.insert(members.begin(), members.end());
        } while (cnt >= 1000);

        co_return list;
    }

    dpp::task<dpp::role *> getHighestRole(dpp::guild_member &member)
    {
        dpp::role *highest = nullptr;
        for (auto r : member.get_roles())
        {
            auto role = dpp::find_role(r);
            if (highest == nullptr)
            {
                highest = role;
            }
            else
            {
                if (role == nullptr)
                    continue;

                if (*highest < *role)
                    highest = role;
            }
        }

        co_return highest;
    }
}