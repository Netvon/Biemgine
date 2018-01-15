#pragma once
#include <string>

namespace spacebiem {
    class Player
    {
    public:

        static Player& current();
        ~Player();

        const std::string& getName() const;
        void setName(const std::string& pName);

        std::string saveLocation() const;
        std::string resourceLocation() const;
        std::string resolvePath(const std::string& filename);

        static constexpr char* playerOne();
        static constexpr char* playerTwo();
        static constexpr char* playerThree();
    private:
        Player();
        std::string name;
    };
}

