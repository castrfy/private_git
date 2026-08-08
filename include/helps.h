#pragma once
#include <string_view>
#include <vector>
#include <iostream>

#define IGNORE_FILE_NAME ".ignore"

std::string_view name;
std::string version = "v1.0";

void printUsage()
{
    std::cout << "Usage: " << name << " [init|pull|add|commit|push|auth] [options: -h]" << std::endl;
}
void printVersion()
{
    std::cout << name << " Version " << version << std::endl;
}