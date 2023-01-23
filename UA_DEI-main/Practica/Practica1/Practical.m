% DEI Practical assignment 2018/19
% Objective: 3D HCI Gesture learning

%% Acquisition
load('scan3d-up-27Feb2014-094145.mat'); % Load dataset

%% Direct Segmentation
figure;imagesc(scan3d.img(:,:,:,1)); %Show images


% Colour direct
maskAuxColor = createMaskColor(scan3d.img(:,:,:,1),100,150,100,150,100,150);

% Depth direct
maskAux = createMaskDepth(scan3d.depth(:,:,1),800);

% Colour + Depth
maskAux = maskAuxColor & maskAux;

%% Temporal segmentation Saval-Calvo, et al. Background substraction


% Hand description

% Bounding box

% Ellipse...

%% Tracking using description 

% Particle filter
% Kalman


%% 