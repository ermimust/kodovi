function y = chi0(x)    if -1 <= x && x <= 1        y = (abs(x) - 1)^2 * (2*abs(x) + 1);    else        y = 0;    end
end