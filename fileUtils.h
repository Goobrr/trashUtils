#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Writer {
    private:
        std::ofstream f;
        
    public:
        int length = 0;

        Writer(char *filename){
            f.open(filename, std::ios::binary);
        }

        template <typename T>
        void write(T value){;
            f.write(reinterpret_cast<char *>(&value), sizeof(T));

            length += sizeof(T);
        }

        int close(){
            f.close();
            std::cout << "wrote " << length << " bytes\n";

            return length;
        }
};

template <>
void Writer::write<std::string>(std::string text){
    write<int>(text.length());
    for(int i = 0; i < text.length(); i++){
        write<char>((char)text.at(i));
    }
}

class Reader {
    private:
        std::ifstream f;
        char* buffer = new char[8];

    public:
        int count = 0;

        Reader(char *filename){
            f.open(filename, std::ios::binary);
        }

        template <typename T>
        T read(){
            T res;
            f.read(reinterpret_cast<char *>(&res), sizeof(T));
            count += sizeof(T);

            return res;
        }

        int close(){
            f.close();
            std::cout << "read " << count << " bytes\n";

            return count;
        }
};

template <>
std::string Reader::read<std::string>(){
    std::string res;

    int len = read<int>();
    res.resize(len);

    f.read(res.data(), len);
    count += len;

    return res;
}