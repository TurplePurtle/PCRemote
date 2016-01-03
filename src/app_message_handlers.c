#include "app_message_handlers.h"
#include "app.h"
#include "message_keys.h"

// Called when a message is received from PebbleKitJS
void in_received_handler(DictionaryIterator *received, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message received"); 

  App *app = (App*)context;
  static char status_buffer[8];
	Tuple *tuple;

	tuple = dict_find(received, STATUS_KEY);
	if (tuple) {
    snprintf(status_buffer, sizeof(status_buffer), "%d", (int)tuple->value->uint32);
    text_layer_set_text(app->time_layer, status_buffer);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", (int)tuple->value->uint32);
	}
}

void in_dropped_handler(AppMessageResult reason, void *context) {	
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Dropped message (%d)", reason);
}

void out_sent_handler(DictionaryIterator *sent, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Message sent");
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send message (%d)", reason);
}
