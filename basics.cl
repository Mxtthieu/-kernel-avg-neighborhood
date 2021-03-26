__kernel void exercise0_1(
	__global float* average_size, 
	__global float* value, 
	__global float* result) {
	int id = get_global_id(0);
	int N = get_global_size(0);
	float sum = 0.f;
	for(int i = id - average_size[id]; i <= id + average_size[id]; i++){
		sum += value[(i%N + N)%N];
	}
	result[id] = sum / (1 + 2 * average_size[id]);	

}