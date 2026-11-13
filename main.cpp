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

    std::string line, level, text;
    int linenum = 0;
    std::map<std::string, int> cntlevels;
    std::map<std::string, int> cnterrors;

    cntlevels["INFO"] = 0; cntlevels["WARNING"] = 0; cntlevels["ERROR"] = 0;

    while (std::getline(file, line)) {
        linenum++;
        auto pos = line.find(':');
        if(pos != std::string::npos){
            level = line.substr(0, pos);
            if (cntlevels.count(level) != 0){
                text = line.substr(pos + 1);
                auto posnotspace = text.find_first_not_of(' ');
                if (posnotspace != std::string::npos){
                    text = text.substr(posnotspace);
                    if (level == "ERROR"){
                        cnterrors[text]++;
                    }
                }else{
                    std::cout << "Пустой текст лога в строке " << linenum << "!\n";
                    continue;
                }
            }else{
                std::cout << "Неизвестный уровень лога в строке " << linenum << "!\n";
                continue;
            }
        }else{
            std::cout << "Строка " << linenum << " неверного формата!\n";
            continue;
        }

        cntlevels[level]++;

        level = "", error = "", text = "";
    }

    for (const auto& entry : cntlevels) {
        std::cout << entry.first << ": " << entry.second << '\n';
    }

    std::string name;
    int kol = 0;
    if (cnterrors.empty()){
        std::cout << "Ошибок нет\n";
    }else{
        for (const auto& entry : cnterrors) {
            if (entry.second > kol){
                kol = entry.second;
            }
        }
        std::cout << "Чаще всего встречалась(-ись) ошибка(-и):\n";
        for (const auto& entry : cnterrors) {
            if (kol == entry.second){
                std::cout << entry.first << " - " << entry.second << " раз(-а)" << "\n";
            }
        }
    }
}