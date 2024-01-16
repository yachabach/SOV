#pragma once

// Possible Events
enum event
{
    NO_EVENT,
    TRANSITION_COMPLETE,
    LONG_USER_PUSH,   // >2 sec
    SHORT_USER_PUSH,  // <1 sec
    DOUBLE_USER_PUSH, // 2 SHORT_USER_PUSHes in < 1"
    AT_HOME,
    MARKER_DETECT,
    POWER_UP,
    LIMIT_REACHED,
    BEGIN_CRUISE,
    RESUME_CRUISE,
    CRUISE_LIMIT_REACHED,
};
