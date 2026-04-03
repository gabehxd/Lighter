#pragma once

#include "Command.h"

class Ping : public Command
{
public:
    ~Ping() = default;
    std::string getCommand() const override;
    std::string getDescription() const override;
    dpp::task<void> run(dpp::cluster&, const dpp::slashcommand_t&) override;
    virtual void addOptions(dpp::slashcommand&) override;
};