This file represents our calculations to validate the torque at joints 1 and 2 of the robot.
You must have a valid Motion Genesis license to be able to generate the results.
Visit http://www.motiongenesis.com for more information1

The maximum torque obtained is that of joint # 1 with a torque of approximately 1.944801 Newton * meters.
Motors must therefore have a stall torque greater than 2 Nm!


   (138) % %Cas 3: 45 degres
   (139) Input theta_a_n = 45 deg, theta_a_b= 45 deg
   (140) Solve(Eq, Frx_N,  Fry_N,  Frz_N, Frx_Ab, Fry_Ab, Frz_Ab, TJ1_x, TJ1_y, TJ1_z, TJ2_x, TJ2_y, TJ2_z)
-> (141) Frx_N = 0
-> (142) Fry_N = g*(masse_bras_horiz+masse_bras_vert+masse_charge+masse_moteur)
-> (143) Frz_N = 0
-> (144) Frx_Ab = 0
-> (145) Fry_Ab = g*(masse_bras_horiz+masse_charge)
-> (146) Frz_Ab = 0
-> (147) TJ1_x = 0
-> (148) TJ1_y = 0
-> (149) TJ1_z = 0.5*g*(2*long_bras_vert*(masse_bras_horiz+masse_charge)*sin(theta_a_n)+long_bras_vert*(masse_bras_vert+4*masse_moteur)*sin(theta_a_n)+long_bras_horiz*(masse_bras_horiz+4*masse_charge)*sin(theta_a_b+theta_a_n))

-> (150) TJ2_x = 0
-> (151) TJ2_y = 0
-> (152) TJ2_z = 0.5*g*long_bras_horiz*(masse_bras_horiz+4*masse_charge)*sin(theta_a_b+theta_a_n)

   (153) EvaluateToNumber(TJ1_x)
 Result = 0
   (153) EvaluateToNumber(TJ1_y)
 Result = 0
   (153) EvaluateToNumber(TJ1_z)
 Result = 1.944801
   (153) EvaluateToNumber(TJ2_x)
 Result = 0
   (153) EvaluateToNumber(TJ2_y)
 Result = 0
   (153) EvaluateToNumber(TJ2_z)
 Result = 0.806382
   (153)
