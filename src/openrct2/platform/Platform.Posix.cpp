#pragma region Copyright (c) 2014-2017 OpenRCT2 Developers
/*****************************************************************************
* OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
*
* OpenRCT2 is the work of many authors, a full list can be found in contributors.md
* For more information, visit https://github.com/OpenRCT2/OpenRCT2
*
* OpenRCT2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* A full copy of the GNU General Public License can be found in licence.txt
*****************************************************************************/
#pragma endregion

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || defined(__FreeBSD__)

#include <cstring>
#include <pwd.h>
#include <cstdlib>
#include "../core/String.hpp"
#include "Platform2.h"
#include "platform.h"

namespace Platform
{
    uint32 GetTicks()
    {
        return platform_get_ticks();
    }

    std::string GetEnvironmentVariable(const std::string &name)
    {
        return String::ToStd(getenv(name.c_str()));
    }

    std::string GetEnvironmentPath(const char * name)
    {
        auto value = getenv(name);
        if (value == nullptr)
        {
            return std::string();
        }
        else
        {
            auto colon = std::strchr(value, ':');
            if (colon == nullptr)
            {
                return std::string(value);
            }
            else
            {
                return std::string(value, colon);
            }
        }
    }

    std::string GetHomePath()
    {
        std::string path;
        auto pw = getpwuid(getuid());
        if (pw != nullptr)
        {
            path = pw->pw_dir;
        }
        else
        {
            path = GetEnvironmentVariable("HOME");
        }
        if (path.empty())
        {
            path = "/";
        }
        return path;
    }

    std::string GetInstallPath()
    {
        utf8 path[MAX_PATH];
        platform_resolve_openrct_data_path();
        platform_get_openrct_data_path(path, sizeof(path));
        return path;
    }
}

#endif
