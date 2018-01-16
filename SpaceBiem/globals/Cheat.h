#pragma once

#include "stdafx.h"
#include <map>

namespace spacebiem
{
    class Cheat
    {
    public:
        static Cheat & Cheat::Instance()
        {
            static Cheat instance;
            return instance;
        }

        bool isEnabled(const std::string & pCheatId) const
        {
            auto cheat = cheats.find(pCheatId);
            if (cheat == cheats.end()) return false;

            return cheat->second;
        }

        void setEnabled(const std::string & pCheatId, bool pEnabled)
        {
            cheats.insert_or_assign(pCheatId, pEnabled);
        }

    private:
        std::map<std::string, bool> cheats;

        Cheat()
        {
            setEnabled("god", false);
            setEnabled("ai_bounce", false);
        }
    };
}
