#include "main.h"

using namespace std;

int main()
{
  ifstream tokenFile("token");
  if (!tokenFile.is_open())
  {
    cout << "Token not found!";
    return EXIT_FAILURE;
  }
  
  string token;
  tokenFile >> token;
  tokenFile.close();
  dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_members);
  

  /* Output simple log messages to stdout */
  bot.on_log(dpp::utility::cout_logger());

  vector<unique_ptr<Event>> events;
  events.push_back(make_unique<CommandEvent>());
  events.push_back(make_unique<VerifyEvent>());
  events.push_back(make_unique<HelloEvent>());
  //events.push_back(make_unique<MediaEvent>());

  for (const auto &event : events)
  {
    event.get()->registerEvent(bot);
  }

  bot.on_ready([&bot](const dpp::ready_t &)
               {
		if (dpp::run_once<struct register_bot_status>()) {
      
			bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_custom, "I love Wise"));
		} });

  /* Start the bot */
  bot.start(dpp::st_wait);

  return EXIT_SUCCESS;
}
