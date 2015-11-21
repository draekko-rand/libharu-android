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

#include "com_draekko_libharu_PdfImage.h"
#include "com_draekko_libharu_HPDF.h"
#include "hpdf.h"
#include "haru_error_handler.h"
#include <assert.h>
#include <android/log.h>  

    jfieldID Document_HPDF_Image_Pointer_ID;
    HPDF_Doc current_pdf;
    HPDF_Page current_page;

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_initHaru
  (JNIEnv *env, jclass cls) {
    Document_HPDF_Image_Pointer_ID = env->GetFieldID(cls, "HPDF_Image_Pointer", "J");
    if (Document_HPDF_Image_Pointer_ID == NULL) {
        return;
    }
}


HPDF_Image get_HPDF_Image(JNIEnv *env, jobject obj) {
    long ptr = env->GetLongField(obj, Document_HPDF_Image_Pointer_ID);
    return (HPDF_Image)ptr;
}

 
void set_HPDF_Image(JNIEnv *env, jobject obj, HPDF_Image ptr)  {
    env->SetLongField(obj, Document_HPDF_Image_Pointer_ID, (long)ptr);
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_constructJpeg
  (JNIEnv *env, jobject obj, jobject document, jstring fileName) {

    haru_setup_error_handler(env, __func__);

    const char* file_str = env->GetStringUTFChars(fileName, 0);
    current_pdf = get_HPDF_Doc(env, document);

    current_page = HPDF_GetCurrentPage(current_pdf); 
    HPDF_Image image = HPDF_LoadJpegImageFromFile(current_pdf, file_str);
    set_HPDF_Image(env, obj, image);

    env->ReleaseStringUTFChars(fileName, file_str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_constructPng
  (JNIEnv *env, jobject obj, jobject document, jstring fileName) {

    haru_setup_error_handler(env, __func__);

    const char* file_str = env->GetStringUTFChars(fileName, 0);
    current_pdf = get_HPDF_Doc(env, document);

    current_page = HPDF_GetCurrentPage(current_pdf); 
    HPDF_Image image = HPDF_LoadPngImageFromFile(current_pdf, file_str);
    set_HPDF_Image(env, obj, image);

    env->ReleaseStringUTFChars(fileName, file_str);
    haru_clear_error_handler();
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getSizeX
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Point point;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    point = HPDF_Image_GetSize(image);
    haru_clear_error_handler();

    return point.x;
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getSizeY
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Point point;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    point = HPDF_Image_GetSize(image);
    haru_clear_error_handler();
    
    return point.y;
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getWidth
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_UINT value;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    value = HPDF_Image_GetWidth(image);
    haru_clear_error_handler();
  
    return value;
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getHeight
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_UINT value;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    value = HPDF_Image_GetHeight(image);
    haru_clear_error_handler();

    return value;
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfImage_getBitsPerComponent
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_UINT value;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    value = HPDF_Image_GetBitsPerComponent(image);
    haru_clear_error_handler();
  
    return value;
}


JNIEXPORT jstring JNICALL Java_com_draekko_libharu_PdfImage_getColorSpace
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    const char* ptr_colorspace;
    jstring value;
    HPDF_Image image = get_HPDF_Image(env, obj); 
    ptr_colorspace = HPDF_Image_GetColorSpace(image);
    value = env->NewStringUTF(ptr_colorspace);
    haru_clear_error_handler();

    return value;
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_setColorMask
  (JNIEnv *env, jobject obj, jint rmin, jint rmax, jint gmin, jint gmax, jint bmin, jint bmax) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Image image = get_HPDF_Image(env, obj); 
    HPDF_Image_SetColorMask(image, rmin, rmax, gmin, gmax, bmin, bmax);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfImage_drawImage
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jfloat width, jfloat height) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Image image = get_HPDF_Image(env, obj); 
    HPDF_Page page = HPDF_GetCurrentPage(current_pdf); 
    HPDF_Page_DrawImage(page, image, x, y, width, height);
    haru_clear_error_handler();
}





