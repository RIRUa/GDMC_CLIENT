//
//  error.hpp
//  GDMC_CLIENT
//
//  Created by 渡辺奈央騎 on 2021/12/15.
//

#ifndef error_hpp
#define error_hpp

#include <iostream>

using error = std::string;

namespace Error {
    const error curlEasyPerformMissing = "curl_easy_perform() in failed.";
}


#endif /* error_hpp */
