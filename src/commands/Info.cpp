#include "Info.h"

using namespace std;

std::string Info::getCommand() const
{
    return "info";
}

std::string Info::getDescription() const
{
    return "Infomration about Lighter";
}

dpp::task<void> Info::run(dpp::cluster &bot, const dpp::slashcommand_t &event)
{
    dpp::embed embed = dpp::embed()
                           .set_color(0x1b4d3e)
                           .set_title("About Lighter")
                           .set_thumbnail(bot.me.get_avatar_url())
                           .set_description("Lighter is helper bot for the /lighterwise Discord server.")
                           .set_footer(
                               dpp::embed_footer()
                                   .set_text("Made with C++ by Gabe"));

    dpp::message msg(event.command.channel_id, embed);
    msg.add_component(
        dpp::component()
            .add_component(
                dpp::component()
                    .set_label("Join the Discord")
                    .set_url("https://discord.gg/lighterwise")
                    .set_emoji("lighter_nui", dpp::snowflake(1450463229284319319))
                    .set_type(dpp::component_type::cot_button)
                    .set_style(dpp::cos_link))
            .add_component(
                dpp::component()
                    .set_label("Source Code")
                    .set_url("https://github.com/gabehxd/Lighter")
                    .set_emoji("wise_nui", dpp::snowflake(1450463298851176509))
                    .set_type(dpp::component_type::cot_button)
                    .set_style(dpp::cos_link)));

    co_await event.co_reply(msg);
    co_return;
}

void Info::addOptions(dpp::slashcommand &cmd)
{
    cmd.set_interaction_contexts({dpp::itc_bot_dm, dpp::itc_guild, dpp::itc_private_channel});
}
