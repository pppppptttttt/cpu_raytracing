#pragma once

#include "mth/mth.h"
#include "utilities/logger.h"

static struct __Dummy
{
    __Dummy()
    {
        LoggerConfig& cfg = LOG::LoggerConfigInstance();
        cfg.FilePath = "log.txt";
        cfg.OutputToConsole = true;
        cfg.OutputToFile = true;
    }
} _;