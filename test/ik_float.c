#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

struct LegCfg { double coxa; double femur; double tibia; };

struct IkSolution { double coxa_deg; double femur_deg; double tibia_deg; };

struct ServoMap {
    double coxa_mount_deg;
    double femur_zero_deg;
    double tibia_zero_deg;
    bool coxa_invert;
    bool femur_invert;
    bool tibia_invert;
    double coxa_horn_deg;
    double femur_horn_deg;
    double tibia_horn_deg;
    double coxa_min_deg, coxa_max_deg;
    double femur_min_deg, femur_max_deg;
    double tibia_min_deg, tibia_max_deg;
};

struct ServoOut {
    double coxa_deg, femur_deg, tibia_deg;
    bool warning;
};

bool ik_to_servo(const struct IkSolution *geo,
                 const struct ServoMap *map,
                 struct ServoOut *out);

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

static void run_servo_case(double x, double y, double z,
                           const struct LegCfg *cfg,
                           const struct ServoMap *map)
{
    struct IkSolution geo = {0};
    struct ServoOut out = {0};

    if (!ik_leg_float(x, y, z, cfg, &geo)) {
        printf("x=%.0f y=%.0f z=%.0f -> geo=false\n", x, y, z);
        return;
    }
    ik_to_servo(&geo, map, &out);
    printf("x=%.0f y=%.0f z=%.0f -> servo: %.2f %.2f %.2f warning=%d\n",
           x, y, z, out.coxa_deg, out.femur_deg, out.tibia_deg, out.warning);
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

bool ik_to_servo(const struct IkSolution *geo,
                 const struct ServoMap *map,
                 struct ServoOut *out)
{
	/*判NULL*/
	if(!geo || !map || !out) { out->warning = true; return false; }
	/*获得解算后真实角度*/
	double coxa = geo->coxa_deg - map->coxa_mount_deg;
	double femur = geo->femur_deg - map->femur_zero_deg;
	double tibia = map->tibia_zero_deg - geo->tibia_deg;

	/*根据invert决定是否取反*/
	if(map->coxa_invert) coxa = -coxa;
	if(map->femur_invert) femur = -femur;
	if(map->tibia_invert) tibia = -tibia;

	/*加上微调值*/
	coxa += map->coxa_horn_deg;
	femur += map->femur_horn_deg;
	tibia += map->tibia_horn_deg;

	/*判断是否越界*/
	if (coxa > map->coxa_max_deg) { coxa = map->coxa_max_deg; out->warning = true; }
	else if (coxa < map->coxa_min_deg) { coxa = map->coxa_min_deg; out->warning = true; }
	if (femur > map->femur_max_deg) { femur = map->femur_max_deg; out->warning = true; }
	else if (femur < map->femur_min_deg) { femur = map->femur_min_deg; out->warning = true; }
	if (tibia > map->tibia_max_deg) { tibia = map->tibia_max_deg; out->warning = true; }
	else if (tibia < map->tibia_min_deg) { tibia = map->tibia_min_deg; out->warning = true; }

	/*返回最终结果*/
	out->coxa_deg = coxa;
	out->femur_deg = femur;
	out->tibia_deg = tibia;
	return true;
}

void gait_function(const struct LegCfg *cfg, const struct ServoMap *rm);
double edge_dist(double x1, double z1, double x2, double z2);
/* 对一条腿进行ik解算与servo解算并打印 */
int main(void)
{
	const struct LegCfg cfg = {45, 75, 120};
	const struct ServoMap rm = {
       	 .coxa_mount_deg = 90.0,
       	 .femur_zero_deg = 45.0,
       	 .tibia_zero_deg = 90.0,
       	 .coxa_invert = false,
       	 .femur_invert = true,
    	 .tibia_invert = true,
       	 .coxa_horn_deg = -1.0,
       	 .femur_horn_deg = -2.0,
       	 .tibia_horn_deg = 0.8,
       	 .coxa_min_deg = -90.0,  .coxa_max_deg = 90.0,
       	 .femur_min_deg = -60.0, .femur_max_deg = 90.0,
       	 .tibia_min_deg = -68.7, .tibia_max_deg = 90.0
   	 };

    	/* 期望 coxa=90.00  femur=44.82  tibia=76.18 */
    	run_case(0.0, 50.0, 160.0, &cfg);

    	/* 期望 coxa=45.00  femur=28.71  tibia=76.09 */
    	run_case(100.0, 80.0, 100.0, &cfg);

    	/* 期望 false（coxa 圆内） */
    	run_case(20.0, 50.0, 0.0, &cfg);

    	/* 期望 false（三角形不成立） */
    	run_case(0.0, 50.0, 300.0, &cfg);


	/* 三例计算实际角度 */
	run_servo_case(0.0, 50.0, 160.0, &cfg, &rm);
	run_servo_case(100.0, 80.0, 100.0, &cfg, &rm);
	run_servo_case(0.0, 0.0, 100.0, &cfg, &rm);

	/* 用gait解算x, y, z坐标计算结果 */
	gait_function(&cfg, &rm);

    	return 0;
}

void gait_function(const struct LegCfg *cfg, const struct ServoMap *rm)
{
    const double L = 40.0;      /* 步长 mm */
    const double H = 20.0;      /* 抬腿高度 mm */
    const int walk = 4;         /* 行走步数 */
    const int step_s = 12;      /* 总步数 */

    int step, s;

    for(step=0; step<step_s; step++) {
        double x, y;
	double z = 160.0;
        if(step<walk) {
            x = L * (step - 2) / 4;
	    y =50 - H * step * (4 - step) / 4;
        }
        else {
            s = step - 4;
            x = L * (4 - s) / 8;
	    y = 50;
        }
    printf("step%2d:\t", step);
    run_servo_case(x, y, z, cfg, rm);
    }
}

double edge_dist(double x1, double z1, double x2, double z2)
{
    double cross = x1 * z2 - x2 * z1;
    double len   = sqrt((x2-x1)*(x2-x1) + (z2-z1)*(z2-z1));
    return fabs(cross) / len;
}
