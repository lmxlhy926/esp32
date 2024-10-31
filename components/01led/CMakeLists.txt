set(src led.c)
set(requires driver)
idf_component_register(SRCS ${src}
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})