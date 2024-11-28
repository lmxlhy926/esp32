set(requires 01led 02key 03exit esp_wifi nvs_flash)

idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})