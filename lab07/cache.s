# void accessWords(int array_size, int step_size, int rep_count, int option) {
#     for (int k = 0; k < rep_count; k++) { 
#         for (int index = 0; index < array_size; index += step_size) {
#             if (option == 0)
#                 array[index] = 0; // Option 0: One cache access - write
#             else
#                 array[index] = array[index] + 1; // Option 1: Two cache accesses - read AND write
#         }
#     }
# }

# int main() {
#     int array_size = 256;
#     int step_size = 2;
#     int rep_count = 1;
#     int option = 1;
#     accessWords(array_size, step_size, rep_count, option);
#     return 0;
# }

.data
array:	.word	2048 # max array size specified in BYTES (DO NOT CHANGE)

.text
main:	li	a0, 128	# array size in BYTES (should be a power of 2 < array size)
	li	a1, 1 # step size  (should be a power of 2 > 0)
	li	a2, 1 # rep count  (int > 0)
	li	a3, 0 # 0 = option 0, 1 = option 1
	jal	accessWords	
	li	a0, 10 # exit
	ecall

# Arguments:
#  a0 = array size in bytes
#  a1 = step size
#  a2 = number of times to repeat
#  a3 = option: 0 (write) / 1 (read and write)
accessWords:
	la	s0, array # ptr to array
	add	s1, s0, a0 # array size
	slli t1, a1, 2 # multiply stepsize by 4 because the size of an int is 4 bytes
wordLoop:
	beq	a3, zero,  optionZero
    # Option 1:
	lw	t0, 0(s0)
	addi t0, t0, 1
	sw t0, 0(s0)
	j wordCheck
optionZero:
	sw zero, 0(s0)
wordCheck:
	add	s0, s0, t1 # increment ptr
	blt	s0, s1, wordLoop # inner loop done?
	addi a2, a2, -1
	bgtz a2, accessWords # outer loop done?
	jr	ra