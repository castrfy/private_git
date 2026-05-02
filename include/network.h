#include <fstream>
#include <iostream>
#include <httplib.h>
#include <file_management.h>
#include <nlohmann/json.hpp>
#include <vector>

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
            std::cerr << "[-] File \""<< filename << "\" Doesnt Exists" << std::endl;
            return false;

        }

        std::vector<char> buffer(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );
        file.close();

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
                std::cerr << "[!] \"" << filename << "\" Error HTTP " << res->status << ": " << res->body << std::endl;
                return false;
            }
            else
            {
                std::cout << "[+] \"" << filename << "\" " << res->body << std::endl;
            }
        } 
        else 
        {
            std::cerr << "[!] \"" << filename << "\" Connection Error: " << httplib::to_string(res.error()) << std::endl;
            return false;
        }
    }
    return true;
    
}

bool pull( std::string repo, std::string branch)
{

    using json = nlohmann::json;

    httplib::Client client(SERVER_URL);
    auto res = client.Get(std::string("/repo/")+repo);

    if (res) 
    {
        if (res->status != 302)
        {
            std::cerr << "Error " << res->status << ":" << std::endl << res->body << std::endl;
            return false;
        }
        else
        {
            std::cout << "Found the files from the repo \"" << repo << "\" " << res->body << std::endl;
            std::vector<std::string> files = json::parse(res->body);
            std::cout << files.size() << std::endl;
            for (std::string file : files)
            {
                httplib::Client client(SERVER_URL);
                const fs::path parent_path = fs::path(file).parent_path();
                if (parent_path != "")
                if (!(fs::exists(parent_path) && fs::is_directory(parent_path)))
                {
                    if (fs::create_directories(parent_path)) std::cout << "Created folder for the file" << std::endl;
                    else 
                    {
                        std::cerr << "Couldnt create the folder needed.";
                        abort();
                    }
                }

                std::ofstream ofs(file, std::ios::binary);
                if (!ofs.is_open()) {
                    std::cerr << "[!] Couldn't create or update file: " << file << "\n";
                    return false;
                }

                httplib::Request req;
                req.method = "GET";
                req.path = "/pull";
                req.body = "{\"filename\": \"" + file +  "\", \"repo\": \"" + repo + "\"}";
                req.set_header("Content-Type", "application/json");
                req.content_receiver = (httplib::ContentReceiverWithProgress) [&](const char* data, size_t length, uint64_t offset, uint64_t totallength) -> bool {
                        ofs.write(data, length);
                        return true; 
                    };
                auto result = client.send(req);

                ofs.close();

                if (!result) {
                    std::cerr << "[!] Connection error: "
                            << httplib::to_string(result.error()) << "\n";
                    return false;
                }

                if (result->status != 200) {
                    std::cerr << "[!] Error, HTTP " << result->status
                            << ": " << result->body << "\n";
                    return false;
                }

                std::cout << "[+] pulled file \"" << file << "\"\n";
            }
            return true;
            
        }
    } 
    else 
    {
        std::cerr << "Connection Error while pulling the files: " << httplib::to_string(res.error()) << std::endl;
        return false;
    }
}
