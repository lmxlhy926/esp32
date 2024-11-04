set(src exit.c test/exit_test.c)

set(requires driver 01led)

idf_component_register(SRCS ${src}
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})