#pragma once

#include "Command.h"

class Role : public Command
{
public:
    virtual ~Role() = default;
    virtual std::string getCommand() const override;
    virtual std::string getDescription() const override;
    virtual dpp::task<void> run(dpp::cluster &, const dpp::slashcommand_t &) override;
    virtual void addOptions(dpp::slashcommand &) override;
    virtual std::vector<dpp::interaction_context_type> getInteractionsContext() override;
};