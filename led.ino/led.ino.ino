#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>

#include "RGB.h"

#define PIN 25
#define H 16
#define W 16

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(H, W, PIN,
                            NEO_MATRIX_LEFT + NEO_MATRIX_TOP +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB + NEO_KHZ800);

RGB bitmap_pixels[16][16] = {{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
};

const char *mdns_name = "pictureFrame";
const char *ssid = "";
const char *password = "";
volatile bool serverSet = false;

WebServer server(80);
HTTPClient http;


void on_ping() {
  Serial.println("/ping hit");
  server.send(200, "text/plain", "Status: Working!");
}

void handle_img_rgb_data() {
  if (server.method() != HTTP_POST) {
    server.send(404, "text/plain", "Incorrect method");
  } else {
    String req_data = server.arg(0);
    char image_uri[req_data.length()];
    req_data.toCharArray(image_uri, req_data.length() + 1);

    if (WiFi.status() != WL_CONNECTED) {
      server.send(503, "text/plain", "WiFi unavailable, please try again in a few seconds");
    } else {
      http.begin("https://digital-picture-frame.herokuapp.com/process");
      http.addHeader("Content-Type", "text/plain");
      
      int httpCode = http.POST(image_uri);
      
      if (httpCode != 200) {
        if (httpCode == 400) {
          server.send(400, "text/plain", "Incorrect format for image_uri. Please ensure the link is of type jpg, png, jpeg or svg.");
        } else {
          server.send(httpCode, "text/plain", "Error with processing server.");
        }
      } else {
        String response = http.getString();
        char rgb_data[response.length()];
        response.toCharArray(rgb_data, response.length() + 1);

        server.send(200, "txt/plain", "Image uploaded!");
        Serial.println("Parsing img");
        parse_rgb_values(rgb_data);
        drawBitmap();
        serverSet = true;
      }

      http.end();
      Serial.println("POST Handling complete!");
    }
  }
}

void setup()
{
  matrix.begin();
  matrix.setBrightness(10);
  matrix.setTextColor(matrix.Color(255, 255, 255));
  matrix.setTextWrap(false);
  // Fill the screen with white bitmap_pixels
  matrix.fillScreen(matrix.Color(white.r, white.g, white.b));
  delay(1000);

  // Turn all bitmap_pixels off
  matrix.fillScreen(0);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); // change to something for having the picture up and running
  }

  if (MDNS.begin(mdns_name)) {
    Serial.println("Success!");
  }

  server.enableCORS();
  server.on("/ping", on_ping);
  //  server.on("/img_data", HTTP_POST, handle_img_rgb_data);
  server.on("/img_data", handle_img_rgb_data);

  server.begin();
  crossFade(off, blue, 20, 5);
}

// Fill the bitmap_pixels one after the other with a color
void colorWipe(RGB color, uint8_t wait)
{
  for (uint16_t row = 0; row < 16; row++)
  {
    for (uint16_t column = 0; column < 16; column++)
    {
      matrix.show();
      delay(wait);
    }
  }
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait)
{
  for (int i = 0; i <= steps; i++)
  {
    int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
    int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
    int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

    matrix.drawPixel(x, y, matrix.Color(endColor.r, endColor.g, endColor.b));
    matrix.show();
    delay(wait);
  }
}

void drawBitmap()
{
  for (int row = 0; row < H; row++)
  {
    for (int col = 0; col < W; col++)
    {
      fadePixel(col, row, off, bitmap_pixels[row][row % 2 == 1 ? W - col : col], 0, 1);
    }
  }
}

// Crossfade entire screen from startColor to endColor
void crossFade(RGB startColor, RGB endColor, int steps, int wait)
{
  for (int i = 0; i <= steps; i++)
  {
    int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
    int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
    int newB = startColor.b + (endColor.b - startColor.b) * i / steps;

    matrix.fillScreen(matrix.Color(newR, newG, newB));
    matrix.show();
    delay(wait);
  }
}

