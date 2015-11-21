/*************************************************************************

 Copyright (C) 2013-2015  Benoit Touchette

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301  USA

 *************************************************************************/

#include "com_draekko_libharu_PdfDocument.h"
#include "com_draekko_libharu_HPDF.h"
#include "haru_error_handler.h"
#include <assert.h>
#include <string.h>
#include <jni.h>
#include <stdio.h>

jfieldID Document_HPDF_Doc_Pointer_ID;

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_initHaru
  (JNIEnv *env, jclass cls) {
    Document_HPDF_Doc_Pointer_ID = env->GetFieldID(cls, "HPDF_Doc_Pointer", "J");
    if (Document_HPDF_Doc_Pointer_ID == NULL) {
        return;
    }
}


HPDF_Doc get_HPDF_Doc(JNIEnv *env, jobject obj) {
    long ptr = env->GetLongField(obj, Document_HPDF_Doc_Pointer_ID);
    return (HPDF_Doc)ptr;
}


void set_HPDF_Doc(JNIEnv *env, jobject obj, HPDF_Doc ptr) {
    env->SetLongField(obj, Document_HPDF_Doc_Pointer_ID, (long)ptr);
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_construct
  (JNIEnv *env, jobject obj) {
    haru_setup_error_handler(env, __func__);
    HPDF_Doc pdf = HPDF_New(haru_error_handler, NULL);
    if (pdf == NULL) {
        haru_throw_exception("Failed to create pdf pointer.");
    }
    set_HPDF_Doc(env, obj, pdf);
    if (pdf == NULL) {
        haru_throw_exception("Failed to create a new PDF document.");
    }
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_destruct
  (JNIEnv *env, jobject obj) {
    haru_setup_error_handler(env, __func__);
    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_Free(pdf);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setCompressionMode
  (JNIEnv *env, jobject obj, jobject compressionMode) {
    haru_setup_error_handler(env, __func__);
    jclass CompressionMode = env->FindClass("com/draekko/libharu/PdfDocument$CompressionMode");
    jmethodID getNameMethod = env->GetMethodID(CompressionMode, "name", "()Ljava/lang/String;");
    jstring comp_value = (jstring)env->CallObjectMethod(compressionMode, getNameMethod);
    const char* comp_str = env->GetStringUTFChars(comp_value, 0);

    HPDF_UINT mode;
    if (strcmp(comp_str, "COMP_NONE") == 0) {
        mode = HPDF_COMP_NONE;
    } else if (strcmp(comp_str, "COMP_TEXT") == 0) {
        mode = HPDF_COMP_TEXT; 
    } else if (strcmp(comp_str, "COMP_IMAGE") == 0) {
        mode = HPDF_COMP_IMAGE; 
    } else if (strcmp(comp_str, "COMP_METADATA") == 0) {
        mode = HPDF_COMP_METADATA;
    } else if (strcmp(comp_str, "COMP_ALL") == 0) {
        mode = HPDF_COMP_ALL;
    } else {
        haru_throw_exception("Unknown compression mode.");
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetCompressionMode (pdf, mode);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setPermission
  (JNIEnv *env, jobject obj, jint permissions) {
    haru_setup_error_handler(env, __func__);

    if (permissions < 1 || permissions > 15) {
        haru_throw_exception("Unknown permission mode.");
    }  

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetPermission (pdf, permissions);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setEncryptionMode
  (JNIEnv *env, jobject obj, jobject encryptionMode) {
    haru_setup_error_handler(env, __func__);
    jclass EncryptionMode = env->FindClass("com/draekko/libharu/PdfDocument$EncryptionMode");
    jmethodID getNameMethod = env->GetMethodID(EncryptionMode, "name", "()Ljava/lang/String;");
    jstring comp_value = (jstring)env->CallObjectMethod(encryptionMode, getNameMethod);
    const char* comp_str = env->GetStringUTFChars(comp_value, 0);

    HPDF_EncryptMode mode;
    HPDF_UINT keylen;

    if (strcmp(comp_str, "ENCRYPT_R2") == 0) {
        mode = HPDF_ENCRYPT_R2;
        keylen = 5;
    } else if (strcmp(comp_str, "ENCRYPT_R3_40") == 0) {
        mode = HPDF_ENCRYPT_R3; 
        keylen = 5;
    } else if (strcmp(comp_str, "ENCRYPT_R3_128") == 0) {
        mode = HPDF_ENCRYPT_R3; 
        keylen = 16;
    } else {
        haru_throw_exception("Unknown encryption mode.");
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetEncryptionMode (pdf, mode, keylen);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setPassword
  (JNIEnv *env, jobject obj, jstring jownerpass, jstring juserpass) {
  
    haru_setup_error_handler(env, __func__);
    const char *ownerpass = (char*)env->GetStringUTFChars(jownerpass, NULL);
    const char *userpass = (char*)env->GetStringUTFChars(juserpass, NULL);
    if (ownerpass == NULL || userpass == NULL) {
        return;
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetPassword(pdf, ownerpass, userpass);

    env->ReleaseStringUTFChars(jownerpass, ownerpass);
    env->ReleaseStringUTFChars(juserpass, userpass);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setInfoAttr
  (JNIEnv *env, jobject obj, jint mode, jstring jvalue) {
  
    haru_setup_error_handler(env, __func__);
    const char *value = (char*)env->GetStringUTFChars(jvalue, NULL);
    if (value == NULL) {
        return;
    }

    HPDF_InfoType infotype;
    switch(mode) {
        case 0x1:
            infotype = HPDF_INFO_AUTHOR;
            break;

        case 0x2:
            infotype = HPDF_INFO_CREATOR;
            break;

        case 0x4:
            infotype = HPDF_INFO_TITLE;
            break;

        case 0x8:
            infotype = HPDF_INFO_SUBJECT;
            break;

        case 0x10:
            infotype = HPDF_INFO_KEYWORDS;
            break;

        default:
            haru_throw_exception("Unknown info type.");
            break;
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetInfoAttr(pdf, infotype, value);

    env->ReleaseStringUTFChars(jvalue, value);
    haru_clear_error_handler();
}

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setInfoDateAttr
  (JNIEnv *env, jobject obj, jint year, jint month, jint day, jint hour, jint minutes, jint seconds, jint infomode ) {

    haru_setup_error_handler(env, __func__);

    HPDF_Date date_info;
    date_info.year = year;
    date_info.month = month;
    date_info.day = day;
    date_info.hour = hour;
    date_info.minutes = minutes;
    date_info.seconds = seconds;
    date_info.ind = ' ';
    date_info.off_hour = 0;
    date_info.off_minutes = 0;

    HPDF_InfoType mode;
    if (infomode == 1) {
        mode = HPDF_INFO_CREATION_DATE;
    } else if (infomode == 2) {
        mode = HPDF_INFO_MOD_DATE;
    } else {
        haru_throw_exception("Unknown info mode.");
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_SetInfoDateAttr(pdf, mode, date_info);

    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_saveToFile
  (JNIEnv *env, jobject obj, jstring filename) {

    haru_setup_error_handler(env, __func__);
    const char *str = (char*)env->GetStringUTFChars(filename, NULL);
    if (str == NULL) {
        return;
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, obj);
    if (pdf == NULL) {
        haru_throw_exception("Failed to get pdf pointer.");
    }
    HPDF_STATUS rc = HPDF_SaveToFile(pdf, str);

    env->ReleaseStringUTFChars(filename, str);
    if (rc == HPDF_OK) {
        // Nothing to do all is OK in the world!
    } else if (rc == HPDF_INVALID_DOCUMENT) {
        haru_throw_exception("An invalid document handle is set.");
    } else if (rc == HPDF_FAILD_TO_ALLOC_MEM) {
        haru_throw_exception("Memory allocation failed.");
    } else if (rc == HPDF_FILE_IO_ERROR) {
        haru_throw_exception("An error occurred while processing file I/O.");
    } else {
        haru_throw_exception("Unknown return code.");
    }

    haru_clear_error_handler();
}

