#pragma once
#include <pebble.h>

// Called when a message is received from PebbleKitJS
void in_received_handler(DictionaryIterator *received, void *context);
void in_dropped_handler(AppMessageResult reason, void *context);
void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);
void out_sent_handler(DictionaryIterator *sent, void *context);
