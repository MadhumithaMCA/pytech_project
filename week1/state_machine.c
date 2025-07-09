#include <stdio.h>
#include <unistd.h> // sleep() function to simulate delay

// Define the possible states of the FSM
typedef enum {
    STATE_IDLE,       // Waiting to send or receive
    STATE_SENDING,    // Sending a message
    STATE_WAIT_ACK,   // Waiting for ACK after sending
    STATE_RECEIVING   // Receiving a message
} State;

// Define the possible events that can trigger state transitions
typedef enum {
    EVENT_SEND,       // Send a message
    EVENT_RECEIVE,    // Receive a message
    EVENT_ACK,        // ACK received
    EVENT_TIMEOUT     // No ACK received within time
} Event;

// Convert State enum to a human-readable string
const char* state_to_string(State state) {
    switch (state) {
        case STATE_IDLE: return "STATE_IDLE";
        case STATE_SENDING: return "STATE_SENDING";
        case STATE_WAIT_ACK: return "STATE_WAIT_ACK";
        case STATE_RECEIVING: return "STATE_RECEIVING";
        default: return "UNKNOWN_STATE";
    }
}

// Convert Event enum to a human-readable string
const char* event_to_string(Event event) {
    switch (event) {
        case EVENT_SEND: return "EVENT_SEND";
        case EVENT_RECEIVE: return "EVENT_RECEIVE";
        case EVENT_ACK: return "EVENT_ACK";
        case EVENT_TIMEOUT: return "EVENT_TIMEOUT";
        default: return "UNKNOWN_EVENT";
    }
}

// FSM transition handler function
State handle_event(State current_state, Event event) {
    switch (current_state) {

        case STATE_IDLE:
            // If SEND event occurs, go to SENDING
            if (event == EVENT_SEND) {
                printf("Sending message...\n");
                sleep(1);
                return STATE_SENDING;
            }
            // If RECEIVE event occurs, go to RECEIVING
            else if (event == EVENT_RECEIVE) {
                printf("Message received. Processing...\n");
                sleep(1);
                return STATE_RECEIVING;
            }
            break;

        case STATE_SENDING:
            // If ACK received, go back to IDLE
            if (event == EVENT_ACK) {
                printf("ACK received. Returning to idle.\n");
                sleep(1);
                return STATE_IDLE;
            }
            // If timeout occurs, retry sending
            else if (event == EVENT_TIMEOUT) {
                printf("Timeout! Resending message...\n");
                sleep(1);
                return STATE_SENDING;
            }
            // Otherwise, wait for ACK
            else {
                printf("Waiting for ACK...\n");
                sleep(1);
                return STATE_WAIT_ACK;
            }

        case STATE_WAIT_ACK:
            // If ACK received, return to IDLE
            if (event == EVENT_ACK) {
                printf("ACK received. Message delivered.\n");
                sleep(1);
                return STATE_IDLE;
            }
            // If timeout, go back to sending
            else if (event == EVENT_TIMEOUT) {
                printf("ACK timeout. Resending message.\n");
                sleep(1);
                return STATE_SENDING;
            }
            break;

        case STATE_RECEIVING:
            // After receiving, send an ACK and return to IDLE
            if (event == EVENT_ACK) {
                printf("Sending ACK back to sender.\n");
                sleep(1);
                return STATE_IDLE;
            }
            break;
    }

    // If no valid transition is found
    printf("No valid transition. Staying in current state.\n");
    sleep(1);
    return current_state;
}

int main() {
    State current_state = STATE_IDLE;  // Start in IDLE state

    // Define a sequence of events to simulate
    Event events[] = {
        EVENT_SEND,     // Send a message
        EVENT_TIMEOUT,  // Timeout waiting for ACK
        EVENT_SEND,     // Send again
        EVENT_ACK,      // ACK received
        EVENT_RECEIVE,  // Message received
        EVENT_ACK       // ACK sent in response
    };

    int num_events = sizeof(events) / sizeof(events[0]);  // Calculate number of events

    printf("Starting Message Exchange FSM:\n");
    sleep(1);

    // Process each event in sequence
    for (int i = 0; i < num_events; i++) {
        printf("\nEvent %d (%s):\n", i + 1, event_to_string(events[i]));
        sleep(1);

        // Handle the event and update current state
        current_state = handle_event(current_state, events[i]);

        // Print the new state
        printf("Current State: %s\n", state_to_string(current_state));
        sleep(1);
    }

    printf("\nFSM Simulation Completed.\n");
    return 0;
}

