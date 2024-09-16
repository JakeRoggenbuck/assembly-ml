.intel_syntax noprefix

.file "regression.s"
.text
.section .rodata

.text
	.globl r_squared_error
	.globl r_mean_squared_error
	.globl r_gradient_descent
	.globl r_regression

# struct DataFrame {
#     double *y;
#     double *x;
#     size_t size;
# };

# struct LinearComponents {
#     double slope;
#     double b;
# };

r_squared_error:  											# double squared_error(struct DataFrame *dataf, double(f)(double)) {
															#     double error = 0.0;
	mov rax, 0			# rax = error, = 0
															#     for (int i = 0; i < dataf->size; i++) {
	mov r10, 0			# r10 = i, = 0
															#         double delta = (dataf->y[i] - f(dataf->x[i]));
	
															#         error += delta * delta;
															#     }
															# 
															#     return error;
															# }
ret

r_mean_squared_error:
															# double mean_squared_error(struct DataFrame *dataf, double(f)(double)) {
															#     return squared_error(dataf, f) / (double)(dataf->size);
															# }
ret

r_gradient_descent:
															# struct LinearComponents *gradient_descent(struct DataFrame *dataf, double slope,
															#                                           double b, double learning_rate) {
															#     struct LinearComponents *g = malloc(sizeof(struct LinearComponents));
															# 
															#     double slope_gradient = 0.0;
															#     double b_gradient = 0.0;
															# 
															#     for (int i = 0; i < dataf->size; i++) {
															#         double a = (dataf->y[i] - (slope * dataf->x[i] + b));
															# 
															#         slope_gradient += -(2.0 / dataf->size) * dataf->x[i] * a;
															#         b_gradient += -(2.0 / dataf->size) * a;
															#     }
															# 
															#     g->slope = slope - slope_gradient * learning_rate;
															#     g->b = b - b_gradient * learning_rate;
															# 
															#     return g;
															# }
ret

r_regression:
															# struct LinearComponents *regression(struct DataFrame *dataf, int epochs,
															#                                     double learning_rate, int verbose) {
															#     struct LinearComponents *l;
															# 
															#     double slope = 0.0;
															#     double b = 0.0;
															# 
															# 	for (int epoch = 0; epoch < epochs; epoch++) {
															# 		l = gradient_descent(dataf, slope, b, learning_rate);
															# 
															# 		slope = l->slope;
															# 		b = l->b;
															# 	}
															# 
															#     return l;
															# }
ret
