set(src led.c 
        test/led_test.c)

set(requires driver)

idf_component_register(SRCS ${src}
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})