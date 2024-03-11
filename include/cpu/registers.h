#pragma once

const std::vector<std::string> cpu_register_names = {
    "zr",
    "at",
    "v0", "v1",
    "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9",
    "k0", "k1",
    "gp",
    "sp",
    "fp",
    "ra"
};

const std::vector<std::string> cop0_register_names = {
    "Index", "Random", "EntryLo0", "EntryLo1",
    "Context", "PageMask", "Wired", "Reserved",
    "BadVAddr", "Count", "EntryHi", "Compare",
    "Status", "Cause", "EPC", "PRId",
    "Config", "LLAddr", "WatchLo", "WatchHi",
    "XContext", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "CacheErr", "TagLo", "TagHi", "ErrorEPC",
    "Reserved"
};
