#pragma once
#include <iostream>

#define SERVER_URL "https://pgit.zenofy.tr"

char *name;
std::string version = "v1.0";

void printUsage()
{
    std::cout << "Usage: " << name << " [init|pull|add|commit|push|auth] [options: -h]" << std::endl;
}
void printVersion()
{
    std::cout << name << " Version " << version << std::endl;
}