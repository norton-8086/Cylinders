struct ring{
	long double R;     // Радиус кольца
	long double z;     // Координата кольца по оси Z
	long double Q;     // Заряд кольца
	long double fi;    // Потенциал кольца
	long double E_z;   // Напряжённость поля в кольце по оси Z
    long double E_z_conserv;
	long double E_r;   // Напряжённость поля в кольце в радиальном направлении
};

struct cylinder{
	int n;        	   // Количество колец в разбиении цилиндра
	long double R;     // Радиус цилиндра
	long double L;     // Длина цилиндра
	long double Q;     // Заряд цилиндра
	long double zleft; // Координата левого края цилиндра по оси Z
	long double fi;    // Потенциал цилиндра

	std::vector<struct ring> rings;

	long double W;     	// Энергия цилиндра
	long double dev_fi; // Отклонение потенциала от среднего
	long double dev_E;  // Отклонение по полю
	long double dev_E_conserv;
	long double Sum_E_r;// Cумма радиальных компонент поля

	long double Sum_Q_Except;

	struct colomn Q_Ohm;
};

struct pair_of_cyl{
	struct cylinder cyl1;
	struct cylinder cyl2;

	struct matrix arr_Fi;
	struct matrix arr_E_r;
	struct matrix arr_E_z;

	long double W;
	long double W_article;
    long double W_far;
	long double dev_fi;
	long double dev_E;
    long double dev_E_conserv;
	long double Sum_E_r;

	struct matrix arr_Fi_conserv;
	struct matrix arr_E_r_conserv;
	struct matrix arr_E_z_conserv;

	long double W_conserv;
	long double dev_fi_conserv;

	struct colomn der_W_colomn;
	struct colomn der_E_colomn;
	struct colomn der_E_conserv_colomn;
	struct colomn der_Fi_colomn;

	struct colomn der_W_prev_colomn;
	struct colomn der_E_prev_colomn;
	struct colomn der_E_conserv_prev_colomn;
	struct colomn der_Fi_prev_colomn;

	struct colomn der_W_v_colomn;
	struct colomn der_E_v_colomn;
	struct colomn der_E_conserv_v_colomn;
    struct colomn der_Fi_v_colomn;

	struct colomn L_W;
	struct colomn v_W;

	struct colomn L_E;
	struct colomn v_E;

	struct colomn L_E_conserv;
	struct colomn v_E_conserv;

	struct colomn L_Fi;
	struct colomn v_Fi;

	struct colomn Q_Ohm_prev;

	std::vector<bool> Fi_Ohm;
	std::vector<bool> Fi_Ohm_prev;

	long double lam_1;
	long double lam_2;

	long double lam_1_der;
	long double lam_2_der;

	long double La_Grange_v_1;
	long double La_Grange_v_2;

    long double La_Grange_W;
};

/* see Butler "Capacitance of a finite-length conducting cylindral tube" */
static long double Capacitance(struct cylinder *pcyl){
	long double a, h;
	a = (*pcyl).R;
	h = (*pcyl).L/2.0;

	if (a/h >= 1.0){
		return 4.0*powl(M_PI_L, 2.0)*(a/logl(16.0*a/h));
	}
	else{
		return -4.0*M_PI_L*(h/(1.0+logl(a/(4.0*h))));
	}
}

/* Расчёт с помощью формулы для ёмкости, q^2/2*C */
static long double Wformula(struct cylinder *pcyl1, struct cylinder *pcyl2){
	return 0.5*(powl((*pcyl1).Q, 2.0)/Capacitance(pcyl1)) + 0.5*(powl((*pcyl2).Q, 2.0)/Capacitance(pcyl2));
}

/* Коэффициент для эллиптического интеграла 1-го рода, Савин. j-е в i-том */
static long double k(struct ring *pring_i, struct ring *pring_j){
	return sqrtl(4.0*(*pring_i).R*(*pring_j).R/(powl((*pring_i).z - (*pring_j).z, 2.0) + powl((*pring_i).R + (*pring_j).R, 2.0)));
}

/* Коэффициент k`, Савин. j-е в i-том */
static long double kh(struct ring *pring_i, struct ring *pring_j){
	return sqrtl(1.0 - powl(k(pring_i, pring_j), 2.0));
}

