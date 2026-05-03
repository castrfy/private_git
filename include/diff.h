#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool calculate_diff(std::string filename1, std::string filename2)
{
    std::ifstream file1(filename1);
    std::ifstream file2(filename2);
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

    int line_diff = data1.size() - data2.size();
    int create_count = 0;
    int removed_count = 0;
    std::cout << "Dosya satır sayısı farkı: " << line_diff << std::endl;
    if (line_diff == 0)
    {
        for (size_t index = 0; index < data1.size(); index++)
        {
            if (data1[index] != data2[index])
            {
                removed.push_back(index);
                removed_count++;
                created.push_back(index);
                create_count++;
            }
        }
        
    }
    else if (line_diff < 0) //data2 büyük
    {
        std::vector<int> shifted(data1.size(), 0);
        
        // çıkarılanlar
        size_t found_i = -1;
        for (size_t k = 1; k <= -line_diff; k++)
        {   
            if (data1[0] == data2[0])
            {
                found_i = 0;
                break;
            }
            if (data1[0] == data2[0 + k])
            {
                found_i = k;
                break;
            }
        }
        if (found_i == -1)
        {
            shifted[0] = -1;
            removed.push_back(0);
            removed_count++;
        }
        else shifted[0] = found_i;
        
        for (size_t i = 1; i < data1.size(); i++)
        {
            if (shifted[i-1] != -1 && data1[i] == data2[i + shifted[i-1]])
            {
                shifted[i] = shifted[i-1];
            }
            else if (data1[i] != data2[i])
            {
                for (size_t k = 1; k <= -line_diff; k++)
                {
                    found_i = -1;
                    if (data1[i] == data2[i + k])
                    {
                        found_i = k;
                        break;
                    }
                }
                if (found_i == -1) 
                {
                    shifted[i] = -1;
                    removed.push_back(i);
                    removed_count++;
                }
                else
                {
                    shifted[i] = found_i;
                }
            }
        }
        
        for (size_t i = data1.size(); i < data2.size(); i++)
        {
            if (data1[i - shifted[i-1]] == data2[i])
            {
                shifted[i] = shifted[i-1];
            }
            else if (data1[i] != data2[i])
            {
                for (size_t k = 1; k <= -line_diff; k++)
                {
                    found_i = -1;
                    if (data1[i] == data2[i + k])
                    {
                        found_i = k;
                        break;
                    }
                }
                if (found_i == -1) 
                {
                    shifted[i] = -1;
                    removed.push_back(i);
                    removed_count++;
                }
                else
                {
                    shifted[i] = found_i;
                }
            }
        }
        


        for (size_t i = 0; i < shifted.size(); i++)
        {
            std::cout << "[" << i << "] " << shifted[i] << std::endl;
        }
        
        
        // eklenenler
        for (size_t i = 0; i < data2.size(); i++)
        {
            if (data1[i] != data2[i])
            {
                if (data1[i - shifted[i]] != data2[i])
                {
                    created.push_back(i);
                    create_count++;
                }
                
            }
            
        }

    }
    else //data1 büyük
    {
        for (size_t i = 0; i < data2.size(); i++)
        {
            if (data2[i] != data1[i])
                if (data2[i - create_count] != data1[i])
                {
                    created.push_back(i);
                    create_count++;
                }
            
        }
        for (size_t i = data1.size() - create_count - 1 ; i < data1.size(); i++)
        {
            
            if (data2[i - create_count] != data1[i])
            {
                created.push_back(i);
                create_count++;
            }
            
        }
    }
    

    std::string output1;
    std::string output2;
    
    std::cout << create_count << " satır eklendi" << std::endl;
    std::cout << removed_count << " satır çıkarıldı" << std::endl;
    for (size_t i : created)
    {
        std::cout << "+ [" << i + 1 << "]:" << (line_diff < 0 ? data2[i] : data1[i]) << std::endl;
    }
    for (size_t i : removed)
    {
        std::cout << "- [" << i + 1 << "]:" << (line_diff < 0 ? data1[i] : data2[i]) << std::endl;
    }
    
    return true;

}