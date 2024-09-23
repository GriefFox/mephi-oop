#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include "prog.hpp"
#include <fstream>

namespace Prog1 {
// функция освобождения занятой памяти
    const char * game(const char**str){
        FILE *fd = fopen("../list.txt", "r");
        if (fd == nullptr){
            throw std::runtime_error("Error in open file");
        }
        int flag = 0;
        char *buf = nullptr;
        size_t size = 0;
        ssize_t a = 0;
        char last = '\0';
        char lastlast = '\0';
        char *laststr = nullptr;
        char *lastlaststr = nullptr;

        const char *before;
        const char **tmp = str;
        while (*tmp != NULL){
            before = *tmp;
            tmp++;
        }
        last = before[strlen(before)-1];
        lastlast = before[strlen(before) - 2];
        do{
            a = getline(&buf, &size, fd);
            size = strlen(buf);
            buf[size-1] = '\0';
            if (buf[0]+0x20 == last){
                tmp = str;
                while (*tmp != NULL){
                    //printf("%s %s\n", buf, *tmp);
                    if (strcmp(buf, *tmp) == 0){
                        flag = 1;
                        break;
                    }
                    tmp++;
                }
                if (flag){
                    flag = 0;
                    continue;
                }
                delete[] laststr;
                laststr = new char[strlen(buf)+1];
                strcpy(laststr, buf);
                // laststr = buf;

                break;
            }
            if (buf[0]+0x20 == lastlast){
                tmp = str;
                while (*tmp != NULL){
                    if (strcmp(buf, *tmp) == 0){
                        flag = 1;
                        break;
                    }
                    tmp++;
                }
                if (flag){
                    flag = 0;
                    continue;
                }
                delete[] lastlaststr;
                lastlaststr = new char[strlen(buf)+1];
                strcpy(lastlaststr, buf);
                // lastlaststr = buf;
            }
        }while(a != -1);
        if (laststr == NULL){
            if (lastlaststr == NULL){
                fclose(fd);
                throw std::runtime_error("Couldn't find a city");
            }
            free(buf);
            buf = new char[strlen(lastlaststr)+1];
            strcpy(buf, lastlaststr);
        } else {
            free(buf);
            buf = new char[strlen(laststr)+1];
            strcpy(buf, laststr);
        }
        fclose(fd);
        delete[]lastlaststr;
        delete[]laststr;
        return buf;
    }

    std::string game(std::vector<std::string> str){
        std::string filename = "list.txt";
        std::ifstream fd(filename);
        if (!fd.is_open()){
            throw std::runtime_error("Error in open file");
        }
      
        std::string tmp = str.back();
        char last = tmp.back();
        char lastlast = tmp[tmp.length()-2];
        bool fl;

        std::string laststr = "";
        std::string lastlaststr = "";

        std::string line;
        while (getline(fd, line)){
          if (line.front()+0x20 == last){
            fl = 0;
            for (uint i=0;i<str.size();i++){
              if (line == str[i]){
                fl = 1;
                break;
              }
            }
            if (fl)
              continue;
            
            laststr = line;
          }
          if (line.front()+0x20 == lastlast){
            fl = 0;
            for (uint i=0;i<str.size();i++){
              if (line == str[i]){
                fl = 1;
                break;
              }
            }
            if (fl)
              continue;

            lastlaststr = line;
          }
        }
        
        std::string res;
        if (laststr.size()==0){
          if (lastlaststr.size() == 0){
            fd.close();
            throw std::runtime_error("Couldn't find a city");
          }
            res = lastlaststr;
        } else {
            res = laststr;
        }
        
        fd.close();
        return res;
    }
}
