#pragma once

#include "Command.h"

class ChromeCount : public Command
{
public:
    ~ChromeCount() = default;
    std::string getCommand() const override;
    std::string getDescription() const override;
    dpp::task<void> run(dpp::cluster &, const dpp::slashcommand_t &) override;
    virtual void addOptions(dpp::slashcommand &) override;
};
