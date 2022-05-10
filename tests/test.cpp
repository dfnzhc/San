//
// Created by 秋鱼 on 2022/5/6.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <filesystem>
#include "win_platform.hpp"

namespace fs = std::filesystem;

TEST_CASE("TestPlatform", "[TestLog]")
{
    Yuan::WinPlatform platform;
    
    auto code = platform.initialize();
    
    if (code == Yuan::ExitCode::Success)
	{
		code = platform.mainLoop();
	}
    
    platform.terminate(code);
}