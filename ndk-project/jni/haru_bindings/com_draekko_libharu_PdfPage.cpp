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

#include "com_draekko_libharu_PdfPage.h"
#include "com_draekko_libharu_HPDF.h"
#include "com_draekko_libharu_PdfImage.h"
#include "hpdf.h"
#include "haru_error_handler.h"
#include <assert.h>
#include <android/log.h>  

jfieldID Document_HPDF_Page_Pointer_ID;

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_initHaru
  (JNIEnv *env, jclass cls) {

    haru_setup_error_handler(env, __func__);
    Document_HPDF_Page_Pointer_ID = env->GetFieldID(cls, "HPDF_Page_Pointer", "J");
  
    if (Document_HPDF_Page_Pointer_ID == NULL) {
        return;
    }
  
    haru_clear_error_handler();
}


HPDF_Page get_HPDF_Page(JNIEnv *env, jobject obj)  {
    long ptr = env->GetLongField(obj, Document_HPDF_Page_Pointer_ID);
    return (HPDF_Page)ptr;
}

 
void set_HPDF_Page(JNIEnv *env, jobject obj, HPDF_Page ptr) {
    env->SetLongField(obj, Document_HPDF_Page_Pointer_ID, (long)ptr);
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_construct
  (JNIEnv *env, jobject obj, jobject document) {

    haru_setup_error_handler(env, __func__);
    HPDF_Doc pdf = get_HPDF_Doc(env, document);
    HPDF_Page page = HPDF_AddPage(pdf); 
    set_HPDF_Page(env, obj, page);
    haru_clear_error_handler();
}

JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_destruct
  (JNIEnv *, jobject) {
    // ain't got nothing to do, ciao!
}

JNIEXPORT jlong JNICALL Java_com_draekko_libharu_PdfPage_setHeight
  (JNIEnv *env, jobject obj, jfloat height) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    
    if (height < 3) {
        height = 3;
    }

    if (height > 14400) {
        height = 14400;
    }
  
    HPDF_REAL status = HPDF_Page_SetHeight (page, height);
    haru_clear_error_handler();
  
    return (long)status;
}

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getHeight
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    jfloat height = HPDF_Page_GetHeight(page);
    haru_clear_error_handler();

    return height;
}

JNIEXPORT jlong JNICALL Java_com_draekko_libharu_PdfPage_setWidth
  (JNIEnv *env, jobject obj, jfloat width) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 

    if (width < 3) {
        width = 3;
    }

    if (width > 14400) {
        width = 14400;
    }

    HPDF_REAL status = HPDF_Page_SetWidth (page, width);
    haru_clear_error_handler();

    return (long)status;
}

JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getWidth
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    jfloat width = HPDF_Page_GetWidth(page);
    haru_clear_error_handler();

    return width;
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineWidth
  (JNIEnv *env, jobject obj, jfloat width) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetLineWidth(page, width);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineCap
  (JNIEnv *env, jobject obj, jobject cap) {
  
    haru_setup_error_handler(env, __func__);

    jclass LineCap = env->FindClass("com/draekko/libharu/PdfPage$LineCap");
    jmethodID getNameMethod = env->GetMethodID(LineCap, "name", "()Ljava/lang/String;");
    jstring cap_value = (jstring)env->CallObjectMethod(cap, getNameMethod);
    const char* cap_str = env->GetStringUTFChars(cap_value, 0);

    HPDF_Page page = get_HPDF_Page(env, obj); 
    if (strcmp(cap_str, "BUTT_END") == 0) {
        HPDF_Page_SetLineCap(page, HPDF_BUTT_END);
    } else if (strcmp(cap_str, "ROUND_END") == 0) {
        HPDF_Page_SetLineCap(page, HPDF_ROUND_END);
    } else if (strcmp(cap_str, "PROJECTING_SQUARE_END") == 0) {
        HPDF_Page_SetLineCap(page, HPDF_PROJECTING_SQUARE_END);
    } else {
        haru_throw_exception("Unsupported Cap style.");
    }

    env->ReleaseStringUTFChars(cap_value, cap_str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setSize
    (JNIEnv *env, jobject obj, jobject sizeEnum, jobject directionEnum) {

    haru_setup_error_handler(env, __func__);

    jclass PageSize = env->FindClass("com/draekko/libharu/PdfPage$PageSize");
    jmethodID PageSize_getNameMethod = env->GetMethodID(PageSize, "name", "()Ljava/lang/String;");
    jstring size_value = (jstring)env->CallObjectMethod(sizeEnum, PageSize_getNameMethod);
    const char* size_str = env->GetStringUTFChars(size_value, 0);

    jclass PageDirection = env->FindClass("com/draekko/libharu/PdfPage$PageDirection");
    jmethodID PageDirection_getNameMethod = env->GetMethodID(PageDirection, "name", "()Ljava/lang/String;");
    jstring direction_value = (jstring)env->CallObjectMethod(directionEnum, PageDirection_getNameMethod);
    const char* direction_str = env->GetStringUTFChars(direction_value, 0);

    HPDF_PageSizes size;
    if (strcmp(size_str, "LETTER") == 0) {
        size = HPDF_PAGE_SIZE_LETTER;
    } else if (strcmp(size_str, "LEGAL") == 0) {
        size = HPDF_PAGE_SIZE_LEGAL;
    } else if (strcmp(size_str, "A3") == 0) {
        size = HPDF_PAGE_SIZE_A3;
    } else if (strcmp(size_str, "A4") == 0) {
        size = HPDF_PAGE_SIZE_A4;
    } else if (strcmp(size_str, "A5") == 0) {
        size = HPDF_PAGE_SIZE_A5;
    } else if (strcmp(size_str, "B4") == 0) {
        size = HPDF_PAGE_SIZE_B4;
    } else if (strcmp(size_str, "B5") == 0) {
        size = HPDF_PAGE_SIZE_B5;
    } else if (strcmp(size_str, "EXECUTIVE") == 0) {
        size = HPDF_PAGE_SIZE_EXECUTIVE;
    } else if (strcmp(size_str, "US4x6") == 0) {
        size = HPDF_PAGE_SIZE_US4x6;
    } else if (strcmp(size_str, "US4x8") == 0) {
        size = HPDF_PAGE_SIZE_US4x8;
    } else if (strcmp(size_str, "US5x7") == 0) {
        size = HPDF_PAGE_SIZE_US5x7;
    } else if (strcmp(size_str, "COMM10") == 0) {
        size = HPDF_PAGE_SIZE_COMM10;
    } else {
        haru_throw_exception("Unsupported page size.");
    }

    HPDF_PageDirection direction;
    if (strcmp(direction_str, "PORTRAIT") == 0) {
        direction = HPDF_PAGE_PORTRAIT;
    } else if (strcmp(direction_str, "LANDSCAPE") == 0) {
        direction = HPDF_PAGE_LANDSCAPE;
    } else {
        haru_throw_exception("Unsupported orientation.");
    }

    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetSize(page, size, direction);

    env->ReleaseStringUTFChars(size_value, size_str);
    env->ReleaseStringUTFChars(direction_value, direction_str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setLineJoin
  (JNIEnv *env, jobject obj, jobject join) {

    haru_setup_error_handler(env, __func__);

    jclass LineJoin = env->FindClass("com/draekko/libharu/PdfPage$LineJoin");
    jmethodID getNameMethod = env->GetMethodID(LineJoin, "name", "()Ljava/lang/String;");
    jstring join_value = (jstring)env->CallObjectMethod(join, getNameMethod);
    const char* join_str = env->GetStringUTFChars(join_value, 0);

    HPDF_Page page = get_HPDF_Page(env, obj); 
    if (strcmp(join_str, "MITER_JOIN") == 0) {
        HPDF_Page_SetLineJoin(page, HPDF_MITER_JOIN);
    } else if (strcmp(join_str, "ROUND_JOIN") == 0) {
        HPDF_Page_SetLineJoin(page, HPDF_ROUND_JOIN);
    } else if (strcmp(join_str, "BEVEL_JOIN") == 0) {
        HPDF_Page_SetLineJoin(page, HPDF_BEVEL_JOIN);
    } else {
        haru_throw_exception("Unsupported line join.");
    }

    env->ReleaseStringUTFChars(join_value, join_str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setMiterLimit
  (JNIEnv *env, jobject obj, jfloat lim) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetMiterLimit(page, lim);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTo
  (JNIEnv *env, jobject obj, jfloat x, jfloat y)
{
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_MoveTo(page, x, y);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_lineTo
  (JNIEnv *env, jobject obj, jfloat x, jfloat y) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_LineTo(page, x, y);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_curveTo
  (JNIEnv *env, jobject obj, jfloat x1, jfloat y1, jfloat x2, jfloat y2, jfloat x3, jfloat y3) {
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_CurveTo(page, x1, y1, x2, y2, x3, y3);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setRGBStroke
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue) {
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetRGBStroke(page, red, green, blue);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setRGBFill
  (JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue) {
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetRGBFill(page, red, green, blue);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_stroke
  (JNIEnv *env, jobject obj) {
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_Stroke(page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_fill
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_Fill(page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_fillStroke
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_FillStroke(page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_image
  (JNIEnv *env, jobject obj_page, jobject obj_image, jfloat x, jfloat y, jfloat width, jfloat height) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj_page); 
    HPDF_Image image = get_HPDF_Image(env, obj_image);
    HPDF_Page_DrawImage(page, image, x, y, width, height);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_beginText
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_BeginText (page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_endText
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_EndText (page);
    haru_clear_error_handler();
}


JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getTextWidth
  (JNIEnv *env, jobject obj, jstring text) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    const char* str = env->GetStringUTFChars(text, 0);
    float tw = HPDF_Page_TextWidth (page, str);
    env->ReleaseStringUTFChars(text, str);
    haru_clear_error_handler();
  
    return tw;
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setFontAndSize
  (JNIEnv *env, jobject obj, jobject font, jfloat size) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Font font_ptr = get_HPDF_Font(env, font);
    HPDF_Page_SetFontAndSize (page, font_ptr, size);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_textOut
  (JNIEnv *env, jobject obj, jfloat x, jfloat y, jstring text) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    const char* str = env->GetStringUTFChars(text, 0);
    HPDF_Page_TextOut (page, x, y, str);
    env->ReleaseStringUTFChars(text, str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTextPos
  (JNIEnv *env, jobject obj, jfloat x, jfloat y) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_MoveTextPos (page, x, y);
    haru_clear_error_handler();
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfPage_textRect
  (JNIEnv *env, jobject obj, jfloat jleft, jfloat jtop, jfloat jright, jfloat jbottom, jstring jtext, jobject jalignmentEnum) {

    haru_setup_error_handler(env, __func__);

    jclass TextRectAlign = env->FindClass("com/draekko/libharu/PdfPage$TextRectAlign");
    jmethodID TextRectAlign_getNameMethod = env->GetMethodID(TextRectAlign, "name", "()Ljava/lang/String;");
    jstring alignment_value = (jstring)env->CallObjectMethod(jalignmentEnum, TextRectAlign_getNameMethod);
    const char* alignment_str = env->GetStringUTFChars(alignment_value, 0);

    const char *text = env->GetStringUTFChars(jtext, 0);
    HPDF_UINT  *len;
    HPDF_REAL  left = jleft;
    HPDF_REAL  top = jtop;
    HPDF_REAL  right = jright;
    HPDF_REAL  bottom = jbottom;
    HPDF_TextAlignment align;
    HPDF_INT   value;

    if (strcmp(alignment_str, "TALIGN_LEFT") == 0) {
        align = HPDF_TALIGN_LEFT;
    } else if (strcmp(alignment_str, "TALIGN_RIGHT") == 0) {
        align = HPDF_TALIGN_RIGHT;
    } else if (strcmp(alignment_str, "TALIGN_CENTER") == 0) {
        align = HPDF_TALIGN_CENTER;
    } else if (strcmp(alignment_str, "TALIGN_JUSTIFY") == 0) {
        align = HPDF_TALIGN_JUSTIFY;
    } else {
        haru_throw_exception("Unsupported alignment.");
    }

    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_TextRect (page, left, top, right, bottom, text, align, len);

    env->ReleaseStringUTFChars(jtext, text);

    if (len == NULL) {
        value = -1;
    } else if (len < 0) {
        value = 0;
    } else {
        value = (long)len;
    }

    haru_clear_error_handler();

    return value;
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_rectangle
  (JNIEnv *env, jobject obj, jfloat jleft, jfloat jtop, jfloat jwidth, jfloat jheight) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_Rectangle (page, jleft, jtop, jwidth, jheight);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_showText
  (JNIEnv *env, jobject obj, jstring text) {

    haru_setup_error_handler(env, __func__);
    const char* str = env->GetStringUTFChars(text, 0);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_ShowText (page, str);
    env->ReleaseStringUTFChars(text, str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_showTextNextLine
  (JNIEnv *env, jobject obj, jstring text) {

    haru_setup_error_handler(env, __func__);
    const char* str = env->GetStringUTFChars(text, 0);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_ShowText (page, str);
    env->ReleaseStringUTFChars(text, str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_concatPage
  (JNIEnv *env, jobject obj, jfloat a, jfloat b, jfloat c, jfloat d, jfloat x, jfloat y) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_Concat(page, a, b, c, d, x, y);
    haru_clear_error_handler();
}


JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentTextPositionX
  (JNIEnv *env, jobject obj) {

    HPDF_Point point;
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    point = HPDF_Page_GetCurrentTextPos(page);
    haru_clear_error_handler();

    return point.x;
}


JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentTextPositionY
  (JNIEnv *env, jobject obj) {

    HPDF_Point point;
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    point = HPDF_Page_GetCurrentTextPos(page);
    haru_clear_error_handler();
  
    return point.y;
}


JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentPositionX
  (JNIEnv *env, jobject obj) {

    HPDF_Point point;
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    point = HPDF_Page_GetCurrentPos(page);
    haru_clear_error_handler();

    return point.x;
}


JNIEXPORT jfloat JNICALL Java_com_draekko_libharu_PdfPage_getCurrentPositionY
  (JNIEnv *env, jobject obj) {

    HPDF_Point point;
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    point = HPDF_Page_GetCurrentPos(page);
    haru_clear_error_handler();

    return point.y;
}


JNIEXPORT jint JNICALL Java_com_draekko_libharu_PdfPage_measureText
  (JNIEnv *env, jobject obj, jstring text, jfloat width, jboolean wordwrap, jfloat real_width) {

    HPDF_UINT ret = -1;
    HPDF_REAL *rw = NULL;
    const char* txt = env->GetStringUTFChars(text, 0);

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    if (real_width > -1) {
        rw = &real_width;
    }
    ret = HPDF_Page_MeasureText(page, txt, width, wordwrap, rw);
    env->ReleaseStringUTFChars(text, txt);
    haru_clear_error_handler();

    return ret;
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setTextLeading
  (JNIEnv *env, jobject obj, jfloat value) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_SetTextLeading(page, value);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveTextPos2
  (JNIEnv *env, jobject obj, jfloat x, jfloat y) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_MoveTextPos2(page, x, y);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_moveToNextLine
  (JNIEnv *env, jobject obj) {
  
    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj);
    HPDF_Page_MoveToNextLine(page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_setTextRenderingMode
  (JNIEnv *env, jobject obj, jobject cap) {

    haru_setup_error_handler(env, __func__);

    jclass RenderingMode = env->FindClass("com/draekko/libharu/PdfPage$RenderingMode");
    jmethodID getNameMethod = env->GetMethodID(RenderingMode, "name", "()Ljava/lang/String;");
    jstring renderMode = (jstring)env->CallObjectMethod(renderMode, getNameMethod);
    const char* mode_str = env->GetStringUTFChars(renderMode, 0);

    HPDF_TextRenderingMode mode;
    HPDF_Page page = get_HPDF_Page(env, obj); 
    if (strcmp(mode_str, "RENDER_MODE_FILL") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_FILL);
    } else if (strcmp(mode_str, "RENDER_MODE_STROKE") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_STROKE);
    } else if (strcmp(mode_str, "RENDER_MODE_FILL_THEN_STROKE") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_FILL_THEN_STROKE);
    } else if (strcmp(mode_str, "RENDER_MODE_INVISIBLE") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_INVISIBLE);
    } else if (strcmp(mode_str, "RENDER_MODE_FILL_CLIPPING") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_FILL_CLIPPING);
    } else if (strcmp(mode_str, "RENDER_MODE_STROKE_CLIPPING") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_STROKE_CLIPPING);
    } else if (strcmp(mode_str, "RENDER_MODE_FILL_STROKE_CLIPPING") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_FILL_STROKE_CLIPPING);
    } else if (strcmp(mode_str, "RENDER_MODE__CLIPPING") == 0) {
        HPDF_Page_SetTextRenderingMode(page, HPDF_CLIPPING);
    } else {
        haru_throw_exception("Unsupported Rendering Mode.");
    }

    env->ReleaseStringUTFChars(renderMode, mode_str);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_gSave
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_GSave(page);
    haru_clear_error_handler();
}


JNIEXPORT void JNICALL Java_com_draekko_libharu_PdfPage_gRestore
  (JNIEnv *env, jobject obj) {

    haru_setup_error_handler(env, __func__);
    HPDF_Page page = get_HPDF_Page(env, obj); 
    HPDF_Page_GRestore(page);
    haru_clear_error_handler();
}

