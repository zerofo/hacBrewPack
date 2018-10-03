#include <stdlib.h>
#include <stdio.h>
#include "nacp.h"
#include "filepath.h"

void nacp_process(hbp_settings_t *settings, cnmt_ctx_t *cnmt_ctx)
{
    filepath_t nacp_filepath;
    filepath_init(&nacp_filepath);
    filepath_copy(&nacp_filepath, &settings->control_romfs_dir);
    filepath_append(&nacp_filepath, "control.nacp");

    FILE *fl;
    fl = os_fopen(nacp_filepath.os_path, OS_MODE_EDIT);
    if (fl == NULL)
    {
        fprintf(stderr, "Failed to open %s!\n", nacp_filepath.char_path);
        exit(EXIT_FAILURE);
    }

    int tname = 0;
    int tauthor = 0;
    uint64_t base_off = 0;
    for (int i=1; i<=16; i++)
    {
        fseeko64(fl, base_off, SEEK_SET);
        tname = fgetc(fl);
        fseeko64(fl, base_off + 0x200, SEEK_SET);
        tauthor = fgetc(fl);
        base_off += 0x300;
        if (tname != 0 && tauthor != 0)
            break;
    }
    // Check Title Name
    printf("Validating Title Name\n");
    if (tname == 0)
    {
        fprintf(stderr, "Error: Invalid Title Name in control.nacp\n");
        exit(EXIT_FAILURE);
    }

    // Check Author
    printf("Validating Author\n");
    if (tauthor == 0)
    {
        fprintf(stderr, "Error: Invalid Author in control.nacp\n");
        exit(EXIT_FAILURE);
    }

    // Read TitleID
    printf("Getting TitleID\n");
    fseeko64(fl, 0x3038, SEEK_SET);
    if (fread(&cnmt_ctx->cnmt_header.title_id, 1, 0x8, fl) != 0x8)
    {
        fprintf(stderr, "Failed to read file %s\n", nacp_filepath.char_path);
        exit(EXIT_FAILURE);
    }

    printf("Validating TitleID\n");
    // Make sure that tid is within valid range
    if (cnmt_ctx->cnmt_header.title_id < 0x0100000000000000 || cnmt_ctx->cnmt_header.title_id > 0x01ffffffffffffff)
    {
        fprintf(stderr, "Error: Bad TitleID found in control.nacp: 0x%016" PRIx64 "\n"
                        "Valid TitleID range: 0100000000000000 - 01ffffffffffffff\n", cnmt_ctx->cnmt_header.title_id);
        exit(EXIT_FAILURE);
    }

    // Change logo handeling to Auto
    printf("Changing logo handeling to auto\n");
    fseeko64(fl, 0x30F1, SEEK_SET);
    fputc(0, fl);

    fclose(fl);
}