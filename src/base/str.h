﻿/**
 * File:   str.h
 * Author: AWTK Develop Team
 * Brief:  string
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-04-30 Li XianJing <xianjimli@hotmail.com> adapt from uclib
 *
 */

#ifndef TK_STR_H
#define TK_STR_H

#include "base/value.h"
#include "base/types_def.h"

BEGIN_C_DECLS

/**
 * @class str_t
 * 可变长度的UTF8字符串。
 */
typedef struct _str_t {
  /**
   * @property {uint16_t} size
   * @readonly
   * 长度。
   */
  uint16_t size;
  /**
   * @property {uint16_t} capacity
   * @readonly
   * 容量。
   */
  uint16_t capacity;
  /**
   * @property {char*} str
   * @readonly
   * 字符串。
   */
  char* str;
} str_t;

/**
 * @method str_init
 * 初始化字符串对象。
 * @constructor
 * @param {str_t*} str str对象。
 * @param {uint16_t} capacity 初始容量。
 *
 * @return {str_t*} str对象本身。
 */
str_t* str_init(str_t* str, uint16_t capacity);

/**
 * @method str_eq
 * 判断两个字符串是否相等。
 * @param {str_t*} str str对象。
 * @param {char*} text 待比较的字符串。
 *
 * @return {bool_t} 返回是否相等。
 */
bool_t str_eq(str_t* str, const char* text);

/**
 * @method str_set
 * 设置字符串。
 * @param {str_t*} str str对象。
 * @param {char*} text 要设置的字符串。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_set(str_t* str, const char* text);

/**
 * @method str_set_with_len
 * 设置字符串。
 * @param {str_t*} str str对象。
 * @param {char*} text 要设置的字符串。
 * @param {uint16_t} len 长度。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_set_with_len(str_t* str, const char* text, uint16_t len);

/**
 * @method str_append
 * 追加字符串。
 * @param {str_t*} str str对象。
 * @param {char*} text 要追加的字符串。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_append(str_t* str, const char* text);

/**
 * @method str_append_char
 * 追加一个字符。
 * @param {str_t*} str str对象。
 * @param {char} c 要追加的字符。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_append_char(str_t* str, char c);

/**
 * @method str_decode_xml_entity
 * 对XML基本的entity进行解码，目前仅支持&lt;&gt;&quota;&amp;。
 * @param {str_t*} str str对象。
 * @param {char*} text 要解码的XML文本。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_decode_xml_entity(str_t* str, const char* text);

/**
 * @method str_from_int
 * 用整数初始化字符串。
 * @param {str_t*} str str对象。
 * @param {int32_t} v 整数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_from_int(str_t* str, int32_t v);

/**
 * @method str_from_float
 * 用浮点数初始化字符串。
 * @param {str_t*} str str对象。
 * @param {float} v 浮点数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_from_float(str_t* str, float v);

/**
 * @method str_from_value
 * 用value初始化字符串。
 * @param {str_t*} str str对象。
 * @param {value_t} v value。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_from_value(str_t* str, const value_t* v);

/**
 * @method str_to_int
 * 将字符串转成整数。
 * @param {str_t*} str str对象。
 * @param {int32_t*} v 用于返回整数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_to_int(str_t* str, int32_t* v);

/**
 * @method str_to_float
 * 将字符串转成浮点数。
 * @param {str_t*} str str对象。
 * @param {float*} v 用于返回浮点数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_to_float(str_t* str, float* v);

/**
 * @method str_end_with
 * 判断字符串是否以指定的子串结尾。
 * @param {str_t*} str str对象。
 * @param {char*} text 子字符串。
 *
 * @return {bool_t} 返回是否以指定的子串结尾。
 */
bool_t str_end_with(str_t* str, const char* text);

/**
 * @method str_start_with
 * 判断字符串是否以指定的子串开头。
 * @param {str_t*} str str对象。
 * @param {char*} text 子字符串。
 *
 * @return {bool_t} 返回是否以指定的子串开头。
 */
bool_t str_start_with(str_t* str, const char* text);

/**
 * @method str_trim
 * 去除首尾指定的字符。
 * @param {str_t*} str str对象。
 * @param {char*} text 要去除的字符集合。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_trim(str_t* str, const char* text);

/**
 * @method str_trim_left
 * 去除首部指定的字符。
 * @param {str_t*} str str对象。
 * @param {char*} text 要去除的字符集合。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_trim_left(str_t* str, const char* text);

/**
 * @method str_trim_right
 * 去除尾部指定的字符。
 * @param {str_t*} str str对象。
 * @param {char*} text 要去除的字符集合。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_trim_right(str_t* str, const char* text);

/**
 * @method str_replace
 * 字符串替换。
 * @param {str_t*} str str对象。
 * @param {char*} text 待替换的子串。
 * @param {char*} new_text 将替换成的子串。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_replace(str_t* str, const char* text, const char* new_text);

/**
 * @method str_to_lower
 * 将字符串转成小写。
 * @param {str_t*} str str对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_to_lower(str_t* str);

/**
 * @method str_to_upper
 * 将字符串转成大写。
 * @param {str_t*} str str对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_to_upper(str_t* str);

/**
 * @method str_reset
 * 重置字符串为空。
 * @param {str_t*} str str对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t str_reset(str_t* str);

END_C_DECLS

#endif /*TK_STR_H*/
