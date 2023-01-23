% EJERCICIO PRACTICO 3%

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

figure(1);
qh = [0 0 0 0 0 0];
qhQ = r.fkine(qh);
r.plot(qh);

figure(2);
qe = [0 0.5236 1.5708 0 1.0472 0];
qeQ = r.fkine(qe);
r.plot(qe);

figure(3);
qs = [0 0.7854 1.5708 0 -0.7854 0];
qsQ = r.fkine(qs);
r.plot(qs);

figure(4);
q1 = [0 0.7854 0.7854 0 1.5708 0];
q1Q = r.fkine(q1);
r.plot(q1);

figure(5);
q2 = [0.3491 1.5708 0.7854 -0.39270 1.0472 0];
q2Q = r.fkine(q2);
r.plot(q2);





