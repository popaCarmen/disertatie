function varargout = Matlab_guide(varargin)
% MATLAB_GUIDE MATLAB code for Matlab_guide.fig
%      MATLAB_GUIDE, by itself, creates a new MATLAB_GUIDE or raises the existing
%      singleton*.
%
%      H = MATLAB_GUIDE returns the handle to a new MATLAB_GUIDE or the handle to
%      the existing singleton*.
%
%      MATLAB_GUIDE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in MATLAB_GUIDE.M with the given input arguments.
%
%      MATLAB_GUIDE('Property','Value',...) creates a new MATLAB_GUIDE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Matlab_guide_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Matlab_guide_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Matlab_guide

% Last Modified by GUIDE v2.5 19-Jun-2020 22:50:57

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Matlab_guide_OpeningFcn, ...
                   'gui_OutputFcn',  @Matlab_guide_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

function init()
global dist_matrix;
global timer_Bluetooth;
global index;
timer_Bluetooth = timer;
timer_Bluetooth.Period = 0.1;
timer_Bluetooth.ExecutionMode = 'fixedRate';
timer_Bluetooth.TasksToExecute = Inf;


dist_matrix = zeros(180,140); %x - linii, y - coloane 
index = 1;
figure(1)
%hold on




% --- Executes just before Matlab_guide is made visible.
function Matlab_guide_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Matlab_guide (see VARARGIN)

% Choose default command line output for Matlab_guide
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Matlab_guide wait for user response (see UIRESUME)
% uiwait(handles.figure1);
init();


% --- Outputs from this function are returned to the command line.
function varargout = Matlab_guide_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in Bluetooth.
function Bluetooth_Callback(hObject, eventdata, handles)
% hObject    handle to Bluetooth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global bluetooth
global timer_Bluetooth
global first 
first = true
bluetooth = Bluetooth('HC-05',1);
try  
    fopen(bluetooth);
    set(bluetooth, 'TimeOut', 1);
    disp('Bluetooth opened succesfully');
    timer_Bluetooth.Timerfcn = @(~,~)Read_data(bluetooth);
    start(timer_Bluetooth)
catch e
    disp('Bluetooth detected an error and could not start');
end

function Read_data(Bluetooth_device)
global dist_matrix
global index
fprintf(Bluetooth_device, 'S'); %request new value from Arduino

received = fgetl(Bluetooth_device) %read the requested data

w = warning('query','last');
id = w.identifier;
warning('off',id)

if received ~= 0
   
        disp('Received message') 

        distance = extractBetween(received,'D','X'); 
        %distance = char(distance)
        distance = str2double(distance);    
        x_position = extractBetween(received,'X','Y')
        x_position = str2double(x_position)
        y_position = extractBetween(received,'Y','D') %cell array
        y_position = str2double(y_position)
        if x_position >= 180
          % 
        else
            for index=1:size(y_position)
                dist_matrix(x_position+1,(151-y_position(index))) = distance(index);
            end
            
        end
        dist_matrix

        
        %size(y_position)
end
% first_str = extractBetween(received,1,1);
% first_str = char(first_str);
% 
% if first_str == 'F'
%     if first == true
%         dist_matrix
%        first = false;
%    end
% end
%  if first_str == 'D'
%      remaining_str = extractBetween(received,2,'.')
%      remaining_str=char(remaining_str)
%      distance = str2double(remaining_str);
%      dist_matrix(index) = distance;
%      index = index+1;
%  %else
%      %save angle values here
%  end


% --- Executes on button press in Request.
function Request_Callback(hObject, eventdata, handles)
% hObject    handle to Request (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global bluetooth
fprintf(bluetooth, 'S'); %request new value from Arduino
pause(0.5);
received = fgetl(bluetooth) %read the requested data
%distance = str2double(received)
set(handles.edit1, 'String', received);


function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: delete(hObject) closes the figure
%ToDO: sa testez cum pot verifica daca e deschis canalul inainte de a-l
%inchide
global bluetooth
global timer_Bluetooth
try 
    fclose(bluetooth);
    delete(bluetooth);
    clear bluetooth;
    disp('Bluetooth closed succesfully');
catch e
    disp('Bluetooth could not close');
end
delete(hObject);
delete(timer_Bluetooth)


% --- Executes on button press in TwoD_map.
function TwoD_map_Callback(hObject, eventdata, handles)
% hObject    handle to TwoD_map (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
azimuth = zeros(1,180);
x = zeros(1,180);
y = zeros(1,180);
deg2rad = pi/180;
%DISTANCE WILL BE READ FROM ROBOT
distances = rand(1,180)*10;

for ser=1:180
    %SERVO-MOTOR POSITION WILL BE READ FROM ROBOT
    posServoX(ser) = ser; 
end

for j=1:180 % servo x
   azimuth(j) =  posServoX(j)*deg2rad;
   x(j) = distances(j)*cos(azimuth(j));
   y(j) = distances(j)*sin(azimuth(j));
end

figure(1)
plot(x,y,'.')
xlabel('x')
ylabel('y')
title("2D Map")
grid on

% --- Executes on button press in ThreeD_Map.
function ThreeD_Map_Callback(hObject, eventdata, handles)
% hObject    handle to ThreeD_Map (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
azimuth = zeros(1,180);
elevation = zeros(1,180);
x = zeros(180);
y = zeros(180);
z = zeros(180);
deg2rad = pi/180;

%DISTANCE WILL BE READ FROM ROBOT
distances = rand(180)*10;

for ser=1:180
    %SERVO-MOTOR POSITION WILL BE READ FROM ROBOT
    posServoX(ser) = ser; 
    posServoY(ser) = ser;
end

for i=1:180 % servo y 
    %servo y are doar 140 valori
    for j=1:180 % servo x
       azimuth(i) =  posServoX(i)*deg2rad;
       elevation(i) = posServoY(i)*deg2rad;
       x(i,j) = distances(i,j)*sin(elevation(i))*cos(azimuth(i));
       y(i,j) = distances(i)*sin(elevation(i))*sin(azimuth(i));
       z(i,j) = distances(i)*cos(elevation(i));
    end
end
figure(1)
plot3(x,y,z,'.')
xlabel('x')
ylabel('y')
zlabel('z')
title("3D Map")
grid on

function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
