#define MAIN_(x) A_CAST_2(x, _crc)
#include "test.h"
#include "a/crc.h"
#if !defined __cplusplus
#include <stdlib.h>
#define WRITE_TABLE(bit, row, fmt)                                                                \
    static void write_table##bit(FILE *out, a_u##bit##_t ctx[A_CRC_SIZ], char const *const label) \
    {                                                                                             \
        (void)fprintf(out, "uint%i_t const %s[0x%X] = {\n", bit, label, A_CRC_SIZ);               \
        (void)fprintf(out, "    /* clang-format off */\n");                                       \
        for (a_size_t i = 0; i != A_CRC_SIZ / (row); ++i)                                         \
        {                                                                                         \
            (void)fprintf(out, "    ");                                                           \
            for (a_size_t j = 0; j != (row); ++j)                                                 \
            {                                                                                     \
                (void)fprintf(out, "0x%0" #fmt PRIX##bit ",", ctx[(row) * i + j]);                \
                if (j != (row)-1)                                                                 \
                {                                                                                 \
                    (void)fputc(' ', out);                                                        \
                }                                                                                 \
            }                                                                                     \
            (void)fputc('\n', out);                                                               \
        }                                                                                         \
        (void)fprintf(out, "    /* clang-format on */\n");                                        \
        (void)fprintf(out, "};\n");                                                               \
    }
WRITE_TABLE(8, 8, 2)
WRITE_TABLE(16, 8, 4)
WRITE_TABLE(32, 8, 8)
WRITE_TABLE(64, 4, 16)
#undef WRITE_TABLE
#endif /* __cplusplus */

static void create_table(char const *const name)
{
#if !defined __cplusplus
    FILE *out = stdout;

    if (name && *name)
    {
        out = fopen(name, "wb");
        if (!out)
        {
            perror(name);
            exit(EXIT_FAILURE);
        }
    }

    (void)fprintf(out, "#include <stdint.h>\n");

    a_u8_t table8[A_CRC_SIZ];
    a_crc8l_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8L");
    a_crc8h_init(table8, A_CRC8_POLY);
    write_table8(out, table8, "CRC8H");

    a_u16_t table16[A_CRC_SIZ];
    a_crc16l_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16L");
    a_crc16h_init(table16, A_CRC16_POLY);
    write_table16(out, table16, "CRC16H");

    a_u32_t table32[A_CRC_SIZ];
    a_crc32l_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32L");
    a_crc32h_init(table32, A_CRC32_POLY);
    write_table32(out, table32, "CRC32H");

    a_u64_t table64[A_CRC_SIZ];
    a_crc64l_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64L");
    a_crc64h_init(table64, A_CRC64_POLY);
    write_table64(out, table64, "CRC64H");

    if (stdout != out && fclose(out) == EOF)
    {
        perror(name);
    }
#else /* !__cplusplus */
    (void)name;
#endif /* __cplusplus */
}

static void test(void)
{
#define TEXT "123456789"
#define SIZE (sizeof(TEXT) - 1)

    a_u8_t table8[A_CRC_SIZ];
    debug("POLY: 0x%02u\n", A_CRC8_POLY);
    debug("INIT: 0x%02u\n", A_CRC8_INIT);
    a_crc8l_init(table8, A_CRC8_POLY);
    debug("LSB: 0x%02" PRIX8 "\n", a_crc8(table8, TEXT, SIZE, A_CRC8_INIT));
    a_crc8h_init(table8, A_CRC8_POLY);
    debug("MSB: 0x%02" PRIX8 "\n", a_crc8(table8, TEXT, SIZE, A_CRC8_INIT));

    a_u16_t table16[A_CRC_SIZ];
    debug("POLY: 0x%04u\n", A_CRC16_POLY);
    debug("INIT: 0x%04u\n", A_CRC16_INIT);
    a_crc16l_init(table16, A_CRC16_POLY);
    debug("LSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
          a_crc16l(table16, TEXT, SIZE, A_CRC16_INIT),
          a_crc16h(table16, TEXT, SIZE, A_CRC16_INIT));
    a_crc16h_init(table16, A_CRC16_POLY);
    debug("MSB: 0x%04" PRIX16 "(L) 0x%04" PRIX16 "(H)\n",
          a_crc16l(table16, TEXT, SIZE, A_CRC16_INIT),
          a_crc16h(table16, TEXT, SIZE, A_CRC16_INIT));

    a_u32_t table32[A_CRC_SIZ];
    debug("POLY: 0x%08" PRIX32 "\n", A_CRC32_POLY);
    debug("INIT: 0x%08" PRIX32 "\n", A_CRC32_INIT);
    a_crc32l_init(table32, A_CRC32_POLY);
    debug("LSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
          a_crc32l(table32, TEXT, SIZE, A_CRC32_INIT),
          a_crc32h(table32, TEXT, SIZE, A_CRC32_INIT));
    a_crc32h_init(table32, A_CRC32_POLY);
    debug("MSB: 0x%08" PRIX32 "(L) 0x%08" PRIX32 "(H)\n",
          a_crc32l(table32, TEXT, SIZE, A_CRC32_INIT),
          a_crc32h(table32, TEXT, SIZE, A_CRC32_INIT));

    a_u64_t table64[A_CRC_SIZ];
    debug("POLY: 0x%016" PRIX64 "\n", A_CRC64_POLY);
    debug("INIT: 0x%016" PRIX64 "\n", A_CRC64_INIT);
    a_crc64l_init(table64, A_CRC64_POLY);
    debug("LSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
          a_crc64l(table64, TEXT, SIZE, A_CRC64_INIT),
          a_crc64h(table64, TEXT, SIZE, A_CRC64_INIT));
    a_crc64h_init(table64, A_CRC64_POLY);
    debug("MSB: 0x%016" PRIX64 "(L) 0x%016" PRIX64 "(H)\n",
          a_crc64l(table64, TEXT, SIZE, A_CRC64_INIT),
          a_crc64h(table64, TEXT, SIZE, A_CRC64_INIT));

#undef TEXT
#undef SIZE
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    if (argc > 1)
    {
        create_table(argv[argc - 1]);
    }
    test();
    return 0;
}
