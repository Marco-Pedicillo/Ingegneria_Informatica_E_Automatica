typedef struct {
  int rows;
  int cols;
  float **rows_pt;
} Mat;


Mat* mat_alloc(int rows, int cols);
Mat* Mat_read(const char *filename);
void mat_free(Mat *m);
void mat_print(Mat *m);
