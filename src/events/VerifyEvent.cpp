#include "VerifyEvent.h"
#include "../lighterwise.h"

using namespace std;

void VerifyEvent::registerEvent(dpp::cluster &bot)
{
    bot.on_message_create([&bot, this](this auto, const dpp::message_create_t &event) -> dpp::task<void>
                          {
        if (event.msg.author == bot.me)
            co_return;

        if (event.msg.channel_id == lighterwise::verifyChannel)
        {
            if (event.msg.content == lighterwise::keyword)
            {
                //TODO: move msg to dm?
                dpp::message message(dpp::utility::user_mention(event.msg.author.id) + " Welcome to the server!");
                message.set_allowed_mentions(true);
                
                co_await bot.set_audit_reason("Verified").co_guild_member_add_role(lighterwise::guild, event.msg.author.id, lighterwise::verifiedRole);
                co_await bot.co_message_delete(event.msg.id, lighterwise::verifyChannel);
                dpp::confirmation_callback_t res = co_await event.co_send(message);
                if (!res.is_error())
                {
                    dpp::message m = res.get<dpp::message>();
                    co_await event.owner->co_sleep(3);
                    co_await bot.co_message_delete(m.id, lighterwise::verifyChannel);
                }
            }
            else{
                dpp::message message(dpp::utility::user_mention(event.msg.author.id) + " Wrong keyword!");
                message.set_allowed_mentions(true);

                dpp::confirmation_callback_t res = co_await event.co_send(message);
                co_await bot.co_message_delete(event.msg.id, lighterwise::verifyChannel);
                if (!res.is_error())
                {
                    dpp::message m = res.get<dpp::message>();
                    co_await event.owner->co_sleep(3);
                    co_await bot.co_message_delete(m.id, lighterwise::verifyChannel);
                }
            }
        } 
        co_return; });
}