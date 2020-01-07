function dynamics()
syms al th al_d th_d al_d2 th_d2 I V tau1 tau2
syms marm mp Jarm_cm J0 Jp_cm Jp Larm larm lp g bma bp Kt Ke Rm Lm eta_g Kg

J1m = diag([0,Jarm_cm,Jarm_cm]);
J2m = diag([0,Jp_cm,Jp_cm]);
R2 = [cos(th),sin(th),0;-sin(th),cos(th),0;0,0,1]...
    *[0,0,1;0,1,0;-1,0,0];
omega1 = [0;0;al_d];
v1c = conj(cross(omega1,[larm;0;0]));
omega2 = R2*omega1 + [0;0;th_d];
v2 = R2*conj(cross(omega1,[Larm;0;0]));
v2c = v2 + conj(cross(omega2,[lp;0;0]));

T = 1/2*(v1c.'*marm*v1c + omega1.'*J1m*omega1...
    + v2c.'*mp*v2c + omega2.'*J2m*omega2);
U = g*mp*lp*(cos(th)-1);

q_d = [al_d;th_d];
M = hessian(T,q_d);
M = subs(M,[Jarm_cm,Jp_cm],[J0-marm*larm^2-mp*Larm^2,Jp-mp*lp^2]);
M = simplify(M);
M_d = simplify(diff(M,th)*th_d);

C = sym('a',2);
C(1,1) = 1/2*diff(M(1,1),al)*al_d + 1/2*diff(M(1,1),th)*th_d;
C(1,2) = 1/2*diff(M(1,1),th)*al_d...
    + 1/2*(2*diff(M(1,2),th)-diff(M(2,2),al))*th_d;
C(2,1) = 1/2*(2*diff(M(2,1),al)-diff(M(1,1),th))*al_d...
    + 1/2*diff(M(2,2),al)*th_d;
C(2,2) = 1/2*diff(M(2,2),al)*al_d + 1/2*diff(M(2,2),th)*th_d;
C = simplify(C);

test = M_d-2*C;
test = test + test.';

N = sym('a',[2,1]);
N(1) = bma*al_d + diff(U,al);
N(2) = bp*th_d + diff(U,th);
N = simplify(N);

q_d = [al_d;
    th_d;
    M\([tau1;tau2]-C*[al_d;th_d]-N)];
% open_system('Quanser_Furuta')
% matlabFunctionBlock('Quanser_Furuta/f_mecc',q_d,'Vars',...
%     {[al;th;al_d;th_d],[tau1;tau2],mp,J0,Jp,Larm,lp,g,bma,bp},...
%     'Outputs',{'qd'},'Optimize',false)

q = [al;th;al_d;th_d];
u = V;
q_d = subs(q_d,[tau1,tau2],[eta_g*Kg*Kt/Rm*(V-Kg*Ke*al_d),0]);
A = jacobian(q_d,q);
B = jacobian(q_d,u);

% matlabFunction(q_d,'File','f_red','Vars',{[al;th;al_d;th_d],V,...
%     mp,J0,Jp,Larm,lp,g,bma,bp,Kt,Ke,Rm,eta_g,Kg},'Optimize',false);
% matlabFunction(A,'File','A_red','Vars',{[al;th;al_d;th_d],V,...
%     mp,J0,Jp,Larm,lp,g,bma,bp,Kt,Ke,Rm,eta_g,Kg},'Optimize',false);
% matlabFunction(B,'File','B_red','Vars',{[al;th;al_d;th_d],V,...
%     mp,J0,Jp,Larm,lp,g,bma,bp,Kt,Ke,Rm,eta_g,Kg},'Optimize',false);

end