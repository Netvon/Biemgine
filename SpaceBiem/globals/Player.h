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
        std::string progressLocation() const;
        std::string resolvePath(const std::string& filename);

        static constexpr char* playerOneName()
        {
            return "biem";
        }

        static constexpr char* playerTwoName()
        {
            return "mummy";
        }

        static constexpr char* playerThreeName()
        {
            return "snowman";
        }

        static Player playerOne() {
            return Player(playerOneName());
        }

        static Player playerTwo() {
            return Player(playerTwoName());
        }

        static Player playerThree() {
            return Player(playerThreeName());
        }

    private:
        Player();
        Player(const std::string& name);
        std::string name;
    };
}

