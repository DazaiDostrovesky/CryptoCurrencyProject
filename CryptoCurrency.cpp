#include <iostream>
#include <curl/curl.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main() {
    string input;
    cout << "Enter coin name or contract address: ";
    cin >> input;  

    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize CURL" << endl;
        return 1;
    }

    string url = "https://api.coingecko.com/api/v3/coins/" + input;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\cacert.pem");

   string response;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        return 1;
    }

    auto data = json::parse(response);
    if (data.contains("market_data")) {
        cout << "Price (USD): $" << data["market_data"]["current_price"]["usd"] << "\n";
        cout << "24h Volume: $" << data["market_data"]["total_volume"]["usd"] << "\n";
        cout << "24h Change: " << data["market_data"]["price_change_percentage_24h"] << "%\n";
    } else {
        cerr << "Could not find market data for this coin." << endl;
    }

    curl_easy_cleanup(curl);
    return 0;
}


    


