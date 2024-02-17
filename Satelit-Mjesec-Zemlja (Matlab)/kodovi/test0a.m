T = 13;

z0 = [0.82
         0
         0
         0];
         
n = T*100;
h = (T - t0) / n;


[~, z] = rk4(f, t0, t0 + h, z0, 1);
  
plot(0, 0, 'b', 1, 0, 'Color', [0.4 0.4 0.4], z0(1), z0(2), 'g', z(1,1:2), z(2,1:2), 'w-');
set(gca, 'Color', 'k');
title(['Orbita satelita (t = ', num2str(h), ')']);
xlabel('x');
ylabel('y');
axis([-1 1 -1 1]);

for k = 2:n-1
    z0 = z(:,2);
    [~, z] = rk4(f, t0 + (k-1)*h, t0 + k*h, z0, 1);
  
    hold on;
    plot(z(1,1:2), z(2,1:2), 'w-');
    title(['Orbita satelita (t = ', num2str(k*h), ')']);
    
    pause(0.001);
end

z0 = z(:,2);
[~, z] = rk4(f, t0 + (n-1)*h, t0 + n*h, z0, 1);

p = plot(z(1,1:2), z(2,1:2), 'w-', z(1,2), z(2,2), 'r');
title(['Orbita satelita (t = ', num2str(n*h), ')']);
legend('Zemlja', 'Mjesec', 'Po?etni položaj');
hold off;