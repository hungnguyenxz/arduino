#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>

const char* ssid = "Doremon";
const char* password = "15011996";

IPAddress broadcastIP(192,168,1,255);                // Broadcast IP mạng LAN bạn
IPAddress local_IP(192,168,1,97);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// ===== Cấu hình bảo mật web =====
const char* webUser = "admin";
const char* webPass = "7fAEUzV6oCgg57!";

// ===== Cấu hình danh sách máy cần bật =====
struct TargetPC {
  const char* name;
  byte mac[6];
};

TargetPC targets[] = {
  {"hung-desktop", {0x3C, 0x7C, 0x3F, 0x80, 0x69, 0x5B}}
  
};
const int targetCount = sizeof(targets) / sizeof(TargetPC);
const int port = 80;
WiFiUDP udp;
ESP8266WebServer server(port);

void sendWOL(byte *mac) {
  const int port = 9;
  byte packet[102];
  for (int i = 0; i < 6; i++) packet[i] = 0xFF;
  for (int i = 1; i <= 16; i++) memcpy(&packet[i * 6], mac, 6);
  udp.beginPacket(broadcastIP, port);
  udp.write(packet, sizeof(packet));
  udp.endPacket();
  Serial.println("WOL packet sent.");
}
void handleRoot() {
  if(!server.authenticate(webUser, webPass)) {
    return server.requestAuthentication();
  }

  String html = "<html><head><meta charset='UTF-8'><title>Wake-on-LAN</title>";
  html += "<style>body{font-size:xxx-large;padding-top:100px;font-family:sans-serif;text-align:center;background:#f0f2f5;}form{margin-bottom:10px;}button{margin:10px;padding:10px 20px;font-size:xx-large;border:none;border-radius:8px;background:#0078D7;color:white;cursor:pointer;}button:hover{background:#005a9e;}</style>";
  html += "</head><body><h2>Wake-on-LAN Dashboard</h2>";

  for (int i = 0; i < targetCount; i++) {
    html += "<form action='/wake' method='get'>";
    html += "<input type='hidden' name='id' value='" + String(i) + "'>";
    html += "<button type='submit'>Turn on PC: " + String(targets[i].name) + "</button></form>";
  }

  html += "<p style='margin-top:20px;font-size:18px;color:#555;'>ESP8266 IP: ";
  html += WiFi.localIP().toString();
  html += "</p>";
  html += "<p style='margin-top:0px;font-size:18px;color:#555;'>Current time (VNT +7): <span id='time'></span></p>";


  String script = R"rawliteral(
    <script>
      function updateClock() {
        const now = new Date();
        const local = new Date(now.getTime() + (7 * 60 * 60 * 1000));
        const str = local.toISOString().replace("T", " ").split(".")[0];
        document.getElementById("time").textContent = str;
      }
      setInterval(updateClock, 1000);
      updateClock();
    </script>
  )rawliteral";

  html += script;
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleWake() {
  if(!server.authenticate(webUser, webPass)) {
    return server.requestAuthentication();
  }

  String idStr = server.arg("id");
  if (idStr == "") {
    server.send(400, "text/plain", "id is missing");
    return;
  }
  int id = idStr.toInt();
  if (id >= 0 && id < targetCount) {
    sendWOL(targets[id].mac);
    server.sendHeader("Location", "/");
    server.send(303);
  } else {
    server.send(404, "text/plain", "PC not found");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.println("\nConnecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("ESP IP: ");
  Serial.println(WiFi.localIP());

  udp.begin(9);

  server.on("/", handleRoot);
  server.on("/wake", handleWake);
  server.begin();
  Serial.println("HTTP server started on port "+port);
}

void loop() {
  server.handleClient();
}
