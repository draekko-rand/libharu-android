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

#ifndef _Included_com_draekko_libharu_PdfFont
#define _Included_com_draekko_libharu_PdfFont
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_construct
  (JNIEnv *, jobject, jobject, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_constructTtf
  (JNIEnv *, jobject, jobject, jstring, jboolean);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfFont_initHaru
  (JNIEnv *, jclass);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfFont_measureText
  (JNIEnv *, jobject, jstring, jint, jfloat, jfloat, jfloat, jfloat, jboolean, jfloat);

#ifdef __cplusplus
}
#endif
#endif
