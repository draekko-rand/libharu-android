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

#include "com_draekko_libharu_PdfFont.h"
#include "com_draekko_libharu_HPDF.h"
#include "hpdf.h"
#include "haru_error_handler.h"
#include <assert.h>
#include <android/log.h>  

jfieldID Document_HPDF_Font_Pointer_ID;

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_initHaru
  (JNIEnv *env, jclass cls) {

    Document_HPDF_Font_Pointer_ID = env->GetFieldID(cls, "HPDF_Font_Pointer", "J");
    if (Document_HPDF_Font_Pointer_ID == NULL) {
        return;
    }
}


HPDF_Font get_HPDF_Font(JNIEnv *env, jobject obj)  {
    long ptr = env->GetLongField(obj, Document_HPDF_Font_Pointer_ID);
    return (HPDF_Font)ptr;
}

 
void set_HPDF_Font(JNIEnv *env, jobject obj, HPDF_Font ptr) {
    env->SetLongField(obj, Document_HPDF_Font_Pointer_ID, (long)ptr);
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_constructTtf
  (JNIEnv *env, jobject obj, jobject document, jstring fontPathName, jboolean embedded) {

    haru_setup_error_handler(env, __func__);

    const char* font_path = env->GetStringUTFChars(fontPathName, 0);
    const char* detail_font_name;
    HPDF_BOOL embed = HPDF_FALSE;

    if (embedded) {
        embed = HPDF_TRUE;
    }

    HPDF_Doc pdf = get_HPDF_Doc(env, document);
    detail_font_name = HPDF_LoadTTFontFromFile(pdf, font_path, embed);
    HPDF_Font font = HPDF_GetFont(pdf, detail_font_name, NULL);
    set_HPDF_Font(env, obj, font);
    env->ReleaseStringUTFChars(fontPathName, font_path);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_construct
  (JNIEnv *env, jobject obj, jobject document, jobject fontEnum, jstring encodingName) {

    haru_setup_error_handler(env, __func__);

    jclass BuiltinFont = env->FindClass("com/draekko/libharu/PdfFont$BuiltinFont");
    jmethodID getNameMethod = env->GetMethodID(BuiltinFont, "name", "()Ljava/lang/String;");
    jstring builtin_value = (jstring)env->CallObjectMethod(fontEnum, getNameMethod);
    const char* builtin_str = env->GetStringUTFChars(builtin_value, 0);
    const char* font_str;

    if (strcmp(builtin_str, "COURIER") == 0) {
        font_str = "Courier";
    } else if (strcmp(builtin_str, "COURIER_BOLD") == 0) {
        font_str = "Courier-Bold";
    } else if (strcmp(builtin_str, "COURIER_OBLIQUE") == 0) {
        font_str = "Courier-Oblique";
    } else if (strcmp(builtin_str, "COURIER_BOLD_OBLIQUE") == 0) {
       font_str = "Courier-BoldOblique";
    } else if (strcmp(builtin_str, "HELVETICA") == 0) {
       font_str = "Helvetica";
    } else if (strcmp(builtin_str, "HELVETICA_BOLD") == 0) {
        font_str = "Helvetica-Bold";
    } else if (strcmp(builtin_str, "HELVETICA_OBLIQUE") == 0) {
        font_str = "Helvetica-Oblique";
    } else if (strcmp(builtin_str, "HELVETICA_BOLD_OBLIQUE") == 0) {
        font_str = "Helvetica-BoldOblique";
    } else if (strcmp(builtin_str, "TIMES_ROMAN") == 0) {
        font_str = "Times-Roman";
    } else if (strcmp(builtin_str, "TIMES_BOLD") == 0) {
        font_str = "Times-Bold";
    } else if (strcmp(builtin_str, "TIMES_ITALIC") == 0) {
        font_str = "Times-Italic";
    } else if (strcmp(builtin_str, "TIMES_BOLD_ITALIC") == 0) {
        font_str = "Times-BoldItalic";
    } else if (strcmp(builtin_str, "SYMBOL") == 0) {
        font_str = "Symbol";
    } else if (strcmp(builtin_str, "ZAPFDINGBATS") == 0) {
        font_str = "ZapfDingbats";
    } else {
        haru_throw_exception("Unknown font.");
    }

    env->ReleaseStringUTFChars(builtin_value, builtin_str);

    const char* encoding_str = env->GetStringUTFChars(encodingName, 0);
    HPDF_Doc pdf = get_HPDF_Doc(env, document);
    HPDF_Font font = HPDF_GetFont(pdf, font_str, encoding_str);
    set_HPDF_Font(env, obj, font);

    env->ReleaseStringUTFChars(encodingName, encoding_str);
    haru_clear_error_handler();
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfFont_measureText
  (JNIEnv *env, jobject obj, jstring text, jint len, jfloat width, jfloat fontsize, jfloat charspace, jfloat wordspace, jboolean wordwrap, jfloat real_width) {

    HPDF_UINT retval = -1;
    HPDF_REAL *rw = NULL;
    const char* str = env->GetStringUTFChars(text, 0);

    haru_setup_error_handler(env, __func__);
    HPDF_Font font = get_HPDF_Font(env, obj);

    if (real_width > -1) {
        rw = &real_width;
    }

    retval = HPDF_Font_MeasureText(font, (const HPDF_BYTE*) str, len, width, fontsize, charspace, wordspace, wordwrap, rw);
    env->ReleaseStringUTFChars(text, str);
    haru_clear_error_handler();

    return retval;
}


