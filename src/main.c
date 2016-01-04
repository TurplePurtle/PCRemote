#include <pebble.h>
#include "app.h"
#include "app_message_handlers.h"
#include "window_handlers.h"
#include "send_message.h"

static App app_struct = {
  .window = NULL,
  .time_layer = NULL,
  .dictation_session = NULL,
  .phone_connected = false,
};

App * const app = &app_struct;

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_message(3);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_message(4);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_message(5);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

static void dictation_session_callback(DictationSession *session, DictationSessionStatus status, char *transcription, void *context) {
  // Print the results of a transcription attempt
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Dictation status: %d", (int)status);
}

static void init(App *app) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Initializing Pebble app...");
  // Init Window
	app->window = window_create();
  window_set_user_data(app->window, (void*)app);
  window_set_window_handlers(app->window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(app->window, true);

	// Register AppMessage handlers
  app_message_set_context((void*)app);
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
	app_message_register_outbox_sent(out_sent_handler);
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  // Register Click
  window_set_click_config_provider(app->window, click_config_provider);
  
  // Init dictation
  // app->dictation_session = dictation_session_create(sizeof(app->dictation_text), dictation_session_callback, NULL);
  // dictation_session_start(app->dictation_session);
}

static void deinit(App *app) {
  // Deinit dictation
  // dictation_session_destroy(app->dictation_session);

  // Deinit AppMessage
	app_message_deregister_callbacks();

  // Deinit Window
	window_destroy(app->window);
}

int main(void) {
  init(app);
	app_event_loop();
	deinit(app);
}