/* j-е в i-том, Савин, диплом, формула 2.2, делю на 4*Pi (в другую сист) */
static long double coef_fi(struct ring *pring_i, struct ring *pring_j){
	return (ellipticK(k(pring_i, pring_j))/(2.0*powl(M_PI_L, 2.0)*sqrtl(powl( (*pring_i).z - (*pring_j).z, 2.0) + powl( (*pring_i).R + (*pring_j).R, 2.0))));
}

/* j-е в i-том по оси Z, Савин, диплом, формула 2.1 */
static long double coef_E_z(struct ring *pring_i, struct ring *pring_j){
	return powl(k(pring_i, pring_j), 3.0)*((*pring_i).z - (*pring_j).z)*(ellipticE(k(pring_i, pring_j)))/(4.0*M_PI_L*(*pring_j).R*sqrtl(powl((*pring_i).R, 3.0) * (*pring_j).R)*powl(kh(pring_i, pring_j), 2.0));
}

/* j-е в i-том по радиальному направлению, Савин, диплом, формула 2.1 */
static long double coef_E_r(struct ring *pring_i, struct ring *pring_j){
	return (k(pring_i, pring_j)/(2.0*M_PI_L*sqrtl((*pring_j).R * powl((*pring_i).R, 3.0)))) * (ellipticK(k(pring_i, pring_j)) - (ellipticE(k(pring_i, pring_j))/(powl(kh(pring_i, pring_j), 2.0)))*(1.0 - ((*pring_i).R + (*pring_j).R)*powl(k(pring_i, pring_j), 2.0)/(2.0*(*pring_j).R)));
}

/* Функция создания цилиндра с заданными параметрами */
static struct cylinder new_cylinder(int n, long double R , long double L, long double Q, long double zleft){
	int i;

	struct cylinder new_cyl;

	new_cyl.R = R;
	new_cyl.L = L;
	new_cyl.Q = Q;
	new_cyl.n = n;
	new_cyl.zleft = zleft;
	new_cyl.fi = (long double)0.0;
	new_cyl.W = (long double)0.0;
	new_cyl.dev_fi = (long double)0.0;
	new_cyl.dev_E = (long double)0.0;
	new_cyl.dev_E_conserv = (long double)0.0;
	new_cyl.Sum_E_r = (long double)0.0;

	(new_cyl.rings).resize(n);

    new_cyl.Q_Ohm = new_colomn(new_cyl.n);

	for(i = 0; i < new_cyl.n; i++){
		new_cyl.rings[i].R = R;
		new_cyl.rings[i].z = zleft + i*L/((long double)n-1.0);
		new_cyl.rings[i].Q = Q/(long double)n;   //при создании цилиндра распределение заряда на его поверхности равномерное
		new_cyl.rings[i].fi = 0.0;
		new_cyl.rings[i].E_r = 0.0;
		new_cyl.rings[i].E_z = 0.0;
        new_cyl.rings[i].E_z_conserv = 0.0;
	}

	return new_cyl;
}


/* функция, заполняющая матрицу коэффициентов для потенциала */
static void calc_coef_Fi(struct pair_of_cyl *pair){
	int i, j;
	int n1, n2;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(i = 0; i < n1; i++){
		for(j = 0; j < i; j++){
			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		pair->arr_Fi.array[i][i] = 0.0; //само в себе потенциал не создает

		for(j = i + 1; j < n1; j++){

			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < n1 + n2; j++){
			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl1.rings[i]), &(pair->cyl2.rings[j - n1]));
		}
	}

	for(i = n1; i < n1 + n2; i++){
		for(j = 0; j < n1; j++){
			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl2.rings[i - n1]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < i; j++){
			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}

		pair->arr_Fi.array[i][i] = 0.0;

		for(j = i+1; j < n1 + n2; j++){
			pair->arr_Fi.array[i][j] = coef_fi( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}
	}
}

