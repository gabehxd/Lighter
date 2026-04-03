#include "VerifyEvent.h"
#include "../lighterwise.h"

using namespace std;

constexpr static dpp::snowflake channel(1376945413889851504);
constexpr static dpp::snowflake verified_role(1376936583080706058);
constexpr static string keyword("proxy");

void VerifyEvent::registerEvent(dpp::cluster &bot)
{
    bot.on_message_create([&bot](const dpp::message_create_t &event) -> dpp::task<void>
                          {
        if (event.msg.author == bot.me)
            co_return;

        if (event.msg.channel_id == channel)
        {
            if (event.msg.content == keyword)
            {
                dpp::message message(dpp::utility::user_mention(event.msg.author.id) + " Welcome to the server!");
                message.set_allowed_mentions(true);
                
                co_await bot.set_audit_reason("Verified").co_guild_member_add_role(lighterwise::guild, event.msg.author.id, verified_role);
                co_await bot.co_message_delete(event.msg.id, channel);
                dpp::confirmation_callback_t res = co_await event.co_send(message);
                if (!res.is_error())
                {
                    dpp::message m = res.get<dpp::message>();
                    co_await event.owner->co_sleep(3);
                    co_await bot.co_message_delete(m.id, channel);
                }
            }
            else{
                dpp::message message(dpp::utility::user_mention(event.msg.author.id) + " Wrong keyword!");
                message.set_allowed_mentions(true);

                dpp::confirmation_callback_t res = co_await event.co_send(message);
                co_await bot.co_message_delete(event.msg.id, channel);
                if (!res.is_error())
                {
                    dpp::message m = res.get<dpp::message>();
                    co_await event.owner->co_sleep(3);
                    co_await bot.co_message_delete(m.id, channel);
                }
            }
        } 
        co_return; });
}