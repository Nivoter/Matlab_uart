 instrreset

igotit = serial('COM4')
set(igotit,'BaudRate',115200);
igotit.InputBufferSize = 4096;
set(igotit,'ByteOrder','littleEndian');
fopen(igotit);
tline = [];
count = 1;
array = [];
tline= fread(igotit,[2000,1],'uint16');

array;
fclose(igotit);
delete(igotit);
clear igotit