static void calc_coef_E_r(struct pair_of_cyl *pair){
	int i, j;
	int n1, n2;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(i = 0; i < n1; i++){
		for(j = 0; j < i; j++){
			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		pair->arr_E_r.array[i][i] = 0.0;

		for(j = i + 1; j < n1; j++){

			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < n1 + n2; j++){
			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl1.rings[i]), &(pair->cyl2.rings[j - n1]));
		}
	}

	for(i = n1; i < n1 + n2; i++){
		for(j = 0; j < n1; j++){
			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl2.rings[i - n1]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < i; j++){
			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}

		pair->arr_E_r.array[i][i] = 0.0;

		for(j = i+1; j < n1 + n2; j++){
			pair->arr_E_r.array[i][j] = coef_E_r( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}

	}
}

static void calc_coef_E_z(struct pair_of_cyl *pair){
	int i, j;
	int n1, n2;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	for(i = 0; i < n1; i++){
		for(j = 0; j < i; j++){
			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		pair->arr_E_z.array[i][i] = 0.0;

		for(j = i + 1; j < n1; j++){

			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl1.rings[i]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < n1 + n2; j++){
			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl1.rings[i]), &(pair->cyl2.rings[j - n1]));
		}
	}

	for(i = n1; i < n1 + n2; i++){
		for(j = 0; j < n1; j++){
			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl2.rings[i - n1]), &(pair->cyl1.rings[j]));
		}

		for(j = n1; j < i; j++){
			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}

		pair->arr_E_z.array[i][i] = 0.0;

		for(j = i+1; j < n1 + n2; j++){
			pair->arr_E_z.array[i][j] = coef_E_z( &(pair->cyl2.rings[i - n1]), &(pair->cyl2.rings[j - n1]));
		}
	}
}

/* на вход ссылка на цил и новое значение координаты левого края */
static void shift_cylinder(struct pair_of_cyl *pair, struct cylinder *pcyl, long double new_zleft){
	int i;

	long double delta_zleft = new_zleft - (*pcyl).zleft; /* дельта между старым и новым  */
	(*pcyl).zleft += delta_zleft; // Изменение zleft самого цилиндра

	for(i = 0; i < (*pcyl).n; i++){
		(*pcyl).rings[i].z += delta_zleft; // Изменение для каждого кольца
	}

	std::thread fi_thread(calc_coef_Fi, pair);
	std::thread E_r_thread(calc_coef_E_r, pair);
	std::thread E_z_thread(calc_coef_E_z, pair);

	if(fi_thread.joinable()){
		fi_thread.join();
	}
	if(E_r_thread.joinable()){
		E_r_thread.join();
	}
	if(E_z_thread.joinable()){
		E_z_thread.join();
	}
}

static struct pair_of_cyl new_pair_of_cyl(int n1, int n2, long double R1, long double R2, long double L1, long double L2, long double Q1, long double Q2, long double zleft1, long double zleft2){
	struct pair_of_cyl new_pair;

	new_pair.cyl1 = new_cylinder(n1, R1, L1, Q1, zleft1);
	new_pair.cyl2 = new_cylinder(n2, R2, L2, Q2, zleft2);

	new_pair.arr_Fi = new_matrix(n1+n2, n1+n2);
	new_pair.arr_E_r = new_matrix(n1+n2, n1+n2);
	new_pair.arr_E_z = new_matrix(n1+n2, n1+n2);

	std::thread fi_thread(calc_coef_Fi, &new_pair);
	std::thread E_r_thread(calc_coef_E_r, &new_pair);
	std::thread E_z_thread(calc_coef_E_z, &new_pair);

	if(fi_thread.joinable()){
		fi_thread.join();
	}
	if(E_r_thread.joinable()){
		E_r_thread.join();
	}
	if(E_z_thread.joinable()){
		E_z_thread.join();
	}

	new_pair.der_W_colomn = new_colomn(n1 + n2);
	new_pair.der_W_prev_colomn = new_colomn(n1 + n2);
	new_pair.der_W_v_colomn = new_colomn(n1 + n2);

	new_pair.der_E_colomn = new_colomn(n1 + n2);
	new_pair.der_E_prev_colomn = new_colomn(n1 + n2);
	new_pair.der_E_v_colomn = new_colomn(n1 + n2);

	new_pair.der_E_conserv_colomn = new_colomn(n1 + n2);
	new_pair.der_E_conserv_prev_colomn = new_colomn(n1 + n2);
	new_pair.der_E_conserv_v_colomn = new_colomn(n1 + n2);

