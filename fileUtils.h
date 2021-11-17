#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

class Writer {
    public:
        std::ofstream f;
        int length = 0;

        Writer(char *filename){
            f.open(filename, std::ios::binary);
        }

        template <typename T>
        void write(T value){;
            f.write(reinterpret_cast<char *>(&value), sizeof(T));
            length += sizeof(T);
        }

        // compiler thinks this is is a primary template and not a template specialisation
        /*
        template <typename T>
        void write<std::string>(std::string text){;
        }
        */

        int close(){
            f.close();
            std::cout << "wrote " << length << " bytes\n";
            return length;
        }
};

class Reader {
    public:
        std::ifstream f;
        char* buffer = new char[8];

        Reader(char *filename){
            f.open(filename, std::ios::binary);
        }

        template <typename T>
        T read(){
            T res;
            f.read(reinterpret_cast<char *>(&res), sizeof(T));

            return res;
        }

        void close(){
            f.close();
        }
};


#endif