void parse_rgb_values(char *string)
{
  char *ptr = strtok(string, " ");

  for (int row = 0; row < H; row++)
  {
    for (int col = 0; col < W; col++)
    {
      int colorR = atoi(ptr);
      ptr = strtok(NULL, " ");
      int colorG = atoi(ptr);
      ptr = strtok(NULL, " ");
      int colorB = atoi(ptr);
      ptr = strtok(NULL, " ");
      Serial.println(colorR);
      Serial.println(colorG);
      Serial.println(colorB);

      bitmap_pixels[row][col] = (RGB) {
        .r = colorR, .g = colorG, .b = colorB
      };
    }
  }
}

void loop()
{
  server.handleClient();
  if (!serverSet) {
    char default_img[] = "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 254 254 253 253 254 254 254 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 253 254 255 210 201 201 218 202 202 220 215 216 229 224 225 238 234 234 246 249 249 255 255 255 255 255 255 255 255 255 254 253 253 255 255 255 255 255 255 255 255 255 255 255 255 255 254 254 255 255 255 149 137 137 105 36 31 128 59 54 99 54 54 133 61 63 129 80 81 131 96 94 158 122 120 223 222 223 255 255 255 254 253 253 254 254 254 255 255 255 255 255 255 255 255 255 252 251 251 233 241 239 118 105 101 131 52 40 133 63 55 89 48 46 121 49 42 104 44 37 82 35 31 118 67 62 195 185 184 252 255 255 255 254 254 254 254 255 254 254 254 255 255 255 222 221 221 224 226 223 209 222 217 99 85 77 159 65 48 164 72 52 120 59 46 146 64 50 143 62 48 108 48 38 116 45 36 181 139 132 250 247 246 255 255 255 254 254 254 255 255 255 227 227 227 175 182 178 232 237 232 207 214 210 79 69 66 96 64 73 87 62 71 78 57 55 116 64 61 98 61 64 91 59 56 99 46 44 119 105 110 237 240 241 255 255 255 253 253 253 246 247 246 192 202 196 196 203 198 227 229 220 30 97 160 23 104 208 35 98 182 46 81 124 30 90 182 41 88 165 47 75 120 33 80 171 67 92 152 242 240 237 255 255 255 255 255 255 207 211 208 229 237 233 201 208 201 173 185 182 33 104 191 39 112 224 45 96 171 50 85 145 40 95 206 50 83 153 53 78 141 32 71 175 144 156 192 255 255 255 255 255 255 255 254 255 223 228 226 212 222 215 252 254 250 115 134 131 39 84 133 45 87 144 51 80 107 52 79 120 48 80 141 59 77 101 57 75 118 49 70 120 211 212 216 255 255 255 255 255 255 253 252 252 243 247 245 206 215 209 255 254 247 133 162 178 33 88 162 48 94 170 55 88 131 41 86 173 47 81 158 60 75 122 42 76 173 88 107 163 255 253 247 255 255 255 255 255 255 255 255 255 244 245 244 236 240 239 230 232 217 105 148 197 30 102 214 42 96 189 53 89 149 41 89 191 53 78 143 60 76 132 39 67 154 159 166 191 255 255 255 252 252 253 255 255 255 255 255 255 250 250 250 249 250 249 222 227 217 66 102 131 43 83 141 54 81 116 60 77 110 60 81 141 64 75 106 62 80 140 70 83 140 230 229 227 255 255 255 254 254 254 255 255 255 255 255 255 254 254 254 251 250 250 226 230 228 57 98 158 44 88 178 49 72 130 46 70 152 41 68 165 49 58 121 36 53 155 127 131 180 255 255 255 253 253 255 255 255 255 255 255 255 255 255 255 254 254 255 255 255 255 188 198 203 39 82 167 56 88 175 87 96 141 101 113 174 133 137 180 165 162 184 188 186 207 237 236 238 255 255 255 254 254 254 255 255 255 255 255 255 255 255 255 254 254 255 255 255 255 230 232 234 211 215 225 234 234 237 251 249 247 255 255 254 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 254 254 255 252 253 254 252 252 253 252 252 253 254 254 254 255 255 255 255 255 255 255 255 255";
    parse_rgb_values(default_img);
    drawBitmap();
  }
}
