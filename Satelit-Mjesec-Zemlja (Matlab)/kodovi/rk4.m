function [t, y] = rk4(f, t0, T, y0, n)
    h = (T-t0) / n;
    
    t = zeros(1, n+1);
    y = zeros(length(y0), n+1);
    
    t(1) = t0;
    y(:,1) = y0;
    
    for i = 1:n
        t(i+1) = t0 + i*h;
        
        k1 = f(t(i), y(:,i));
        k2 = f(t(i) + h/2, y(:,i) + (h/2)*k1);
        k3 = f(t(i) + h/2, y(:,i) + (h/2)*k2);
        k4 = f(t(i+1), y(:,i) + h*k3);
        
        y(:,i+1) = y(:,i) + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
    end
end