	new_pair.der_Fi_colomn = new_colomn(n1 + n2);
	new_pair.der_Fi_prev_colomn = new_colomn(n1 + n2);
	new_pair.der_Fi_v_colomn = new_colomn(n1 + n2);

	new_pair.L_W = new_colomn(n1 +n2);
	new_pair.v_W = new_colomn(n1 +n2);

	new_pair.L_E = new_colomn(n1 +n2);
	new_pair.v_E = new_colomn(n1 +n2);

	new_pair.L_E_conserv = new_colomn(n1 +n2);
	new_pair.v_E_conserv = new_colomn(n1 +n2);

	new_pair.L_Fi = new_colomn(n1 +n2);
	new_pair.v_Fi = new_colomn(n1 +n2);

	new_pair.Fi_Ohm.resize(n1 + n2);
	new_pair.Fi_Ohm_prev.resize(n1 + n2);

	new_pair.lam_1 = 0.001;
	new_pair.lam_2 = 0.001;
	new_pair.lam_1_der = 0.0;
	new_pair.lam_2_der = 0.0;
	new_pair.La_Grange_v_1 = 0.0;
	new_pair.La_Grange_v_2 = 0.0;

	return new_pair;
}

static long double Sum_Q_Except_First(struct cylinder *pcyl){
	int i, n;
	n = pcyl->n;
	long double Sum_Q = (long double)0.0;

	for(i = 1; i < n; i++){
		Sum_Q += pcyl->rings[i].Q;
	}

	return Sum_Q;
}

/* потенциал i-го кольца в цилиндре  3 указателя: на цилиндр, из которого кольцо, на 1 и на 2 цилиндры */
static long double fi_ring(int i, struct cylinder *pcyl_of_ring, struct pair_of_cyl *pair){
	int j, n1, n2, index;
	/* index - индекс кольца в матрице coef_FI */
	long double fi = 0;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	if(pcyl_of_ring == &(pair->cyl1)){
		index = i;
	}
	else{
		index = i + pair->cyl1.n;
	}

	for(j = 0; j < n1; j++){
		fi += pair->cyl1.rings[j].Q * pair->arr_Fi.array[index][j]; /* j-е в i-том создает такой потенциал */
	}
	for(j = 0; j < n2; j++){
		fi += pair->cyl2.rings[j].Q * pair->arr_Fi.array[index][j + n1]; /* Если j-е кольцо принадлежит второму цилиндру, необходимо к его индексу в цилиндре прибавить число колец первого цилиндра, чтобы получить индекс кольца в матрице коэффициентов arr_FI */
	}

	return fi;
}

/* поле по z в i-м кольце в цилиндре  3 указателя: на цилиндр, из которого кольцо, на 1 и на 2 цилиндры */
static long double E_z_ring(int i, struct cylinder *pcyl_of_ring, struct pair_of_cyl *pair){
	int j, n1, n2, index;
	/* index - индекс кольца в матрице coef_FI */
	long double E_z = 0;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	if(pcyl_of_ring == &(pair->cyl1)){
		index = i;
	}
	else{
		index = i + pair->cyl1.n;
	}

	for(j = 0; j < n1; j++){
		E_z += pair->cyl1.rings[j].Q * pair->arr_E_z.array[index][j]; /* j-е в i-том создает такой потенциал */
	}
	for(j = 0; j < n2; j++){
		E_z += pair->cyl2.rings[j].Q * pair->arr_E_z.array[index][j + n1]; /* Если j-е кольцо принадлежит второму цилиндру, необходимо к его индексу в цилиндре прибавить число колец первого цилиндра, чтобы получить индекс кольца в матрице коэффициентов arr_FI */
	}

	return E_z;
}

