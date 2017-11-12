#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {
    string id;
    int numberOfFrames;
    map<int, SDL_Rect> keyframes;
};

#endif
