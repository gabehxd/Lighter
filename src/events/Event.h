#pragma once

#include <dpp/dpp.h>

class Event
{
public:
    virtual ~Event() = default;
    virtual void registerEvent(dpp::cluster&) = 0;
};