static long double E_z_conserv_ring(int i, struct cylinder *pcyl_of_ring, struct pair_of_cyl *pair){
	int j, n1, n2, index;
	long double E_z_conserv = 0.0;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	if(pcyl_of_ring == &(pair->cyl1)){
		index = i;
	}
	else{
		index = i + pair->cyl1.n;
	}

	for(j = 1; j < n1; j++){
		E_z_conserv += pair->cyl1.rings[j].Q * (pair->arr_E_z.array[index][j] - pair->arr_E_z.array[index][0]); /* j-е в i-том создает такой потенциал */
	}
	for(j = 1; j < n2; j++){
		E_z_conserv += pair->cyl2.rings[j].Q * (pair->arr_E_z.array[index][j + n1] - pair->arr_E_z.array[index][n1]); /* Если j-е кольцо принадлежит второму цилиндру, необходимо к его индексу в цилиндре прибавить число колец первого цилиндра, чтобы получить индекс кольца в матрице коэффициентов arr_FI */
	}

	E_z_conserv += (pair->cyl1.Q * pair->arr_E_z.array[index][0] + pair->cyl2.Q * pair->arr_E_z.array[index][n1]);

    return E_z_conserv;
}


/* поле по радиусу в i-м кольце в цилиндре  3 указателя: на цилиндр, из которого кольцо, на 1 и на 2 цилиндры */
static long double E_r_ring(int i, struct cylinder *pcyl_of_ring, struct pair_of_cyl *pair){
	int j, n1, n2, index;
	/* index - индекс кольца в матрице coef_FI */
	long double E_r = 0;

	n1 = pair->cyl1.n;
	n2 = pair->cyl2.n;

	if(pcyl_of_ring == &(pair->cyl1)){
		index = i;
	}
	else{
		index = i + pair->cyl1.n;
	}

	for(j = 0; j < n1; j++){
		E_r += pair->cyl1.rings[j].Q * pair->arr_E_r.array[index][j]; /* j-е в i-том создает такой потенциал */
	}
	for(j = 0; j < n2; j++){
		E_r += pair->cyl2.rings[j].Q * pair->arr_E_r.array[index][j + n1]; /* Если j-е кольцо принадлежит второму цилиндру, необходимо к его индексу в цилиндре прибавить число колец первого цилиндра, чтобы получить индекс кольца в матрице коэффициентов arr_FI */
	}

	return E_r;
}

/* Функция, пересчитывающая потенциалы ВСЕХ колец и цилиндров */
static void calc_fi_rings_cyl(struct cylinder *pcyl, struct pair_of_cyl *pair){
	int i, n;
	n = pcyl -> n;
	long double fi = (long double)(0.0);

	for(i = 0; i < n; i++){
		fi += pcyl->rings[i].fi = fi_ring(i, pcyl, pair);
	}
	pcyl->fi = fi/(long double)(n);
}

static void calc_fi_rings_pair(struct pair_of_cyl *pair){
	std::thread first_cyl(calc_fi_rings_cyl, &pair->cyl1, pair);
	std::thread second_cyl(calc_fi_rings_cyl, &pair->cyl2, pair);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}
}

static void calc_E_r_rings_cyl(struct cylinder *pcyl, struct pair_of_cyl *pair){
	int i, n;
	n = pcyl->n;

	for(i = 0; i < n; i++){
		pcyl->rings[i].E_r = E_r_ring(i, pcyl, pair);
	}
}

static void calc_E_r_rings_pair(struct pair_of_cyl *pair){
	std::thread first_cyl(calc_E_r_rings_cyl, &(pair->cyl1), pair);
	std::thread second_cyl(calc_E_r_rings_cyl, &(pair->cyl2), pair);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}
}

static void calc_E_z_rings_cyl(struct cylinder *pcyl, struct pair_of_cyl *pair){
	int i, n;
	n = pcyl->n;

	for(i = 0; i < n; i++){
		pcyl->rings[i].E_z = E_z_ring(i, pcyl, pair);
	}
}

static void calc_E_z_rings_pair(struct pair_of_cyl *pair){
	std::thread first_cyl(calc_E_z_rings_cyl, &pair->cyl1, pair);
	std::thread second_cyl(calc_E_z_rings_cyl, &pair->cyl2, pair);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}
}

static void calc_E_z_conserv_rings_cyl(struct cylinder *pcyl, struct pair_of_cyl *pair){
	int i, n;
	n = pcyl->n;

	for(i = 0; i < n; i++){
		pcyl->rings[i].E_z_conserv = E_z_conserv_ring(i, pcyl, pair);
	}
}

static void calc_E_z_conserv_rings_pair(struct pair_of_cyl *pair){
	std::thread first_cyl(calc_E_z_conserv_rings_cyl, &pair->cyl1, pair);
	std::thread second_cyl(calc_E_z_conserv_rings_cyl, &pair->cyl2, pair);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}
}

