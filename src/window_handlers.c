#include "window_handlers.h"
#include "app.h"
#include "send_message.h"

void window_load(Window *window) {
  // Get app
  App *app = (App*)window_get_user_data(window);

  // Get window layer and bounds
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create time layer
  app->time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(28, 22), bounds.size.w, 80));

  // Set time layer properties
  text_layer_set_background_color(app->time_layer, GColorClear);
  text_layer_set_text_color(app->time_layer, GColorBlack);
  text_layer_set_font(app->time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_text_alignment(app->time_layer, GTextAlignmentCenter);

  text_layer_set_text(app->time_layer, "~ Connecting ~");

  // Add time layer to window
  layer_add_child(window_layer, text_layer_get_layer(app->time_layer));
}

void window_unload(Window *window) {
  // Get app
  App *app = (App*)window_get_user_data(window);

  // Unload window layers
  text_layer_destroy(app->time_layer);
}
