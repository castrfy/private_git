#include <fstream>
#include <iostream>
#include <httplib.h>
#include <file_management.h>

bool push( std::string repo, std::string branch)
{
    std::vector<std::string> filepaths(get_file_paths());
    if (filepaths.empty())
    {
        std::cerr << "There is no files added to the commission!" << std::endl << "\ttry using \"" << name <<" add [<filepath>|<dirpath>]\"" << std::endl;
        return false;
    }


    for (std::string filename : filepaths)
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "- File \""<< filename << "\" Doesnt Exists" << std::endl;
            return false;

        }

        std::vector<char> buffer(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
        file.close();

        // Sunucuya bağlan
        httplib::Client client(SERVER_URL);

        httplib::Headers headers = {
            { "X-Filename", filename }
        };

        
        auto res = client.Post(
            std::string("/upload?repo=") + repo ,
            headers,
            buffer.data(),
            buffer.size(),
            "application/octet-stream"
        );

        if (res) 
        {
            if (res->status != 201)
            {
                std::cerr << "- \"" << filename << "\" Error " << res->status << ": " << res->body << std::endl;
                return false;
            }
            else
            {
                std::cout << "+ \"" << filename << "\" " << res->body << std::endl;
            }
        } 
        else 
        {
            std::cerr << "- \"" << filename << "\" Connection Error: " << httplib::to_string(res.error()) << std::endl;
            return false;
        }
    }
    return true;
    
}