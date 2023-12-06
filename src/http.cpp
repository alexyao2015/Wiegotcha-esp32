#include <esp_http_server.h>

#include <string>

/* Our URI handler function to be called during GET /uri request */
esp_err_t get_handler(httpd_req_t *req)
{
    /* Send a simple response */
    // build path based on url path. Strip leading slash
    std::string path;
    req->uri[0] == '/' ? path = std::string(req->uri + 1) : path = std::string(req->uri);
    path = "/littlefs/" + path;

    char buffer[1024]; // array of bytes, not pointers-to-bytes
    size_t bytesRead = 0;

    FILE *file = fopen(path.c_str(), "r");

    if (file != NULL)
    {
        httpd_resp_set_status(req, HTTPD_200);
        httpd_resp_set_type(req, "application/csv");
        // read up to sizeof(buffer) bytes
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0)
        {
            httpd_resp_send_chunk(req, buffer, sizeof(buffer));
        }
    }

    fclose(file);
    return ESP_OK;
}

/* URI handler structure for GET /uri */
httpd_uri_t uri_get = {
    .uri = "/*",
    .method = HTTP_GET,
    .handler = get_handler,
    .user_ctx = NULL};

/* Function for starting the webserver */
void start_webserver()
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK)
    {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
    }
    /* If server failed to start, handle will be NULL */
    return;
}
