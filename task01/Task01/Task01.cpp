#include <iostream>
#include <cstring>  // для strtok
#include <vector>
#include <string>

std::vector<std::string> splitString(const std::string& input, const char* delimiters) {
    std::vector<std::string> result;
    // Создаём копию строки (strtok_s её модифицирует)
    const size_t bufferSize = input.size() + 1;
    char* strCopy = new char[bufferSize];

    // Копируем с проверкой ошибки
    errno_t copyErr = strcpy_s(strCopy, bufferSize, input.c_str());
    if (copyErr != 0) {
        delete[] strCopy;
        throw std::runtime_error("Failed to copy string for tokenization");
    }

    // Контекст для strtok_s (хранит внутреннее состояние)
    char* context = nullptr;
    char* token = strtok_s(strCopy, delimiters, &context);

    while (token != nullptr) {
        result.emplace_back(token);  // эффективнее, чем push_back(string(token))
        token = strtok_s(nullptr, delimiters, &context);  // продолжаем с context
    }

    delete[] strCopy;  // освобождаем память
    return result;
    
}

int main() {
    std::string text = "https://alice.yandex.ru/chat/019bb202-04fb-4000-bba9-9883d5631e46/?utm_source=ya&utm_campaign=morda_header_oknyx&utm_medium=interface";
    const char* delims = "/";  // разделители: запятая, точка с запятой, вертикальная черта

    std::vector<std::string> tokens = splitString(text, delims);

    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}