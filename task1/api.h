#ifndef QT_API_API_H
#define QT_API_API_H
#include <bits/stdc++.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>
// Функция обратного вызова для записи данных
size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                     std::string* out);
// Функция для получения ответа на основе запроса
std::string getResponse(const std::string& userInput);
#endif
