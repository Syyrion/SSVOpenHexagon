#include <sol/sol.hpp>

#include "SSVOpenHexagon/Core/LevelScripting.hpp"
#include "SSVOpenHexagon/Core/RandomNumberGenerator.hpp"

namespace hg::LevelScripting
{
    Lua::Lua()
    {
        // Create libraries
        // The os and debug libraries are never loaded
        
        lua.open_libraries(
            sol::lib::base,
            sol::lib::coroutine,
            sol::lib::string,
            sol::lib::table,
            sol::lib::math,
            sol::lib::io,
            sol::lib::package
        );

        // Clear malicious functions

        lua["io"]["popen"] = sol::lua_nil;
        lua["io"]["flush"] = sol::lua_nil;
        lua["io"]["write"] = sol::lua_nil;
        lua["io"]["setvbuf"] = sol::lua_nil;

        lua["math"]["randomseed"] = sol::lua_nil;

        lua["package"]["loadlib"] = sol::lua_nil;
        lua["package"]["searchpath"] = sol::lua_nil;
        lua["package"]["loaders"] = sol::lua_nil;

        // Redefine io.open

        lua.script(R"(
            local io_open = io.open
            io.open = function(filename, mode)
                return io_open(filename, mode == \"rb\" and mode or \"r\")
            end
        )");
    }

    void Lua::initRandom(random_number_generator& rng)
    {
        // Initialize random functions

        const auto rndReal = [&rng]() -> float
        {
            return rng.get_real<float>(0, 1);
        };

        const auto rndIntUpper = [&rng](int upper) -> float
        {
            return rng.get_int<int>(1, upper);
        };

        const auto rndInt = [&rng](int lower, int upper) -> float
        {
            return rng.get_int<int>(lower, upper);
        };
        
        lua["rndReal"] = rndReal;
        lua["rndIntUpper"] = rndIntUpper;
        lua["rndInt"] = rndInt;

        lua["u_rndSwitch"] = [rndReal, rndIntUpper, rndInt](int mode, int lower, int upper) -> float
        {
            switch (mode)
            {
            case 0:
                return rndReal();
            case 1:
                return rndIntUpper(upper);
            case 2:
                return rndInt(lower, upper);
            }
            SSVOH_ASSERT(false);
            return 0;
        };

        lua.set_function("math.random", sol::overload());
        
        lua.script(R"(
            math.random = function(a, b)
                return a and b 
            end
        )");
    }
} // namespace LevelScripting