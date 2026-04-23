#include <iostream>
#include <filesystem>
#include <fstream>
#include <helps.h>
#include <vector>
#include <stdlib.h>
#pragma once

namespace fs = std::filesystem;

void clear_commission()
{
    fs::path dirPath =  ".pgit";

    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {

        std::ofstream commit_data(".pgit/.commit");
        commit_data.close(); 
        
    } 
    else 
    {
        std::cerr << name << "isn't initialized properly" << std::endl << "\ttry using \"" << name <<" init\"" << std::endl;
        abort();
    }
}
void initialize()
{
    
    fs::path dirPath =  ".pgit";

    if (fs::exists(dirPath) && fs::is_directory(dirPath)) {
        std::cout << "Folder exists!" << std::endl;
        

        std::ofstream auth_data(".pgit/.auth");
        std::ofstream commit_data(".pgit/.commit");
        std::ofstream branch_info(".pgit/.branch");


        auth_data.close(); 
        commit_data.close(); 
        branch_info.close(); 
        std::cout << "Initialized!" << std::endl;

        
    }
    else 
    {
        std::cout << "Folder does not exist." << std::endl;
        if (fs::create_directory(dirPath))
        {
            std::cout << "Folder created!" << std::endl;
            
            std::ofstream auth_data(".pgit/.auth");
            std::ofstream commit_data(".pgit/.commit");
            std::ofstream branch_info(".pgit/.branch");


            auth_data.close(); 
            commit_data.close(); 
            branch_info.close(); 
        }
    }
}

int addFile(std::string filepath, bool isOnRecursive=false)
{
    if (!fs::exists(fs::path(filepath)))
    {
        std::cerr << "File not found \"" << filepath << "\"" << std::endl;
        return 0;
    }

    // .ignore file
    static std::vector<std::string> ignores;
    static bool ignores_loaded = false;
    if (!ignores_loaded) 
    {
        if (fs::exists(IGNORE_FILE_NAME))
        {
            std::cout << "Reading " << IGNORE_FILE_NAME << std::endl;
            ignores.push_back(IGNORE_FILE_NAME);
            ignores.push_back(".pgit");
            std::ifstream ignore_file(IGNORE_FILE_NAME);
            if (ignore_file.is_open())
            {
                std::string line;
                while (std::getline(ignore_file, line)) 
                {
                    ignores.push_back(line);
                }

                ignore_file.close();
            }
            else
            {
                std::cerr << "[!] Error: Couldn't open " << IGNORE_FILE_NAME << std::endl;
            }
        }
        else std::cout << "There is no " << IGNORE_FILE_NAME << " file every file will be included." << std::endl;
        
        std::cout << ignores.size() << " file names will be ignored" << std::endl;
        ignores_loaded = true;
    }


    int counter = 0;
    static std::vector<std::string> oldcommit;
    static bool oldcommit_loaded = false;
    static std::vector<std::string> newcommit;
    

    //old commit
    if (!oldcommit_loaded)
    {
        fs::path commit_path(".pgit/.commit");
        if (fs::exists(commit_path)&& !fs::is_directory(commit_path))
        {

            std::ifstream commit_file(commit_path);
            if (commit_file.is_open()) 
            {
                std::string line;
                while (std::getline(commit_file, line)) 
                {
                    oldcommit.push_back(line);
                }
            }
            else 
            {
                std::cerr << "Unable to open .commit file" << std::endl;
                commit_file.close();
            }
        }
        else 
        {
            std::cout << name << " not initialized properly" << std::endl << "\ttry running \"" << name << " init\"" << std::endl;;
        }
        oldcommit_loaded = true;
    }


    

    if (!fs::is_directory(filepath)) 
    {
        //ignoring
        bool willignore = false;
        for (std::string ignore : ignores)
        {
            if ( std::string(filepath).find(ignore) != std::string::npos){
                willignore = true;

            }
            
        }
        
        if (!willignore) 
        {
            
            newcommit.push_back(fs::path(filepath.c_str()));
            counter++;
        }
    }
    else
    {
        for (const auto& entry : fs::directory_iterator(filepath)) {
            counter += addFile(entry.path().c_str(), true);
        }
    }


    if (!isOnRecursive)
    {
        std::cout << "Writing into .commit file..." << std::endl;

        fs::path commit_path(".pgit/.commit");
        std::ofstream newfile(commit_path);
        if (newfile.is_open())
        {
            for (std::string line : newcommit)
            {
                
                newfile << line << std::endl;
            }

            newfile.close();

            std::cout << "Writing finished." << std::endl;

            //std::cout << "File \"" << filepath << "\" added to commission" << std::endl;
        }
        else
        {
            std::cerr << "Unable to open .commit file" << std::endl;
            newfile.close();
        }
                
    }
    
    
    return counter;
}

std::vector<std::string> get_file_paths()
{
    fs::path commit_path("./.pgit/.commit");
    if (fs::exists(commit_path) && !fs::is_directory(commit_path))
    {
        std::ifstream file(commit_path);
        std::string line;

        if (file.is_open()) 
        {
            std::vector<std::string> files_to_commit;
            while (std::getline(file, line)) 
            {
                files_to_commit.push_back(line);
            }
            
            file.close();

            return files_to_commit;
        }
        else
        {
            std::cerr << name << "isn't initialized properly" << std::endl << "\ttry using \"" << name <<" init\"" << std::endl;
            abort();
            return std::vector<std::string>();
        }
    }
    else
    {
        std::cerr << name << "isn't initialized properly" << std::endl << "\ttry using \"" << name <<" init\"" << std::endl;
        abort();
        return std::vector<std::string>();
    }
}
