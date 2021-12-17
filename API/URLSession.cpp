//
//  URLSession.cpp
//  GDMC_Client
//
//  Created by 渡辺奈央騎 on 2021/12/03.
//

#include "URLSession.hpp"

URLSession::URLSession(){
    this->curl = curl_easy_init();
    if (curl == NULL) {
        std::cerr << "curl_easy_init() failed." << std::endl;
        exit(1);
    }
}

URLSession::~URLSession(){
    curl_easy_cleanup(this->curl);
}

std::string URLSession::httpGet(const std::string url) throw(error) {
    
    std::string chunk;
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, callbackWrite);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &chunk);
    
    this->ret = curl_easy_perform(this->curl);
    
    if (this->ret != CURLE_OK) {
        std::cerr << "curl_easy_perform() in httpGet failed." << std::endl;
        throw Error::curlEasyPerformMissing;
    }
    
    return chunk;
}

std::string URLSession::httpPost(const std::string url, const std::string requestBody) throw(error) {
    std::string chunk;
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POST, 1);
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, requestBody.length());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, callbackWrite);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(this->curl, CURLOPT_PROXY, "");
    
    this->ret = curl_easy_perform(curl);
    
    if (this->ret != CURLE_OK) {
        std::cerr << "curl_easy_perform() in httpPost failed." << std::endl;
        throw Error::curlEasyPerformMissing;
    }
    
    return chunk;
}

std::string URLSession::httpPut(const std::string url, const std::string requestBody) throw(error) {
    std::string chunk;
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, requestBody.length());
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, callbackWrite);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(this->curl, CURLOPT_PROXY, "");
    
    this->ret = curl_easy_perform(curl);
    
    if (this->ret != CURLE_OK) {
        std::cerr << "curl_easy_perform() in httpPut failed." << std::endl;
        throw Error::curlEasyPerformMissing;
    }
    
    return chunk;
}

std::string URLSession::httpDelete(const std::string url) throw(error) {
    std::string chunk;
    curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(this->curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, callbackWrite);
    curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &chunk);
    
    this->ret = curl_easy_perform(this->curl);
    
    if (this->ret != CURLE_OK) {
        std::cerr << "curl_easy_perform() in httpDelete failed." << std::endl;
        throw Error::curlEasyPerformMissing;
    }
    
    return chunk;
}
