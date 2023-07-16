#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

int main(int argc, char *argv[]) {
    // public api key given by the doc.
    const char* api_key = "at_JE901c9XrEoPE5gQwcvtkSeURZSkE";
    const char* base_url = "https://www.whoisxmlapi.com/whoisserver/WhoisService";
    char url[256];

    if (argc < 2) {
        printf("Usage: program_name <domain_name>\n");
        return 1;
    }

    // Extract domain name from the URL
    char* domain_name = argv[1];
    if (strstr(domain_name, "https://") == domain_name) {
        domain_name += strlen("https://");
    } else if (strstr(domain_name, "http://") == domain_name) {
        domain_name += strlen("http://");
    }

    if (strstr(domain_name, "www.") == domain_name) {
        domain_name += strlen("www.");
    }

    // Construct the complete URL
    sprintf(url, "%s?apiKey=%s&domainName=%s", base_url, api_key, domain_name);

    printf("Getting data for: %s\n", argv[1]);

    CURL* curl_handle = curl_easy_init();
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);

        // Set file to save the response
        char filename[256];
        strcpy(filename, domain_name);
        FILE* response_file = fopen(filename, "w");
        if (response_file) {
            curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, response_file);

            // Perform the HTTP request here
            CURLcode res = curl_easy_perform(curl_handle);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }

            fclose(response_file);
        } else {
            printf("Error opening file for writing.\n");
        }
        printf("File written.\n");
        curl_easy_cleanup(curl_handle);
    }

    return 0;
}
