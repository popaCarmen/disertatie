%http://crackeconcept.blogspot.com/2014/03/arduino-and-matlab-interfacing-via.html

 b = Bluetooth('HC-05',1);
fopen(b);
set(b, 'TimeOut', 1);
disp('Bluetooth opened succesfully');

% try 
%     b = Bluetooth('HC-05',1);
%     fopen(b);
%     set(b, 'TimeOut', 1);
%     disp('Bluetooth opened succesfully');
%     
% catch e
%     %errordlg('Unable to start bluetooth communication');
%     disp('Bluetooth did not started succesufully');
%     fclose(b);
%     delete(b);
%     clear b;
%     disp('Bluetooth closed succesfully')
% end

i=1; 
fprintf(b, 'S'); %request new value from Arduino
pause(0.5);
received = fgetl(b) %read the requested data
distance = str2double(received)
% if(received <= 0)
%     fclose(b);
%     delete(b);
%     clear b;
%     disp('Bluetooth closed succesfully')
% 
% end
% if (received ~= 0 ) %different
%     distance(i) = received; 
%     i=+1;
% else
%     fprintf(b, 'P'); %request for a break
% end

%for i=1:10
%    fwrite(b,10)
%    q=fscanf(b,'%i')
%     fwrite(b,20)
%     z=fscanf(b,'%d')
%end

   
fclose(b);
    delete(b);
    clear b;
    disp('Bluetooth closed succesfully')

% if e== NULL
%     while 1
%         fprintf(b, 'S'); %request new value
%         delay(500); %half second delay
%         temp = fgetl(b); %read the requested data
% 
%         distance = temp; 
%     end


%end
