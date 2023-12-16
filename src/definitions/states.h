#pragma once

// Possible stable states
enum state
{
    BEGIN,
    AT_SPEED,
    END,
    START_UP,
    STOPPED,
    CRUISING,
    REVERSING,
    RESUMING,
    SEEKING_HOME,
    RUNNING_HOME,
    ACCELERATING,
    PAUSED,
    DECELERATING,
    HOME,
    LOST,
    ANY
};
