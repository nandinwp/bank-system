#include "HttpService.h"
#include <stdexcept>
#include <iostream>

HttpService::HttpService() 
{
	baseUrl = PROTOCOL + std::string(SERVER) + POINT + "/" + VERSION;
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

HttpService::~HttpService() 
{
	curl_global_cleanup();
}

std::string HttpService::buildUrl(const std::string& endpoint) const 
{
	return baseUrl + endpoint;
}

size_t HttpService::writeCallback(void* contents, size_t size, size_t nmemb, void* userp) 
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string HttpService::getRequest(const std::string& endpoint)
{
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = buildUrl(endpoint);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}

std::string HttpService::postRequest(const std::string& endpoint, const std::string& data) 
{
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = buildUrl(endpoint);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}