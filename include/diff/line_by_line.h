#include <string_view>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


bool calculate_diff_lbl(std::string_view filename1, std::string_view filename2)
{
    
    std::ifstream file1(filename1.data());
    std::ifstream file2(filename2.data());
    std::vector<std::string> data1;
    std::vector<std::string> data2;

    //reading
    std::string line1;
    if (file1.is_open())
    {
        while (std::getline(file1, line1))
        {
            data1.push_back(line1);
        }
    }
    else
    {
        std::cerr << "[!] Error: Couldn't open file1" << std::endl;
        return false;
    }

    std::string line2;
    if (file2.is_open())
    {
        while (std::getline(file2, line2))
        {
            data2.push_back(line2);
        }
    }
    else
    {
        std::cerr << "[!] Error: Couldn't open file2" << std::endl;
        return false;
    }

    //differencing
    std::vector<size_t> created; //index on file2
    std::vector<size_t> removed; //index on file1

    int line_diff = data2.size() - data1.size();
    std::cout << line_diff <<std::endl;

    if (line_diff == 0)
    {
        for (size_t i1 = 0; i1 < data1.size(); i1++)
        {
            if (data1[i1] != data2[i1])
            {
                removed.push_back(i1);
                
                for (size_t i_removed = 0; i_removed< removed.size(); i_removed++)
                {
                    if (data1[removed[i_removed]] == data2[i1])
                    {
                        removed.erase(removed.begin() + i_removed);
                    }
                    else
                    {
                        created.push_back(i1);
                    }
                }
            }
        }
    }
    else if (line_diff > 0) // file2 bigger 
    {
        for (size_t i1 = 0; i1 < data1.size(); i1++)
        {
            if (data1[i1] != data2[i1])
            {
                removed.push_back(i1);
                
                for (size_t i_removed = 0; i_removed< removed.size(); i_removed++)
                {
                    if (data1[removed[i_removed]] == data2[i1])
                    {
                        removed.erase(removed.begin() + i_removed);
                    }
                    else
                    {
                        created.push_back(i1);
                    }
                }
            }
        }
        
        const size_t last_i = data1.size() - 1;
        for (size_t i_remaining = 1; i_remaining <= line_diff; i_remaining++)
        {
            for (size_t i_removed = 0; i_removed< removed.size(); i_removed++)
            {
                if (data1[removed[i_removed]] == data2[last_i + i_remaining])
                {
                    removed.erase(removed.begin() + i_removed);
                }
                else
                {
                    created.push_back(last_i + i_remaining);
                }
            }
        }

    }
    else if (line_diff < 0) // file1 bigger  [TODO: NOT WORKING PROPERLY MAKE IT WORK]
    {
        std::cout << "a" << std::endl;
        for (size_t i1 = 0; i1 < data2.size(); i1++)
        {
            if (data1[i1] != data2[i1])
            {
                removed.push_back(i1);
                
                for (size_t i_removed = 0; i_removed< removed.size(); i_removed++)
                {
                    if (data1[removed[i_removed]] == data2[i1])
                    {
                        removed.erase(removed.begin() + i_removed);
                    }
                    else
                    {
                        created.push_back(i1);
                    }
                }
            }
        }
        
    }

    


    // result


    std::string output1;
    std::string output2;
    
    std::cout << created.size() << " satır eklendi" << std::endl;
    std::cout << removed.size() << " satır çıkarıldı" << std::endl;
    for (size_t i : removed)
    {
        std::cout << "- [" << i + 1 << "]:" << data1[i] << std::endl;
    }
    for (size_t i : created)
    {
        std::cout << "+ [" << i + 1 << "]:" << data2[i] << std::endl;
    }
    
    
    return true;

}