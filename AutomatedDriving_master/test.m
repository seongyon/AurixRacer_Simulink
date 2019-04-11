% function plottest(lane,curPose,Waypoints)
color = {'r','b','m','g','k','y'};
figure;
plot(-lane.LaneBoundaries(1).Coordinates(:,2),lane.LaneBoundaries(1).Coordinates(:,1),[color{1},'*-']);hold on;
plot(-lane.LaneBoundaries(2).Coordinates(:,2),lane.LaneBoundaries(2).Coordinates(:,1),[color{2},'*-']);hold on;
plot(-lane.LaneBoundaries(3).Coordinates(:,2),lane.LaneBoundaries(3).Coordinates(:,1),[color{3},'*-']);hold on;
plot(-lane.LaneBoundaries(4).Coordinates(:,2),lane.LaneBoundaries(4).Coordinates(:,1),[color{4},'*-']);hold on;

cc = zeros(length(Waypoints),2);
cc(:,1) = Waypoints(:,1) - curPose(1)';
cc(:,2) = Waypoints(:,2) - curPose(2)';
theta = curPose(3)*pi/180;
ll = ([cos(theta),-sin(theta);sin(theta),cos(theta)] * cc')';
disp(ll);
plot(-ll(:,2),ll(:,1),'o-');
scatter(0,0,'ko');
xlim([-2,2]);
ylim([-2,2]);
grid on;
hold off;

figure;
% yy = spline(lane.LaneBoundaries(1).Coordinates(:,1),lane.LaneBoundaries(1).Coordinates(:,2),1:0.1:1.5);
f = fit(lane.LaneBoundaries(1).Coordinates(:,1),lane.LaneBoundaries(1).Coordinates(:,2),'smoothingspline');
% yf = f(1:0.1:1.5);
plot(-lane.LaneBoundaries(1).Coordinates(:,2),lane.LaneBoundaries(1).Coordinates(:,1),'r*-');hold on;
% plot(-yy,1:0.1:1.5,'b*-');
plot(-f(0:0.1:1.5),0:0.1:1.5,'b*-');
% end

figure; plot(-f(0.5:0.05:0.9),0.5:0.05:0.9);