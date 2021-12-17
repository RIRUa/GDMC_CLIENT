//
//  URLSession.hpp
//  GDMC_Client
//
//  Created by 渡辺奈央騎 on 2021/12/03.
//

#ifndef Request_hpp
#define Request_hpp

#include <iostream>
#include <curl/curl.h>
#include <regex>

#include "../util/error.hpp"

class URLSession {
    
    CURL *curl;
    CURLcode ret;
    
public:
    // コンストラクタ
    URLSession();
    // デストラクタ
    ~URLSession();
    
    // GETメソッドでHTTPSessionをする関数
    std::string httpGet(const std::string url) throw(error);
    // POSTメソッドでHTTPSessionをする関数
    std::string httpPost(const std::string url, const std::string requestBody) throw(error);
    // PUTメソッドでHTTPSessionをする関数
    std::string httpPut(const std::string url, const std::string requestBody) throw(error);
    // DELETEメソッドでHTTPSessionをする関数
    std::string httpDelete(const std::string url) throw(error);
};

static size_t callbackWrite(char *ptr, size_t size, size_t nmemb, std::string *stream) {
        unsigned long dataLength = size * nmemb;
        stream->append(ptr, dataLength);
        return dataLength;
}

#endif /* Request_hpp */
