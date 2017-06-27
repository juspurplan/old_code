clear all;
clc;

% this is in dB
SNR_axis = [0,2,4,6,8,10,12,14];

AWGN_channel_BER = [.216, .162, .062, .028, .006, .004, 0, 0];
EQ_len_1_BER = [.184, .114, .086, .06, .026, .018, .004, .002];
EQ_len_6_BER = [.212, .16, .116, .038, .022, .008, .002, 0];

figure(1);
semilogy(SNR_axis, AWGN_channel_BER);
hold on;
semilogy(SNR_axis, EQ_len_1_BER);
ylabel('BER (log)');
xlabel('SNR (dB)');
legend('AWGN Channel', 'Equalizer L=1');

figure(2);
semilogy(SNR_axis, AWGN_channel_BER);
hold on;
semilogy(SNR_axis, EQ_len_6_BER);
ylabel('BER (log)');
xlabel('SNR (dB)');
legend('AWGN Channel', 'Equalizer L=6');