/* Функция, вычисляющая энергию системы через заряды и потенциалы колец по формуле Q*Fi/2 */
static void Wrings_cyl(struct cylinder *pcyl){
	int i, n;
	n = pcyl->n;
    long double W = (long double)0.0;

	for(i = 0; i < n; i++){
		W += pcyl->rings[i].fi * pcyl->rings[i].Q;
	}

	pcyl->W = W/(long double)2.0;
}

static void Wrings(struct pair_of_cyl *pair){
	std::thread first_cyl(Wrings_cyl, &pair->cyl1);
	std::thread second_cyl(Wrings_cyl, &pair->cyl2);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}

	pair->W = pair->cyl1.W + pair->cyl2.W;
}

//-------------------ОТКЛОНЕНИЯ-------------------------------------------------
/* Отклонение потенциала от среднего, деленное на число колец */
static void dev_fi_cyl(struct cylinder *pcyl){
	int i, n;
	long double dev_fi = (long double)(0.0);
	long double fi = pcyl->fi;

	n = pcyl->n;
	for (i = 0; i < n; i++){
		dev_fi += powl((pcyl->rings[i].fi - fi), 2.0);
	}

	pcyl->dev_fi = dev_fi;
}

static void dev_fi(struct pair_of_cyl *pair){
	std::thread first_cyl(dev_fi_cyl, &pair->cyl1);
	std::thread second_cyl(dev_fi_cyl, &pair->cyl2);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}

	pair->dev_fi = pair->cyl1.dev_fi + pair->cyl2.dev_fi;
}

/* Сумма квадратов поля по Z, делим на число колец */
static void dev_E_cyl(struct cylinder *pcyl){
	int i, n;
	long double dev_E = (long double)(0.0);
	n = pcyl->n;

	for(i = 0; i < n; i++){
		dev_E += powl(pcyl->rings[i].E_z, 2.0);
	}

	pcyl->dev_E = dev_E;
}

static void dev_E(struct pair_of_cyl *pair){
	std::thread first_cyl(dev_E_cyl, &pair->cyl1);
	std::thread second_cyl(dev_E_cyl, &pair->cyl2);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}

	pair->dev_E = pair->cyl1.dev_E + pair->cyl2.dev_E;
}

static void dev_E_conserv_cyl(struct cylinder *pcyl){
	int i, n;
	long double dev_E_conserv = (long double)(0.0);
	n = pcyl->n;

	for(i = 0; i < n; i++){
		dev_E_conserv += powl(pcyl->rings[i].E_z_conserv, 2.0);
	}

	pcyl->dev_E_conserv = dev_E_conserv;
}

static void dev_E_conserv(struct pair_of_cyl *pair){
	std::thread first_cyl(dev_E_conserv_cyl, &pair->cyl1);
	std::thread second_cyl(dev_E_conserv_cyl, &pair->cyl2);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}

	pair->dev_E_conserv = pair->cyl1.dev_E_conserv + pair->cyl2.dev_E_conserv;
}

/* Сумма квадратов радиальных составляющих полей колец */
static void Sum_E_r_cyl(struct cylinder *pcyl){
	int i, n;
	n = pcyl->n;
	long double Sum_E_r = (long double)0.0;

	for(i = 0; i < n; i++){
		Sum_E_r += powl(pcyl->rings[i].E_r, 2.0);
	}

	pcyl->Sum_E_r = Sum_E_r;
}

static void Sum_E_r(struct pair_of_cyl *pair){
	std::thread first_cyl(Sum_E_r_cyl, &pair->cyl1);
	std::thread second_cyl(Sum_E_r_cyl, &pair->cyl2);

	if(first_cyl.joinable()){
		first_cyl.join();
	}
	if(second_cyl.joinable()){
		second_cyl.join();
	}

	pair->Sum_E_r = pair->cyl1.Sum_E_r + pair->cyl2.Sum_E_r;
}

