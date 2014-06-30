#include <stdio.h>

/*
 message m
 m2 = m . crc
 |crc| = 2
 m2 % g = 0
 */
#define G 34943
#define MAX_LINE_SIZE 1048
typedef unsigned long long li;

int main() {
  char line[MAX_LINE_SIZE];
  while(gets(line) && line[0] != '#') {
    // Read number from line:
    li m = 0;
    for(int i = 0; line[i] != '\0'; ++i) {
      /*if(line[i] == '\r')
	continue;//*/
      m = ((m << 8) + line[i]) % G;
    }

    m = (m << 8) % G;
    m = (m << 8) % G;
    m = (G-m)%G;
    printf("%02X %02X\n", (int)(m>>8), (int)(m & 0xFF));
  }
  return 0;
}
