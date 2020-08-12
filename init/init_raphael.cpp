/*
 * Copyright (c) 2021, The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include "vendor_init.h"
#include "property_service.h"

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info *)__system_property_find(prop);

    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvik_properties()
{
    struct sysinfo sys;

    sysinfo(&sys);
    if (sys.totalram > 7168ull * 1024 * 1024)
    {
        // 8GB & 12GB RAM
        property_override("dalvik.vm.heapstartsize", "32m");
        property_override("dalvik.vm.heapgrowthlimit", "512m");
        property_override("dalvik.vm.heapsize", "768m");
        property_override("dalvik.vm.heapmaxfree", "64m");
    }
    else
    {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        property_override("dalvik.vm.heapstartsize", "16m");
        property_override("dalvik.vm.heapgrowthlimit", "256m");
        property_override("dalvik.vm.heapsize", "512m");
        property_override("dalvik.vm.heapmaxfree", "32m");
    }

    property_override("dalvik.vm.heaptargetutilization", "0.5");
    property_override("dalvik.vm.heapminfree", "8m");
}

void load_raphael()
{
    property_override("ro.build.fingerprint", "Xiaomi/raphael/raphael:11/RKQ1.200826.002/V12.5.6.0.RFKCNXM:user/release-keys");
    property_override("ro.build.product", "raphael");
    property_override("ro.product.device", "raphael");
    property_override("ro.product.model", "Redmi K20 Pro");
}

void load_raphaelglobal()
{
    property_override("ro.build.fingerprint", "Xiaomi/raphael/raphael:11/RKQ1.200826.002/V12.5.2.0.RFKMIXM:user/release-keys");
    property_override("ro.build.product", "raphael");
    property_override("ro.product.device", "raphael");
    property_override("ro.product.model", "Mi 9T Pro");
}

void load_raphaelin()
{
    property_override("ro.build.fingerprint", "Xiaomi/raphaelin/raphaelin:11/RKQ1.200826.002/V12.5.1.0.RFKINXM:user/release-keys");
    property_override("ro.build.product", "raphaelin");
    property_override("ro.product.device", "raphaelin");
    property_override("ro.product.model", "Redmi K20 Pro");
}

void vendor_load_properties()
{
    std::string region = android::base::GetProperty("ro.boot.hwc", "");

    if (region.find("CN") != std::string::npos)
    {
        load_raphael();
    }
    else if (region.find("GLOBAL") != std::string::npos)
    {
        load_raphaelglobal();
    }
    else if (region.find("INDIA") != std::string::npos)
    {
        load_raphaelin();
    }
    load_dalvik_properties();
}
