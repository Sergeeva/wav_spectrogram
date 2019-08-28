#include <math.h>

void bpf( int n, int p, float *re, float *im )
	 /*	int   n;       число точек - непременно 2**n                */
	 /*	int   p;       тип (1 прямое), (-1 обратное)                */
	 /* float re[];   массив действительной составляющей           */
	 /*	float im[];   массив мнимой составляющей                   */
{
	int           k, l, n1, n2;
	register int      i, j, ii, jj;
	float         a, b, c, co, r, s, si, t = - 3.14159265359;

	n1 = n / 2;
	l  = n1 / 2;
	n2 = n1 + 1;
	j = jj = 0;
 
	while ( (++j) - n1 <= 0 )
	{
		ii = jj + n1;

		r  = re[j];
		re[j] = re[ii];
		re[ii]= r;

		r  = im[j];
		im[j] = im[ii];
		im[ii]= r;

		k = l;
		while ( jj - k  >=   0 )
		{
			jj = jj - k;
			k  = k / 2;
		}
		if ( (jj += k) - (++j) <= 0 )
			continue;

		r  = re[j];
		re[j] = re[jj];
		re[jj] = r;

		r  = im[j];
		im[j] = im[jj];
		im[jj] = r;

		i  = j  + n2;
		ii = jj + n2;

		r  = re[i];
		re[i] = re[ii];
		re[ii]= r;

		r  = im[i];
		im[i] = im[ii];
		im[ii]= r;
	}
	i  = 1;

	if( p < 0)
	{
		t = -t;
		r = 1. / n;
		for(j = 0; j < n; j++)
		{
			re[j] = re[j] * r;  im[j] = im[j] * r;
		}
	}

	do
	{
		si  = 0.;
		co  = 1.;
		s   = sin(t);
		c   = cos(t);
		t   = 0.5 * t;
		ii  = i;
		i   = i + i;

		for(k = 0; k < ii; k++)
		{
			for(j = k; j < n; j = j + i)
			{
				jj = j + ii;
				a  = re[jj];
				b  = im[jj];
				r  = a * co - b * si;
				re[jj] = re[j] - r;
				re[j] = re[j] + r;
				r  = b * co + a * si;
				im[jj] = im[j] - r;
				im[j] = im[j] + r;
			}
			r  = c * co - s * si;
			si = c * si + s * co;  co = r;
		}
	}
	while(i - n < 0);
}
