/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "font/lv_font.h"
#include "widgets/keyboard/lv_keyboard.h"
#include "widgets/label/lv_label.h"
#include <time.h>
LV_FONT_DECLARE(GohuFont_14);

#include "app_hal.h"
#include "core/lv_obj.h"
#include "core/lv_obj_event.h"
#include "core/lv_obj_pos.h"
#include "display/lv_display.h"

#include "demos/lv_demos.h"
#include "layouts/flex/lv_flex.h"
#include "layouts/lv_layout.h"
#include "misc/lv_area.h"
#include "misc/lv_event.h"
#include "misc/lv_types.h"
#include "widgets/button/lv_button.h"
#include "widgets/calendar/lv_calendar.h"
#include "widgets/checkbox/lv_checkbox.h"
#include "widgets/keyboard/lv_keyboard.h"
#include "widgets/list/lv_list.h"
#include "widgets/textarea/lv_textarea.h"
#include <stdio.h>

#define TIMER_PERIOD_MS 5000

lv_obj_t *textbox;
lv_obj_t *datepicker;
lv_obj_t *keyboard;
lv_obj_t *datepicker_label;

void example_lvgl_demo_ui();
static void button_event_handler(lv_event_t *e);
static void textarea_event_handler(lv_event_t *e);
static void keyboard_event_handler(lv_event_t *e);

void load_textbox_content(void) {
  // Open the saved file
  FILE *file = fopen("output.txt", "r");
  if (file) {
    // Get the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Allocate memory to store the file content
    char *text = (char *)malloc(filesize + 1);
    if (text) {
      fread(text, 1, filesize, file);
      text[filesize] = '\0'; // Null-terminate the string

      // Set the content to the textbox
      lv_textarea_set_text(textbox, text);

      // Free the allocated memory
      free(text);
    }
    fclose(file);
  } else {
    printf("No saved file found. Starting with empty textbox.\n");
    lv_textarea_set_text(textbox, ""); // If no file found, set empty text
  }
}

int main(void) {
  lv_init();
  hal_setup();
  example_lvgl_demo_ui();
  load_textbox_content();
  hal_loop();
}

void autosave_timer_callback(lv_timer_t *timer) {
  const char *text = lv_textarea_get_text(textbox);

  FILE *file = fopen("output.txt", "w");
  if (file) {
    fprintf(file, "%s", text);
    fclose(file);
    printf("Autosaved textbox content.\n");
  } else {
    printf("Failed to open file for writing.\n");
  }
}

