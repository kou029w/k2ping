#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>

extern "C" {
  #include <ping.h>
}

// Digital pins for WeMos D1
static const uint8_t D[] = {3, 1, 16, 5, 4, 14, 12, 13, 0, 2, 15};

// LCD Keypad Shield for Arduino
LiquidCrystal lcd(D[8], D[9], D[4], D[5], D[6], D[7]);
void p(char *fmt, ...){
  char buf[17];
  va_list args;
  va_start (args, fmt);
  vsnprintf(buf, 17, fmt, args);
  va_end (args);
  lcd.print(buf);
}

uint8_t errors = 0;
uint8_t success = 0;
int min_time = 0;
int avg_time = 0;
int max_time = 0;
int total_bytes = 0;

void setup() {
  lcd.begin(16, 2);

  WiFi.begin("network-name", "pass-to-network");

  lcd.print("Connecting");
  lcd.setCursor(0, 1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    static uint8_t i = 0;
    lcd.setCursor((i %= 32) % 16, 1);
    if (i < 16) {
      lcd.write(0xFF);
      i++;
    } else if (i < 32) {
      lcd.print(" ");
      i++;
    }
  }

  lcd.clear();
  lcd.print("Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);

  IPAddress dest_ip;
  WiFi.hostByName("www.google.com", dest_ip);
  lcd.clear();
  lcd.print(dest_ip);

  lcd.setCursor(15, 0);
  lcd.blink();
  while (analogRead(0) >= 128) yield();
  lcd.noBlink();

  // Let's enjoy ping!
  ping(dest_ip);
}

void loop() {
  ;
}

void ping(IPAddress dest_ip) {
  ping_option opt;
  memset(&opt, 0, sizeof(struct ping_option));

  opt.count = 4;
  opt.coarse_time = 1;
  opt.ip = dest_ip;

  opt.recv_function = reinterpret_cast<ping_recv_function>(&ping_recv_cb);
  opt.sent_function = NULL;

  lcd.clear();
  lcd.print(IPAddress(opt.ip));
  lcd.setCursor(15, 0);
  lcd.print("*");

  ping_start(&opt);
}

void ping_recv_cb(void *_option, void *_resp) {
  ping_resp*   resp = reinterpret_cast<struct ping_resp*>(_resp);
  ping_option* opt  = reinterpret_cast<struct ping_option*>(_option);

  if (resp->ping_err == -1) {
    errors++;
    lcd.setCursor(0, 1);
    lcd.print("Transmit failed.");
  } else {
    success++;
    avg_time += resp->resp_time;
    if (success == 1 || resp->resp_time < min_time) min_time = resp->resp_time;
    if (resp->resp_time > max_time) max_time = resp->resp_time;
    total_bytes += resp->bytes;
    lcd.setCursor(0, 1);
    p((char*)"#%-2d%3dbyte%4dms", resp->seqno, resp->bytes, resp->resp_time);
  }

  if (errors + success >= opt->count) {
    if (success > 0) avg_time /= success;
    lcd.clear();
    p((char*)"%4dbyte%3d%%loss", total_bytes, 100 * errors / opt->count);
    lcd.setCursor(0, 2);
    p((char*)"%4d/%4d/%4dms", min_time, avg_time, max_time);
  }
}
