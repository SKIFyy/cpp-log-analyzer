#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::ifstream file("logs.txt");
    if (!file) {
        std::cerr << "Cannot open logs.txt\n";
        return 1;
    }

    std::vector<std::string> errors;
    std::string line, level, error;
    int flag2 = 0, flagsp = 0;
    std::map<std::string, int> cntrs;

    while (std::getline(file, line)) {
        flag2 = 0;
        flagsp = 0;
        for (char symbol : line) {
            if (flagsp == 10){
                flagsp = 0;
                continue;
            }
            if (symbol == ':'){
                flag2 = 1;
                flagsp = 10; 
                continue;
            }
            if (flag2 == 0){
                level += symbol;
            }else if((flag2 == 1) & (level == "ERROR")){
                error += symbol;
            }
            
        }
        
        if (level == "ERROR"){
            errors.push_back(error);
        }

        if (level == "INFO"){
            cntrs["INFO"]++;
        }else if (level == "WARNING"){
            cntrs["WARNING"]++;
        }else if (level == "ERROR"){
            cntrs["ERROR"]++;
        }

        
        // std::cout << line << '\n';
        // std::cout << level << '\n';
        // std::cout << error << '\n';
        
        level = "", error = "";

    }
    
    int cnt = 0;
    std::map<std::string, int> cnterrors;
    for (std::string i : errors){
        for (std::string f : errors){
            if (i == f){
                cnt++;
            }
        }
        cnterrors[i] = cnt;
        cnt = 0;
    }

    std::string name;
    int kol = 0;
    for (const auto& entry : cnterrors) {
        if (entry.second > kol){
            kol = entry.second;
            name = entry.first;
        }
    }

    for (const auto& entry : cntrs) {
    std::cout << entry.first << ": " << entry.second << '\n';
    }
    std::cout << "Чаще всего встречалась ошибка:" << name << " " << kol << " раз" << "\n";
}