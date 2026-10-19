#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct LegCfg { double coxa; double femur; double tibia; };
struct IkSolution { double coxa_deg; double femur_deg; double tibia_deg; };
bool ik_leg_float(double x, double y, double z,
                  const struct LegCfg *cfg,
                  struct IkSolution *sol);
static void run_case(double x, double y, double z, const struct LegCfg *cfg)
{
	struct IkSolution sol = {0};
	bool ok = ik_leg_float(x, y, z, cfg, &sol);

	printf("x=%.0f y=%.0f z=%.0f -> ", x, y, z);
	if (ok)
    		printf("ok  coxa=%.2f  femur=%.2f  tibia=%.2f\n",
               sol.coxa_deg, sol.femur_deg, sol.tibia_deg);
    	else
        	printf("false\n");
}

bool ik_leg_float( double x, double y, double z,
		const struct LegCfg *cfg,
		struct IkSolution *sol )
{
	if(!cfg || !sol) return false;

	/*抄目标值
	double coxa = x;
	double femur = y;
	double tibia = z;
	*/
	/*计算coxa角度*/
	double coxa_angle = atan2(z, x) * 180.0 / M_PI;

	/*算femur & tibia的斜边长*/
	double coxa_feet_dist = sqrt(x*x + z*z);
	if(coxa_feet_dist < cfg->coxa) return false;
	double ik_feet_dist = coxa_feet_dist - cfg->coxa;
	double ik_feet_dist_sq = ik_feet_dist * ik_feet_dist;
	double ik_a1_sq = y * y;
	double ik_a_sq = ik_feet_dist_sq + ik_a1_sq;
	double ik_a = sqrt(ik_a_sq);
	if(ik_a > cfg->femur + cfg->tibia || ik_a < fabs(cfg->femur - cfg->tibia)) return false;

	/*取femur & tibia边长*/
	double femur_len = cfg->femur;
	double tibia_len = cfg->tibia;

	/*计算tibia角度*/
	double cos_tibia_num = femur_len * femur_len + tibia_len * tibia_len - ik_a_sq;
	double cos_tibia_den = 2 * femur_len * tibia_len;
	double cos_tibia = cos_tibia_num / cos_tibia_den;
	double tibia_angle = acos(cos_tibia) * 180.0 / M_PI;

	/*计算femur角度*/
	double angle_a1 = atan2(y, ik_feet_dist) * 180.0 / M_PI;
	double cos_a2_num = femur_len * femur_len + ik_a_sq -tibia_len * tibia_len;
	double cos_a2_den = 2 * femur_len * ik_a;
	double angle_a2 = acos(cos_a2_num / cos_a2_den) * 180.0 / M_PI;
	double femur_angle = angle_a2 - angle_a1;

	/*写入*/
	sol->coxa_deg = coxa_angle;
	sol->femur_deg = femur_angle;
	sol->tibia_deg = tibia_angle;

	return true;
}

int main(void)
{
	const struct LegCfg cfg = {45, 75, 120};

    	/* 期望 coxa=90.00  femur=44.82  tibia=76.18 */
    	run_case(0.0, 50.0, 160.0, &cfg);

    	/* 期望 coxa=45.00  femur=28.71  tibia=76.09 */
    	run_case(100.0, 80.0, 100.0, &cfg);

    	/* 期望 false（coxa 圆内） */
    	run_case(20.0, 50.0, 0.0, &cfg);

    	/* 期望 false（三角形不成立） */
    	run_case(0.0, 50.0, 300.0, &cfg);

    	return 0;
}
