#include "Role.h"
#include "../lighterwise.h"
#include "../utils.h"

using namespace std;

dpp::task<map<dpp::snowflake, dpp::guild_member>> getMasterList(dpp::cluster &, dpp::snowflake);

string Role::getCommand() const
{
    return "role";
}

string Role::getDescription() const
{
    return "[ADMIN] Role tools";
}

void Role::addOptions(dpp::slashcommand &cmd)
{
    cmd.set_default_permissions(0);
    cmd.add_option(
        dpp::command_option(dpp::co_sub_command, "all", "[ADMIN] Give roles to all nonbot users")
            .add_option(dpp::command_option(dpp::co_role, "role", "Role to give", true)));

    cmd.set_interaction_contexts({dpp::interaction_context_type::itc_guild});
}

dpp::task<void> Role::run(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    dpp::command_interaction cmd_data = event.command.get_command_interaction();
    auto subcommand = cmd_data.options[0];
    if (subcommand.name == "all")
    {
        co_await event.co_thinking();
        dpp::snowflake target_id = get<dpp::snowflake>(event.get_parameter("role"));

        map<dpp::snowflake, dpp::guild_member> members = co_await utils::getMemberList(bot, event.command.guild_id);
        string auditStr = "Role given to everyone by: " + event.command.get_issuing_user().username;
        for (auto member : members)
        {
            if (member.second.get_user()->is_bot())
                continue;

            co_await bot.set_audit_reason(auditStr).co_guild_member_add_role(event.command.guild_id, member.first, target_id);
        }
        co_await event.co_follow_up(dpp::message("Role given out!"));
        co_return;
        }
    co_return;
}
