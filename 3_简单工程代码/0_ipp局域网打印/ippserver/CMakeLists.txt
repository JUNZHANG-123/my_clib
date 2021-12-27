idf_component_register(SRCS
    "ipp.c"
    "printer.c"
    "job.c"
    "ipp_server.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES mdns esp_http_server common)

