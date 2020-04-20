clc; clear all; close all; 

yellow = 'D10';
green = 'D11';
red = 'D12';
blue = 'D13';
Ard_robot = arduino() %create Arduino object

while(1)
    for i = 1:3
          writeDigitalPin(Ard_robot, yellow, 0);
          pause(0.5);
          writeDigitalPin(Ard_robot, yellow, 1);
          pause(0.5);
    end
    writeDigitalPin(Ard_robot, yellow, 0);
    for i = 1:3
          writeDigitalPin(Ard_robot, green, 0);
          pause(0.5);
          writeDigitalPin(Ard_robot, green, 1);
          pause(0.5);
    end
    writeDigitalPin(Ard_robot, green, 0);

       for i = 1:3
          writeDigitalPin(Ard_robot, red, 0);
          pause(0.5);
          writeDigitalPin(Ard_robot, red, 1);
          pause(0.5);
       end
     writeDigitalPin(Ard_robot, red, 0);

       for i = 1:3
          writeDigitalPin(Ard_robot, blue, 0);
          pause(0.5);
          writeDigitalPin(Ard_robot, blue, 1);
          pause(0.5);
       end
    writeDigitalPin(Ard_robot, blue, 0);
end

clear Ard_robot