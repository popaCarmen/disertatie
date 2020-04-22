%http://crackeconcept.blogspot.com/2014/03/arduino-and-matlab-interfacing-via.html

b = Bluetooth('HC-05',1);
fopen(b);
disp('Bluetooth opened succesfully')
%for i=1:10
    fwrite(b,10)
    q=fscanf(b,'%i')
%     fwrite(b,20)
%     z=fscanf(b,'%d')
%end
fclose(b)
delete(b)
clear b
disp('Bluetooth closed succesfully')
