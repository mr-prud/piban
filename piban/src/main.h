const uint16_t LONG_DELAY_US = 702;

const uint16_t SHORT_DELAY_US = 317;
const uint16_t REPEAT_DELAY_MS = 8;
const uint16_t REPEAT_NUM = 2;
const uint16_t START_DELAY_US = 4535;
const uint16_t START_DELAY_BEFORE_US = 1500;

const uint8_t RF433MHZ_PIN = 3;

//Static array from wave analysis
const byte enterban[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1};
const byte getoutban[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1};
const byte stopban[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};

// Connect to the WiFi
const char *ssid = "********";
const char *password = "********";
const char *mqtt_server = "********";

// #define DEBUG
#ifdef DEBUG
const char *BANTOPIC = "bantest/set";
#else
const char *BANTOPIC = "ban/set";
#endif

void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
