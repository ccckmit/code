#include <MessagePassing.h>

msg_t msg;
keyboard_t keyboard;
mouse_t mouse;

int main() {
  while (1) {
    if (getMessage(&msg))
      processMessage(&msg);
  }
}

void processMessage(msg_t *msg) {
  if (msg->source == KEYBOARD) {
	// ...
  } else if (msg->source ==MOUSE) {
    // ...
  }
}

int getMessage(msg_t *msg) {
  if (keyboardHit()) {
    msg->source = KEYBOARD;
    // mouse.key = getKey();
  } else if (mouseHit()) {
    msg->source = MOUSE;
    // getMouseXY(&msg->x, &msg->y);
  }
  return 0;
}

int keyboardHit() {}
int mouseHit() {}
