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

#ifndef _Included_com_draekko_libharu_PdfImage
#define _Included_com_draekko_libharu_PdfImage
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_initHaru
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_constructPng
  (JNIEnv *, jobject, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_constructJpeg
  (JNIEnv *, jobject, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_setColorMask
  (JNIEnv *env, jobject obj, jint rmin, jint rmax, jint gmin, jint gmax, jint bmin, jint bmax);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getSizeX
  (JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getSizeY
  (JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getWidth
  (JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getHeight
  (JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getBitsPerComponent
  (JNIEnv *env, jobject obj);

JNIEXPORT jstring JNICALL Java_com_draekko_libharu_PdfImage_getColorSpace
  (JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_drawImage
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat width, jfloat height);

#ifdef __cplusplus
}
#endif
#endif
