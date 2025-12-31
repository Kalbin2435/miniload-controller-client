#include <iostream>
#include "AgoransState.hpp"
#include "curl/curl.h"

namespace main_window {
    AgoransState& AgoransState::getInstance() {
        static AgoransState instance;
        return instance;
    }

    AgoransState::AgoransState() {
        std::cout << "TEST\n";
        FetchAgoransData();
        Agoran Agoran1 = { 1, AgoranStatus::StandBy, AgoranMode::Automatic, 0, 0, 0 };
        Agoran Agoran2 = { 2, AgoranStatus::StandBy, AgoranMode::Automatic, 0, 0, 0 };

        agorans_list_.push_back(Agoran1);
        agorans_list_.push_back(Agoran2);
    }

    void AgoransState::FetchAgoransData() {
        std::cout << "FetchAgoransData called\n";
        CURL* curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                std::cout << "GOOD!\n";
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
        // load data of active warehouse from database
        // start up agorans as many as in active warehouse
        // nothing else can ever change the active warehouse again :)
        // make getter that allowes getting information about current active warehouse
    }
    AgoransState::~AgoransState() {
        /*
           defined deconstructor as private
           to prevent someone( future me :) )
           from forgetting about it and
           accidently calling the destructor
           */
    }
}
