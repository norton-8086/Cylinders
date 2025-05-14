/*READ "SPECIAL FUNCTIONS AND DEFINITE INTEGRALS", CIMRING, MOSCOW, "RADIO AND COMMUNICATION", 1988*/
/*READ ABOUT PRECISION IN THAT ARTICLE, TAKE n = 10 */
/*CHECKED IN WOLFRAM*/


const long double M_PI_L = 3.1415926535897932384626433832795028841971693993751; /* FROM WOLFRAM */

static long double ellipticK(long double k) /* Ёллиптический интеграл 1-го рода, метод ј√—*/
{
	int n = 10;
	long double k1 = sqrtl(1.0 - powl(k, 2.0));
	long double a, b, aprev, bprev;

	a = aprev = 1.0;
	b = bprev = k1;

	for(int i = 1; i <= n; i++){
		a = 0.5*(aprev + bprev);
		b = sqrtl(aprev * bprev);

		aprev = a;
		bprev = b;
	}

	return (M_PI_L/(2.0*a));
}

static long double ellipticE(long double k) /* Ёллиптический интеграл 2-го рода, метод ј√— */
{
	int n = 10;
	long double k1 = sqrtl(1.0 - powl(k, 2.0));
	long double a, b, c, aprev, bprev, sum, K;

	a = aprev = 1.0;
	b = bprev = k1;
	c = k;
	sum = powl(2.0, 0.0)*powl(c, 2.0);

	for(int i = 1; i <= n; i++){
		a = 0.5*(aprev + bprev);
		b = sqrtl(aprev * bprev);
		c = 0.5*(aprev - bprev);

		sum += powl(2.0, i)*powl(c, 2.0);

		aprev = a;
		bprev = b;
	}

	K = M_PI_L/(2.0*a);

	return (1.0 - 0.5*sum)*K;
}

//static double my_round(long double number, int num_of_symb_after_point){
//	long double multiplier = powl(10.0, (long double)num_of_symb_after_point);
//
//	return round(multiplier * (double)number)/multiplier;
//}

