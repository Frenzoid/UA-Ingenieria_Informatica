% EJERCICIO PRACTICO 7%

r = DynamicParams(loadPA10Params());
qs = [0,           deg2rad(45), deg2rad(90),                0,           deg2rad(-45),0];
q1 = [0,           deg2rad(45), deg2rad(45),                0,           deg2rad(90),0];
q2 = [deg2rad(20), deg2rad(90), deg2rad(45),deg2rad(-22.5), deg2rad(60), 0];

r.gravity = [0 0 1.62];

G0 = r.gravload(qs);
G1 = r.gravload(q1);
G2 = r.gravload(q2);

M0_0 = r.itorque(qs,[1 0 0 0 0 0]);
M0_1 = r.itorque(qs,[1 1 0 0 0 0]);
M0_2 = r.itorque(qs,[1 1 1 0 0 0]);
 
M1_0 = r.itorque(q1,[1 0 0 0 0 0]);
M1_1 = r.itorque(q1,[1 1 0 0 0 0]);
M1_2 = r.itorque(q1,[1 1 1 0 0 0]);

C0_1 = r.coriolis(qs, [0 pi 0 0 0 0]);
C0_2 = r.coriolis(qs, [pi pi 0 0 0 0]);

C1_1 = r.coriolis(q1, [0 pi 0 0 0 0]);
C1_2 = r.coriolis(q1, [pi pi 0 0 0 0]);
