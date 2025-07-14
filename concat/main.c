
#include <limits.h>
void concat_strings(char *str1, const char *str2){
  char *term_ptr = str1;


  while (*term_ptr != '\0') {
    term_ptr++; 
  }

  for (int j = 0; str2[j] != '\0'; j++) {
    *term_ptr = str2[j];
    term_ptr++;
  }

  *term_ptr = '\0';  
}

int main(void)
{
  char str1[50] = "Hola ";
  const char *str2 = "Mundo";
  concat_strings(str1, str2);
  return 0;
}
