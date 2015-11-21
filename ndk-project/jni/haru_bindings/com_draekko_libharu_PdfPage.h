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

#ifndef _Included_com_draekko_libharu_PdfPage
#define _Included_com_draekko_libharu_PdfPage

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setSize
  (JNIEnv *, jobject, jobject, jobject);

JNIEXPORT jlong JNICALL Java_com_draekko_libharu_PdfPage_setHeight
  (JNIEnv *, jobject, jfloat);

JNIEXPORT jlong JNICALL Java_com_draekko_libharu_PdfPage_setWidth
  (JNIEnv *, jobject, jfloat);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getHeight
  (JNIEnv *, jobject);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getWidth
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineWidth
  (JNIEnv *, jobject, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineCap
  (JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineJoin
  (JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setMiterLimit
  (JNIEnv *, jobject, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setRGBStroke
  (JNIEnv *, jobject, jfloat, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setRGBFill
  (JNIEnv *, jobject, jfloat, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTo
  (JNIEnv *, jobject, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_lineTo
  (JNIEnv *, jobject, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_curveTo
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_stroke
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_fill
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_fillStroke
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_image
  (JNIEnv *, jobject, jobject, jfloat, jfloat, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_beginText
  (JNIEnv *, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_endText
  (JNIEnv *, jobject);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getTextWidth
  (JNIEnv *, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setFontAndSize
  (JNIEnv *, jobject, jobject, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_textOut
  (JNIEnv *, jobject, jfloat, jfloat, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTextPos
  (JNIEnv *, jobject, jfloat, jfloat);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_initHaru
  (JNIEnv *, jclass);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_construct
  (JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_destruct
  (JNIEnv *, jobject);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfPage_textRect
  (JNIEnv *env, jobject obj, jfloat jleft, jfloat jtop, jfloat jright, jfloat jbottom, jstring jtext, jobject jalignmentEnum);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_rectangle
  (JNIEnv *env, jobject obj, jfloat jleft, jfloat jtop, jfloat jright, jfloat jbottom);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_showText
  (JNIEnv *, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_showTextNextLine
  (JNIEnv *, jobject, jstring);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_concatPage
  (JNIEnv *env, jobject obj, jfloat a, jfloat b, jfloat c, jfloat d, jfloat x, jfloat y);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentTextPositionX
  (JNIEnv *env, jobject obj);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentTextPositionY
  (JNIEnv *env, jobject obj);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentPositionX
  (JNIEnv *env, jobject obj);

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentPositionY
  (JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfPage_measureText
  (JNIEnv *env, jobject obj, jstring text, jfloat width, jboolean wordwrap, jfloat real_width);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setTextLeading
  (JNIEnv *env, jobject obj, jfloat value);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTextPos2
  (JNIEnv *env, jobject obj, jfloat x, jfloat y);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveToNextLine
  (JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setTextRenderingMode
  (JNIEnv *env, jobject obj, jobject cap);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_gSave
  (JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_gRestore
  (JNIEnv *env, jobject obj);

#ifdef __cplusplus
}
#endif
#endif
