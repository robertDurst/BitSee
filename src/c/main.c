#include <pebble.h>

// Creating the elements of the app
static Window *s_main_window;

static TextLayer *s_title_layer;
static GFont s_title_font;

static TextLayer *s_Coin1_layer;
static TextLayer *s_Coin2_layer;
static TextLayer *s_Coin3_layer;
static TextLayer *s_Coin4_layer;
static TextLayer *s_Coin5_layer;

static GFont s_crypto_font;

static void main_window_load(Window *window) {
    // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_title_layer = text_layer_create(
      GRect(0, 0, bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_title_layer, GColorClear);
  text_layer_set_text_color(s_title_layer, GColorWhite);
  text_layer_set_font(s_title_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_title_layer, GTextAlignmentCenter);
  text_layer_set_text(s_title_layer, "BitSee");

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_title_layer));
  
  // Create GFont
  s_title_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_Nueue_40));

  // Apply to TextLayer
  text_layer_set_font(s_title_layer, s_title_font);
  
  // Create Coin 1 Layer
  s_Coin1_layer = text_layer_create( GRect(5, 50, bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_Coin1_layer, GColorClear);
  text_layer_set_text_color(s_Coin1_layer, GColorWhite);
  text_layer_set_text_alignment(s_Coin1_layer, GTextAlignmentLeft);
  text_layer_set_text(s_Coin1_layer, "Loading...");
  
  // Create second custom font, apply it and add to Window
  s_crypto_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_NUEUE_20));
  text_layer_set_font(s_Coin1_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_Coin1_layer));
  
   // Create Coin 2 Layer
  s_Coin2_layer = text_layer_create( GRect(5, 70, bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_Coin2_layer, GColorClear);
  text_layer_set_text_color(s_Coin2_layer, GColorWhite);
  text_layer_set_text_alignment(s_Coin2_layer, GTextAlignmentLeft);
  text_layer_set_text(s_Coin2_layer, "Loading...");
  
  // Apply font and add to Window
  text_layer_set_font(s_Coin2_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_Coin2_layer));
  
  // Create Coin 3 Layer
  s_Coin3_layer = text_layer_create( GRect(5, 90, bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_Coin3_layer, GColorClear);
  text_layer_set_text_color(s_Coin3_layer, GColorWhite);
  text_layer_set_text_alignment(s_Coin3_layer, GTextAlignmentLeft);
  text_layer_set_text(s_Coin3_layer, "Loading...");
  
  // Apply font and add to Window
  text_layer_set_font(s_Coin3_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_Coin3_layer));
  
  
  // Create Coin 4 Layer
  s_Coin4_layer = text_layer_create( GRect(5, 110, bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_Coin4_layer, GColorClear);
  text_layer_set_text_color(s_Coin4_layer, GColorWhite);
  text_layer_set_text_alignment(s_Coin4_layer, GTextAlignmentLeft);
  text_layer_set_text(s_Coin4_layer, "Loading...");
  
  // Apply font and add to Window
  text_layer_set_font(s_Coin4_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_Coin4_layer));
  
   // Create Coin 5 Layer
  s_Coin5_layer = text_layer_create( GRect(5, 130, bounds.size.w, 25));

  // Style the text
  text_layer_set_background_color(s_Coin5_layer, GColorClear);
  text_layer_set_text_color(s_Coin5_layer, GColorWhite);
  text_layer_set_text_alignment(s_Coin5_layer, GTextAlignmentLeft);
  text_layer_set_text(s_Coin5_layer, "Loading...");
  
  // Apply font and add to Window
  text_layer_set_font(s_Coin5_layer, s_crypto_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_Coin5_layer));

}

