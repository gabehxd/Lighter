#pragma once

#include "Event.h"

class VerifyEvent : public Event
{
public:
    ~VerifyEvent() = default;
    virtual void registerEvent(dpp::cluster &) override;
};