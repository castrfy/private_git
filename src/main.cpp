#include <iostream>
#include <httplib.h>
#include <string>
#include <helps.h>
#include <network.h>
#include <file_management.h>





int main(int argc, char *argv[])
{
    name = argv[0];
    switch (argc)
    {
        case 1:
            printVersion();
            printUsage();
            
            break;
        case 2:
            {
                if (std::strcmp(argv[1], "init") == 0)
                {
                    std::cout << "initializing..." << std::endl;
                    initialize();

                }
                else if (std::strcmp(argv[1], "push") == 0)
                {
                    if (push("main","main")) 
                    {
                        std::cout << "Successfully pushed the commission" << std::endl;
                        clear_commission();
                    }
                }
                else if (std::strcmp(argv[1], "pull") == 0)
                {
                    if (pull("main","main")) 
                    {
                        std::cout << "Successfully pulled the latest version" << std::endl;
                        
                    }
                }
                else if (std::strcmp(argv[1], "--server-status") == 0)
                {
                    using namespace httplib;
                    Client cli(SERVER_URL);


                    if (auto res = cli.Get("/")) {
                        int status = res->status;
                        std::string body = res->body;
                        std::cout << "HTTP " << status << ": " << body << std::endl;
                    }
                }
                else 
                {
                    printUsage();
                }
            } break;
            
        case 3:
            {
                if (std::strcmp(argv[1], "pull") == 0)
                {
                    pull(argv[2],"main");
                }
                else if (std::strcmp(argv[1], "push") == 0)
                {
                    push(argv[2],"main");
                }
                else if (std::strcmp(argv[1], "add") == 0)
                {
                    
                    std::cout << addFile(argv[2]) <<" Files added to commission" << std::endl;
                }
                else 
                {
                    printUsage();
                }
            } break;
        default:
            printUsage();
            break;
    }





    //std::cout << "sa" << std::endl;
}
