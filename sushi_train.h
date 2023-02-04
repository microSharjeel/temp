//node struct sushi tray

typedef struct tray {
  unsigned short hour,
  unsigned short min,
  unsigned short sec,
  struct tray* next,
}trayType,*ptrTray;
#define MAX_LEN 23
ptrTray push(void);
//push pop functions
