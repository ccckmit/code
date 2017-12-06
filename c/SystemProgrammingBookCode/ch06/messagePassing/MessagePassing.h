#ifndef _MESSAGE_PASSING_H_

#define KEYBOARD 1
#define MOUSE 2

typedef struct {
  int source;
} msg_t;

typedef struct {
  char key;
} keyboard_t;

typedef struct {
  int x, y;
} mouse_t;

extern msg_t msg;
extern keyboard_t keyboard;
extern mouse_t mouse;

void processMessage(msg_t *msg);
int getMessage(msg_t *msg);

int keyboardHit();
int mouseHit();

#endif
