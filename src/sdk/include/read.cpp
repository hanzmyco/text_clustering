#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <map>
#include <thread>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

const int cols = 12048;
const int rows = 80000;
const int linesToRead = 100;
const char *filename = "all_in_one.txt";

int indices[linesToRead];

float dstData[linesToRead][cols];

void first100() {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    for(int i = 0; i < linesToRead; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            float data = 0;
            file.read((char *)(&data), sizeof(data));
            dstData[i][j] = data;
        }
    }

    file.close();
}

void seek100() {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    for(int i = 0; i < linesToRead; i++)
    {
        int idx = indices[i];
        file.seekg(idx * sizeof(float) * cols);
        for(int j = 0; j < cols; j++)
        {
            float data = 0;
            file.read((char *)(&data), sizeof(data));
            dstData[i][j] = data;
        }
    }
}

void mmap() {
    boost::iostreams::mapped_file_source file;
    file.open(filename, sizeof(float) * rows * cols);

    float *dataPtr = (float *)file.data();

    for(int i = 0; i < linesToRead; i++)
    {
        int idx = indices[i];
        float *rowPtr = dataPtr + idx * cols;

        for(int j = 0; j < cols; j++)
        {
            dstData[i][j] = rowPtr[j];
        }
    }
}


void read_line(int idx, float *rowPtr)
{
    for(int i = 0; i < cols; ++i)
    {
        dstData[idx][i] = rowPtr[i];
    }
}

void mmap_mt(){
    boost::thread_group threads;
    boost::iostreams::mapped_file_source file;
    file.open(filename, sizeof(float) * rows * cols);

    float *dataPtr = (float *)file.data();

    for(int i = 0; i < linesToRead; i++)
    {
        int idx = indices[i];
        float *rowPtr = dataPtr + idx * cols;
        threads.add_thread(new boost::thread(read_line, i, rowPtr));
    }
    threads.join_all();
}

int main()
{
    const int numOfRep = 100;

    /// setup functions
    typedef void (func_ptr)();
    std::map<std::string, func_ptr*> funcs;
    funcs.insert(std::make_pair("first100", first100));
    funcs.insert(std::make_pair("seek100", seek100));
    funcs.insert(std::make_pair("mmap", mmap));
    funcs.insert(std::make_pair("mmap_mt", mmap_mt));

    /// setup random numbers
    for(int i = 0; i < linesToRead; ++i)
    {
        indices[i] = rand() % rows;
    }

    for(const auto &pair : funcs)
    {
        const auto start = std::chrono::high_resolution_clock::now();

        for(int j = 0; j < numOfRep; ++j)
        {
            pair.second();
        }

        const auto end = std::chrono::high_resolution_clock::now();
        std::cout << pair.first << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(end
            - start).count() << "ms" << std::endl;
    }

    return 0;
}