static void main_window_unload(Window *window) {
  
  // Destroy TextLayer
  text_layer_destroy(s_title_layer);
  
   // Unload GFont
  fonts_unload_custom_font(s_title_font);
  
  // Destroy crypto elements
  text_layer_destroy(s_Coin1_layer);
  text_layer_destroy(s_Coin2_layer);
  text_layer_destroy(s_Coin3_layer);
  text_layer_destroy(s_Coin4_layer);
  text_layer_destroy(s_Coin5_layer);
  fonts_unload_custom_font(s_crypto_font);
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
  // Get cryptocurrency update every 1 minute
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
  static char Coin1_Price_buffer[32];
  static char Coin2_Price_buffer[32];
  static char Coin3_Price_buffer[32];
  static char Coin4_Price_buffer[32];
  static char Coin5_Price_buffer[32];
  
  static char Coin1_Label_buffer[32];
  static char Coin2_Label_buffer[32];
  static char Coin3_Label_buffer[32];
  static char Coin4_Label_buffer[32];
  static char Coin5_Label_buffer[32];
  
  static char Coin1_layer_buffer[32];
  static char Coin2_layer_buffer[32];
  static char Coin3_layer_buffer[32];
  static char Coin4_layer_buffer[32];
  static char Coin5_layer_buffer[32];
  
  // Read tuples for data
  Tuple *Coin1_Price_tuple = dict_find(iterator, MESSAGE_KEY_Coin1_Price);
  Tuple *Coin2_Price_tuple = dict_find(iterator, MESSAGE_KEY_Coin2_Price);
  Tuple *Coin3_Price_tuple = dict_find(iterator, MESSAGE_KEY_Coin3_Price);
  Tuple *Coin4_Price_tuple = dict_find(iterator, MESSAGE_KEY_Coin4_Price);
  Tuple *Coin5_Price_tuple = dict_find(iterator, MESSAGE_KEY_Coin5_Price);
  
  Tuple *Coin1_Label_tuple = dict_find(iterator, MESSAGE_KEY_Coin1_Label);
  Tuple *Coin2_Label_tuple = dict_find(iterator, MESSAGE_KEY_Coin2_Label);
  Tuple *Coin3_Label_tuple = dict_find(iterator, MESSAGE_KEY_Coin3_Label);
  Tuple *Coin4_Label_tuple = dict_find(iterator, MESSAGE_KEY_Coin4_Label);
  Tuple *Coin5_Label_tuple = dict_find(iterator, MESSAGE_KEY_Coin5_Label);
  
  // If all data is available, use it
  if(Coin1_Price_tuple && Coin2_Price_tuple && Coin3_Price_tuple && Coin4_Price_tuple && Coin5_Price_tuple && Coin1_Label_tuple && Coin2_Label_tuple && Coin3_Label_tuple && Coin4_Label_tuple && Coin5_Label_tuple) {
     snprintf(Coin1_Price_buffer, sizeof(Coin1_Price_buffer), "$%d", (int)Coin1_Price_tuple->value->uint16);
     snprintf(Coin2_Price_buffer, sizeof(Coin2_Price_buffer), "$%d", (int)Coin2_Price_tuple->value->uint16);
     snprintf(Coin3_Price_buffer, sizeof(Coin3_Price_buffer), "$%d", (int)Coin3_Price_tuple->value->uint16);
     snprintf(Coin4_Price_buffer, sizeof(Coin4_Price_buffer), "$%d", (int)Coin4_Price_tuple->value->uint16);
     snprintf(Coin5_Price_buffer, sizeof(Coin5_Price_buffer), "$%d", (int)Coin5_Price_tuple->value->uint16);
     snprintf(Coin1_Label_buffer, sizeof(Coin1_Label_buffer), "1. %s", Coin1_Label_tuple->value->cstring);
     snprintf(Coin2_Label_buffer, sizeof(Coin2_Label_buffer), "2. %s", Coin2_Label_tuple->value->cstring);
     snprintf(Coin3_Label_buffer, sizeof(Coin3_Label_buffer), "3. %s", Coin3_Label_tuple->value->cstring);
     snprintf(Coin4_Label_buffer, sizeof(Coin4_Label_buffer), "4. %s", Coin4_Label_tuple->value->cstring);
     snprintf(Coin5_Label_buffer, sizeof(Coin5_Label_buffer), "5. %s", Coin5_Label_tuple->value->cstring);
  }
  // Assemble full string and display
    snprintf(Coin1_layer_buffer, sizeof(Coin1_layer_buffer), "%s: %s", Coin1_Label_buffer,  Coin1_Price_buffer);
    text_layer_set_text(s_Coin1_layer, Coin1_layer_buffer);
    snprintf(Coin2_layer_buffer, sizeof(Coin2_layer_buffer), "%s: %s", Coin2_Label_buffer, Coin2_Price_buffer);
    text_layer_set_text(s_Coin2_layer, Coin2_layer_buffer);
    snprintf(Coin3_layer_buffer, sizeof(Coin3_layer_buffer), "%s: %s", Coin3_Label_buffer, Coin3_Price_buffer);
    text_layer_set_text(s_Coin3_layer, Coin3_layer_buffer);
    snprintf(Coin4_layer_buffer, sizeof(Coin4_layer_buffer), "%s: %s", Coin4_Label_buffer, Coin4_Price_buffer);
    text_layer_set_text(s_Coin4_layer, Coin4_layer_buffer);
    snprintf(Coin5_layer_buffer, sizeof(Coin5_layer_buffer), "%s: %s", Coin5_Label_buffer, Coin5_Price_buffer);
    text_layer_set_text(s_Coin5_layer, Coin5_layer_buffer);
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



