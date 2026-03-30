#include <stdio.h>

typedef union SensorData {
  long int temperature;
  long int humidity;
  long int preasure;
} sensor_data_t;

typedef union PacketPayload {
  char text[256];
  unsigned char binary[256];
  struct ImageData {
    int width;
    int height;
    unsigned char data[1024];
  } image;
} packet_payload_t;

typedef union Item {
  struct {
    int damage;
    int range;
    int size;
  } weapon;
  struct {
    int healingAmount;
    int duration;
  } potion;
  struct {
    int doorID;
  } key;
} item_t;

int main() {
  sensor_data_t sensor_data = {
    .temperature = 12341234
  };

  printf("sensor_data_t size: %zu\n", sizeof(sensor_data));
  printf("packet_payload_t size: %zu\n", sizeof(packet_payload_t));
  printf("item_t size: %zu\n", sizeof(item_t));
  return 1;
}
