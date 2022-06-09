//
// Created by 秋鱼 on 2022/6/9.
//

#include "system_utils.hpp"

namespace San {

std::string GetCPUNameString()
{
    int nIDs = 0;
    int nExIDs = 0;

    char strCPUName[0x40] = {};

    std::array<int, 4> cpuInfo;
    std::vector<std::array<int, 4>> extData;

    __cpuid(cpuInfo.data(), 0);

    // Calling __cpuid with 0x80000000 as the function_id argument
    // gets the number of the highest valid extended ID.
    __cpuid(cpuInfo.data(), 0x80000000);

    nExIDs = cpuInfo[0];
    for (int i = 0x80000000; i <= nExIDs; ++i) {
        __cpuidex(cpuInfo.data(), i, 0);
        extData.push_back(cpuInfo);
    }

    // Interpret CPU strCPUName string if reported
    if (nExIDs >= 0x80000004) {
        memcpy(strCPUName, extData[2].data(), sizeof(cpuInfo));
        memcpy(strCPUName + 16, extData[3].data(), sizeof(cpuInfo));
        memcpy(strCPUName + 32, extData[4].data(), sizeof(cpuInfo));
    }

    return strlen(strCPUName) != 0 ? strCPUName : "Unknown";
}

} // San