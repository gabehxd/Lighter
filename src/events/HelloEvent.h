#pragma once

#include "Event.h"

class HelloEvent : public Event
{
public:
    virtual ~HelloEvent() = default;
    virtual void registerEvent(dpp::cluster &) override;
};