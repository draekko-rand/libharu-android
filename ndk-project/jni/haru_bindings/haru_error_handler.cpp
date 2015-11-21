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

#include <android/log.h>
#include "haru_error_handler.h"

JNIEnv *jni_env = NULL;
const char* current_function_name = "<unknown>";

void haru_setup_error_handler(JNIEnv *env, const char* function_name) {
    jni_env = env;
    current_function_name = function_name;
}

void haru_clear_error_handler() {
    jni_env = NULL;
    current_function_name = "<unknown>";
}

void haru_error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    __android_log_print(
        ANDROID_LOG_DEBUG, 
        "HPDF",
        "ERROR in %s: error_no=%04X, detail_no=%d\n",
        current_function_name, (unsigned int)error_no, (int)detail_no);
    haru_throw_exception("HPDF: Error");
}

void haru_throw_exception(const char* message) {
    if (jni_env == NULL) {
        __android_log_print(
            ANDROID_LOG_DEBUG, 
            "HPDF", 
            "ERROR in %s: cannot throw exception, haru_setup_error_handler() wasn't called.",
            current_function_name);
    } else {
        jclass excCls = jni_env->FindClass("java/io/IOException");
        if (excCls == NULL) {
            __android_log_print(
                ANDROID_LOG_ERROR, 
                "HPDF",
                "ERROR in %s: could not find java/io/IOException.",
                current_function_name);
            return;
        }
        __android_log_print(ANDROID_LOG_ERROR, "HPDF", "throwing");
        jni_env->ThrowNew(excCls, message);
        haru_clear_error_handler();
    }
}

