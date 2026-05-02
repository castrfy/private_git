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
    std::vector<size_t> diff;

    int line_diff = data1.size() - data2.size();
    int diff_count = 0;
    std::cout << "Dosya satır sayısı farkı: " << line_diff << std::endl;
    if (line_diff == 0)
    {
        for (size_t index = 0; index < data1.size(); index++)
        {
            if (data1[index] != data2[index])
            {
                diff.push_back(index);
            }
        }
        
    }
    else
    {
        if (line_diff < 0) //data2 büyük
        {
            for (size_t i = 0; i < data1.size(); i++)
            {
                if (data1[i] != data2[i])
                {
                    if (data1[i - (diff_count + line_diff)] != data2[i])
                        {
                            if (data1[i - diff_count] != data2[i])
                            {
                                diff.push_back(i);
                                diff_count++;
                            }
                        }
                }
                else
                {
                    // aynı satır eşit ama önceki satırın klonu olabilir, diff_count
                }
            }
            for (size_t i = data2.size() - diff_count -2 ; i < data2.size(); i++)
            {
                
                if (data1[i] != data2[i])
                {
                    if (data1[i - (diff_count + line_diff)] != data2[i])
                        {
                            if (data1[i - diff_count] != data2[i])
                            {
                                diff.push_back(i);
                                diff_count++;
                            }
                        }
                }
                
            }
        }
        else //data1 büyük
        {
            for (size_t i = 0; i < data2.size(); i++)
            {
                if (data2[i] != data1[i])
                    if (data2[i - diff_count] != data1[i])
                    {
                        diff.push_back(i);
                        diff_count++;
                    }
                
            }
            for (size_t i = data1.size() - diff_count - 1 ; i < data1.size(); i++)
            {
                
                if (data2[i - diff_count] != data1[i])
                {
                    diff.push_back(i);
                    diff_count++;
                }
                
            }
        }
    }

    std::string output1;
    std::string output2;
    
    std::cout << diff_count << " satırda fark bulundu" << std::endl;
    for (size_t i : diff)
    {
        std::cout << "Yeni Satır " << i + 1 << ":" << std::endl << (line_diff < 0 ? data2[i] : data1[i]) << std::endl;
    }
    
    return true;

}