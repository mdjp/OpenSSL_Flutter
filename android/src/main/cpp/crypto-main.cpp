#include <jni.h>
#include <openssl/evp.h>
#include <cstring>
#include <android/log.h>
#include <stdio.h>

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-libs::", __VA_ARGS__))

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_codingfeline_opensslflutter_OpensslFlutterPlugin_getDigest(JNIEnv *env, jobject thiz, jstring digestType, jstring message) {
    const char* nativeMessage = env->GetStringUTFChars(message, JNI_FALSE);
    const char* nativeDigestType = env->GetStringUTFChars(digestType, JNI_FALSE);
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;
    int i;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_get_digestbyname(nativeDigestType);
    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, nativeMessage, strlen(nativeMessage));
    EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_free(ctx);

    jbyteArray resultDigest = env->NewByteArray(md_len);
    env->SetByteArrayRegion(resultDigest, 0, md_len, (jbyte*)md_value);

    return resultDigest;
}
