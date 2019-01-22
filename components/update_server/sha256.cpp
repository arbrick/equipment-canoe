#include "esp_log.h"
#include "mbedtls/md.h"
#include "string.h"
#include "stdio.h"

static const char* TAG = "sha256";

unsigned char* sha256 (char* buf) {
    unsigned char shaResult[32];
    mbedtls_md_context_t ctx = {};
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
    size_t payloadLength = strlen(buf);

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char *) buf, payloadLength);
    mbedtls_md_finish(&ctx, shaResult);
    mbedtls_md_free(&ctx);

    for(int i= 0; i< sizeof(shaResult); i++){
        char str[3];
        sprintf(str, "%02x", (int)shaResult[i]);
        ESP_LOGI(TAG, "%s", str);
    }
    return shaResult;
}