#include <stdio.h>

typedef enum {
    FLOOR_GROUND,
    FLOOR_FIRST,
    FLOOR_SECOND
} Floor;

typedef enum {
    EVENT_GO_UP,
    EVENT_GO_DOWN,
    EVENT_STOP
} Event;

const char* floor_to_string(Floor f) {
    switch (f) {
        case FLOOR_GROUND: return "GROUND FLOOR";
        case FLOOR_FIRST:  return "FIRST FLOOR";
        case FLOOR_SECOND: return "SECOND FLOOR";
        default: return "UNKNOWN";
    }
}

const char* event_to_string(Event e) {
    switch (e) {
        case EVENT_GO_UP: return "GO UP";
        case EVENT_GO_DOWN: return "GO DOWN";
        case EVENT_STOP: return "STOP";
        default: return "UNKNOWN EVENT";
    }
}

Floor handle_event(Floor current_floor, Event event) {
    switch (current_floor) {
        case FLOOR_GROUND:
            if (event == EVENT_GO_UP) {
                printf("Going up to First Floor...\n");
                return FLOOR_FIRST;
            } else if (event == EVENT_STOP) {
                printf("Lift stopped at Ground Floor.\n");
                return FLOOR_GROUND;
            } else {
                printf("Already at Ground. Can't go down.\n");
            }
            break;

        case FLOOR_FIRST:
            if (event == EVENT_GO_UP) {
                printf("Going up to Second Floor...\n");
                return FLOOR_SECOND;
            } else if (event == EVENT_GO_DOWN) {
                printf("Going down to Ground Floor...\n");
                return FLOOR_GROUND;
            } else if (event == EVENT_STOP) {
                printf("Lift stopped at First Floor.\n");
                return FLOOR_FIRST;
            }
            break;

        case FLOOR_SECOND:
            if (event == EVENT_GO_DOWN) {
                printf("Going down to First Floor...\n");
                return FLOOR_FIRST;
            } else if (event == EVENT_STOP) {
                printf("Lift stopped at Second Floor.\n");
                return FLOOR_SECOND;
            } else {
                printf("Already at top. Can't go up.\n");
            }
            break;
    }

    return current_floor;
}

int main() {
    Floor current_floor = FLOOR_GROUND;

    Event events[] = {
        EVENT_GO_UP,
        EVENT_STOP,
        EVENT_GO_UP,
        EVENT_STOP,
        EVENT_GO_UP,
        EVENT_GO_DOWN,
        EVENT_STOP
    };

    int num_events = sizeof(events) / sizeof(events[0]);

    printf("Starting Lift FSM Simulation...\n");
    for (int i = 0; i < num_events; i++) {
        printf("\nEvent %d: %s\n", i + 1, event_to_string(events[i]));
        current_floor = handle_event(current_floor, events[i]);
        printf("Current Floor: %s\n", floor_to_string(current_floor));
    }

    return 0;
}



