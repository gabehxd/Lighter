#include "HelloEvent.h"

using namespace std;

void HelloEvent::registerEvent(dpp::cluster &bot)
{
  bot.on_message_create([&bot, this](this auto, const dpp::message_create_t &event) -> dpp::task<void>
                        {
      static string mention = "<@" + bot.me.id.str() + ">";
      if (event.msg.content.contains(mention))
      {
        co_await bot.co_channel_typing(event.msg.channel_id);
        co_await event.owner->co_sleep(2);
        co_await event.co_reply(dpp::message("Hi"));
      } });
}
