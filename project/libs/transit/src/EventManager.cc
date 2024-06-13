#include "../include/EventManager.h"

void EventManager::Subscribe(Event event, IEventListener* listener) {
    listeners[event].push_back(listener);
}


void EventManager::Unsubscribe(Event event, IEventListener* listener) {
    std::vector<IEventListener*>* subscribers = &listeners[event];

    for (int i = 0; i < subscribers->size(); i++) {
        // simply compare pointers to find the match
        if (subscribers->at(i) == listener) {
            subscribers->erase(subscribers->begin() + i);
        }
    }
}


void EventManager::NotifyAll(Event event, IEntity* entity) {
    for (IEventListener* listener : listeners[event]) {
        listener->Update(entity);
    }
}


void EventManager::NotifyClosest(Event event, IEntity* entity) {
    float minDis = std::numeric_limits<float>::max();
    IEventListener* nearestListener = nullptr;
    for(IEventListener* listener : listeners[event]){
        float disToListener = listener->GetLocation().Distance(entity->GetPosition());
        if(disToListener <= minDis){
            minDis = disToListener;
            nearestListener = listener;
        }
    }
    if (nearestListener) {
        nearestListener->Update(entity);
    }
}