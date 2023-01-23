% EJERCICIO PRACTICO 8%

r = DynamicParams(loadPA10Params());

qs = [0,           deg2rad(45), deg2rad(90),                0,           deg2rad(-45),0];
q1 = [0,           deg2rad(45), deg2rad(45),                0,           deg2rad(90),0];
q2 = [deg2rad(20), deg2rad(90), deg2rad(45),deg2rad(-22.5), deg2rad(60), 0];

r.payload(2.5, [0, 0, 0.1]);
Res0 = r.gravload(qs);
Res1 = r.gravload(q1);
Res2 = r.gravload(q2);

Vqs_0 = r.itorque(qs,[1 0 0 0 0 0]);
Vq1_0 = r.itorque(q1,[1 0 0 0 0 0]);
Vq2_0 = r.itorque(q2,[1 0 0 0 0 0]);

r.payload(2.5,[0.5, 0, 0.1]);
Res0 = r.gravload(qs);
Res1 = r.gravload(q1);
Res2 = r.gravload(q2);

Vqs_1 = r.itorque(qs,[1 0 0 0 0 0]);
Vq1_1 = r.itorque(q1,[1 0 0 0 0 0]);
Vq2_1 = r.itorque(q2,[1 0 0 0 0 0]);