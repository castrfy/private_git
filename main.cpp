#include <iostream>
#include <httplib.h>
#include <string>
#include <helps.h>

#define SERVER_URL "https://pgit.zenofy.tr"

int main(int argc, char *argv[])
{
    switch (argc)
    {
        case 1:
        
            {
                using namespace httplib;
                Client cli(SERVER_URL);


                if (auto res = cli.Get("/")) {
                    int status = res->status;
                    std::string body = res->body;
                    std::cout << status << std::endl;
                    std::cout << body << std::endl;
                }
            }
            
            break;
        case 2:
            if (std::strcmp(argv[1], "pull") == 0)
            {
                std::cout << "pulling..." << std::endl;
            }
            else 
            if (std::strcmp(argv[1], "push") == 0)
            {
                std::cout << "pushing..." << std::endl;
            }
            else 
            {
                printUsage();
            }
            break;
        default:
            printUsage();
            break;
    }





    //std::cout << "sa" << std::endl;
}
