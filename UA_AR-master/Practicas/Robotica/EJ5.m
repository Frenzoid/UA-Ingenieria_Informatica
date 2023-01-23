% EJERCICIO PRACTICO 5%

% Datos %
L(1) = Link([0 0.317 0 -pi/2  0]);
L(2) = Link([0 0     0.45 0 0 -pi/2]);
L(3) = Link([0 0     0 pi/2 0 pi/2]);
L(4) = Link([0 0.48  0 -pi/2  0]);
L(5) = Link([0 0     0 pi/2   0]);
L(6) = Link([0 0.07  0 0      0]);

% Limites %
L(1).qlim=[deg2rad(-177) deg2rad(177)];
L(2).qlim=[deg2rad(-64) deg2rad(124)];
L(3).qlim=[deg2rad(-107) deg2rad(158)];
L(4).qlim=[deg2rad(-255) deg2rad(255)];
L(5).qlim=[deg2rad(-165) deg2rad(165)];
L(6).qlim=[deg2rad(-255) deg2rad(255)];

r = SerialLink(L,'name', 'PA10-6GDL');


q = [0 -pi/2 0 0 0 0];
disp("1");
disp(jacob0(r, q));
disp(det(jacob0(r, q)));
r.plot(q);

q = [0 0 -pi/2 0 0 0];
disp("2");
disp(jacob0(r, q));
disp(det(jacob0(r, q)));
r.plot(q);


q = [0 0 0 pi/2 0 0];
disp("3");
disp(jacob0(r, q));
disp(det(jacob0(r, q)));
r.plot(q);


q = [0 0 0 0 0 pi/2];
disp("4");
disp(q);
disp(jacob0(r, q));
disp(det(jacob0(r, q)));
r.plot(q);

