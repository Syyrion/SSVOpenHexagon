#include <sol/sol.hpp>
#include "SSVOpenHexagon/Core/RandomNumberGenerator.hpp"

namespace hg::LevelScripting
{
    class Lua
    {
    private:
        sol::state lua;
    public:
        Lua();
        
        void initRandom(random_number_generator& rng);
    };
} // namespace hg::LevelScripting
