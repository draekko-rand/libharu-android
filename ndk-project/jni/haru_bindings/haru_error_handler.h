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

#ifndef HARU_ERROR_HANDLER_H
#define HARU_ERROR_HANDLER_H

#include <jni.h>
#include "hpdf.h"

void haru_setup_error_handler(JNIEnv *env, const char* function_name);
void haru_clear_error_handler();
void haru_throw_exception(const char* message);
void haru_error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

#endif
