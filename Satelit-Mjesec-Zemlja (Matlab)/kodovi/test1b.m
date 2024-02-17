T = 30;

z0 = [0.37
         0
         0
         0];
         
n = T*100;


[t, z] = ode45(f, [t0 T], z0);

figure(1);
plot(0, 0, 'b', 1, 0, 'Color', [0.4 0.4 0.4], z0(1), z0(2), 'g', z(length(z),1), z(length(z),2), 'r', z(:,1), z(:,2), 'w-');
set(gca, 'Color', 'k');
title('Orbita satelita (ode45)');
legend('Zemlja', 'Mjesec', 'Po?etni položaj', 'Kona?ni položaj');
xlabel('x');
ylabel('y');

[tt, zz] = rk4(f, t0, T, z0, n);

figure(2);
plot(0, 0, 'b', 1, 0, 'Color', [0.4 0.4 0.4], z0(1), z0(2), 'g', zz(1,n+1), zz(2,n+1), 'r', zz(1,:), zz(2,:), 'w-');
set(gca, 'Color', 'k');
title('Orbita satelita (rk4)');
legend('Zemlja', 'Mjesec', 'Po?etni položaj', 'Kona?ni položaj');
xlabel('x');
ylabel('y');