#pragma once
#include <pebble.h>

typedef struct {
  Window *window;
  TextLayer *time_layer;
  DictationSession *dictation_session;
  char dictation_text[512];
  bool phone_connected;
} App;
