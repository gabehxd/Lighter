#include "CommandEvent.h"
#include "../commands/Info.h"
#include "../commands/Ping.h"
#include "../commands/Role.h"
#include "../commands/ChromeCount.h"
#include "../lighterwise.h"

using namespace std;

CommandEvent::CommandEvent()
{
  insert<Ping>();
  insert<Role>();
  insert<Info>();
  insert<ChromeCount>();
}

void CommandEvent::registerEvent(dpp::cluster &bot)
{
  bot.on_ready(
      [&bot, this](const dpp::ready_t &) -> dpp::task<void>
      {
        if (dpp::run_once<struct register_bot_commands>())
        {
          
          #ifdef NDEBUG
          co_await bot.co_guild_bulk_command_delete(lighterwise::guild);
          co_await bot.co_global_bulk_command_create(getBuiltCommandsList(bot.me.id));
          #else
          co_await bot.co_guild_bulk_command_create(getBuiltCommandsList(bot.me.id), lighterwise::guild);
          #endif

        }
        co_return;
      });

  bot.on_slashcommand(
      [&bot, this](const dpp::slashcommand_t &event) -> dpp::task<void>
      {
        try
        {
          co_await commandMap.at(event.command.get_command_name()).get()->run(bot, event);
        }
        catch (out_of_range &ex)
        {
          cout << "OUT OF RANGE WHILE LOOKING FOR " << event.command.get_command_name() << endl;
        }

        co_return;
      });
  /*
    bot.on_autocomplete([&bot, this](const dpp::autocomplete_t &event) ->
    dpp::task<void>
                        {
                          auto cmd =
    commandMap.at(event.command.get_command_name()).get();

                          for (dpp::command_option opt : event.options) {
                            if (opt.focused)
                            {
                              cmd->createAutoComplete(bot, event, opt);
                            }
                           }
                          co_return; });
  */
}

vector<dpp::slashcommand>
CommandEvent::getBuiltCommandsList(const dpp::snowflake id)
{
  vector<dpp::slashcommand> list;

  for (auto const &value : std::views::values(commandMap))
  {
    list.push_back(value.get()->BuildCommand(id));
  }
  return list;
}

template <typename Command>
void CommandEvent::insert()
{
  auto command = make_unique<Command>();
  commandMap.emplace(command->getCommand(), move(command));
}
