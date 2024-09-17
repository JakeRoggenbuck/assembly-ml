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
#     double *y;		8 bytes, 0
#     double *x;		8 bytes, 8
#     size_t size;		8 bytes, 16
# };

# struct LinearComponents {
#     double slope;		8 bytes, 0
#     double b;			8 bytes, 8
# };

r_squared_error:  															# double squared_error(struct DataFrame *dataf, double(f)(double)) {
	sub rsp, 32						# rsp -= 32

	mov [rsp], r12					# save r12
	mov [rsp+8], r13				# save r13
	mov [rsp+16], r14				# save r14
	mov [rsp+24], r15				# save r15

	mov r12, rdi					# save dataf to r12
	mov r13, rsi					# save f to r13
																			#     double error = 0.0;
	mov r14, 0						# r14 = error, = 0
																			#     for (int i = 0; i < dataf->size; i++) {
	mov r15, 0						# r15 = i, = 0
																			#         double delta = (dataf->y[i] - f(dataf->x[i]));
	mov [r12 + 8 + 8 * r10], rdi	# get dataf->x[i]
	call r13						# call f on dataf->x[i]

	mov [r12 + 8 * r10], r11		# get dataf->y[i]
	sub r11, rax					# subtract y value with f's output (in rax)
	mov rax, r11					# move r11 over to rax
																			#         error += delta * delta;

	mul rax							# multipy delta (rax) by delta (rax)
	add r14, rax					# add output to error

																			#     }
																			#     return error;
																			# }
	mov r12, [rsp]					# load r12
	mov r13, [rsp+8] 				# load r13
	mov r14, [rsp+16] 				# load r14
	mov r15, [rsp+24] 				# load r15

	add rsp, 32						# rsp += 32
ret									# return rax with error value

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
