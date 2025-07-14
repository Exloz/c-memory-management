
#include "http.h"
#include <stdio.h>

char *http_to_str(HttpErrorCode code) {

  switch (code){
    case HTTP_BAD_REQUEST:
      printf("400 Bad Request\n");
      break;
    case HTTP_UNAUTHORIZED:
      printf("401 Unauthorized\n");
      break;
    case HTTP_NOT_FOUND:
      printf("404 Not Found\n");
      break;
    case HTTP_TEAPOT:
      printf("418 I AM A TEAPOT\n");
      break;
    case HTTP_INTERNAL_SERVER_ERROR:
      printf("500 Internal Server Error\n");
      break;
    default:
      printf("Unknown HTTP status code\n");
    break;
  }

}
