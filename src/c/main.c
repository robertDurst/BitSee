#include <pebble.h>

// Creating the elements of the app
static Window *s_main_window;

static TextLayer *s_time_layer;
static GFont s_time_font;

static TextLayer *s_crypto_layer;
static GFont s_crypto_font;

static void main_window_load(Window *window) {
    // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(
      GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  
  // Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Nueue_48));

  // Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);
  
  // Create crypto Layer
  s_crypto_layer = text_layer_create( GRect(0, PBL_IF_ROUND_ELSE(125, 120), bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_crypto_layer, GColorClear);
  text_layer_set_text_color(s_crypto_layer, GColorWhite);
  text_layer_set_text_alignment(s_crypto_layer, GTextAlignmentCenter);
  text_layer_set_text(s_crypto_layer, "Loading...");
  
  // Create second custom font, apply it and add to Window
  s_crypto_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_NUEUE_20));
  text_layer_set_font(s_crypto_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_crypto_layer));
}

static void main_window_unload(Window *window) {
  
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  
   // Unload GFont
  fonts_unload_custom_font(s_time_font);
  
  // Destroy weather elements
  text_layer_destroy(s_crypto_layer);
  fonts_unload_custom_font(s_crypto_font);
}

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  
  // Get weather update every 1 minute
  if(tick_time->tm_min % 1 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message!
    app_message_outbox_send();
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char BTC_buffer[32];
  static char ETH_buffer[32];
  static char crypto_layer_buffer[32];
  
  // Read tuples for data
  Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_BTC);
  Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_ETH);
  
  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
     snprintf(BTC_buffer, sizeof(BTC_buffer), "BTC: $%d", (int)temp_tuple->value->uint16);
     snprintf(ETH_buffer, sizeof(ETH_buffer), "ETH: $%d", (int)conditions_tuple->value->uint16);
  }
  // Assemble full string and display
    snprintf(crypto_layer_buffer, sizeof(crypto_layer_buffer), "%s %s", BTC_buffer, ETH_buffer);
    text_layer_set_text(s_crypto_layer, crypto_layer_buffer);
}
  
static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}


// Initialization
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  
   // Set background
  window_set_background_color(s_main_window, GColorBlack);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  // Open AppMessage
  const int inbox_size = 128;
  const int outbox_size = 128;
  app_message_open(inbox_size, outbox_size);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
}

// Reallocating memory and deinitialization
static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}



