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

#include <jni.h>

#ifndef _Included_com_draekko_libharu_PdfDocument
#define _Included_com_draekko_libharu_PdfDocument
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setCompressionMode
  (JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setPermission
  (JNIEnv *, jobject, jint);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setEncryptionMode
  (JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setPassword
  (JNIEnv *, jobject, jstring, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setInfoAttr
  (JNIEnv *, jobject, jint, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_setInfoDateAttr
  (JNIEnv *, jobject, jint, jint, jint, jint, jint, jint, jint);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_saveToFile
  (JNIEnv *, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_initHaru
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_construct
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfDocument_destruct
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
