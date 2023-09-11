% sim_cm_sat.m
% This file simulates a single coil magnetic circuit with core saturation.
%
% Copyright Alberto Sanchez 2021
%  ver 1.0 28/01/2021
%
% Modify by Alex Andrade 2022
%  ver 2.0 20/01/2022
%
%******************************************************************
% Model Description:
% 
% State Variables: Psi
% Parameters: wb r1 rp2 xl xm
%
%******************************************************************
% This Simulations is for a 120/240 V, 1.5 KVA, 60-Hz transformer
% with the following parameters:
%
% r1 = 0.62 Ohms   
% rp2 = 0.62 Ohms      
% xl1 = 0.056 Ohms    
% xlp2 = 0.056 Ohms
% xm = 315.92 Ohms
%
%******************************************************************
% This Simulations is for a 120/240 V, 1.5 KVA, 60-Hz transformer.
%
%*****************************************************************
% Any change to be performed at this point of the code
%*****************************************************************
%
% Voltaje devanado primario
%

V1 = sqrt(2)*120;       % Voltaje pico
V1f = pi/2;                 % Desfasamiento de voltaje V1. Altere este valor segun lo requerido 0 o pi/2

%
%*****************************************************************
% DO NOT MAKE ANY CHANGES BELOW THIS POINT
%*****************************************************************
%
cm_init;
%
%
% Simulacion
%
disp('');
disp('Espere unos instantes.....simulacion en progreso')
tic;
sim('cm_sat_model',1);
toc
disp('');
disp('Simulacion finalizada')
i1 = salida(:,1);
ip2 = salida(:,2);
fem1 = salida(:,3);
fem2 = salida(:,4);
psi1 = salida(:,5);
psi2 = salida(:,6);
Psimsat = salida(:,7);
v = salida(:,8);
%
% Resultados
%
figure;
title('Circuito Magnético con Saturacion - Magnitudes Eléctricas');
%subplot(2,1,1);
plot(T,v);
ylabel('volts');
hold on
plot(T,fem1);
ylabel('volts');
hold on
plot(T,fem2);
ylabel('volts');
xlabel('Tiempo [s]');
legend('Vs','Fem_1','Fem_2');
grid on;
% subplot(2,1,2);
% plot(T,vp2);
% ylabel("v'_{2} [A]");
% xlabel('Tiempo [s]');
% grid on;

figure;
title('Circuito Magnético con Saturacion - Magnitudes Eléctricas');
subplot(2,1,1);
plot(T,i1);
ylabel('i_{1} [A]');
grid on;
subplot(2,1,2);
plot(T,ip2);
ylabel("i'_{2} [A]");
xlabel('Tiempo [s]');
grid on;

figure;
title('Circuito Magnético con Saturacion - Concatenación de Flujo');
subplot(3,1,1);
plot(T,psi1);
ylabel('\Psi_1 [Wb/s]');
grid on;
subplot(3,1,2);
plot(T,psi2);
ylabel('\Psi_2 [Wb/s]');
hold on;
grid on;
subplot(3,1,3);
plot(T,Psimsat);
ylabel('\Psimsat_{m} [Wb/s]');
xlabel('Tiempo [s]');
grid on;

figure;
title('Circuito Magnético con Saturacion - Concatenación de Flujo');
plot(psisat,Dpsi);
xlabel('\Psi_{m}^{sat} [Wb/s]');
ylabel('\Delta \Psi [Wb/s]');
grid on;
