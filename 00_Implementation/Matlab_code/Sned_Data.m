if ~isempty(instrfind)
     fclose(instrfind);
      delete(instrfind);
end
a = serial('COM3','BaudRate',115200,'TimeOut',20,'Terminator', 'CR');
val=2;
fopen(a);
fprintf(a,'%i',val,'async');
a