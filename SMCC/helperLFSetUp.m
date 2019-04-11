SMCC_Parameters;
%% Create driving scenario
% The scenario name is a scenario file created by the Driving Scenario Designer App. 
scenariosNames = 'scenario_example_DoubleLane.mat';
% The scenario file is converted to a drivingScenario object
% initial conditions of ego car and actor profiles
[scenario,egoCar,actor_Profiles] = helperSessionToScenario(scenariosNames);


% Initial condition for the ego car in ISO 8855 coordinates
v0_ego   = 0;                 % Initial speed of the ego car           (m/s)
x0_ego   = egoCar.x0;          % Initial x position of ego car          (m)
y0_ego   = egoCar.y0;          % Initial y position of ego car          (m)
yaw0_ego = egoCar.yaw0;        % Initial yaw angle of ego car           (rad)

% Convert ISO 8855 to SAE J670E coordinates
y0_ego = -y0_ego;
yaw0_ego = -yaw0_ego;

% Define a simulation stop time
simStopTime = inf;

%% Bus Creation
% Load the Simulink model
modelName = 'SMCC_Example_TestBench';
wasModelLoaded = bdIsLoaded(modelName);
if ~wasModelLoaded
    load_system(modelName)
end

% Create buses for lane sensor and lane sensor boundaries
createLaneSensorBuses;

% load the bus for scenario reader
blk=find_system(modelName,'System','driving.scenario.internal.ScenarioReader');
s = get_param(blk{1},'PortHandles');
get(s.Outport(1),'SignalHierarchy');

% Set the scenario reader file name to the selected scenario
set_param(blk{1},'ScenarioFileName',scenariosNames);

