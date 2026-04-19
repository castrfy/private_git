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

void addFile(std::string filepath)
{
    if (!fs::exists(fs::path(filepath)))
    {
        std::cerr << "File not found \"" << filepath << "\"" << std::endl;
        return;
    }
    if (fs::is_directory(filepath))
    {
        for (const auto& entry : fs::directory_iterator(filepath)) {
            addFile(entry.path().c_str());
        }
    }
    else 
    {
        fs::path commit_path(".pgit/.commit");
        if (fs::exists(commit_path)&& !fs::is_directory(commit_path))
        {
            std::ifstream file(commit_path);
            if (file.is_open()) 
            {
                std::vector<std::string> oldcommit;
                std::string line;
                while (std::getline(file, line)) 
                {
                    oldcommit.push_back(line);
                }
                
                file.close();

                std::ofstream newfile(commit_path);
                if (newfile.is_open())
                {
                    for (std::string line : oldcommit)
                    {
                        if (line != filepath )
                            newfile << line << std::endl;
                    }

                    newfile << filepath;
                    newfile.close();

                    std::cout << "File \"" << filepath << "\" added to commission" << std::endl;
                }
                else
                {
                    std::cerr << "Unable to open .commit file" << std::endl;
                    newfile.close();
                }
                
            } 
            else 
            {
                std::cerr << "Unable to open .commit file" << std::endl;
                file.close();
            }
        }
        else 
        {
            std::cout << name << " not initialized properly" << std::endl << "\ttry running \"" << name << " init\"" << std::endl;;
        }
    }
    
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
