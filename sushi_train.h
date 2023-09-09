
//node struct sushi tray
typedef struct tray {
  unsigned short hour;
  unsigned short min;
  unsigned short sec;
  struct tray* next;
}trayType,*ptrTray;
void push(void);
void pop(void);
void adjustment_1(void);
void adjustment_2(void);
void deleteFIFO(void);

