% Synthetic Data  
%xy = rand(20,2);
xy = []
intensity = rand(20,1);
% Interpolate to grid
interpolant = scatteredInterpolant(xy(:,1),xy(:,2),intensity);
% Grid
[xx,yy] = meshgrid(linspace(0,1,10));  % replace, 0 1, 10 with range of your values
% Interpolate
intensity_interp = interpolant(xx,yy);
contourf(xx,yy,intensity_interp)