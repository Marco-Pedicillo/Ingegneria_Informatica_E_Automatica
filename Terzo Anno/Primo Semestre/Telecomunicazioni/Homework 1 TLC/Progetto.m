close all
clear
clc

% Il file importato deve trovarsi nella stessa cartella del file matlab
% eseguito
addpath('..\');
load('FilteredData_Subject_10_task_BL.mat');

%% PUNTO 1
% seleziono i campioni richiesti del segnale e ne stampo il grafico
t = 55000:56500; %il tempo secondo me va da questi due parametri e non da 0:1500


% Perchè non t?
x = ECG(55000:56500,1);
num_campioni = length(x);


% disegno il segnale
%pongo il titolo alla figura
figure('Name', "Segnale del soggetto 10 task Baseline");



%subplot(2, 1, 1);
plot(t, x);
% rinomino assi e grafico
title("Segnale");
xlabel("Tempo");            % credo siano le unità giuste,  
ylabel("Ampiezza");        % quelle che ha usato la prof

% tengo il grafico aperto per disegnare il valore medio
hold on;

%% PUNTO 2
% valor medio e disegno sul grafico in sovraimpressione
valore_medio_x = mean(x);
yline(valore_medio_x, '-.r', 'Valore Medio', 'LineWidth', 2);

hold on;

%% PUNTO 3
% energia e varianza
energia_x = sum(abs(x).^2);
%disp(x);
varianza_x= var(x);
annotation('textbox', [0.630, 0.825, 0.275, 0.1], 'BackgroundColor', [1 0.3 0.3], 'String', "Energia = " + energia_x + newline +"Varianza = " + varianza_x) 
%valori scelti prima della grandezza del box erano [0.6, 0.8, 0.35, 0.1]


%% PUNTO 4
numzeri = num_campioni*0.1;
vettBin = ones(num_campioni, 1);
flag = 1;

for c = 1:numzeri
    while flag
        r = randi(num_campioni);
        if vettBin(r) == 1
            flag = 0;
            vettBin(r) = 0;
        end
    end
    flag = 1;
end

y = x .* vettBin;
figure('Name', "Segnale Degradato del soggetto 10 task Baseline");
%subplot(2, 1, 2);
plot(t, y);
title("Segnale Degradato");
xlabel("Tempo");           
ylabel("Ampiezza");        

hold on;

valore_medio_y = mean(y);
yline(valore_medio_y, '-.r', 'Valore Medio', 'LineWidth', 2);

energia_y = sum(abs(y).^2);
annotation('textbox', [0.630, 0.875, 0.275, 0.05], 'BackgroundColor', [1 0.3 0.3], 'String', "Energia = " + energia_y);

%% PUNTO 5

addpath('..\');
load('FilteredData_Subject_3_task_CW.mat');

z = ECG(55000:56500,1);
num_campioni_z = length(z);

figure('Name', "Segnale del soggetto 3 task CW");
plot(t, z);

[c, tz] = xcorr(y, z);          % riguardare per il tempo da usare nella plot
plot(tz, c);    

%% PUNTO 6
rho_mat = corrcoef(y, z);       % ottengo la matrice con tutti i coefficienti di correlazione
rho = rho_mat(1, 2);            % prendiamo il coefficiente di correlazione incrociato (poteva essere anche la posizione 2, 1 
                                % in quanto il coefficiente tra y e z e il coefficiante tra z e y sono uguali)
annotation('textbox', [0.430, 0.865, 0.475, 0.06], 'BackgroundColor', [1 0.3 0.3], 'String', "Coefficiente di Correlazione = " + rho);
title("Segnale");
xlabel("Tempo");           
ylabel("Ampiezza");

%% PUNTO 7
pks = findpeaks(x); 
pks_len = length(pks);
pks_count = 0;
for i = 1 : pks_len
    if pks(i) > 0.8
        pks_count = pks_count + 1;
    end
end