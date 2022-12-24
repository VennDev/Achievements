#include "EventListener.h"

void eventListen() {
    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent& event) {
        // addPoint(event.mPlayer, rand() % 10);
        return true;
    });
    Event::PlayerPlaceBlockEvent::subscribe([](const Event::PlayerPlaceBlockEvent& event) {
        // addPoint(event.mPlayer, rand() % 10);
        return true;
    });
    Event::PlayerExperienceAddEvent::subscribe([](const Event::PlayerExperienceAddEvent& event) {
        // addPoint(event.mPlayer, rand() % 10);
        return true;
    });
}