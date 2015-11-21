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

#ifndef com_draekko_libharu_HPDF__H
#define com_draekko_libharu_HPDF__H

#include <jni.h>
#include "hpdf.h"

#ifdef __cplusplus
extern "C" {
#endif

HPDF_Page get_HPDF_Page(JNIEnv *env, jobject obj);
void set_HPDF_Page(JNIEnv *env, jobject obj, HPDF_Page ptr);

HPDF_Doc get_HPDF_Doc(JNIEnv *env, jobject obj);
void set_HPDF_Doc(JNIEnv *env, jobject obj, HPDF_Doc ptr);

HPDF_Font get_HPDF_Font(JNIEnv *env, jobject obj);
void set_HPDF_Font(JNIEnv *env, jobject obj, HPDF_Font ptr);

HPDF_Image get_HPDF_Image(JNIEnv *env, jobject obj);
void set_HPDF_Image(JNIEnv *env, jobject obj, HPDF_Image ptr);

#ifdef __cplusplus
}
#endif
#endif
