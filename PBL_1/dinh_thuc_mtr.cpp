#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

double determinant(double A[MAX_SIZE][MAX_SIZE], int n, int level) {
    double det = 0;
    double submatrix[MAX_SIZE][MAX_SIZE];


    if (n == 1) {
        return A[0][0];
    } else if (n == 2) {
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    } else {
        for (int k = 0; k < n; k++) {
            for (int i = 1; i < n; i++) {
                int j;
                for (j = 0; j < n; j++) {
                    if (j < k) {
                        submatrix[i - 1][j] = A[i][j];
                    } else if (j > k) {
                        submatrix[i - 1][j - 1] = A[i][j];
                    }
                }
            }

            double sign = (k % 2 == 0) ? 1 : -1;
            double sub_det = determinant(submatrix, n - 1, level + 1);
            det += A[0][k] * sign * sub_det;
            
            // In ra quá trình tính định thức
            if (level == 0) {
                printf("Buoc %d: %.2lf * (%.2f) * det(submatrix)\n", k+1, A[0][k], sign);
                for (int i = 1; i < n; i++) {
                    for (int j = 0; j < n - 1; j++) {
                        printf("%6.2f ", submatrix[i - 1][j]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
    }
    return det;
}


void printMatrix(double A[][MAX_SIZE],int n) {
    int i,j;
	printf("Ma tran can tinh:\n");
    for ( i = 0; i < n; i++) {
        for ( j = 0; j < n; j++) {
            printf("%6.2lf ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
int n,i,j;
double A[MAX_SIZE][MAX_SIZE];
char input_file_name[100];
char output_file_name[100];
printf("TINH DINH THUC MA TRAN BANG PHUONG PHAP LAPLACE\n\n");
// Nhập tên tệp tin đầu vào và kiểm tra tính hợp lệ
printf("Nhap ten file dau vao: ");
fgets(input_file_name, sizeof(input_file_name), stdin);
input_file_name[strcspn(input_file_name, "\n")] = '\0';  // Xóa ký tự newline

FILE* input_file = fopen(input_file_name, "r");
while (input_file == NULL) {
    printf("Loi:File khong ton tai. Nhap lai ten file: ");
    fgets(input_file_name, sizeof(input_file_name), stdin);
    input_file_name[strcspn(input_file_name, "\n")] = '\0';  // Xóa ký tự newline
    input_file = fopen(input_file_name, "r");
}

// Đọc kích thước ma trận và các phần tử từ tệp tin đầu vào
fscanf(input_file, "%zu", &n);
if (n==0 || n <= 0 || n > MAX_SIZE) {
    printf("Loi:Ma tran sai dinh dang.\n");
    fclose(input_file);
    return 1;
}

for ( i = 0; i < n; i++) {
    for ( j = 0; j < n; j++) {
    	
        fscanf(input_file, "%lf", &A[i][j]);
    }
}
fclose(input_file);
printf("%d",n);

printMatrix(A, n);

printf("\n");
// Tính định thức của ma trận
double det = determinant(A,n,0);

// Nhập tên tệp tin đầu ra và ghi kết quả
printf("Nhap ten file dau ra: ");
fgets(output_file_name, sizeof(output_file_name), stdin);
output_file_name[strcspn(output_file_name, "\n")] = '\0';  // Xóa ký tự newline

FILE* output_file = fopen(output_file_name, "w");
if (output_file == NULL) {
    printf("Error:File khong ton tai.\n");
    return 1;
}

fprintf(output_file, "%.4lf\n", det);
fclose(output_file);


// In kết quả ra màn hình
printf("Dinh thuc ma tran can tinh = %.4lf\n", det);
printf("Ket qua duoc luu vao file %s\n", output_file_name);

return 0;
}