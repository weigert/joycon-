#define MAX_EVENT_BUFFER 20

enum eventType{
  EVENTTYPE_NONE,
  BUTTON_UP,
  BUTTON_DOWN,
  JOYSTICK_MOVED
};

enum eventInput{
  EVENTINPUT_NONE,
  JOYSTICK,
  JOYCLICK,
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  TRIGGER_L,
  TRIGGER_R,
  TRIGGER_K,
  TRIGGER_Z,
  BUTTON_SPECIAL,
  BUTTON_SIGNED
};

/* Event Storage! */
struct event{
  //Easy Constructor!
  event(eventInput _input, eventType _type){
    input = _input;
    type = _type;
  }

  eventInput input = EVENTINPUT_NONE;
  eventType type = EVENTTYPE_NONE;
};
