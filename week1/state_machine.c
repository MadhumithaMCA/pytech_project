#include <stdio.h>


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


State handle_event(State current_state, Event event) {
    switch (current_state) {
        case STATE_IDLE:
            if (event == EVENT_SEND) {
                printf("Sending message...\n");
                return STATE_SENDING;
            } else if (event == EVENT_RECEIVE) {
                printf("Message received. Processing...\n");
                return STATE_RECEIVING;
            }
            break;

        case STATE_SENDING:
            if (event == EVENT_ACK) {
                printf("ACK received. Returning to idle.\n");
                return STATE_IDLE;
            } else if (event == EVENT_TIMEOUT) {
                printf("Timeout! Resending message...\n");
                return STATE_SENDING;
            } else {
                printf("Waiting for ACK...\n");
                return STATE_WAIT_ACK;
            }

        case STATE_WAIT_ACK:
            if (event == EVENT_ACK) {
                printf(" ACK received. Message delivered.\n");
                return STATE_IDLE;
            } else if (event == EVENT_TIMEOUT) {
                printf("ACK timeout. Resending message.\n");
                return STATE_SENDING;
            }
            break;

        case STATE_RECEIVING:
            if (event == EVENT_ACK) {
                printf("Sending ACK back to sender.\n");
                return STATE_IDLE;
            }
            break;
    }

    printf("No valid transition. Staying in current state.\n");
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
    for (int i = 0; i < num_events; i++) {
        printf("Event %d: ", i+1);
        current_state = handle_event(current_state, events[i]);
    }

    return 0;
}

