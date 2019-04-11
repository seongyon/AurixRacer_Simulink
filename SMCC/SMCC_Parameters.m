%% Ego Car Parameters
% Dynamics modeling parameters
m       = 2;        % Total mass of vehicle                          (kg)
Iz      = 0.0150;   % Yaw moment of inertia of vehicle               (m*N*s^2)
lf      = 0.15;      % Longitudinal distance from c.g. to front tires (m)
lr      = 0.15;      % Longitudinal distance from c.g. to rear tires  (m)
Cf      = 25;       % Cornering stiffness of front tires             (N/rad)
Cr      = 44;       % Cornering stiffness of rear tires              (N/rad)
tau     = 0.3;      % time constant for longitudinal dynamics 1/s/(tau*s+1)
wheelbase = 0.3;

%% Path following Controller Parameters
max_ac          = 2;     % Maximum acceleration   (m/s^2)
min_ac          = -3;    % Minimum acceleration   (m/s^2)
max_steer       = 0.26;  % Maximum steering       (rad)
min_steer       = -0.26; % Minimum steering       (rad) 

%% Line scanner information
paramLS.numLineScanner = 1;
paramLS.LS(1).InstallPose = [0.3, 0 ,0.3 , 23.1986, 0]; % x, y, z, pitch, yaw (meter & degree, roll is not included.)

%% Simulation Parameters
simStopTime = 10;
Ts = 0.01;
v_set = 1.5;

%% Waypoints
Waypoints = [2.3 -0.0300000000000002 0;
    4.01 -0.0200000000000005 0.01;
    5.02 0.44 0.01;
    4.94 1.5 0.01;
    5.04 1.94 0.01;
    4.91 2.49 0.01;
    5.01 3.03 0.01;
    4.94 3.57 0.01;
    4.04 4 0.01;
    2.88 3.78 0.01;
    2.313 4.64 0.01;
    3.428 5.814 0.01;
    5.178 5.922 0.01;
    6.59 5.96 0.01;
    7.02 6.9 0.01;
    6.43 7.85 0.01;
    5.56 7.85 0.01;
    4.778 8.015 0.01;
    4.103 7.839 0.01;
    2.53 7.73 0.01;
    1.94 7.39 0.01;
    0.17 7.62 0.01;
    -1.01 5.5 0.01;
    -0.57 3.97 0.01;
    -0.5 2.69 0.01;
    -1.03 1.52 0.01;
    -0.44 0.109999999999999 0.01;
    1.33 -0.04 0.01];
dx = Waypoints(2:end,1)-Waypoints(1:end-1,1);
dy = Waypoints(2:end,2)-Waypoints(1:end-1,2);
theta = [0;atan(dy./dx)];
Waypoints(:,3) = theta*180/pi;


directions = ones(length(Waypoints),1);
speedProfile = v_set*ones(500,1);
curvatures = zeros(500,1);