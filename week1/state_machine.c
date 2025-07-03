#include <stdio.h>
#include <unistd.h> // For sleep()

typedef enum {
    STATE_IDLE,
    STATE_SENDING,
    STATE_WAIT_ACK,
    STATE_RECEIVING
} State;

typedef enum {
    EVENT_SEND,
    EVENT_RECEIVE,
    EVENT_ACK,
    EVENT_TIMEOUT
} Event;

// Convert state enum to string
const char* state_to_string(State state) {
    switch (state) {
        case STATE_IDLE: return "STATE_IDLE";
        case STATE_SENDING: return "STATE_SENDING";
        case STATE_WAIT_ACK: return "STATE_WAIT_ACK";
        case STATE_RECEIVING: return "STATE_RECEIVING";
        default: return "UNKNOWN_STATE";
    }
}

// Convert event enum to string
const char* event_to_string(Event event) {
    switch (event) {
        case EVENT_SEND: return "EVENT_SEND";
        case EVENT_RECEIVE: return "EVENT_RECEIVE";
        case EVENT_ACK: return "EVENT_ACK";
        case EVENT_TIMEOUT: return "EVENT_TIMEOUT";
        default: return "UNKNOWN_EVENT";
    }
}

State handle_event(State current_state, Event event) {
    switch (current_state) {
        case STATE_IDLE:
            if (event == EVENT_SEND) {
                printf("Sending message...\n");
                sleep(1);
                return STATE_SENDING;
            } else if (event == EVENT_RECEIVE) {
                printf("Message received. Processing...\n");
                sleep(1);
                return STATE_RECEIVING;
            }
            break;

        case STATE_SENDING:
            if (event == EVENT_ACK) {
                printf("ACK received. Returning to idle.\n");
                sleep(1);
                return STATE_IDLE;
            } else if (event == EVENT_TIMEOUT) {
                printf("Timeout! Resending message...\n");
                sleep(1);
                return STATE_SENDING;
            } else {
                printf("Waiting for ACK...\n");
                sleep(1);
                return STATE_WAIT_ACK;
            }

        case STATE_WAIT_ACK:
            if (event == EVENT_ACK) {
                printf("ACK received. Message delivered.\n");
                sleep(1);
                return STATE_IDLE;
            } else if (event == EVENT_TIMEOUT) {
                printf("ACK timeout. Resending message.\n");
                sleep(1);
                return STATE_SENDING;
            }
            break;

        case STATE_RECEIVING:
            if (event == EVENT_ACK) {
                printf("Sending ACK back to sender.\n");
                sleep(1);
                return STATE_IDLE;
            }
            break;
    }

    printf("No valid transition. Staying in current state.\n");
    sleep(1);
    return current_state;
}

int main() {
    State current_state = STATE_IDLE;

    Event events[] = {
        EVENT_SEND,
        EVENT_TIMEOUT,
        EVENT_SEND,
        EVENT_ACK,
        EVENT_RECEIVE,
        EVENT_ACK
    };

    int num_events = sizeof(events) / sizeof(events[0]);

    printf("Starting Message Exchange FSM:\n");
    sleep(1);

    for (int i = 0; i < num_events; i++) {
        printf("\nEvent %d (%s):\n", i + 1, event_to_string(events[i]));
        sleep(1);

        current_state = handle_event(current_state, events[i]);

        printf("Current State: %s\n", state_to_string(current_state));
        sleep(1);
    }

    printf("\nFSM Simulation Completed.\n");
    return 0;
}
