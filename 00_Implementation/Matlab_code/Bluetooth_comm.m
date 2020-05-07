%http://crackeconcept.blogspot.com/2014/03/arduino-and-matlab-interfacing-via.html

try 
    b = Bluetooth('HC-05',1);
    fopen(b);
    set(b, 'TimeOut', 1);
    disp('Bluetooth opened succesfully');
catch e
    errordlg('Unable to start bluetooth communication');
    disp('Bluetooth did not started succesufully');
end



%for i=1:10
%    fwrite(b,10)
%    q=fscanf(b,'%i')
%     fwrite(b,20)
%     z=fscanf(b,'%d')
%end

if e== NULL
    while 1
        fprintf(b, 'S'); %request new value
        delay(500); %half second delay
        temp = fgetl(b); %read the requested data

        distance = temp; 
    end

    fclose(b)
    delete(b)
    clear b
    disp('Bluetooth closed succesfully')
end
