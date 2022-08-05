#include "helper.h"

static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

#define BLUE "\033[34m"
#define RESET "\033[39m"

void download_file(char* path, char* url)
{
    CURL* curl;
    FILE* fh;
    curl = curl_easy_init();
    if (curl != NULL) {
        fh = fopen(path, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fh);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fh);
    } else {
        fprintf(
            stderr, "Error: could not download: %s from url: %s\n", path, url);
    }
}

// TODO: windows
int make_directory(char* path) { return mkdir(path, S_IRWXU); }
