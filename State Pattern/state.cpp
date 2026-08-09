#include <iostream>
using namespace std;

class MediaPlayer; 


class PlayerState {
public:
    virtual void play(MediaPlayer* player) = 0;
    virtual void pause(MediaPlayer* player) = 0;
    virtual ~PlayerState() {}
};


class MediaPlayer {
private:
    PlayerState* state;
public:
    void setState(PlayerState* s) { state = s; }
    void pressPlay() { state->play(this); }
    void pressPause() { state->pause(this); }
};


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

    player.pressPlay();   
    player.pressPause();  
    player.pressPlay();   
    player.pressPause();  
    player.pressPause();  

    return 0;
}