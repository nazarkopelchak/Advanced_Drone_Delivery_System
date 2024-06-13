#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "IEventListener.h"
#include <unordered_map>
#include <vector>

class EventManager {
  public:
    /**
     * @brief Subscribe a listener to an event type
     * 
     * @param event event type to be listened to
     * @param listener listener to be subscribed
     */
    void Subscribe(Event event, IEventListener* listener);
    /**
     * @brief Unsubscribe a specific listener from a specific event type
     * 
     * @param event event type of concern
     * @param listener listener to be unsubscribed
     */
    void Unsubscribe(Event event, IEventListener* listener);
    /**
     * @brief Alert all listeners of a given event type
     * 
     * @param event event type of concern
     * @param entity entity which is the source of the event
     */
    void NotifyAll(Event event, IEntity* entity);
    /**
     * @brief Alert the closest listener of a given event type
     * 
     * @param event event type of concern
     * @param entity entity which is the source of the event
     */
    void NotifyClosest(Event event, IEntity* entity);
    
  private:
    /**
     * O(1) lookup time for event
     */
    std::unordered_map<Event, std::vector<IEventListener*>> listeners;
};

#endif