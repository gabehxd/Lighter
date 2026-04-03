#pragma once

#include "Event.h"
#include <unordered_map>
#include "../commands/Command.h"

class CommandEvent : public Event
{
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commandMap;
    std::vector<dpp::slashcommand> getBuiltCommandsList(const dpp::snowflake);
    template <typename Command>
    void insert();

public:
    CommandEvent();
    ~CommandEvent() = default;
    virtual void registerEvent(dpp::cluster &) override;
};