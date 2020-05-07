%% Setup Bluetooth connection
%https://forum.arduino.cc/index.php?topic=575443.0
instrhwinfo('Bluetooth','TexMatITA')
bt = Bluetooth('TexMatITA', 1)
fopen(bt)
set(bt, 'TimeOut', .5);

figure(1);
v=0;
xlabel('Time');
ylabel('PPG');
 
g = animatedline;
g.Color = 'red';  %EKG
ax = gca;
s=0;
x_axis_sec = datenum(seconds(8));
t_num = 0;

double ppg_red;
double ppg_ir;
double ppg_hr;
double ppg_hr_v;
double ppg_spo2;
double ppg_spo2_v;
double ecg_val;
double acc_x;
double acc_y;
double acc_z;

del = {'R', 'I', 'H', 'V', 'S', 'W','E','X','Y','Z'};  %delimiters to split the incoming string
char temp;   %variable to store the incoming string
char split_temp[];    %variable to store split string
double num_temp[];  %variable to store split string converted to numbers

stop = false;
startTime = datetime('now');
t_start_num = datenum(startTime);  % Convert to num for faster calculations

fprintf(bt,'S');  % Request first value

while ~stop;
     try  
      temp = fgetl(bt);    % Read value
      fprintf(bt,'S');   % Request new value until processing the current one
      split_temp = strsplit(temp, del);   % Split incoming string
      num_temp = str2double(convertCharsToStrings(split_temp));  % Convert to numbers
      ppg_red = num_temp(2);
      ppg_ir = num_temp(3);
      ppg_hr = num_temp(4);
      ppg_hr_v = num_temp(5);
      ppg_spo2 = num_temp(6);
      ppg_spo2_v = num_temp(7);
      ecg_val = num_temp(8);
      acc_x = num_temp(9);
      acc_y = num_temp(10);
      acc_z = num_temp(11);

     % Get current times
     t_num = datenum(datetime('now')) - t_start_num;

    % Add points to animation - in this case only for PPG
    addpoints(g, t_num, ppg_ir);   % PPG infrared LED

       % Update axes
    ax.XLim = [t_num - x_axis_sec, t_num];
%      datetick('x','keeplimits');
     drawnow
  catch
  end
end