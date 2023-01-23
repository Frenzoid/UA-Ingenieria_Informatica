% EJERCICIO PRACTICO 9%


% Datos %
L(1) = Link([0 0.317 0 -pi/2  0]);
L(2) = Link([0 0     0.45 0 0 -pi/2]);
L(3) = Link([0 0     0 pi/2 0 pi/2]);
L(4) = Link([0 0.48  0 -pi/2  0]);
L(5) = Link([0 0     0 pi/2   0]);
L(6) = Link([0 0.07  0 0      0]);

% Limites %
L(1).qlim=[deg2rad(-177) deg2rad(177)];
L(2).qlim=[deg2rad(-64)  deg2rad(124)];
L(3).qlim=[deg2rad(-107) deg2rad(158)];
L(4).qlim=[deg2rad(-255) deg2rad(255)];
L(5).qlim=[deg2rad(-165) deg2rad(165)];
L(6).qlim=[deg2rad(-255) deg2rad(255)];

r = SerialLink(L,'name', 'PA10-6GDL');

qh = [0 0 0 0 0 0];
qhQ = r.fkine(qh);

qe = [0 0.5236 1.5708 0 1.0472 0];
qeQ = r.fkine(qe);

qs = [0 0.7854 1.5708 0 -0.7854 0];
qsQ = r.fkine(qs);

q1 = [0 0.7854 0.7854 0 1.5708 0];
q1Q = r.fkine(q1);

q2 = [0.3491 1.5708 0.7854 -0.39270 1.0472 0];
q2Q = r.fkine(q2);

% Pedazo plots. %
TR1 = jtraj(qh, q1, 50);
r.plot(TR1);

TR2 = jtraj(qh, q2, 50);
r.plot(TR2);

TR3 = jtraj(qh, qs, 50);
r.plot(TR3);


% [q , qd, qdd] = jtraj(qh, q2, 50); %
% [q , qd, qdd] = jtraj(qh, qs, 50); %
[q , qd, qdd] = jtraj(qh, qs, 50);

plot(qd);