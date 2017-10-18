fid1 = fopen('Imb.dat');
np=0;
while(~feof(fid1))
  char = fgetl(fid1);
  np = np + 1;
end
fclose(fid1);

dt = zeros(np,1);
 
fid2 = fopen('Imb.dat');
for i=1:np
  dt(i) = str2num(fgetl(fid2));
end
fclose(fid2);

grid on;
hold on;
plot(dt,'-.')
title('Time Step Evolution')
xlabel('Step')
ylabel('Time Step Dt')
