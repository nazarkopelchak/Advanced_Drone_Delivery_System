#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "controller.h"
#include "CompositeFactory.h"
#include "IEntityFactory.h"
#include "DeliveryDroneFactory.h"
#include "ChargingDroneFactory.h"
#include "RobotFactory.h"
#include "Beeline.h"
#include "AstarStrategy.h"
#include "DeliveryDrone.h"
#include "entity.h"
#include "graph.h"
#include "robot.h"
#include "drone.h"
#include "station.h"
#include "ChargingDrone.h"

using namespace routing;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate with the controller.
class SimulationModel {
public:
    SimulationModel(IController& controller);

    void SetGraph(const IGraph* graph) {this->graph = graph;}

    /// Creates an simulation entity
    void CreateEntity(JsonObject& entity);

    /// Schedules a trip for an object in the scene
    void ScheduleTrip(JsonObject& details);

    /// Updates the simulation
    void Update(double dt);

    /// Adds a new entity type
    void AddFactory(IEntityFactory* factory);

    //void Notify(DeliveryDrone* drone);

protected:
    IController& controller;
    std::vector<IEntity *> entities;
    std::vector<DeliveryDrone*> deliveryDrones;
    std::vector<ChargingDrone*> chargingDrones;
    std::vector<Robot*> robots;
    std::vector<Station*> stations;
    std::vector<IEntity*> scheduler;
    CompositeFactory* compFactory;
    const IGraph* graph;
};

#endif
