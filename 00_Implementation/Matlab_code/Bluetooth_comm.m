%http://crackeconcept.blogspot.com/2014/03/arduino-and-matlab-interfacing-via.html

b = Bluetooth('HC-05',1);
fopen(b);
  
    fwrite(b,50)
    q=fscanf(b,'%d')
    fwrite(b,20)
    z=fscanf(b,'%d')

fclose(b)
delete(b)
clear b