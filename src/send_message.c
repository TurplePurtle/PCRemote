#include "send_message.h"
#include <pebble.h>
#include "message_keys.h"

void send_message(int status) {
	DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  dict_write_int8(iter, STATUS_KEY, status);
	dict_write_end(iter);
  app_message_outbox_send();
}