void example_lvgl_demo_ui() {
  lv_obj_t *screen = lv_screen_active();
  lv_obj_t *scr = lv_obj_create(screen);
  lv_obj_set_size(scr, LV_PCT(100), LV_PCT(100)); // Full screen container
  lv_obj_set_layout(scr, LV_LAYOUT_FLEX);         // Set flex layout
  lv_obj_set_flex_flow(scr, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_style_pad_all(scr, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_gap(scr, 0, 0);
  lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

  datepicker = lv_button_create(scr);
  lv_obj_set_size(datepicker, LV_HOR_RES, LV_VER_RES * 0.1);
  lv_obj_set_style_bg_color(datepicker, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(datepicker, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_align(datepicker, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_margin_all(datepicker, 0, 0);

  datepicker_label = lv_label_create(datepicker);
  lv_obj_align(datepicker_label, LV_ALIGN_CENTER, 0, 0);
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  char date_str[32];
  strftime(date_str, sizeof(date_str), "%Y-%m-%d", t);
  lv_label_set_text(datepicker_label, date_str);

  textbox = lv_textarea_create(scr);
  lv_obj_set_size(textbox, LV_HOR_RES, LV_VER_RES);
  lv_obj_align(textbox, LV_ALIGN_TOP_MID, 0, lv_obj_get_y2(datepicker));
  lv_obj_set_style_bg_color(textbox, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(textbox, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_add_event_cb(textbox, textarea_event_handler, LV_EVENT_FOCUSED, NULL);
  lv_obj_set_style_margin_all(textbox, 0, 0);

  keyboard = lv_keyboard_create(scr);
  lv_obj_set_size(keyboard, LV_HOR_RES, LV_VER_RES * 0.667);
  lv_obj_set_style_bg_color(keyboard, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(keyboard, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
  lv_obj_align(keyboard, LV_ALIGN_BOTTOM_MID, 0, lv_obj_get_y2(textbox));
  lv_keyboard_set_textarea(keyboard, textbox);
  lv_obj_set_style_margin_all(keyboard, 0, 0);
  lv_obj_add_event_cb(keyboard, keyboard_event_handler, LV_EVENT_CANCEL, NULL);
  lv_timer_create(autosave_timer_callback, TIMER_PERIOD_MS, NULL);

  /*lv_obj_add_event_cb(textbox, textarea_event_handler, LV_EVENT_INSERT,
   * NULL);*/

  /*lv_obj_t *todo_list = lv_list_create(scr);*/
  /*lv_obj_set_align(todo_list, LV_ALIGN_TOP_RIGHT);*/
  /*lv_obj_set_size(todo_list, LV_HOR_RES / 2, LV_VER_RES / 3);*/
  /**/
  /*lv_obj_t *todo = lv_obj_create(todo_list);*/
  /*lv_obj_set_layout(todo, LV_LAYOUT_FLEX);*/
  /*lv_obj_set_flex_flow(todo, LV_FLEX_FLOW_ROW);*/
  /*lv_obj_set_size(todo, LV_SIZE_CONTENT, LV_SIZE_CONTENT);*/
  /*lv_obj_set_style_pad_all(todo, 0, LV_PART_MAIN);  // Set padding for all
   * sides to 0*/
  /*/*lv_obj_set_style_pad_gap(todo, 0, LV_PART_MAIN);  // Set gap between
  children to 0*
  /*lv_obj_set_style_border_width(todo, 0, LV_PART_MAIN);*/
  /**/
  /*lv_obj_t * checkbox = lv_checkbox_create(todo);*/
  /*lv_checkbox_set_text(checkbox, "");*/
  /*lv_obj_set_style_pad_all(checkbox, 5, LV_PART_MAIN);  // Set padding for all
   * sides to 0*/
  /**/
  /*lv_obj_t * todo_txt = lv_textarea_create(todo);*/
  /*lv_textarea_set_one_line(todo_txt, true);*/
  /*lv_obj_set_style_pad_all(todo_txt, 5, LV_PART_MAIN);  // Set padding for all
   * sides to 0*/
  /*lv_obj_set_size(todo_txt, lv_obj_get_width(todo_list) * 0.6667,
   * lv_obj_get_height(todo_list)  / 3);*/
  /*lv_obj_add_event_cb(todo_txt, textarea_event_handler,
   * LV_EVENT_VALUE_CHANGED, NULL);*/
  /**/

  static lv_style_t style_btn;
  lv_style_init(&style_btn);
  lv_style_set_text_font(&style_btn, &GohuFont_14);
  lv_style_set_bg_color(&style_btn, lv_color_black());
  lv_style_set_text_color(&style_btn, lv_color_white());
  lv_obj_add_style(keyboard, &style_btn, LV_PART_MAIN);
  lv_obj_add_style(keyboard, &style_btn, LV_PART_ITEMS);
  lv_obj_add_style(textbox, &style_btn, LV_PART_MAIN);
  lv_obj_add_style(textbox, &style_btn, LV_PART_ITEMS);
  lv_obj_add_style(datepicker_label, &style_btn, LV_PART_MAIN);

  static lv_style_t style_btn_checked;
  lv_style_init(&style_btn_checked);
  lv_style_set_text_font(&style_btn_checked, &GohuFont_14);
  lv_style_set_bg_color(&style_btn_checked, lv_color_make(0xaa, 0xaa, 0xaa));
  lv_obj_add_style(keyboard, &style_btn_checked,
                   LV_PART_ITEMS | LV_STATE_PRESSED);

  /*lv_obj_t * calendarBtn = lv_button_create(scr);*/
  /*lv_obj_add_event_cb(calendarBtn, button_event_handler, LV_EVENT_CLICKED,
   * NULL);*/
}

static void button_event_handler(lv_event_t *e) {
  static lv_obj_t *calendar = NULL;

  if (calendar == NULL) {
    // Create a calendar if it does not exist yet
    calendar = lv_calendar_create(lv_scr_act());
    lv_obj_set_size(calendar, 200, 200);           // Set size of the calendar
    lv_obj_align(calendar, LV_ALIGN_CENTER, 0, 0); // Center on the screen
  } else {
    // Toggle calendar visibility
    if (lv_obj_is_visible(calendar)) {
      lv_obj_add_flag(calendar, LV_OBJ_FLAG_HIDDEN); // Hide the calendar
    } else {
      lv_obj_clear_flag(calendar, LV_OBJ_FLAG_HIDDEN); // Show the calendar
    }
  }
}
static void keyboard_event_handler(lv_event_t *e) {
  if (lv_obj_is_visible(keyboard) && e->code == LV_EVENT_CANCEL) {
    lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_height(textbox, LV_VER_RES - lv_obj_get_y2(datepicker));
    lv_obj_clear_state(textbox, LV_STATE_FOCUSED);
  }
}

static void textarea_event_handler(lv_event_t *e) {
  lv_obj_t *textarea = lv_event_get_target(e);

  if (e->code == LV_EVENT_FOCUSED) {
    lv_obj_set_height(textarea, LV_VER_RES - lv_obj_get_height(keyboard) -
                                    lv_obj_get_height(datepicker));
    lv_obj_clear_flag(keyboard, LV_OBJ_FLAG_HIDDEN);
  }
}
