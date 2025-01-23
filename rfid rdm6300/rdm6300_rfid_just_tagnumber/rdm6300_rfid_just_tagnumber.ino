const int BUFFER_SIZE = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const int DATA_SIZE = 10; // 10byte data (2byte version + 8byte tag)
const int DATA_VERSION_SIZE = 2; // 2byte version (actual meaning of these two bytes may vary)
const int DATA_TAG_SIZE = 8; // 8byte tag
const int CHECKSUM_SIZE = 2; // 2byte checksum

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame
int buffer_index = 0;

long hexstr_to_value(uint8_t *str, unsigned int length) {
  char *copy = (char *)malloc((sizeof(char) * length) + 1);
  memcpy(copy, str, sizeof(char) * length);
  copy[length] = '\0';
  // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
  long value = strtol(copy, NULL, 16); // strtol converts a null-terminated string to a long value
  free(copy); // clean up
  return value;
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, D6, D7); // Hardware serial for RFID reader (RX, TX)
}

void loop() {
  if (Serial1.available() > 0) {
    bool call_extract_tag = false;

    int ssvalue = Serial1.read(); // read
    if (ssvalue == -1) { // no data was read
      return;
    }

    if (ssvalue == 2) { // RDM630/RDM6300 found a tag => tag incoming
      buffer_index = 0;
    } else if (ssvalue == 3) { // tag has been fully transmitted
      call_extract_tag = true; // extract tag at the end of the function call
    }

    if (buffer_index >= BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that a buffer overflow comes up!)
      //      Serial.println("Error: Buffer overflow detected!");
      return;
    }

    buffer[buffer_index++] = ssvalue; // everything is alright => copy current value to buffer

    if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        unsigned tag = extract_tag();
      } else { // something is wrong... start again looking for preamble (value: 2)
        buffer_index = 0;
        return;
      }
    }
  }
}

unsigned extract_tag() {
  uint8_t msg_head = buffer[0];
  uint8_t *msg_data = buffer + 1;               // 10 bytes => data contains 2 bytes version + 8 bytes tag
  uint8_t *msg_data_version = msg_data;
  uint8_t *msg_data_tag = msg_data + 2;
  uint8_t *msg_checksum = buffer + 11; // 2 bytes
  uint8_t msg_tail = buffer[13];


  long tag = hexstr_to_value(msg_data_tag, DATA_TAG_SIZE);
  //  Serial.print("Extracted Tag: ");
  Serial.println(tag);

  return tag;
}
