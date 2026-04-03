#pragma once

#include "Command.h"

class Info : public Command
{
public:
    ~Info() = default;
    std::string getCommand() const override;
    std::string getDescription() const override;
    dpp::task<void> run(dpp::cluster &, const dpp::slashcommand_t &) override;
    virtual void addOptions(dpp::slashcommand &) override;
};