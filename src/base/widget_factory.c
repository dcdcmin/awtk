/**
 * File:   widget_factory.c
 * Author: AWTK Develop Team
 * Brief:  widget factory
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
 * 2018-06-16 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "base/mem.h"
#include "base/utils.h"
#include "base/image.h"
#include "base/label.h"
#include "base/value.h"
#include "base/window.h"
#include "base/button.h"
#include "base/dialog.h"
#include "base/slider.h"
#include "base/edit.h"
#include "base/pages.h"
#include "base/view.h"
#include "base/dragger.h"
#include "base/keyboard.h"
#include "base/candidates.h"
#include "base/spin_box.h"
#include "base/group_box.h"
#include "base/scroll_bar.h"
#include "base/scroll_view.h"
#include "base/list_item.h"
#include "base/list_view.h"
#include "base/list_view_h.h"
#include "base/slide_view.h"
#include "base/dialog_title.h"
#include "base/dialog_client.h"
#include "base/check_button.h"
#include "base/progress_bar.h"
#include "base/window_manager.h"
#include "base/widget_factory.h"

static widget_factory_t* s_widget_factory = NULL;
typedef struct _creator_item_t {
  char type[NAME_LEN + 1];
  widget_create_t create;
} creator_item_t;

static const creator_item_t s_builtin_creators[] = {
    {WIDGET_TYPE_DIALOG, dialog_create},
    {WIDGET_TYPE_DIALOG_TITLE, dialog_title_create},
    {WIDGET_TYPE_DIALOG_CLIENT, dialog_client_create},
    {WIDGET_TYPE_NORMAL_WINDOW, window_create},
    {WIDGET_TYPE_IMAGE, image_create},
    {WIDGET_TYPE_BUTTON, button_create},
    {WIDGET_TYPE_LABEL, label_create},
    {WIDGET_TYPE_EDIT, edit_create},
    {WIDGET_TYPE_PROGRESS_BAR, progress_bar_create},
    {WIDGET_TYPE_SLIDER, slider_create},
    {WIDGET_TYPE_GROUP_BOX, group_box_create},
    {WIDGET_TYPE_VIEW, view_create},
    {WIDGET_TYPE_CHECK_BUTTON, check_button_create},
    {WIDGET_TYPE_RADIO_BUTTON, check_button_create_radio},
    {WIDGET_TYPE_PAGES, pages_create},
    {WIDGET_TYPE_SPIN_BOX, spin_box_create},
    {WIDGET_TYPE_DRAGGER, dragger_create},
#ifndef WITH_LOW_RES
    {WIDGET_TYPE_SCROLL_VIEW, scroll_view_create},
    {WIDGET_TYPE_LIST_VIEW, list_view_create},
    {WIDGET_TYPE_LIST_VIEW_H, list_view_h_create},
    {WIDGET_TYPE_LIST_ITEM, list_item_create},
    {WIDGET_TYPE_SCROLL_BAR, scroll_bar_create},
    {WIDGET_TYPE_SCROLL_BAR_DESKTOP, scroll_bar_create_desktop},
    {WIDGET_TYPE_SCROLL_BAR_MOBILE, scroll_bar_create_mobile},

    {WIDGET_TYPE_SLIDE_VIEW, slide_view_create},
    {WIDGET_TYPE_KEYBOARD, keyboard_create},
    {WIDGET_TYPE_CANDIDATES, candidates_create},
#endif /*WITH_LOW_RES*/
};

static const creator_item_t* widget_factory_find_builtin_creator(const char* type) {
  uint32_t i = 0;
  for (i = 0; i < ARRAY_SIZE(s_builtin_creators); i++) {
    const creator_item_t* iter = s_builtin_creators + i;
    if (tk_str_eq(iter->type, type)) {
      return iter;
    }
  }

  return NULL;
}

widget_factory_t* widget_factory(void) {
  return s_widget_factory;
}

widget_factory_t* widget_factory_create(void) {
  widget_factory_t* factory = TKMEM_ZALLOC(widget_factory_t);
  return_value_if_fail(factory != NULL, NULL);

  return widget_factory_init(factory);
}

widget_factory_t* widget_factory_init(widget_factory_t* factory) {
  return_value_if_fail(factory != NULL, NULL);

  array_init(&(factory->creators), 0);

  return factory;
}

ret_t widget_factory_register(widget_factory_t* factory, const char* type, widget_create_t create) {
  creator_item_t* item = NULL;
  return_value_if_fail(factory != NULL && type != NULL && create != NULL, RET_BAD_PARAMS);

  item = TKMEM_ZALLOC(creator_item_t);
  return_value_if_fail(item != NULL, RET_OOM);

  item->create = create;
  tk_strncpy(item->type, type, NAME_LEN);
  array_push(&(factory->creators), item);

  return RET_OK;
}

widget_t* widget_factory_create_widget(widget_factory_t* factory, const char* type,
                                       widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  uint32_t i = 0;
  uint32_t nr = 0;
  const creator_item_t* iter = NULL;
  const creator_item_t** items = NULL;
  return_value_if_fail(factory != NULL && type != NULL, NULL);

  iter = widget_factory_find_builtin_creator(type);
  if (iter != NULL) {
    return iter->create(parent, x, y, w, h);
  }

  items = (const creator_item_t**)(factory->creators.elms);
  return_value_if_fail(items != NULL, NULL);

  for (i = 0, nr = factory->creators.size; i < nr; i++) {
    iter = items[i];
    if (tk_str_eq(iter->type, type)) {
      return iter->create(parent, x, y, w, h);
    }
  }

  return NULL;
}

ret_t widget_factory_set(widget_factory_t* factory) {
  s_widget_factory = factory;

  return RET_OK;
}

ret_t widget_factory_deinit(widget_factory_t* factory) {
  uint32_t i = 0;
  uint32_t nr = 0;
  creator_item_t* iter = NULL;
  creator_item_t** items = NULL;
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  items = (creator_item_t**)(factory->creators.elms);
  return_value_if_fail(items != NULL, RET_OOM);

  for (i = 0, nr = factory->creators.size; i < nr; i++) {
    iter = items[i];
    TKMEM_FREE(iter);
  }

  array_deinit(&(factory->creators));

  return RET_OK;
}

ret_t widget_factory_destroy(widget_factory_t* factory) {
  return_value_if_fail(factory != NULL, RET_BAD_PARAMS);

  widget_factory_deinit(factory);
  TKMEM_FREE(factory);

  return RET_OK;
}
