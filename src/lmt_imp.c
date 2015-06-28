#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_hour_one_layer;
static TextLayer *s_background_layer;
static TextLayer *s_hour_two_layer;
static Layer *s_drawing_layer;
static TextLayer *s_date_layer;
static char date_buffer[] = "000 00";
static char hour_buffer[] = "00";
static char mins_buffer[] = "00";
static char one_hour[] = "0";
static char two_hour[] = "0";

static GBitmap *s_bt_on;
static GBitmap *s_bt_off;
static BitmapLayer *s_bitmap_layer;

static GFont s_time_font;
static GFont s_time_two_font;

static void update_hour(){
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  //Set date buffer
  strftime(date_buffer, sizeof("000 00"), "%a %d", tick_time);
  
  if(clock_is_24h_style() == true) {
    //Use 2h hour format
    strftime(hour_buffer, sizeof("00"), "%H", tick_time);
  } else {
    //Use 12 hour format
    strftime(hour_buffer, sizeof("00"), "%I", tick_time);
  }
  if (hour_buffer[0] == '0') {
    memmove(one_hour, " ", 1);
  } else {
    memmove(one_hour, &hour_buffer[0], 1);
  }
  memmove(two_hour, &hour_buffer[1], 1);
  text_layer_set_text(s_hour_one_layer, one_hour);
  text_layer_set_text(s_hour_two_layer, two_hour);
  text_layer_set_text(s_date_layer, date_buffer);
  
  //Set minutes buffer
  strftime(mins_buffer, sizeof("00"), "%M", tick_time);
}

static void create_background_layer() {
  // Create background TextLayer
  s_background_layer = text_layer_create(GRect(0, 0, 144, 168)); // 144 x 166
  text_layer_set_background_color(s_background_layer, GColorRed);
}

static void create_hour_layer() {
  s_hour_one_layer = text_layer_create(GRect(5, 0, 72, 72));
  text_layer_set_background_color(s_hour_one_layer, GColorClear);
  
  text_layer_set_text_color(s_hour_one_layer, GColorWhite);
  text_layer_set_text(s_hour_one_layer, "0");
  
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SOLARIA_64));

  text_layer_set_font(s_hour_one_layer, s_time_font);
  text_layer_set_text_alignment(s_hour_one_layer, GTextAlignmentRight);
}

static void create_hour_layer_2(){
  s_hour_two_layer = text_layer_create(GRect(5, 70, 72, 72));
  text_layer_set_background_color(s_hour_two_layer, GColorClear);
  
  text_layer_set_text_color(s_hour_two_layer, GColorWhite);
  text_layer_set_text(s_hour_two_layer, "0");
  
  s_time_two_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SOLARIA_64));
  text_layer_set_font(s_hour_two_layer, s_time_two_font);
  text_layer_set_text_alignment(s_hour_two_layer, GTextAlignmentRight);
}

static void create_date_layer(){
  s_date_layer = text_layer_create(GRect(0, 153, 72, 15));
  text_layer_set_background_color(s_date_layer, GColorClear);
  
  text_layer_set_text_color(s_date_layer, GColorWhite);
  text_layer_set_text(s_date_layer, "000 00");
  
  s_time_two_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_SOLARIA_12));
  text_layer_set_font(s_date_layer, s_time_two_font);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
}

static void white_line_update(GPoint first_point,GPoint second_point, GContext *ctx){
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_stroke_width(ctx, 2);
  graphics_draw_line(ctx, first_point, second_point);
}

static void black_line_update(GPoint first_point,GPoint second_point, GContext *ctx){
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 1);
  graphics_draw_line(ctx, first_point, second_point);
}

