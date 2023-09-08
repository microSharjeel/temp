#define MAX_LEN 23
//node struct sushi tray
typedef struct tray {
  unsigned short hour,
  unsigned short min,
  unsigned short sec,
  struct tray* next,
}trayType,*ptrTray;
ptrTray push(void);
void pop(void);
void adjustment1(void);
void adjustment2(void);
void deleteFIFO(void);

