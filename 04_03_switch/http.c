#include "http.h"

char *http_to_str(http_error_code_t code) {
  char *error_code_msg = "";

  switch (code) {
    case HTTP_BAD_REQUEST:
      error_code_msg = "400 Bad Request";
      break;
    case HTTP_UNAUTHORIZED:
      error_code_msg = "401 Unauthorized";
      break;
    case HTTP_NOT_FOUND:
      error_code_msg = "404 Not Found";
      break;
    case HTTP_TEAPOT:
      error_code_msg = "418 I AM A TEAPOT!";
      break;
    case HTTP_INTERNAL_SERVER_ERROR:
      error_code_msg = "500 Internal Server Error";
      break;
    default:
      error_code_msg = "Unknown HTTP status code";
      break;
  }
  return  error_code_msg;
}