static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  // Enable antialiasing
  graphics_context_set_antialiased(ctx, true);
  int i = atoi(mins_buffer);
  
  if (i <= 5){
    black_line_update(GPoint(0, 140), GPoint(10, 140), ctx); //5 min
  }else{
    white_line_update(GPoint(0, 140), GPoint(10, 140), ctx); //5 min
  }
  if (i <= 10){
    black_line_update(GPoint(0, 128), GPoint(10, 128), ctx); //10 min
  }else{
    white_line_update(GPoint(0, 128), GPoint(10, 128), ctx); //10 min
  }
  if (i <= 15){
    black_line_update(GPoint(0, 116), GPoint(20, 116), ctx); //15 min
  }else{
    white_line_update(GPoint(0, 116), GPoint(20, 116), ctx); //15 min
  }
  if (i <= 20){
    black_line_update(GPoint(0, 104), GPoint(10, 104), ctx); //20 min
  }else{
    white_line_update(GPoint(0, 104), GPoint(10, 104), ctx); //20 min
  }
  if (i <= 25){
    black_line_update(GPoint(0, 92), GPoint(10, 92), ctx); //25 min
  }else{
    white_line_update(GPoint(0, 92), GPoint(10, 92), ctx); //25 min
  }
  if (i <= 30){
    black_line_update(GPoint(0, 80), GPoint(40, 80), ctx); //30 min
  }else{
    white_line_update(GPoint(0, 80), GPoint(40, 80), ctx); //30 min
  }
  if (i <= 35){
    black_line_update(GPoint(0, 68), GPoint(10, 68), ctx); //35 min
  }else{
    white_line_update(GPoint(0, 68), GPoint(10, 68), ctx); //35 min
  }
  if (i <= 40){
    black_line_update(GPoint(0, 56), GPoint(10, 56), ctx); //40 min
  }else{
    white_line_update(GPoint(0, 56), GPoint(10, 56), ctx); //40 min
  }
  if (i <= 45){
    black_line_update(GPoint(0, 44), GPoint(20, 44), ctx); //45 min
  }else{
    white_line_update(GPoint(0, 44), GPoint(20, 44), ctx); //45 min
  }
  if (i <= 50){
    black_line_update(GPoint(0, 32), GPoint(10, 32), ctx); //50 min
  }else{
    white_line_update(GPoint(0, 32), GPoint(10, 32), ctx); //50 min
  }
  if (i <= 55){
    black_line_update(GPoint(0, 20), GPoint(10, 20), ctx); //55 min
  }else{
    white_line_update(GPoint(0, 20), GPoint(10, 20), ctx); //55 min
  }
}

static void create_bt_icon_layer(){
  s_bt_on = gbitmap_create_with_resource(RESOURCE_ID_BT_ON_WHITE);
  s_bitmap_layer = bitmap_layer_create(GRect(4, 4, 10, 20));
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpOr);
  bitmap_layer_set_background_color(s_bitmap_layer, GColorClear);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bt_on);
}

static void bt_handler(bool connected) {
  // Show current connection state
  if (connected) {
    s_bt_on = gbitmap_create_with_resource(RESOURCE_ID_BT_ON_WHITE);
    bitmap_layer_set_bitmap(s_bitmap_layer, s_bt_on);
  } else {
    s_bt_off = gbitmap_create_with_resource(RESOURCE_ID_BT_OFF_WHITE);
    bitmap_layer_set_bitmap(s_bitmap_layer, s_bt_off);
  }
}

static void main_window_load(Window *window) {
  
  // Create background layer and add it as a child layer to the Window's root layer
  create_background_layer();
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_background_layer));
  
  //Create hour TestLayer and add it to the background layer
  create_hour_layer();
  layer_add_child(text_layer_get_layer(s_background_layer), text_layer_get_layer(s_hour_one_layer));
  
  create_hour_layer_2();
  layer_add_child(text_layer_get_layer(s_background_layer), text_layer_get_layer(s_hour_two_layer));
  
  create_date_layer();
  layer_add_child(text_layer_get_layer(s_background_layer), text_layer_get_layer(s_date_layer));
  
  create_bt_icon_layer();
  layer_add_child(text_layer_get_layer(s_background_layer), bitmap_layer_get_layer(s_bitmap_layer));
  
  // Show current connection state
  bt_handler(bluetooth_connection_service_peek());
  
  // Create drawing layer
  s_drawing_layer = layer_create(GRect(90, 0, 72, 168));
  layer_add_child(text_layer_get_layer(s_background_layer), s_drawing_layer);
  
  // Make sure the time is displayed from the start
  update_hour();
  
  // Set the update_proc
  layer_set_update_proc(s_drawing_layer, canvas_update_proc);
}

static void main_window_unload(Window *window) {
  //Unload GFont
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_time_two_font);
  
  // Destroy layers
  text_layer_destroy(s_background_layer);
  text_layer_destroy(s_hour_one_layer);
  text_layer_destroy(s_hour_two_layer);
  layer_destroy(s_drawing_layer);
  text_layer_destroy(s_date_layer);
  gbitmap_destroy(s_bt_on);
  gbitmap_destroy(s_bt_off);
  bitmap_layer_destroy(s_bitmap_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_hour();
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Subscribe to Bluetooth updates
  bluetooth_connection_service_subscribe(bt_handler);
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}