% create serial object
device = serialport("COM12",115200);

device.UserData.bufCap = 50000;
device.UserData.buf = zeros(device.UserData.bufCap, 3, "double");
device.UserData.time = zeros(device.UserData.bufCap, 1, "double");
device.UserData.i = 0;

% timer for plotting every 1s
t = timer;
t.ExecutionMode = "fixedRate";
t.Period = 0.05;

% setup figure
fig = uifigure('CloseRequestFcn', @(src,event) onClose(src,device,t));

outergrid = uigridlayout(fig,[1 2]);
outergrid.ColumnWidth = {'7x','2x'};
outergrid.RowHeight = {'1x'};

% set up plots
leftgrid = uigridlayout(outergrid,[3 1]);
leftgrid.Layout.Row = 1;
leftgrid.Layout.Column = 1;
leftgrid.RowHeight = {'1x','1x','1x'};

ax1 = uiaxes(leftgrid);
h1 = plot(ax1,nan,nan);
xlabel(ax1,"Time (s)"); ylabel(ax1,"Pressure (Pa)");
grid(ax1,"on");

ax2 = uiaxes(leftgrid);
h2 = plot(ax2,nan,nan);
xlabel(ax2,"Time (s)"); ylabel(ax2,"Valve 1 Duty Cycle (%)");
grid(ax2,"on");

ax3 = uiaxes(leftgrid);
h3 = plot(ax3,nan,nan);
xlabel(ax3,"Time (s)"); ylabel(ax3,"Valve 2 Duty Cycle (%)");
grid(ax3,"on");

t.TimerFcn = @(~,~) plotCallback(device,h1,h2,h3);

% Disable hover datatips/interactive listeners
disableDefaultInteractivity(ax1);
disableDefaultInteractivity(ax2);
disableDefaultInteractivity(ax3);
ax1.Toolbar.Visible = 'off';
ax2.Toolbar.Visible = 'off';
ax3.Toolbar.Visible = 'off';

% set up input parameters
rightgrid = uigridlayout(outergrid,[11 1]);
rightgrid.RowHeight = {'fit','fit','fit','fit','fit','fit','fit','1x','fit','fit','fit'};
p_targ_lb = uilabel(rightgrid,'Text',"Target Pressure");
p_targ_ef = uieditfield(rightgrid,"numeric");

v_1_gains_lb = uilabel(rightgrid,'Text',"Valve 1 PID gains");
PID1 = uigridlayout(rightgrid,[3 2]);
PID1.Padding = 0;
PID1.ColumnWidth = {'fit','1x'};
P1_lb = uilabel(PID1,'Text',"P");
P1_ef = uieditfield(PID1,"numeric");
I1_lb = uilabel(PID1,'Text',"I");
I1_ef = uieditfield(PID1,"numeric");
D1_lb = uilabel(PID1,"Text","D");
D1_ef = uieditfield(PID1,"numeric");

v_2_gains_lb = uilabel(rightgrid,'Text',"Valve 2 PID gains");
PID2 = uigridlayout(rightgrid,[3 2]);
PID2.Padding = 0;
PID2.ColumnWidth = {'fit','1x'};
P2_lb = uilabel(PID2,'Text',"P");
P2_ef = uieditfield(PID2,"numeric");
I2_lb = uilabel(PID2,'Text',"I");
I2_ef = uieditfield(PID2,"numeric");
D2_lb = uilabel(PID2,"Text","D");
D2_ef = uieditfield(PID2,"numeric");

input = {p_targ_ef,P1_ef,I1_ef,D1_ef,P2_ef,I2_ef,D2_ef};

submit = uibutton(rightgrid,"Text","Send");
submit.ButtonPushedFcn = @(src,event) onSend(device,input);

% save data
save_lb = uilabel(rightgrid,"Text","Save Data");
save_lb.Layout.Row = 9;
save_ef = uieditfield(rightgrid,"Placeholder","File Name");
save_but = uibutton(rightgrid,"Text","Save");

save_but.UserData.i = 1;
save_but.ButtonPushedFcn = @(src,event) onSave(src,device,save_ef.Value);

% callback when bytes available
device.UserData.t0 = tic;
flush(device,"input")
configureCallback(device,"byte",16,@readCallback);

% start plotting
start(t);


%% -------- Callback functions --------

% Read values from serial
function readCallback(src,~)
    ud = src.UserData;
    ud.i = ud.i + 1;  % Increment index for the next data point

    % Read exactly one packet worth of raw bytes
    vals = read(src, 4, "single");
    
    if isequal(vals, [0 0 0 0])
        return
    end

    % Time since start
    ud.time(ud.i) = toc(ud.t0);

    % Append to buffer
    ud.buf(ud.i,:) = vals(2:4)';

    if ud.i >= ud.bufCap
        ud.i = 0;  % Wrap around if buffer is full
    end

    src.UserData = ud;
end

% Plot data on figure
function plotCallback(src,h1,h2,h3)
    
    ud = src.UserData;

    if ud.i == 0
        return
    end

    span = 10;

    if max(ud.time)<=span
        start = 1;
    else
        a = ud.time-(ud.time(ud.i)-span);
        a = a(a<0);
        [~,start] = max(a);
    end

    time = ud.time(start:ud.i)-min(ud.time(1:ud.i));

    set(h1, "XData", time, "YData", ud.buf(start:ud.i,1))
    set(h1.Parent, "XLim",[ud.time(ud.i)-span,ud.time(ud.i)])
    set(h2, "XData", time, "YData", ud.buf(start:ud.i,2)*100)
    set(h2.Parent, "XLim",[ud.time(ud.i)-span,ud.time(ud.i)])
    set(h3, "XData", time, "YData", ud.buf(start:ud.i,3)*100)
    set(h3.Parent, "XLim",[ud.time(ud.i)-span,ud.time(ud.i)])

    drawnow limitrate nocallbacks
end

% Send parameters on button press
function onSend(device,input)
    parameters = cellfun(@(in) in.Value, input);
    write(device,parameters,"single")
end

% Save data
function onSave(src,device,name)
    if isempty(name)
        return
    end
    last_save_i = src.UserData.i;
    data = device.UserData.buf;
    time = device.UserData.time;
    i = device.UserData.i;
    S.data = data(last_save_i:i,:);
    S.time = time(last_save_i:i,:);
    save("Test Data\"+name,"S")

    src.UserData.i = device.UserData.i;
end

% Close comunication and stop plotting
function onClose(src,device,timer)
    % stop timer and data collection
    stop(timer)
    pause(0.1)
    configureCallback(device,"off")
    pause(0.1)

    % save data
    data = device.UserData.buf;
    time = device.UserData.time;
    i = device.UserData.i;
    S.data = data(1:i,:);
    S.time = time(1:i,:);
    save("Test Data\auto_saved_data","S")
    
    pause(0.1)
    % delete timer and device
    delete(timer)
    delete(device)

    % close plot
    delete(src)
end
