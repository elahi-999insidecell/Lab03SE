# Lab 03 -- State Pattern

## 1. Pattern Name

**State Pattern**

## 2. Category

**Behavioral Design Pattern**

## 3. Intent

The State Pattern allows an object to alter its behavior when its
internal state changes, making the object appear as if it changed its
class. Instead of scattering conditional logic throughout the code, each
state's behavior is encapsulated in its own class, and the object
delegates behavior to the current state object.

## 4. Problem Statement

Many real-world objects behave differently depending on which "mode" or
"status" they are currently in. If this behavior is implemented directly
with conditional statements (`if-else` or `switch`) inside the main
class, the class becomes difficult to read, test, and extend. Every time
a new state is introduced, the developer must locate and modify every
conditional block that checks the state, which is error-prone and
violates the Open/Closed Principle.

## 5. Motivation

Consider a media player that can be **Stopped**, **Playing**, or
**Paused**. A naive implementation would store the state as a string or
enum inside the `MediaPlayer` class and check it everywhere:

``` cpp
if (state == "STOPPED") { ... }
else if (state == "PLAYING") { ... }
else if (state == "PAUSED") { ... }
```

As more states and actions are added, this conditional logic grows and
becomes duplicated across every method that depends on the state
(`play`, `pause`, `stop`, `next track`, etc.). The State Pattern solves
this by moving each branch of behavior into its own class, so the main
class simply delegates to whichever state object is currently active.

## 6. Pattern Structure (UML Class Diagram)

> **UML diagram:** Add the State Pattern UML image pushed by the team to
> the repository and update the filename below.
>
> `![State Pattern UML](path/to/state-pattern-uml.png)`

## 7. Class Responsibilities

-   **MediaPlayer (Context)** -- Holds a reference to the current
    `PlayerState` object and forwards user actions (`pressPlay`,
    `pressPause`) to it. Does not itself contain any state-specific
    logic.
-   **PlayerState (Interface)** -- Declares the two operations every
    state must implement: `play()` and `pause()`.
-   **StoppedState** -- Handles behavior when the player is stopped.
    Starts playback and transitions to `PlayingState`; pause is invalid
    in this state.
-   **PlayingState** -- Handles behavior while music is playing. Pausing
    moves to `PausedState`; pressing play again is a no-op.
-   **PausedState** -- Handles behavior while paused. Pressing play
    resumes playback and transitions to `PlayingState`; pressing pause
    again is a no-op.

## 8. Code Implementation

``` cpp
#include <iostream>
using namespace std;

class MediaPlayer; // forward declaration

// State interface
class PlayerState {
public:
    virtual void play(MediaPlayer* player) = 0;
    virtual void pause(MediaPlayer* player) = 0;
    virtual ~PlayerState() {}
};

// Context
class MediaPlayer {
private:
    PlayerState* state;

public:
    void setState(PlayerState* s) { state = s; }
    void pressPlay() { state->play(this); }
    void pressPause() { state->pause(this); }
};

// Concrete States
class StoppedState : public PlayerState {
public:
    void play(MediaPlayer* player) override;
    void pause(MediaPlayer* player) override;
};

class PlayingState : public PlayerState {
public:
    void play(MediaPlayer* player) override;
    void pause(MediaPlayer* player) override;
};

class PausedState : public PlayerState {
public:
    void play(MediaPlayer* player) override;
    void pause(MediaPlayer* player) override;
};

void StoppedState::play(MediaPlayer* player) {
    cout << "Starting playback...\n";
    player->setState(new PlayingState());
}

void StoppedState::pause(MediaPlayer* player) {
    cout << "Cannot pause. Player is already stopped.\n";
}

void PlayingState::play(MediaPlayer* player) {
    cout << "Already playing.\n";
}

void PlayingState::pause(MediaPlayer* player) {
    cout << "Pausing playback...\n";
    player->setState(new PausedState());
}

void PausedState::play(MediaPlayer* player) {
    cout << "Resuming playback...\n";
    player->setState(new PlayingState());
}

void PausedState::pause(MediaPlayer* player) {
    cout << "Already paused.\n";
}

int main() {
    MediaPlayer player;
    player.setState(new StoppedState());

    player.pressPlay();   // Starting playback...
    player.pressPause();  // Pausing playback...
    player.pressPlay();   // Resuming playback...
    player.pressPause();  // Pausing playback...
    player.pressPause();  // Already paused.

    return 0;
}
```

## 9. Execution Flow (Object Interaction)

1.  `MediaPlayer` is created and initialized with a `StoppedState`
    object.
2.  The client calls `player.pressPlay()`, and `MediaPlayer` delegates
    to `state->play(this)`.
3.  `StoppedState::play()` prints a message and changes the Context
    state to `PlayingState`.
4.  The client calls `player.pressPause()`, which delegates to
    `PlayingState::pause()` and switches the Context to `PausedState`.
5.  The client calls `player.pressPlay()` again, which delegates to
    `PausedState::play()` and switches back to `PlayingState`.
6.  Each state object is responsible only for its own transitions;
    `MediaPlayer` never contains conditional logic about the current
    state.

## 10. Advantages

-   Eliminates large conditional statements from the Context class.
-   Each state's behavior and transition logic is isolated and easy to
    understand.
-   New states can be added without modifying existing state classes,
    following the Open/Closed Principle.
-   Makes invalid state transitions explicit and easy to handle
    gracefully.

## 11. Limitations

-   Increases the number of classes in the system, which can be
    excessive for very few states.
-   State transition logic is distributed across multiple classes, which
    can make the overall flow harder to trace without a diagram.
-   If not managed carefully, state objects can end up needing to know
    about other state classes, increasing coupling.

## 12. Real-life Applications

-   Media players (Play / Pause / Stop) -- Spotify, VLC, YouTube.
-   Traffic light controllers (Red / Yellow / Green).
-   Order and package tracking systems (Pending → Shipped → Delivered).
-   ATM machines (Idle, CardInserted, PinEntered, Dispensing).
-   TCP connection states (Closed, Listen, Established, etc.).
-   Elevator control systems (Idle, MovingUp, MovingDown, DoorOpen).
-   Game character behavior (Idle, Walking, Jumping, Attacking).

## 13. Industry Examples

-   Android Activity lifecycle (Created, Started, Resumed, Paused,
    Destroyed) follows the same conceptual model.
-   Streaming platforms such as Netflix use similar state handling for
    Buffering, Playing, Paused, and Error states.
-   Workflow/ticket tools such as JIRA model ticket status (To-Do → In
    Progress → Done) as states.
-   Banking systems use state-driven pipelines for loan or application
    approval status.

## 14. Conclusion

The State Pattern turns state-dependent behavior into a set of
well-defined, interchangeable classes, removing complex conditional
logic from the main object. By letting each state manage its own
transitions, the MediaPlayer example remains easy to extend---for
example, adding a new state such as `Buffering` requires creating a new
class without touching the existing state classes.
