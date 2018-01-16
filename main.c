#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "jsonHandle.h"

char jsonData[500];
int string_parser(char* bufferr, char* ptr);

int main(void) {
  printf("Hello World\n");
  char *data = "0control{\"surya\":\"mass\"}";
  printf("%s\n",data);
  char* text = "{\"1\":25}";
  char *out;
  cJSON *json;
  json = cJSON_Parse(text);
  if (!json) {
    //LOG_W(common, "Error before: [%s]\n", cJSON_GetErrorPtr());
  } else {
  	int status = cJSON_GetObjectItem(json, "1")->valueint;
    out = cJSON_Print(json);
    printf("Status: %d\n",status);
    cJSON_Delete(json);
    cJSON_free(out);
  }
  
  string_parser(data, jsonData);
  printf("\n%s\n",jsonData);
  return 0;
}

int string_parser(char* bufferr, char* ptr) {
  char* json = ptr;
  int flower_count = 0;
  typedef enum {
    STATE_INIT = 0,
    STATE_START_JSON,
    STATE_END_JSON,
  } STATE;
  STATE state = STATE_INIT;
  int j = 0;
  printf("Init Buffer: %s.\n",bufferr);
  for (int i = 1; i <= strlen(bufferr); i++) {
    
    if (bufferr[i+1] == '{' && state == STATE_INIT) {
      state = STATE_START_JSON;
      memset(json,'\0',500);
      continue;
    }
    switch (state) {
      case STATE_START_JSON:
        if (bufferr[i] == '{') {
          flower_count++;
          json[j++] = bufferr[i];
        }
        else if (bufferr[i] == '}') {
          flower_count--;
          json[j++] = bufferr[i];
          if (flower_count <= 0) {
            state = STATE_END_JSON;
          }
        }
        else {
          json[j++] = bufferr[i];
          if (bufferr[i] == '}') {
            state = STATE_END_JSON;
          }
        }
        break;
      case STATE_END_JSON:
        json[j++] = '\0';
        break;
      default:
        break;
    }
  }
  return 0;
}