static void La_Grange_W_func(struct pair_of_cyl *pair){
	int n1 = pair->cyl1.n;
	int n2 = pair->cyl2.n;

	long double Sum_Q_1 = (long double)0.0;
	long double Sum_Q_2 = (long double)0.0;

	for(int i = 0; i < n1; i++){
		Sum_Q_1 += pair->cyl1.rings[i].Q;
	}
	for(int i = n1; i < n1 + n2; i++){
		Sum_Q_2 += pair->cyl2.rings[i - n2].Q;
	}

	Wrings(pair);

	pair->La_Grange_W = pair->W + pair->lam_1 *(pair->cyl1.Q - Sum_Q_1) + pair->lam_2 *(pair->cyl2.Q - Sum_Q_2);
}

//------------------------------------------------------------------------------
//-------------------ФУНКЦИИ УЧИТЫВАЮЩИЕ ЗАКОН СОХРАНЕНИЯ-----------------------
//------------------------------------------------------------------------------

static void update(struct pair_of_cyl *pair){
	std::thread fi_thread(calc_fi_rings_pair, pair);
	std::thread E_r_thread(calc_E_r_rings_pair, pair);
	std::thread E_z_thread(calc_E_z_rings_pair, pair);

	if(fi_thread.joinable()){
		fi_thread.join();
	}
	if(E_r_thread.joinable()){
		E_r_thread.join();
	}
	if(E_z_thread.joinable()){
		E_z_thread.join();
	}

	std::thread W_thread(Wrings, pair);
	std::thread dev_fi_thread(dev_fi, pair);
	std::thread E_thread(dev_E, pair);
	std::thread E_conserv_thread(dev_E_conserv, pair);
	std::thread S_thread(Sum_E_r, pair);
	std::thread La_Grange_W_thread(La_Grange_W_func, pair);

	if(W_thread.joinable()){
		W_thread.join();
	}
	if(dev_fi_thread.joinable()){
		dev_fi_thread.join();
	}
	if(E_thread.joinable()){
		E_thread.join();
	}
	if(E_conserv_thread.joinable()){
		E_conserv_thread.join();
	}
	if(S_thread.joinable()){
		S_thread.join();
	}
	if(La_Grange_W_thread.joinable()){
		La_Grange_W_thread.join();
	}

	pair->cyl1.Sum_Q_Except = Sum_Q_Except_First(&pair->cyl1);
	pair->cyl2.Sum_Q_Except = Sum_Q_Except_First(&pair->cyl2);

}

static void print_inf_about_cyl(struct pair_of_cyl *pair){
	printf("W_from_art: %Lf W: %Lf dev_fi: %Lf div_by_N: %Lf dev_E: %Lf div_by_N: %Lf dev_E/Sum_E_r: %Lf\n", Wformula(&(pair->cyl1), &(pair->cyl2)), pair->W, pair->dev_fi, pair->dev_fi/(long double)(pair->cyl1.n + pair->cyl2.n), pair->dev_E, pair->dev_E/(long double)(pair->cyl1.n + pair->cyl2.n), pair->dev_E/pair->Sum_E_r);
}

//-------------------МИНИМУМЫ-МАКСИМУМЫ-(ДЛЯ-ГРАФИКОВ)-----------------------------------
static long double max_Q_cyl(struct cylinder *pcyl){
	long double max_Q;
	max_Q = (*pcyl).rings[0].Q;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].Q > max_Q ){
			max_Q = (*pcyl).rings[i].Q;
		}
	}

	return max_Q;
}

static long double min_Q_cyl(struct cylinder *pcyl){
	long double min_Q;
	min_Q = (*pcyl).rings[0].Q;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].Q < min_Q ){
			min_Q = (*pcyl).rings[i].Q;
		}
	}

	return min_Q;
}

static long double max_fi_cyl(struct cylinder *pcyl){
	long double max_fi;
	max_fi = (*pcyl).rings[0].fi;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].fi > max_fi ){
			max_fi = (*pcyl).rings[i].fi;
		}
	}

	return max_fi;
}

static long double min_fi_cyl(struct cylinder *pcyl){
	long double min_fi;
	min_fi = (*pcyl).rings[0].fi;

	for (int i = 0; i < (*pcyl).n; i++){
		if( (*pcyl).rings[i].fi < min_fi ){
			min_fi = (*pcyl).rings[i].fi;
		}
	}

	return min_fi;
}




//long double W_conserv(struct pair_of_cyl *pair){
//	long double W_cons = (long double)0.0;
//
//}
