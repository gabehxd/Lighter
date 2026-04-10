#include "ChromeCount.h"
#include "../utils.h"

using namespace std;

std::string ChromeCount::getCommand() const
{
    return "chromecount";
}

std::string ChromeCount::getDescription() const
{
    return "Count the total amount of pulls you have for ZenlessZoneZero!";
}

dpp::task<void> ChromeCount::run(dpp::cluster &, const dpp::slashcommand_t &event)
{
    int64_t rSig = utils::getOrDefault<int64_t>(event.get_parameter("residual_signal"), 0) / 20;
    int64_t fSig = utils::getOrDefault<int64_t>(event.get_parameter("fading_signal"), 0) / 90;
    int64_t mChrome = utils::getOrDefault<int64_t>(event.get_parameter("monochrome"), 0) / 160;
    int64_t pChrome = get<int64_t>(event.get_parameter("polychrome")) / 160;
    int64_t total = rSig + fSig + mChrome + pChrome;

    dpp::embed embed = dpp::embed()
                           .set_color(0xff2fbe)
                           .set_title("Encrypted Master Tape Count")
                           .set_thumbnail("https://static.wikia.nocookie.net/zenless-zone-zero/images/4/40/Item_Encrypted_Master_Tape.png");
    if (total > 0)
    {
        embed.set_description(to_string((total)) + " total pulls!");
        if (rSig > 0)
        {
            embed.add_field(
                "Residual Signal",
                to_string(rSig) + " pulls");
        }
        if (fSig > 0)
        {
            embed.add_field(
                "Fading Signal",
                to_string(fSig) + " pulls");
        }
        if (mChrome > 0)
        {
            embed.add_field(
                "Monochrome",
                to_string(mChrome) + " pulls");
        }
        if (pChrome > 0)
        {
            embed.add_field(
                "Polychrome",
                to_string(pChrome) + " pulls");
        }
    }
    else
    {
        embed.set_description("broke :(");
    }

    dpp::message msg(event.command.channel_id, embed);

    co_await event.co_reply(msg);

    co_return;
}

void ChromeCount::addOptions(dpp::slashcommand &cmd)
{
    cmd.add_option(dpp::command_option(dpp::co_integer, "polychrome", "The amount of Polychromes you have", true))
        .add_option(dpp::command_option(dpp::co_integer, "monochrome", "The amount of Monochrome you have", false))
        .add_option(dpp::command_option(dpp::co_integer, "fading_signal", "The amount of Fading Signal you have", false))
        .add_option(dpp::command_option(dpp::co_integer, "residual_signal", "The amount of Residual Singal you have", false));
}
