#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream  in{"log.bin", std::ios::binary};
    int hours;
    in.read(reinterpret_cast<char*>(&hours),sizeof(hours));
    in.close();

    int plus;
    std::cout << "何時間勉強しましたか : ";
    std::cin >> plus;
    std::cout << std::endl << "合計勉強時間は " << (hours += plus) << " 時間です。" << std::endl;

    std::cout << std::endl << "セーブして終了するには、何かを入力してください : ";
    std::string str;
    std::cin >> str;
    if (str == "reset"){
        std::ofstream  out{"log.bin", std::ios::binary};
        out.write(0, 1);
        out.close();
        return 0;
    }else{
        std::ofstream  out{"log.bin", std::ios::binary};
        out.write(reinterpret_cast<const char*>(&hours), sizeof(hours));
        out.close();
        return 0;
    }
}