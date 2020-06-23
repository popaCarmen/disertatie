clc; clear all; close all; 

%distance1 = [1, 2, 3, 4, 5, 4, 3, 2, 1]; %7
%distance2 = [2, 3, 4, 5, 6, 5, 4, 3, 2]; %7
%posServoX = [0, 5, 10, 15, 20, 25, 30, 35, 40]; %7
%posServoY = [0, 5, 10, 15, 20, 25, 30, 35, 40]; %7
azimuth = zeros(1,180);
elevation = zeros(1,180);
x = zeros(180);
y = zeros(180);
z = zeros(180);
deg2rad = pi/180;
distances = rand(180)*10;

for ser=1:180
    posServoX(ser) = ser; 
    posServoY(ser) = ser;
end

for i=1:180 % servo y
    for j=1:180 % servo x
       azimuth(i) =  posServoX(i)*deg2rad;
       elevation(i) = posServoY(i)*deg2rad;
       x(i,j) = distances(i,j)*sin(elevation(i))*cos(azimuth(i));
       y(i,j) = distances(i)*sin(elevation(i))*sin(azimuth(i));
       z(i,j) = distances(i)*cos(elevation(i));
    end
end
% for i=1:9
%    azimuth2(i) =  posServoX(i)*deg2rad;
%    elevation(i) = 0.5*deg2rad;
%    x2(i) = distance2(i)*cos(azimuth2(i))
%    y2(i) = distance2(i)*sin(azimuth2(i))
%    z2(i) = 0.5;
% end

%zticks(0:0.1:0.5)
plot3(x,y,z,'.')
xlabel('x')
ylabel('y')
zlabel('z')
grid on
%[Z] = meshgrid(x,y)
%contour(x,y,Z)
%mesh(x,y)
%surf(X,Y,Z)