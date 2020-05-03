%http://crackeconcept.blogspot.com/2014/03/arduino-and-matlab-interfacing-via.html

b_Ard = Bluetooth('HC-05',1);
fopen(b_Ard);
disp('Bluetooth opened succesfully')
while(1)
    %fwrite(b,10)
%     disp('Base 10 integer')
%     a=fread(b_Ard) 
%     disp('Sequence of characters')
%     b=fscanf(b_Ard,'%c')
%     disp('Floating point number')
%     c=fscanf(b_Ard,'%e')
%     disp('Floating point number')
%     d=fscanf(b_Ard,'%f')
%     disp('Floating point number')
%     e=fscanf(b_Ard,'%g')
%     disp('Defaults to base 10 integers')
%     f=fscanf(b_Ard,'%i')
%     disp('Signed octal integer')
%     g=fscanf(b_Ard,'%o')
%     disp('A series of non-white-space characters')
%     h=fscanf(b_Ard,'%s')
%     disp('Signed decimal integer')
%     i=fscanf(b_Ard,'%u')
%     disp('Signed hexadecimal integer')
%     f=fscanf(b_Ard,'%x')
    Bluetooth_Read[i]=fgets(b_Ard)
%     fwrite(b,20)
%     z=fscanf(b,'%d')
    if(a == 0)
       break; 
    end
end
fclose(b_Ard)
delete(b_Ard)
clear b_Ard
disp('Bluetooth closed succesfully')
