
#include    "struct.h"
#include    "function.h"
#include    "vector.h"
#include    "math.h"



/*double turbulence(double x, double y, double size)
{
  double value = 0.0, initialSize = size;

  while(size >= 1)
  {
    value += smoothNoise(x / size, y / size) * size;
    size /= 2.0;
  }

  return(128.0 * value / initialSize);
}*/

double              my_rand(int x)
{
    x = (x<<13) ^ x;
    return ( 2.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0) / 2.0;
}

double              my_rand2(int x, int y, int z)
{
    int n = x + y * 57 + z * 7;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

//p->color = turbulence(p->i_point[0] * 10, p->i_point[1] * 10, p->i_point[2] * 10, 1 << 3);
double turbulence(double x, double y, double z, double size)
{
  double value = 0.0, initialSize = size;

  while(size >= 1)
  {
    value += my_rand2(x / size, y / size, z / size) * size;
    size /= 2.0;
  }

  return( 128.0 * value / initialSize);
}

void                normal_disturbance(void *intersect_param)
{
    t_iparam        *p;

    p = intersect_param;
    //double      u, v;
    /*
    //normal
    p->normal[0] = cos(p->i_point[0]) + p->normal[0];
    norm_vector(&p->normal);
    */


    /*
    //checkerboard
    p->color = p->color * (((int)round(p->i_point[0] / 10) & 1) ^ ((int)round(p->i_point[1] / 10) & 1) ? 1 : 0);
    */
        
    
    /*
    //Perlin noise
    p->color = turbulence(p->i_point[0] * 10, p->i_point[1] * 10, p->i_point[2] * 10, 1 << 3);
    */
}