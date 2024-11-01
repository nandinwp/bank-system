#pragma once
#include <string>
#include "Imports.h"

#define SERVER "example.com"
#define POINT "/api"
#define VERSION "v1"
#define PROTOCOL "https://"

class HttpService {
public:
    HttpService();
    ~HttpService();

    std::string getRequest(const std::string& endpoint);
    std::string postRequest(const std::string& endpoint, const std::string& data);

private:
    std::string baseUrl;
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp);

    std::string buildUrl(const std::string& endpoint) const;
};