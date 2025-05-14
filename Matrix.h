struct matrix{
	std::vector<std::vector <long double>> array;

	int str;
	int clm;
};

struct colomn{
	std::vector<long double> data;

	int str;
};

static struct matrix new_matrix(int str, int clm){
	struct matrix A;

	A.str = str;
	A.clm = clm;

	(A.array).assign(str, std::vector<long double>(clm));

	return A;
}

static struct colomn new_colomn(int str){
	struct colomn b;

	b.str = str;
	b.data.resize(str);

	return b;
}

static void print_colomn_on_screen(struct colomn *b){
	int i;
	for(i = 0; i < (*b).str; i++){
		printf("%Lf\n", (*b).data[i]);
	}
	printf("\n");
}

static void print_matrix_on_screen(struct matrix* A){
	int i, j;
	for(i = 0; i < A->str; i++){
		for(j = 0; j < A->clm; j++){
			printf("%Lf ", A->array[i][j]);
		}
		printf("\n");
	}

}

static void print_colomn_to_file(struct colomn *b, char const *name){
	int i;

	FILE *file = fopen (name,"w");

	for(i = 0; i < (*b).str; i++){
		fprintf(file, "%Le\n", (*b).data[i]);
	}

	fclose(file);
}

static void print_matrix_to_file(struct matrix *A, char const *name){
	int i, j;

	FILE *file = fopen (name,"w");

	for(i = 0; i < (*A).str; i++){
		for(j = 0; j < (*A).clm; j++){
			fprintf(file, "%Lf ", (*A).array[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

static void print_colomn_WM(struct colomn *b, char const *name){
	int i;

	FILE *file = fopen (name,"w");

	for(i = 0; i < (*b).str - 1; i++){
		fprintf(file, "%2.15Lf\n ", (*b).data[i]);
	}
	fprintf(file, "%2.15Lf", b->data[(*b).str-1]);

	fclose(file);
}

static void print_matrix_WM(struct matrix *A, char const *name){
	int i, j;

	FILE *file = fopen (name,"w");

	for(i = 0; i < (*A).str; i++){
		for(j = 0; j < (*A).clm; j++){
			fprintf(file, "%2.15Lf ", (*A).array[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

static long double KroneckerDelta(int i, int j){
	if(i == j){
		return  (long double)1.0;
	}
	else{
		return  (long double)0.0;
    }
}
