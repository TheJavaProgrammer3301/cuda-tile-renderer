#include <curl/curl.h>
#include <vector>
#include <stdexcept>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t totalSize = size * nmemb;
    auto* buffer = reinterpret_cast<std::vector<uint8_t>*>(userp);
    buffer->insert(buffer->end(), (uint8_t*)contents, (uint8_t*)contents + totalSize);
    return totalSize;
}

std::vector<uint8_t> fetchURL(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) throw std::runtime_error("Failed to initialize libcurl");

    std::vector<uint8_t> buffer;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error("libcurl error: " + std::string(curl_easy_strerror(res)));
    }

    curl_easy_cleanup(curl);
    return buffer;
}
